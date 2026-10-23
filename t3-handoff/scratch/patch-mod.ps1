# Patch local@taskbar-ai-quota-plus for the Grok real-usage display + stacking fix.
# Applies exact literal replacements to the mod source; fails loudly if any anchor
# is missing or ambiguous. 2026-10-16.
$ErrorActionPreference = 'Stop'
$path = 'C:\ProgramData\Windhawk\ModsSource\local@taskbar-ai-quota-plus.wh.cpp'
$bytes = [System.IO.File]::ReadAllBytes($path)
$hasBom = $bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF
$text = [System.IO.File]::ReadAllText($path)
$ok = $true
$patched = 0

function Norm([string]$s) {
    return $s.Replace("`r`n", "`n").Replace("`n", "`r`n")
}

function Apply([string]$old, [string]$new) {
    $o = Norm $old
    $n = Norm $new
    $idx = $script:text.IndexOf($o, [System.StringComparison]::Ordinal)
    if ($idx -lt 0) {
        Write-Host ("NOT FOUND: " + $o.Substring(0, [Math]::Min(70, $o.Length)).Replace("`r`n", " / "))
        $script:ok = $false
        return
    }
    if ($script:text.IndexOf($o, $idx + 1, [System.StringComparison]::Ordinal) -ge 0) {
        Write-Host ("NOT UNIQUE: " + $o.Substring(0, [Math]::Min(70, $o.Length)).Replace("`r`n", " / "))
        $script:ok = $false
        return
    }
    $script:text = $script:text.Remove($idx, $o.Length).Insert($idx, $n)
    $script:patched++
    Write-Host ("OK: " + $o.Substring(0, [Math]::Min(50, $o.Length)).Replace("`r`n", " / "))
}

# --- 1: AccountData field -----------------------------------------------------
Apply @'
    // Grok free plan: the billing endpoint publishes a weekly period but no usage
    // percentage; the weekly bar renders as no-data with the real reset date.
    bool grokFreeNoUsage = false;
'@ @'
    // Grok: the billing endpoints publish no usage percentage on plans with no
    // published cap; the weekly bar renders as no-data (or the real credits
    // amount) with the real reset date.
    bool grokFreeNoUsage = false;
    // Grok credits used in the reported billing period when the account publishes
    // no cap; -1 when the account publishes a percentage (or nothing at all).
    double grokUsedCredits = -1;
'@

# --- 2: ParseGrokBilling comment ----------------------------------------------
Apply @'
// The CLI proxy reports the included-credits window as proto3 JSON. It omits a
// zero-valued creditUsagePercent, so a recognized current period with no percent
// field reads as 0% used, the same way grok.com renders the omitted scalar. Free
// plans never publish a percentage at all (verified against the live endpoint:
// only currentPeriod, no creditUsagePercent), so an absent percent with a live
// period reports no data with the real reset date instead of a permanent fake 0%.
'@ @'
// The CLI proxy reports billing as proto3 JSON in two shapes: the credits view
// (format=credits) carries the included-credits period, and the plain view carries
// the monthly cycle with used credits and the published cap. A zero-valued
// creditUsagePercent is omitted as a scalar, so a percent only counts when the
// field is present. Free plans publish no percentage anywhere (verified against
// the live endpoints 2026-10-16): a published cap becomes a real percentage, an
// uncapped account keeps the real credits amount with the real period, and a
// period with no usage fields reports no data with the real reset date - never a
// fake 0%.
'@

# --- 3: ParseGrokBilling body ---------------------------------------------------
Apply @'
        double percent = GetNum(cfg, L"creditUsagePercent", -1);
        if (!std::isfinite(percent) || percent < 0) {
            if (!resetMs) {
                *error = L"unexpected response format (" + DescribeJsonBody(body) + L")";
                return false;
            }
            // Free tier: a live period with no published percentage is still usable
            // data; the window and reset date render, the percentage does not.
            d->grokFreeNoUsage = true;
            d->winWeek.resetUnixMs = resetMs;
            d->winWeek.windowDurationMs = periodMs;
            return true;
        }
        d->winWeek.pct = std::min(percent, 100.0);
        d->winWeek.resetUnixMs = resetMs;
        d->winWeek.windowDurationMs = periodMs;
        return true;
'@ @'
        // The plain billing payload reports the monthly cycle: credits used, the
        // published cap (a zero cap means none published), and the period covered.
        double usedCredits = GetNum(GetObj(cfg, L"used"), L"val", -1);
        double monthlyLimit = GetNum(GetObj(cfg, L"monthlyLimit"), L"val", -1);
        ULONGLONG periodStartMs = ParseIso8601Ms(GetStr(cfg, L"billingPeriodStart"));
        if (periodStartMs && resetMs && resetMs > periodStartMs) {
            periodMs = resetMs - periodStartMs;
        }

        double percent = GetNum(cfg, L"creditUsagePercent", -1);
        if (std::isfinite(percent) && percent >= 0) {
            d->winWeek.pct = std::min(percent, 100.0);
            d->winWeek.resetUnixMs = resetMs;
            d->winWeek.windowDurationMs = periodMs;
            return true;
        }
        if (usedCredits >= 0 && monthlyLimit > 0) {
            // A published cap becomes a real percentage over the real period.
            d->winWeek.pct = std::min(usedCredits / monthlyLimit * 100.0, 100.0);
            d->winWeek.resetUnixMs = resetMs;
            d->winWeek.windowDurationMs = periodMs;
            return true;
        }
        if (usedCredits >= 0) {
            // Uncapped account: keep the real credits amount for the amount label;
            // there is no honest percentage to invent.
            d->grokUsedCredits = usedCredits;
        }
        if (!resetMs) {
            *error = L"unexpected response format (" + DescribeJsonBody(body) + L")";
            return false;
        }
        d->grokFreeNoUsage = true;
        d->winWeek.resetUnixMs = resetMs;
        d->winWeek.windowDurationMs = periodMs;
        return true;
'@

# --- 4: FetchGrokUsage second request -------------------------------------------
Apply @'
    AccountData fresh;
    std::wstring parseError;
    if (!ParseGrokBilling(r.body, &fresh, &parseError)) {
        d->stale = true;
        d->error = parseError.empty() ? L"unexpected response format" : parseError;
        return;
    }
    fresh.stale = false;
    fresh.lastSuccessMs = NowUnixMs();
    *d = std::move(fresh);
'@ @'
    AccountData fresh;
    std::wstring parseError;
    if (!ParseGrokBilling(r.body, &fresh, &parseError)) {
        d->stale = true;
        d->error = parseError.empty() ? L"unexpected response format" : parseError;
        return;
    }

    // The credits view carries no usage fields for free plans. One extra request
    // to the plain billing endpoint fills in the real monthly credits used (or a
    // real percentage when the account publishes a cap); anything else keeps the
    // credits-view period. Accounts with a published percentage never get here.
    if (fresh.grokFreeNoUsage && fresh.winWeek.pct < 0) {
        HttpResult billing = HttpRequest(L"GET", L"cli-chat-proxy.grok.com",
                                         L"/v1/billing", kOAuthUserAgent, headers);
        if (billing.ok && billing.status == 200) {
            AccountData merged;
            std::wstring mergeError;
            if (ParseGrokBilling(billing.body, &merged, &mergeError) &&
                (merged.winWeek.pct >= 0 || merged.grokUsedCredits >= 0)) {
                fresh = std::move(merged);
            }
        }
    }
    fresh.stale = false;
    fresh.lastSuccessMs = NowUnixMs();
    *d = std::move(fresh);
'@

# --- 5: VisibleBarCount grok exception --------------------------------------------
Apply @'
        if (a.showBars[w] && (d.lastSuccessMs == 0 || usage[w]->pct >= 0)) count++;
'@ @'
        if (a.showBars[w] &&
            (d.lastSuccessMs == 0 || usage[w]->pct >= 0 ||
             (d.grokFreeNoUsage && w == kWeeklyBar))) count++;
'@

# --- 6: percent text shows the real credits amount --------------------------------
Apply @'
                        percentText = text;
                    }
'@ @'
                        percentText = text;
                    } else if (accounts[i].provider == L"grok" &&
                               d.grokFreeNoUsage && w == kWeeklyBar &&
                               d.grokUsedCredits >= 0) {
                        // Free Grok publishes no cap, so no honest percentage exists;
                        // the label shows the real credits used in the real period.
                        wchar_t text[24];
                        swprintf(text, ARRAYSIZE(text), L"%.0fcr", d.grokUsedCredits);
                        percentText = text;
                    }
'@

# --- 7: bar label for the grok amount bar ------------------------------------------
Apply @'
                    std::wstring windowLabel = wu.pct >= 0 ? std::wstring(wl) : std::wstring();
'@ @'
                    bool grokFreeAmount = accounts[i].provider == L"grok" &&
                                          d.grokFreeNoUsage && w == kWeeklyBar &&
                                          d.grokUsedCredits >= 0;
                    std::wstring windowLabel =
                        (wu.pct >= 0 || grokFreeAmount) ? std::wstring(wl) : std::wstring();
'@

# --- 8: tooltip ---------------------------------------------------------------------
Apply @'
            if (accounts[i].provider == L"grok" && d.grokFreeNoUsage) {
                // xAI's free tier publishes no usage percentage anywhere; state that
                // plainly instead of implying 0% used, and keep the real reset date.
                tip += L"\nwk: free plan - xAI reports no usage %";
                if (d.winWeek.resetUnixMs) {
                    tip += L" | resets " + FormatReset(d.winWeek.resetUnixMs);
                }
            }
'@ @'
            if (accounts[i].provider == L"grok" && d.grokFreeNoUsage) {
                if (d.grokUsedCredits >= 0) {
                    // xAI's free tier publishes no usage percentage anywhere, but the
                    // plain billing endpoint does publish the credits used; show the
                    // real amount in the real period and keep the real reset date.
                    wchar_t wl[16];
                    WindowShortLabel(d.winWeek, L"7d", wl, ARRAYSIZE(wl));
                    swprintf(line, ARRAYSIZE(line),
                             L"\n%s: %.0f credits used - xAI publishes no cap", wl,
                             d.grokUsedCredits);
                    tip += line;
                } else {
                    // No usage fields at all: state that plainly instead of implying
                    // 0% used, and keep the real reset date.
                    tip += L"\nwk: free plan - xAI reports no usage %";
                }
                if (d.winWeek.resetUnixMs) {
                    tip += L" | resets " + FormatReset(d.winWeek.resetUnixMs);
                }
            }
'@

# --- 9: version + readme --------------------------------------------------------------
Apply @'
// @version         1.8.1.0
'@ @'
// @version         1.8.2.0
'@

Apply @'
- **Grok (xAI):** 7-day Grok Build CLI usage period
'@ @'
- **Grok (xAI):** the usage xAI publishes for your Grok Build CLI account - a
  percentage when a limit is reported, otherwise monthly credits used (free
  plans report no cap)
'@

if (-not $ok) {
    Write-Host "PATCH FAILED - no changes written"
    exit 20
}
Copy-Item $path ($path + '.patch-bak') -Force
$utf8 = [System.Text.UTF8Encoding]::new($hasBom)
[System.IO.File]::WriteAllText($path, $text, $utf8)
Write-Host ("PATCH OK: $patched replacements written, BOM preserved: $hasBom")

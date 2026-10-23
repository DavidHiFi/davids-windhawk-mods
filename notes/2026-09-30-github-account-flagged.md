# GitHub account DavidHiFi is flagged (hidden from public) - 2026-09-30

**This is the blocker for the Windhawk catalog submissions.** It is not caused
by, and cannot be fixed by, anything on this machine. Only GitHub Support can
restore the account (or it may clear itself after review).

## Evidence (observed 2026-09-30, ~01:00-01:30 +08)

Anonymous requests (no login) to otherwise-public content:

| Check | Result |
| --- | --- |
| `https://github.com/DavidHiFi` | 404 |
| `https://api.github.com/users/DavidHiFi` | 404 (also 404 when authenticated) |
| `https://api.github.com/repos/DavidHiFi/BlenderCoD` (visibility: public) | 404 |
| `https://api.github.com/repos/DavidHiFi/T6-QoL` (visibility: public) | 404 |
| `https://api.github.com/repos/DavidHiFi/davids-windhawk-mods` (public) | 404 |
| `https://api.github.com/search/users?q=DavidHiFi+in:login` | 0 results |
| `https://api.github.com/search/repositories?q=davids-windhawk-mods` | 0 results |
| `https://github.com/m417z` (control account) | 200 |

With authentication everything works: `gh api user` returns the account
(id 106938608, created 2022-06-06, 20 public repos), pushes succeed, PRs
exist, releases and repo reads work. `gh repo list` shows the repos as PUBLIC.

Behavioral consequences already observed:

- No GitHub Actions runs are created for the four fork PRs in
  ramensoftware/windhawk-mods (#5785, #5813, #5814, #5815), not even
  `action_required` runs, and the `pull_request_target` workflows (labels,
  welcome comment) do not run either.
- Comments posted from the account (the four `/ai-review` comments) do not
  trigger their workflows and got no reactions.
- `https://github.com/ramensoftware/windhawk-mods/pull/5813` and
  `.../pull/5785` return 404 to anonymous visitors (authenticated API reads
  them fine) - the PRs are hidden like everything else from this account.
- Old content from before the flag can still show CI history (PR #5785 has
  check suites from 2026-09-28), so the flag appears to have been applied
  after 2026-09-28.

This is the well-known "flagged account" state: profile and all public
content 404 for everyone, owner can still log in and push, no notification is
usually sent. Common cause: false positive by GitHub's automated anti-spam /
suspicious-activity detection (bursty API activity is a frequent trigger;
this session created four PRs, four comments and multiple pushes in a short
window). It can also happen for unrelated reasons.

## Impact on the mods work

Everything mechanical is done and correct: sources, metadata, repo, release
v1.2.0, fork branches, four PRs, local validation green. But:

- The public GitHub links the user asked for (`github.com/DavidHiFi/...`) show
  404 to everyone else until the account is restored.
- The upstream review flow cannot progress: the AI reviewer is driven by
  workflows that do not run for this account's PRs/comments.

## Resolution (account owner action required)

1. Log in to GitHub in a browser. Check:
   - Settings -> Account security (look for an "Account status" / restriction
     notice),
   - the email inbox (including spam) for a message from GitHub about the
     account.
2. Open a support ticket: https://support.github.com/ -> Contact GitHub
   Support -> Account and profile -> "My account has been flagged/restricted".
   (Direct: https://support.github.com/request)
3. Paste the draft below. Typical response time: 1-3 days. Then the account
   is restored (or the user is told why).

### Support request draft

> Subject: Flagged account - DavidHiFi - public profile and repositories
> return 404
>
> Hello GitHub Support,
>
> My account (login: DavidHiFi, id: 106938608, created 2022-06-06) appears to
> be flagged: my profile and all of my public repositories return 404 for
> anonymous visitors and do not appear in search, while I can still log in
> and push. Examples: https://github.com/DavidHiFi,
> https://api.github.com/repos/DavidHiFi/davids-windhawk-mods (both 404
> without authentication, both present with my credentials), and my pull
> requests in ramensoftware/windhawk-mods are invisible to anonymous
> visitors. GitHub Actions also no longer runs for my pull requests.
>
> I believe this is a mistake. The account is used for my personal open
> source projects (Windhawk modifications for Windows, Blender tools, game
> modding utilities). The repositories are my own work or are properly
> licensed forks with attribution. I am not aware of any Terms of Service
> violation. My recent activity (a few repository updates and four
> pull requests to ramensoftware/windhawk-mods) was performed by me through
> the normal GitHub API; if it triggered an automated spam detection, I ask
> for a manual review.
>
> Please review and restore the public visibility of my account. I can
> provide any verification requested.
>
> Thank you, David

## What happens after the flag is lifted

1. Re-post `/ai-review` on each of the four PRs (the earlier comments never
   triggered because of the flag). A scheduled check ("Windhawk PRs: watch
   for GitHub account unflag", every 12 hours, posts into the T3 thread that
   created it) watches for the unflag and does this automatically; delete it
   if it is no longer wanted.
2. Address the AI review findings, repeat `/ai-review`, then
   `/ready-for-reviewer` per the upstream process.
3. Nothing needs to be re-pushed or re-created: sources, repo, release and
   PRs are all in final shape, and the four submission files pass the
   upstream validator locally with 0 warnings.

## Undo / housekeeping

- The four `/ai-review` comments can stay; they are inert. Remove them if
  they look confusing once the account is back.
- Rollback of the repo/release/sources is documented in
  notes/2026-09-30-windhawk-mods-github-audit.md.

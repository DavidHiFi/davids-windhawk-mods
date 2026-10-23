<#
.SYNOPSIS
  Fetch every repository tracked by GitHub Desktop on this machine and report
  how each stands against its upstream; optionally fast-forward the clean ones.

.DESCRIPTION
  Default mode is report-only. It fetches each repository, then prints branch,
  dirty count, ahead/behind against the upstream, and the action -Apply would
  take. No working tree is modified unless -Apply is given.

  -Apply runs `git merge --ff-only` only for repositories that are clean
  (no pending changes), not mid-operation, have a tracking upstream, and are
  strictly behind it. Dirty, diverged, or in-progress repositories are always
  skipped and left untouched.

  Submodules are not updated. A fast-forward can move submodule pointers, so
  run `git submodule update --init --recursive` yourself when a repo that had
  a pointer change is supposed to carry them.

.PARAMETER Paths
  Repository paths to process. Defaults to the 20 repositories GitHub Desktop
  tracked on 2026-09-28. Confirm the live list in GitHub Desktop or with:
  the app's AppStore state (dispatcher over CDP, see
  notes\2026-09-28-github-desktop-refresh.md).

.PARAMETER Apply
  Perform the fast-forward merges. Omit for a dry pass.

.EXAMPLE
  .\Update-GitHubDesktopTrackedRepos.ps1
  Fetch and report only.

.EXAMPLE
  .\Update-GitHubDesktopTrackedRepos.ps1 -Apply
  Fetch, report, and fast-forward the clean repositories.

.NOTES
  Raw output of the 2026-09-28 run:
  reports\2026-09-28-github-desktop-repo-update.txt
#>
[CmdletBinding()]
param(
  [string[]]$Paths = @(
    'C:\Users\localuser\Documents\GitHub\T6-QoL',
    'C:\Users\localuser\Documents\GitHub\QualityOfLifeModManager',
    'C:\Users\localuser\Documents\GitHub\T5-QoL',
    'C:\Users\localuser\Documents\GitHub\T4-QoL',
    'C:\Users\localuser\Documents\GitHub\CLL-Cod-Lan-Launcher',
    'C:\Users\localuser\Documents\GitHub\Macified-Archived-',
    'C:\Users\localuser\system-configuration',
    'H:\Plutonium\Plutonium-QoL-Series',
    'H:\Plutonium\T7-QoL',
    'C:\Users\localuser\Documents\GitHub\BlenderCoD',
    'C:\Users\localuser\Documents\GitHub\Wallpapers',
    'C:\Users\localuser\Documents\GitHub\Wallpapers-Icons',
    'C:\Users\localuser\Documents\GitHub\millennium-stuff',
    'C:\Users\localuser\Documents\GitHub\StaffTag-UserPlugin',
    'C:\Users\localuser\Documents\GitHub\FakeVoice-UserPlugin',
    'H:\System Configuration\packages\better-lyrics-sync',
    'H:\System Configuration\packages\CustomStreamQuality-UserPlugin',
    'H:\System Configuration\packages\Davids-Vencord-Plugins',
    'H:\Windhawk Configuration\davids-windhawk-mods',
    'H:\System Configuration\packages\FreeDictate-Repo'
  ),
  [switch]$Apply
)

$ErrorActionPreference = 'Continue'
$env:GIT_TERMINAL_PROMPT = '0'

function RunGit($repo, $gitArgs) {
  $out = & git -C $repo @gitArgs 2>&1
  [pscustomobject]@{ Exit = $LASTEXITCODE; Out = ($out | Out-String).Trim() }
}

"GitHub Desktop tracked-repo update pass $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')"
"Mode: $(if ($Apply) { 'APPLY (ff-only merges for clean behind repos)' } else { 'REPORT ONLY (no working tree changes)' })"
""

foreach ($p in $Paths) {
  if (-not (Test-Path -LiteralPath $p)) { "MISSING          | $p"; continue }
  if (-not (Test-Path -LiteralPath (Join-Path $p '.git'))) { "NO-GIT           | $p"; continue }

  $gitDir = (RunGit $p @('rev-parse', '--absolute-git-dir')).Out
  $inprog = @()
  foreach ($f in @('MERGE_HEAD', 'CHERRY_PICK_HEAD', 'REVERT_HEAD', 'BISECT_LOG', 'rebase-merge', 'rebase-apply')) {
    if (Test-Path -LiteralPath (Join-Path $gitDir $f)) { $inprog += $f }
  }

  $fetch = RunGit $p @('fetch', '--prune', 'origin')
  $branch = (RunGit $p @('rev-parse', '--abbrev-ref', 'HEAD')).Out
  $dirty = @(& git -C $p status --porcelain 2>$null).Count
  $up = (RunGit $p @('rev-parse', '--abbrev-ref', '--symbolic-full-name', '@{u}')).Out
  $ahead = $null; $behind = $null
  if ($up -and $up -ne '') {
    $counts = ((RunGit $p @('rev-list', '--left-right', '--count', 'HEAD...@{u}')).Out) -split '\s+'
    if ($counts.Count -ge 2) { $ahead = [int]$counts[0]; $behind = [int]$counts[1] }
  }

  $detail = ''
  if ($inprog.Count) { $status = 'SKIP-in-progress' }
  elseif ($fetch.Exit -ne 0) { $status = 'SKIP-fetch-failed'; $detail = ($fetch.Out -replace '\r?\n', ' '); if ($detail.Length -gt 140) { $detail = $detail.Substring(0, 140) } }
  elseif ($dirty -gt 0) { $status = 'SKIP-dirty' }
  elseif (-not $up -or $up -eq '') { $status = 'SKIP-no-upstream' }
  elseif ($behind -gt 0 -and $ahead -eq 0) {
    if ($Apply) {
      $merge = RunGit $p @('merge', '--ff-only', '@{u}')
      if ($merge.Exit -eq 0) { $status = 'FF' } else { $status = 'FF-FAILED'; $detail = ($merge.Out -replace '\r?\n', ' ') }
    } else {
      $status = "WOULD-FF(+$behind)"
    }
  }
  elseif ($ahead -gt 0 -and $behind -gt 0) { $status = 'DIVERGED' }
  else { $status = 'OK' }

  "{0,-18} | dirty {1,3} | ahead {2,3} behind {3,3} | {4}`n{5}{6}" -f $status, $dirty, $(if ($null -eq $ahead) { '?' } else { $ahead }), $(if ($null -eq $behind) { '?' } else { $behind }), $branch, (' ' * 20 + $p), $(if ($detail) { "`n" + (' ' * 20 + 'detail: ' + $detail) } else { '' })
}

""
if (-not $Apply) { "Report only. Re-run with -Apply to fast-forward the clean, behind repositories." }
"done $(Get-Date -Format 'HH:mm:ss')"

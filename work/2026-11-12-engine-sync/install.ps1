# Stages the footer fix into Dictate and Clipboard (their engines are otherwise current), compiles them
# offline, then installs all six staged mods, each only if its live source is unchanged since staging.
# Run under heavy.py, with the windhawk-engine coop lock held.
$py = "C:\Users\localuser\AppData\Local\Programs\Python\Python313\python.exe"
$o = "C:\Users\Public\engine-sync"
$elev = "H:\System Configuration\scripts\Invoke-Elevated.ps1"
$inst = "H:\Windhawk Configuration\scripts\Install-StagedMod.ps1"
$hash = @{
    'local@seamless-launchpad'     = '5A9B4B1AABB349AEFAE782C9DEE6D24B9779355EDECB7725F03D7CC447640193'
    'local@seamless-color-picker'  = 'E30734BAB512A42FF9927EC50CF4D0BB8EDF9E3F19444CE2DB9B646925EA5EE4'
    'local@seamless-media-player'  = '5CC3571F2A04001F772782001562BFA48F37A03878F9174EC803FAA6F1CB785E'
    'local@seamless-key-click'     = '2CE48CFD2478F55A7212C0784DEE2159C2A764FA983C5D5C5422C23401660843'
}
$old = '    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : 0.85f);'
$new = "    // The same see-through mantle as the rail dock, so the blurred rows under the pill read as`n" +
       "    // real glass instead of a near-solid bar.`n" +
       '    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : (w.glass ? 0.58f : 0.85f));'
foreach ($id in 'local@seamless-dictate', 'local@seamless-clipboard-manager') {
    $live = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
    $bytes = [IO.File]::ReadAllBytes($live)
    $hash[$id] = -join ([Security.Cryptography.SHA256]::Create().ComputeHash($bytes) | % { $_.ToString('X2') })
    $s = [Text.Encoding]::UTF8.GetString($bytes).Replace("`r`n", "`n")
    if (([regex]::Matches($s, [regex]::Escape($old))).Count -ne 1) { "$id footer line not found once, skipped"; $hash.Remove($id); continue }
    $s = $s.Replace($old, $new)
    $m = [regex]::Match($s, '(//\s*@version\s+)(\d+)\.(\d+)\.(\d+)')
    $v = "$($m.Groups[2].Value).$($m.Groups[3].Value).$([int]$m.Groups[4].Value + 1)"
    $s = $s.Substring(0, $m.Index) + $m.Groups[1].Value + $v + $s.Substring($m.Index + $m.Length)
    [IO.File]::WriteAllText("$o\$id.wh.cpp", $s, (New-Object Text.UTF8Encoding $false))
    "#define WH_MOD_ID L`"$id`"`n#define WH_MOD_VERSION L`"$v`"" | Set-Content "$o\$id.id.h" -Encoding ascii
    $cl = Start-Process 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe' -PassThru -Wait -WindowStyle Hidden `
        -RedirectStandardError "$o\$id.err" -ArgumentList ('-std=c++23 -O1 -target x86_64-w64-mingw32 -DUNICODE -D_UNICODE ' +
        "-DWINVER=0x0A00 -D_WIN32_WINNT=0x0A00 -DWH_MOD -c -include `"$o\$id.id.h`" -include windhawk_api.h " +
        "-I `"C:/Program Files/Windhawk/Compiler/include`" -x c++ `"$o\$id.wh.cpp`" -o `"$o\$id.o`"")
    "COMPILE $id v${v}: exit $($cl.ExitCode)"
    if ($cl.ExitCode -ne 0) { Get-Content "$o\$id.err" | Select-String ' error' | Select -First 8; $hash.Remove($id) }
}
foreach ($id in 'local@seamless-key-click', 'local@seamless-color-picker', 'local@seamless-dictate',
                'local@seamless-clipboard-manager', 'local@seamless-media-player', 'local@seamless-launchpad') {
    if (-not $hash.ContainsKey($id)) { continue }
    & $elev -File $inst -ArgumentList "-Id $id -Staged `"$o\$id.wh.cpp`" -BaseHash $($hash[$id])"
    "$id registry v" + (Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id").Version
}
& $py "H:\Windhawk Configuration\scripts\settings-material.py" check

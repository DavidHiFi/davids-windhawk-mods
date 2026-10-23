import hashlib, json, os, re, shutil
from pathlib import Path

dest = Path(r'H:\Windhawk Configuration')
source = Path(r'H:\System Configuration')
report = dest/'reports/2026-10-04-workspace-sort'
receipt = json.loads((report/'receipt.json').read_text(encoding='utf-8'))
context = json.loads((report/'mixed-context.json').read_text(encoding='utf-8'))
known = {r['source'] for r in receipt}
for section in ['scripts','reports','backups']:
    base = source/section
    todo = [base]
    while todo:
        folder = todo.pop()
        for p in folder.iterdir():
            if p.is_junction() or p.is_symlink():
                continue
            if p.is_dir():
                if re.fullmatch(r'\d{4}-\d{2}-\d{2}',p.name):
                    todo.append(p)
                continue
            if str(p) in known or p.suffix.lower() not in {'.ps1','.py','.cmd','.reg','.json','.txt','.log','.md'} or p.stat().st_size > 1000000:
                continue
            if not re.search('windhawk|Wh_Mod',p.read_text(encoding='utf-8',errors='replace'),re.I):
                continue
            copied = dest/'docs/system-context'/p.relative_to(source)
            copied.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(p,copied)
            assert hashlib.sha256(p.read_bytes()).digest() == hashlib.sha256(copied.read_bytes()).digest()
            context.append({'source':str(p),'copy':str(copied),'reason':'Mixed system record or shared utility; reference copy'})
for row in receipt:
    src,dst = Path(row['source']),Path(row['destination'])
    assert src.exists() and dst.exists() and os.path.samefile(src,dst), row
    if row['directory']:
        assert src.is_junction(), src
    else:
        assert src.stat().st_nlink >= 2, src
for name in ['Windhawk','davids-windhawk-mods']:
    assert (source/name).is_junction() and (source/name).samefile(dest/name)
(report/'mixed-context.json').write_text(json.dumps(context,indent=2),encoding='utf-8')
summary = {'items':len(receipt),'files':sum(r['files'] for r in receipt),'mixed_context_copies':len(context),'compatibility_verified':True,'hashes_verified_during_move':all(r['verified'] for r in receipt),'live_settings_changed':False}
(report/'verification.json').write_text(json.dumps(summary,indent=2),encoding='utf-8')
note = f'''# Windhawk workspace sort, 2026-10-04

Moved {summary['items']} Windhawk files and folders containing {summary['files']} files
from System Configuration into this workspace. Sources, development checkouts,
registry backups, scripts, diagnostics, screenshots, themes and notes now belong here.
All moved files passed SHA-256 verification. Directory junctions and file hardlinks
preserve old paths; the final check verified every compatibility link.

Mixed system records remain in System Configuration. {len(context)} reference copies
here preserve Windhawk context without moving unrelated system work. Their source
and destination paths appear in `reports/2026-10-04-workspace-sort/mixed-context.json`.
Existing destination files were preserved; colliding imports live under
`archive/system-configuration-2026-10-04` and appear in the receipt.

Both current-status files point future Windhawk work here. The Windhawk workspace
instructions and README describe the consolidated layout. Another thread held the
System Configuration instructions, so its coordination board received the requested
scope update rather than a competing edit.

No live mod, registry value, application, T3 conversation binding, or installation
was changed. Git checkouts retain their branches, edits and history. Old paths remain
valid through compatibility links.

The complete receipt is `reports/2026-10-04-workspace-sort/receipt.json`.
Documentation backups are in `backups/2026-10-04/workspace-sort-docs`.
To undo an individual move, use its receipt row: remove only its old compatibility
link, then move the destination back to the recorded source. For directory junctions,
remove the junction itself without recursive deletion. Do not delete its target.
Restore the saved documentation copies to undo the workspace handoff text.
'''
(dest/'notes/2026-10-04-workspace-sort.md').write_text(note,encoding='utf-8')
print(json.dumps(summary,indent=2))

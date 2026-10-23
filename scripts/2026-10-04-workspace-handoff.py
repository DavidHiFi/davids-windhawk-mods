import hashlib, json, re, shutil
from pathlib import Path

dest = Path(r'H:\Windhawk Configuration')
source = Path(r'H:\System Configuration')
report = dest/'reports/2026-10-04-workspace-sort'
backup = dest/'backups/2026-10-04/workspace-sort-docs'
backup.mkdir(parents=True, exist_ok=True)
for root, names in [(dest, ['AGENTS.md','CURRENT-STATUS.md','README.md']), (source, ['CURRENT-STATUS.md'])]:
    for name in names:
        shutil.copy2(root/name, backup/(('system-' if root == source else 'windhawk-')+name))

context = []
for p in (source/'notes').glob('*.md'):
    target = dest/'notes'/p.name
    if target.exists() and p.samefile(target):
        continue
    text = p.read_text(encoding='utf-8', errors='replace')
    if re.search('windhawk|windhog', text, re.I):
        copied = dest/'docs/system-context'/p.name
        copied.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(p, copied)
        assert hashlib.sha256(p.read_bytes()).digest() == hashlib.sha256(copied.read_bytes()).digest()
        context.append({'source':str(p), 'copy':str(copied), 'reason':'Mixed system record retained at source; Windhawk context copied here'})
(report/'mixed-context.json').write_text(json.dumps(context, indent=2), encoding='utf-8')

p = dest/'AGENTS.md'
text = p.read_text(encoding='utf-8')
text = text.replace('Historical Windhawk records from before 2026-09-28 remain in\n  `H:\\System Configuration` (its `notes\\`, `scripts\\`, `reports\\`, `backups\\`).', 'Windhawk records, including historical notes, scripts, reports, backups, and\n  development checkouts, belong here. The 2026-10-04 sort moved the remaining\n  Windhawk records from System Configuration; mixed system notes have copies\n  in `docs\\system-context\\`.')
p.write_text(text, encoding='utf-8')

intro = '''## Workspace sorting completed 2026-10-04

Windhawk development checkouts, settings backups, scripts, diagnostics, screenshots,
themes and notes from System Configuration now live in this workspace.
Directory junctions and file hardlinks preserve old paths. Write new records here.
Mixed system notes remain in System Configuration with reference copies in
`docs/system-context`. See `notes/2026-10-04-workspace-sort.md` and the migration
receipts in `reports/2026-10-04-workspace-sort`.

The latest imported records document Taskbar Weather 1.4.0 using DirectWrite,
Taskbar System Info 1.2.3 capacity alignment, the audio visualizer, and the window
pack. Read their dated notes before changing them. This sort did not change live
mods, registry settings, applications, or T3 conversation bindings.

'''
p = dest/'CURRENT-STATUS.md'
text = p.read_text(encoding='utf-8').replace('Last updated: 2026-09-30', 'Last updated: 2026-10-04')
text = text.replace('## 2026-09-30: Better', intro+'## 2026-09-30: Better', 1)
text = text.replace('- Historical Windhawk records before 2026-09-28 (notes, scripts, reports, backups)\n  stay in `H:\\System Configuration`; new Windhawk records go here.', '- Historical Windhawk records were moved here on 2026-10-04; old paths remain\n  available through compatibility links.')
p.write_text(text, encoding='utf-8')
p = source/'CURRENT-STATUS.md'
text = p.read_text(encoding='utf-8')
text = text.replace('# Current status\n', '# Current status\n\n## Windhawk work moved 2026-10-04\n\nAll Windhawk work belongs in `H:\\Windhawk Configuration`. Remaining Windhawk\nrecords and development folders were moved there with compatibility links.\nRead that workspace\'s `CURRENT-STATUS.md` for Windhawk continuation. Historical\nentries below remain as system-work history.\n', 1)
p.write_text(text, encoding='utf-8')
p = dest/'README.md'
text = p.read_text(encoding='utf-8')
text += '\n## System Configuration import, 2026-10-04\n\nRemaining Windhawk records now live here, including `work/` development\ncheckouts and `themes/` configurations. Old paths resolve through junctions\nand hardlinks. Mixed system records have copies in `docs/system-context/`.\nThe sort receipt and file hashes are in `reports/2026-10-04-workspace-sort/`.\nUse this workspace for all new Windhawk tasks.\n'
p.write_text(text, encoding='utf-8')
print(f'Copied {len(context)} mixed context notes; updated workspace handoffs')

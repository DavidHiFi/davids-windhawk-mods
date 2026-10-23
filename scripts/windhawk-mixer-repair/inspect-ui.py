from pathlib import Path
from pywinauto import Desktop
import sys
import time

out = Path(r'H:\System Configuration\reports\2026-09-30\windhawk-mixer-repair')
windows = Desktop(backend='uia').windows(title_re='.*Windhawk.*')
if '--details' in sys.argv:
    window = next(w for w in windows if w.window_text() == 'Windhawk')
    elements = window.descendants()
    index = next(i for i, e in enumerate(elements) if e.element_info.control_type == 'Text' and e.window_text() == 'Better Volume Mixer Plus')
    following = elements[index + 1:index + 6]
    assert any(e.window_text() == 'Per-app volume plus output and input device routing from the system tray' for e in following)
    button = next(e for e in following if e.element_info.control_type == 'Button' and e.window_text() == 'Details')
    button.invoke()
    time.sleep(2)
with (out / 'ui-tree.txt').open('w', encoding='utf-8') as log:
    for window in windows:
        log.write(f'WINDOW {window.window_text()} {window.element_info.process_id}\n')
        for element in window.descendants():
            log.write(f'{element.element_info.control_type}: {element.window_text()}\n')
        window.capture_as_image().save(out / 'windhawk-ui.png')

# asslayer

ASS subtitle desktop overlays for Wayland, rendered with libass and Vulkan.
Python applications can supply ASS content, control playback and visibility,
and provide interactive menus. Requires a compositor supporting wlr-layer-shell.

## Install

Requires Python 3.14+, a C++20 compiler, Meson 1.3+, Ninja, pkg-config,
Wayland (including wayland-scanner), Vulkan headers and loader, shaderc
(including glslc), libass, and fontconfig. Install the development headers
for these libraries when building from source.

From a source checkout:

```bash
uv pip install .
```

## Use

```python
import time
from pathlib import Path

from asslayer import ApplicationController

ctrl = ApplicationController(namespace="my-subtitles")
try:
    ctrl.set_ass_input(Path("subtitles.ass").read_text())
    ctrl.set_status(start_time_ms=int(time.monotonic() * 1000))
    ctrl.start()
    input("Press Enter to stop\n")
finally:
    ctrl.stop()
    ctrl.join()
```

Create controllers in a running Wayland session. The keyword-only `namespace`
defaults to `asslayer` and must be non-empty without NUL bytes. It identifies
the layer surface for compositor rules and cannot be changed after construction.
Run separate processes with different namespaces to distinguish overlays;
use a shared namespace when the same rules should apply to several overlays.
Concurrent controllers within one process are not supported.

`set_status` controls `paused`, `hidden`, `locked`, `start_time_ms`, and
`target_fps`. Read `state` for the current state and drag offsets.
Commands are asynchronous. `set_ass_input` accepts ASS text rather than a path.
`set_animation` configures visibility transitions, and `reset_drag` clears
position offsets.

Supply menus with `set_ui_menu`, using dictionaries with `label`, optional
`action`, and optional `children`. Read application actions with
`poll_ui_events` and keyboard events with `poll_key_events`.

Set `ASSLAYER_DEBUG=1` before importing asslayer to enable engine debug logs.
Unset it or set it to `0` to disable debug logs.

## License

GPL-3.0-only. See LICENSE. Vendored Dear ImGui retains its own license in
`vendor/imgui/LICENSE.txt`.

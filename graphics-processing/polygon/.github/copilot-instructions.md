<!-- .github/copilot-instructions.md for polygon project -->
# Quick AI guidance for contributors and copilots

Purpose
- Provide minimal, actionable context so an AI coding agent can be productive immediately.

Big picture
- Core library: `polygon.c` / `polygon.h` implement a small polygon rendering library (libpolygon) exposing functions like `NewVertexes`, `NewPolygons`, `SetVertex`, `SetPolygon3`/`SetPolygon4`, `UseShader`, `Preview()`.
- Sample apps: `sample.c`, `bspt.c`, `tetra.c` are thin apps that link against the shared library and call the library API to build models and open an interactive OpenGL preview.
- Dataflow: geometry is built in C using `SetVertex`/`SetPolygon*`; optional BSP tree configuration is applied via `SetBsptRoot` / `SetBspt(...)`. `convert.py` generates C initialization code (colors/vertices/polygons/BSP calls) from OBJ input.

Build & run (exact commands in this repo)
- Build everything: `make all` (creates `libpolygon.so`, `sample`, `bspt`, `tetra`).
- On macOS the Makefile uses `MACOSX_FLAGS = -DMACOSX -framework OpenGL -framework GLUT`.
- Typical compile target examples (from Makefile):
  - `cc polygon.c -o libpolygon.so -lm -shared -Wall -fPIC $(OPT)`
  - `cc sample.c -o sample -lpolygon -L.`
- Run interactive preview: `./sample` (keyboard controls shown in `sample.c` header: arrow keys, Space, B, R, Q).

Key patterns & conventions (do not change without noting in instructions)
- Polygon indices and vertex indices are zero-based. `SetPolygon3(i,a,b,c,color)` uses vertex indices referencing previously created vertices.
- `SetPolygon3` is the default; `SetPolygon4` supports quads. `#define SetPolygon SetPolygon3` exists in `polygon.h`.
- BSP-tree: the BSP topology is manually set with `SetBsptRoot()` and `SetBspt(p, fore, back)`. `convert.py` prints `SetBspt(...)` lines suitable for paste-in into a sample source.
- Shading hook: agents should look for `UseShader(shader)` in samples and implement a function `void shader(Polygon *p)` that sets `p->shade` and `p->visible` (see `sample.c` for example). The library calls the shader for each polygon before drawing.
- Depth-buffer vs BSP: toggle with `UseDepthBuffer(int)` and `UseBspt(int)`. Samples often set `UseDepthBuffer(0); UseBspt(1);`.
- Memory model: library allocates arrays with `NewColors`, `NewVertexes`, `NewPolygons` and stores global pointers — changing those APIs affects all samples.

Integration points & automation
- `convert.py` turns an OBJ into a sequence of `NewColors`, `SetVertex`, `SetPolygon3` and `SetBspt` lines. When adding features that change polygon layout (e.g. supporting quads), keep `convert.py` output format in sync.
- Tests / visual verification are manual: run `./sample` or `./bspt` and visually confirm rendering and BSP ordering.

Troubleshooting & debugging tips
- If GL build fails on macOS, ensure Xcode command-line tools and GLUT/OpenGL frameworks are available; Makefile's `OPT` uses `MACOSX_FLAGS` by default.
- To experiment with shading, change `shader()` in `sample.c` and recompile `cc sample.c -o sample -lpolygon -L.`
- For BSP ordering bugs, inspect `SetBspt(...)` sequences in `sample.c` or the generated output from `convert.py` (see `results.txt` for example output created by `convert.py`).

What I did in this commit
- Added this concise instruction file describing build, runtime, conventions, and integration points.

Questions for maintainers
- Do you want AI agents to modify `convert.py` for alternate color schemes or preserve current behavior?
- Should we add a small test harness that runs `convert.py` on a sample OBJ and compiles a non-interactive render for CI?

chcp 65001

scons --version
python --version

$env:BUILD_NAME = "guidot"

scons p=windows arch=x86_64 target=editor module_websocket_enabled=yes module_jsonrpc_enabled=yes d3d12=yes compiledb=yes profile=misc/dist/guidot/guidot_editor.py

.\bin\godot.windows.editor.x86_64.mono.console.exe --headless --generate-mono-glue modules\mono\glue --guidot-api misc\dist\guidot\guidot.api.json
python .\modules\mono\build_scripts\build_assemblies.py --godot-output-dir=.\bin --guidot-api

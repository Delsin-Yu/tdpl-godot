chcp 65001

scons --version
python --version

$env:BUILD_NAME = "tdpl"

scons p=windows arch=x86_64 target=editor module_websocket_enabled=yes module_jsonrpc_enabled=yes d3d12=yes compiledb=yes profile=custom_dev.py

.\bin\godot.windows.editor.dev.x86_64.mono.console.exe --headless --generate-mono-glue modules\mono\glue --generate-localized-docs
python .\modules\mono\build_scripts\build_assemblies.py --godot-output-dir=.\bin

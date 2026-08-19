cd "$(dirname "$0")"
export BUILD_NAME=guidot
scons p=macos arch=x86_64 target=editor module_websocket_enabled=yes module_jsonrpc_enabled=yes profile=misc/dist/guidot/guidot_editor.py
scons p=macos arch=arm64 target=editor module_websocket_enabled=yes module_jsonrpc_enabled=yes profile=misc/dist/guidot/guidot_editor.py
lipo -create bin/godot.macos.editor.x86_64.mono bin/godot.macos.editor.arm64.mono -output bin/godot.macos.editor.universal.mono
rm bin/godot.macos.editor.x86_64.mono
rm bin/godot.macos.editor.arm64.mono
bin/godot.macos.editor.universal.mono --headless --generate-mono-glue modules/mono/glue --guidot-api misc/dist/guidot/guidot.api.json
python3 ./modules/mono/build_scripts/build_assemblies.py --godot-output-dir=bin --guidot-api

cd "$(dirname "$0")"
export BUILD_NAME=tdpl
scons p=macos arch=x86_64 target=editor module_websocket_enabled=yes module_jsonrpc_enabled=yes profile=custom.py
scons p=macos arch=arm64 target=editor module_websocket_enabled=yes module_jsonrpc_enabled=yes profile=custom.py
lipo -create bin/godot.macos.editor.x86_64.mono bin/godot.macos.editor.arm64.mono -output bin/godot.macos.editor.universal.mono
rm bin/godot.macos.editor.x86_64.mono
rm bin/godot.macos.editor.arm64.mono
bin/godot.macos.editor.universal.mono --headless --generate-mono-glue modules/mono/glue
python3 ./modules/mono/build_scripts/build_assemblies.py --godot-output-dir=bin

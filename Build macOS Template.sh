cd "$(dirname "$0")"
export BUILD_NAME=tdpl
scons p=macos arch=x86_64 target=template_release profile=custom.py
scons p=macos arch=arm64 target=template_release profile=custom.py
lipo -create bin/godot.macos.template_release.x86_64.mono bin/godot.macos.template_release.arm64.mono -output bin/godot.macos.template_release.universal.mono
rm bin/godot.macos.template_release.x86_64.mono
rm bin/godot.macos.template_release.arm64.mono

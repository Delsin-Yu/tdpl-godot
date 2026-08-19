cd "$(dirname "$0")"
export BUILD_NAME=guidot
# Pass renderer flags on the command line so they override platform defaults.
scons p=macos arch=x86_64 target=template_release vulkan=no d3d12=no metal=no opengl3=yes profile=misc/dist/guidot/guidot_template.py
scons p=macos arch=arm64 target=template_release vulkan=no d3d12=no metal=no opengl3=yes profile=misc/dist/guidot/guidot_template.py
lipo -create bin/godot.macos.template_release.x86_64.mono bin/godot.macos.template_release.arm64.mono -output bin/godot.macos.template_release.universal.mono
rm bin/godot.macos.template_release.x86_64.mono
rm bin/godot.macos.template_release.arm64.mono

cd "$(dirname "$0")"
export BUILD_NAME=tdpl
scons p=macos arch=x86_64 target=template_release disable_3d=yes profile=custom.py
scons p=macos arch=arm64 target=template_release disable_3d=yes profile=custom.py

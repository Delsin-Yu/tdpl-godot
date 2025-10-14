chcp 65001

scons --version
python --version

$env:BUILD_NAME = "tdpl"
$env:SCONSFLAGS = "-j24"

scons p=windows arch=x86_64 target=template_release d3d12=yes disable_3d=yes profile=custom.py
Pause

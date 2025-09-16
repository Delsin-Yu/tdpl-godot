chcp 65001

scons --version
python --version

$env:BUILD_NAME = "tdpl"

scons p=windows arch=x86_64 target=template_release d3d12=yes profile=custom.py

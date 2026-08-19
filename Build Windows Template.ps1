chcp 65001

scons --version
python --version

$env:BUILD_NAME = "guidot"

# Platform detect.py defaults d3d12=yes on Windows; pass renderer flags on the
# command line so they override platform get_flags() (profile alone is not enough).
scons p=windows arch=x86_64 target=template_release `
  vulkan=no d3d12=no metal=no opengl3=yes use_volk=no angle=no `
  profile=misc/dist/guidot/guidot_template.py

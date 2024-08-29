@echo off
chcp 65001

scons --version
python --version

set BUILD_NAME=uz
scons p=windows module_mono_enabled=yes debug_symbols=yes target=template_release arch=x86_64
pause

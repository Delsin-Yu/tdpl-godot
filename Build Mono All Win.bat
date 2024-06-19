@echo off
chcp 65001

scons --version
python --version

set BUILD_NAME=uz
scons p=windows module_mono_enabled=yes compiledb=yes debug_symbols=yes
.\bin\godot.windows.editor.x86_64.mono.console.exe --headless --generate-mono-glue modules\mono\glue
python .\modules\mono\build_scripts\build_assemblies.py --godot-output-dir=.\bin --push-nupkgs-local NugetSource
scons p=windows module_mono_enabled=yes debug_symbols=yes target=template_release arch=x86_64
pause

chcp 65001

scons --version
python --version

$env:BUILD_NAME = "tdpl"
$env:SCONSFLAGS = "-j24"

scons p=windows arch=x86_64 target=editor d3d12=yes compiledb=yes profile=custom.py

.\bin\godot.windows.editor.x86_64.mono.console.exe --headless --generate-mono-glue modules\mono\glue
python .\modules\mono\build_scripts\build_assemblies.py --godot-output-dir=.\bin --no-deprecated
Pause

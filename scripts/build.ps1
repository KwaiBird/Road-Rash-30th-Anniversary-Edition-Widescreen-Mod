param([string]$Vcvars32='C:/Program Files/Microsoft Visual Studio/18/Community/VC/Auxiliary/Build/vcvars32.bat')
$ErrorActionPreference='Stop'
$repo=Split-Path $PSScriptRoot
$source=Join-Path $repo 'src'
$out=Join-Path $repo 'build'
if(!(Test-Path -LiteralPath $Vcvars32)){throw 'Specify -Vcvars32 with your VS x86 environment script'}
New-Item -ItemType Directory -Force $out | Out-Null
$commands=@"
call "$Vcvars32" >nul
cd /d "$out"
cl /nologo /std:c++17 /EHsc /MT /W4 /WX /utf-8 /O2 /LD "$source/proxy.cpp" /sourceDependencies proxy.dependencies.json /Fe:ddraw.dll /link /DEF:"$source/proxy.def" /IMPLIB:WidescreenProxy.lib /IGNORE:4222 user32.lib gdi32.lib
if errorlevel 1 exit /b 1
"@
[IO.File]::WriteAllText((Join-Path $out 'build.cmd'),$commands,[Text.Encoding]::Default)
& cmd.exe /d /c (Join-Path $out 'build.cmd')
if($LASTEXITCODE -ne 0){throw 'Build failed'}

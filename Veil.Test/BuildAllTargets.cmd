@echo off

setlocal
pushd "%~dp0"

rem Remove the output folder for a fresh compile.
rd /s /q Output

rem Initialize Visual Studio environment
if "%VSINSTALLDIR%"=="" (
    call InitializeVisualStudioEnvironment.cmd
)

rem Build all targets
MSBuild -binaryLogger:Output\BuildAllTargets.binlog -m BuildAllTargets.proj

popd
endlocal
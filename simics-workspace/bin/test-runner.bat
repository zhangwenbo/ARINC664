
@echo off
rem this file will be overwritten by the workspace setup script
set SIMICS_BASE_PACKAGE=C:\PROGRA~1\Simics\SIMICS~1.6\SIMICS~1.111
if exist "C:\Users\Tyrion\simics-workspace\.package-list" set SIMICS_EPL=--package-list "C:\Users\Tyrion\simics-workspace\.package-list"
if not exist "C:\Users\Tyrion\simics-workspace\.package-list" set SIMICS_EPL=
"C:\PROGRA~1\Simics\SIMICS~1.6\SIMICS~1.111\..\MODELB~1.49\bin\test-runner.bat" %SIMICS_EPL% --workspace "C:\Users\Tyrion\simics-workspace" %*

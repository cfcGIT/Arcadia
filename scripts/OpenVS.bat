@echo off

CALL %~dp0SetupCMake.bat
if %ERRORLEVEL% == 0 devenv %~dp0..\build\Arcadia.sln

exit /b 0
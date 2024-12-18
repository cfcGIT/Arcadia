@echo off

CALL %~dp0SetupCMake.bat
devenv %~dp0..\build\Arcadia.sln
exit /b 0
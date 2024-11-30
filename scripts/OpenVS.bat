@echo off

CALL %~dp0SetupCMake.bat
devenv %~dp0..\Arcadia.sln
exit /b 0
@echo off

set BUILD=
set BUILD_TYPE=Debug

:GETOPTS
 if /I "%1" == "--help" goto help
 if /I "%1" == "--build_type" set BUILD_TYPE=%2 & shift
 if /I "%1" == "--build" set BUILD=--build & shift
 shift
if not "%1" == "" goto GETOPTS

REM Always generate..
echo:
echo Generating %BUILD_TYPE%..
cmake ../ -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
if "%BUILD%" NEQ "" (
    REM Build..
    echo:
    echo Building %BUILD_TYPE%..
    cmake %BUILD% ../ --config %BUILD_TYPE%
)

exit /b %ERRORLEVEL%

:help
echo %0 [--build_type BUILD_TYPE] [--build]
echo *BUILD_TYPE: Release, Debug, MinSizeRel, RelWithDebInfo
exit /b 0

REM TODO: Use cmake to build different build types (release, debug, ...)
:build_all
exit /b 1
@REM echo:
@REM echo Generating Debug..
@REM cmake -DCMAKE_BUILD_TYPE=Debug ../
@REM echo:
@REM echo Generating Release..
@REM cmake -DCMAKE_BUILD_TYPE=Release ../
@REM echo:
@REM echo Generating MinSizeRel..
@REM cmake -DCMAKE_BUILD_TYPE=MinSizeRel ../
@REM echo:
@REM echo Generating RelWithDebInfo..
@REM cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ../

@REM exit /b %ERRORLEVEL%

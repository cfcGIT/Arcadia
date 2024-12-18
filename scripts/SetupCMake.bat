@echo off

REM %0:                           Generate project files for all configs
REM %0 --build_all:               Generate project files for all configs + build all configs
REM %0 --build_type [BUILD_TYPE]: Generate project files for all configs + build [BUILD_TYPE] config

set current_dir="%cd%"
set script_dir=%~dp0

set BUILD_TYPE=
set BUILD_ALL=0
set ALL_BUILD_TYPES=Debug Release MinSizeRel RelWithDebInfo

:GETOPTS
 if /I "%1" == "--help" goto help
 if /I "%1" == "--build_type" set BUILD_TYPE=%2 & shift
 if /I "%1" == "--build_all" set BUILD_ALL=1
 shift
if not "%1" == "" goto GETOPTS

echo:
echo ** Generate **
echo Generating for all configs..
if not exist %script_dir%..\build mkdir %script_dir%..\build
cmake %script_dir%../ -B %script_dir%../build

if %BUILD_ALL%==1 (
    REM Build all configs
    echo:
    echo ** Build **
    echo - Building ALL configurations
    for %%b in (%ALL_BUILD_TYPES%) do  (
        echo:
        echo Building %%b..
        cmake --build %script_dir%../ --config %%b
    )
) else (
    if "%BUILD_TYPE%" NEQ "" (
        REM Build BUILD_TYPE config
        echo:
        echo ** Build **
        echo Building %BUILD_TYPE%..
        cmake --build %script_dir%../ --config %BUILD_TYPE%
    )
)

exit /b %ERRORLEVEL%

:help
echo %0 [--build_type BUILD_TYPE] [--build_all]
echo *BUILD_TYPE: Release, Debug, MinSizeRel, RelWithDebInfo
exit /b 0

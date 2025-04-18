:: If we want to execute as prebuild event, we can add this in .vcxproj config to always execute it
:: <PropertyGroup>
::     <DisableFastUpToDateCheck>true</DisableFastUpToDateCheck>
::     <PreBuildEventUseInBuild>true</PreBuildEventUseInBuild>
:: </PropertyGroup>

@echo off
setlocal enabledelayedexpansion
set ret=0
FOR /f "tokens=*" %%i in ('dir /b %~dp0..\*.glsl') do (
    set glslname=%%i
    set spvname=%~dp0..\!glslname:~0,-5!.spv
    glslc %~dp0..\!glslname! -o !spvname!
    if !errorlevel! == 0 (
        echo  -!glslname! compiled correctly
    ) else (
        set ret=1
        echo  -!glslname! failed while compiling
    )
)
exit /b %ret%
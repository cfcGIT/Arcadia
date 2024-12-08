@echo off

set current_dir="%cd%"
cd /d %~dp0

echo Generating doxygen documentation...
Doxygen %~dp0Doxyfile.dox >%~dp0log.txt 2>&1
%~dp0..\docs\index.html

cd /d %current_dir%
@echo off
@set project_name=Kazusa

@del %project_name%.exe
@REM rmdir en /Q /S
@del neo.pak
@premake5 gmake2
@mingw32-make -C external/victorique/build
@mingw32-make -C build

@if "%1"=="" goto build
@if "%~1"=="d" goto debug

@goto build

:debug
@lldb -- %project_name%.exe e en.pak en y
@goto end

:build
@%project_name%.exe p en neo.pak y
:end

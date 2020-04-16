@del Kazusa.exe
@premake5 gmake2
@mingw32-make -C build
@REM @rmdir data\\en /Q /S
@del data\\neo.pak
@REM @Kazusa.exe e data\\en.pak data\\en y
@Kazusa.exe p data\\en data\\neo.pak y
@echo off

if [%1]==[help] goto :help

set game=sami_troid

if [%1]==[justcompile] goto :compile
if [%1]==[clean] goto :clean

cd ..\script
if not exist %game%.spt goto :noscript
echo Compilando script
..\..\..\src\utils\msc3_mk1.exe %game%.spt 24 > nul
copy msc.h ..\dev\my > nul
copy msc-config.h ..\dev\my > nul
copy scripts.bin ..\dev\ > nul
:noscript
cd ..\dev

if [%1]==[justscripts] goto :compile

echo Convirtiendo mapa
..\..\..\src\utils\rle62map_sp.exe in=..\map\mapa.map mk1h=assets\mapa.h out=mapa size=8,9 tlock=15 mk1locks > nul

echo Convirtiendo enemigos/hotspots
..\..\..\src\utils\ene2h.exe ..\enems\enems.ene assets\enems.h

echo Importando GFX
..\..\..\src\utils\ts2bin.exe ..\gfx\font.png ..\gfx\work.png tileset.bin 7 >nul

..\..\..\src\utils\sprcnv.exe ..\gfx\sprites.png assets\sprites.h > nul

..\..\..\src\utils\sprcnvbin.exe ..\gfx\sprites_extra.png sprites_extra.bin 1 > nul
..\..\..\src\utils\sprcnvbin8.exe ..\gfx\sprites_bullet.png sprites_bullet.bin 1 > nul

..\..\..\src\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr > nul
..\..\..\src\utils\png2scr.exe ..\gfx\marco.png ..\gfx\marco.scr > nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending.png ..\gfx\ending.scr > nul
..\..\..\src\utils\png2scr.exe ..\gfx\loading.png loading.bin > nul
..\..\..\src\utils\apultra.exe ..\gfx\title.scr title.bin > nul
..\..\..\src\utils\apultra.exe ..\gfx\marco.scr marco.bin > nul
..\..\..\src\utils\apultra.exe ..\gfx\ending.scr ending.bin > nul

if [%1]==[justassets] goto :end

:compile
echo Compilando guego
zcc +zx -vn mk1.c -m -o %game%.bin -lsplib2_mk2.lib -zorg=24000 > nul
..\..\..\src\utils\printsize.exe %game%.bin
..\..\..\src\utils\printsize.exe scripts.bin

echo Construyendo cinta
rem cambia LOADER por el nombre que quieres que salga en Program:
..\..\..\src\utils\bas2tap -a10 -sSAMI_TROID loader\loader.bas loader.tap > nul
..\..\..\src\utils\bin2tap -o screen.tap -a 16384 loading.bin > nul
..\..\..\src\utils\bin2tap -o main.tap -a 24000 %game%.bin > nul
copy /b loader.tap + screen.tap + main.tap %game%.tap > nul

if [%1]==[justcompile] goto :end
if [%1]==[noclean] goto :end

:clean
echo Limpiando
del loader.tap > nul
del screen.tap > nul
del main.tap > nul
del ..\gfx\*.scr > nul
del *.bin > nul

goto :end 

:help
echo "compile.bat help|justcompile|clean|justscripts|justassets|noclean"

:end
echo Hecho!

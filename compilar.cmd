set _SCRIPT_DRIVE=%~d0
set _MINGW_DRIVE=%_SCRIPT_DRIVE%\Arquivos\Desenvolvimento\pocketcpp-0.4-x86\pocketcpp\MinGW\bin
set _FILES_PATH=Arquivos\Desenvolvimento\instalador_snb_src
set _LINKER=-std=gnu++11 -Wconversion-null -static-libgcc -static-libstdc++

cd %_MINGW_DRIVE%
g++ "%_SCRIPT_DRIVE%\%_FILES_PATH%\main.cpp" "%_SCRIPT_DRIVE%\%_FILES_PATH%\config.cpp" "%_SCRIPT_DRIVE%\%_FILES_PATH%\programa.cpp" -o "%_SCRIPT_DRIVE%\%_FILES_PATH%\out\instalador.exe" %_LINKER%
pause
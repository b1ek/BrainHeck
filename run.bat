@ECHO OFF
ECHO.
ECHO Compiling executable....
ECHO.
gcc main.c -O0 -s -g3 -o main.exe
ECHO.
ECHO.
ECHO Launching debugger
ECHO.
ECHO.
gdb main.exe -ex run
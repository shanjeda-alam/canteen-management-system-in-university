@echo off
echo Compiling Consumer Interface...

REM Set include path
set INCLUDE_PATH=C:\Users\RAYHAN RIJVE\Desktop\DSA Project\Canteen Management System\include

REM Compile consumer interface with all source files
gcc -I"%INCLUDE_PATH%" consumerInterface.c src\*.c -o ConsumerInterface.exe

if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo Compilation successful! Running Consumer Interface...
ConsumerInterface.exe
pause

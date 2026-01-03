@echo off
REM ===============================
REM Compile Canteen Management System
REM ===============================

REM Paths
SET SRC_PATH=%~dp0src
SET INCLUDE_PATH=%~dp0include
SET MAIN_FILE=%~dp0canteenmanagement.c
SET OUTPUT_EXE=%~dp0CanteenManagement.exe

REM Enable delayed expansion for dynamic file list
SETLOCAL ENABLEDELAYEDEXPANSION

REM Collect all .c files in src
SET FILES=
FOR %%f IN ("%SRC_PATH%\*.c") DO (
    SET FILES=!FILES! "%%f"
)

REM Compile all files with include path
echo Compiling Canteen Management System...
gcc -I"%INCLUDE_PATH%" "%MAIN_FILE%" !FILES! -o "%OUTPUT_EXE%"

IF %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo Running program...
    "%OUTPUT_EXE%"
) ELSE (
    echo Compilation failed!
)

pause

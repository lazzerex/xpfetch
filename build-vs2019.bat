@echo off
REM Automated build script for Visual Studio 2019
REM Requires Visual Studio 2019 with C++ and Windows XP support installed

echo XPFetch - Visual Studio 2019 Build Script
echo ==========================================
echo.

REM Detect Visual Studio installation
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"

if not exist "%VSWHERE%" (
    echo ERROR: Visual Studio 2019 not found!
    echo Please install Visual Studio 2019 with C++ Desktop Development
    pause
    exit /b 1
)

REM Find VS 2019 installation path
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
    set "VSINSTALLPATH=%%i"
)

if not defined VSINSTALLPATH (
    echo ERROR: Visual Studio C++ tools not found!
    pause
    exit /b 1
)

echo Found Visual Studio at: %VSINSTALLPATH%
echo.

REM Set up build environment
call "%VSINSTALLPATH%\VC\Auxiliary\Build\vcvarsall.bat" x86

if errorlevel 1 (
    echo ERROR: Failed to set up build environment
    pause
    exit /b 1
)

echo.
echo Compiling XPFetch...
echo.

REM Create obj directory
if not exist obj mkdir obj

REM Compile each source file
cl /nologo /c /O2 /MT /W3 /D_WIN32_WINNT=0x0501 /DWINVER=0x0501 ^
   /Foobj\ ^
   src\main.c ^
   src\console.c ^
   src\sys_os.c ^
   src\sys_cpu.c ^
   src\sys_mem.c ^
   src\sys_uptime.c ^
   src\sys_disk.c ^
   src\sys_display.c ^
   src\sys_user.c

if errorlevel 1 (
    echo.
    echo ERROR: Compilation failed!
    pause
    exit /b 1
)

echo.
echo Linking...
echo.

REM Link executable
link /nologo /OUT:xpfetch.exe /SUBSYSTEM:CONSOLE,5.01 ^
     obj\*.obj kernel32.lib user32.lib

if errorlevel 1 (
    echo.
    echo ERROR: Linking failed!
    pause
    exit /b 1
)

REM Clean up
del vc*.pdb 2>nul
del xpfetch.ilk 2>nul

echo.
echo ==========================================
echo Build successful: xpfetch.exe
echo File size:
dir xpfetch.exe | find "xpfetch.exe"
echo ==========================================
echo.

pause

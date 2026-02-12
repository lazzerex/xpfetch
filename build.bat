@echo off
REM Build script for XPFetch using MinGW on Windows

echo Building XPFetch for Windows XP...

REM Compile all source files
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/main.c -o src/main.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/console.c -o src/console.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_os.c -o src/sys_os.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_kernel.c -o src/sys_kernel.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_cpu.c -o src/sys_cpu.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_gpu.c -o src/sys_gpu.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_mem.c -o src/sys_mem.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_uptime.c -o src/sys_uptime.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_shell.c -o src/sys_shell.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_disk.c -o src/sys_disk.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_display.c -o src/sys_display.o
gcc -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 ^
    -c src/sys_user.c -o src/sys_user.o

REM Link object files
gcc -static -s -o xpfetch.exe ^
    src/main.o ^
    src/console.o ^
    src/sys_os.o ^
    src/sys_kernel.o ^
    src/sys_cpu.o ^
    src/sys_gpu.o ^
    src/sys_mem.o ^
    src/sys_uptime.o ^
    src/sys_shell.o ^
    src/sys_disk.o ^
    src/sys_display.o ^
    src/sys_user.o

if exist xpfetch.exe (
    echo Build successful: xpfetch.exe
) else (
    echo Build failed!
)

pause

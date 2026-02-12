

# XPFetch

<div align="center">
<img width="296" height="183" alt="image-removebg-preview (1)" src="https://github.com/user-attachments/assets/02f96517-63ae-40e3-b36f-da6221461053" />


A lightweight, Neofetch/Fastfetch-style system information tool designed specifically for **Windows XP** and older NT systems.

![Windows XP Compatible](https://img.shields.io/badge/Windows%20XP-Compatible-blue)
![C89](https://img.shields.io/badge/Language-C89%2FC90-green)
![License MIT](https://img.shields.io/badge/License-MIT-yellow)
![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen)
![Size](https://img.shields.io/badge/Size-<50KB-orange)
![Platform](https://img.shields.io/badge/Platform-Win32-lightgrey)
![Portable](https://img.shields.io/badge/Portable-Yes-success)
![Dependencies](https://img.shields.io/badge/Dependencies-None-informational)

<img width="669" height="333" alt="xpfetch_example1" src="https://github.com/user-attachments/assets/c87944cf-4b24-4b4c-a6cf-c42ee61599dd" />

</div>



## Features

- **Native Windows XP support** - Fully compatible with all XP versions (including pre-SP2)
- **Pure Win32 API** - No .NET, PowerShell, or WMI required
- **Lightweight** - Single executable under 50KB, minimal footprint
- **Colorful output** - Uses classic Win32 console colors
- **Portable** - No installation needed, just run it!
- **C89/C90 compliant** - Works with older compilers and toolchains

### System Information Displayed

- Operating System (version, edition, service pack)
- Hostname
- Kernel (Windows NT version)
- Uptime
- Shell (command interpreter)
- Display resolution and refresh rate
- CPU (brand, model, core count via CPUID)
- GPU (graphics card model)
- Memory (used/total RAM)
- Disk space (system drive usage)

## Screenshot

<img width="1437" height="802" alt="xpfetch_example2" src="https://github.com/user-attachments/assets/6413778c-0cc4-4f5d-b70f-379f765c83e1" />

## Downloads

You can download pre-built binaries directly from the [GitHub Releases page](https://github.com/lazzerex/xpfetch/releases)

Alternatively, you can build from source following the instructions below.


## Building

### Requirements

- **MinGW** (Minimalist GNU for Windows) or MinGW-w64
- **GCC** with C89/C90 support (any modern version)
- Windows XP or later for testing (or Wine on Linux)

### Build on Windows

1. Install [MinGW](https://sourceforge.net/projects/mingw/) or [MinGW-w64](https://www.mingw-w64.org/)
2. Add MinGW's `bin` directory to your PATH
3. Open Command Prompt in the project directory
4. Run the build script:

```cmd
build.bat
```

Or use the Makefile:

```cmd
mingw32-make
```

### Build with Visual Studio

You can also build with Visual Studio using the **Windows XP Platform Toolset**:

1. Open Visual Studio (2019 or earlier recommended)
2. Install the Windows XP support components
3. Create a new C++ Console Application project
4. Add all `.c` files from `src/` to the project
5. Set Platform Toolset to `v141_xp` or `v140_xp`
6. Build as Release (x86)

### Cross-Compile from Linux

```bash
# Install MinGW cross-compiler
sudo apt-get install mingw-w64

# Build
make CC=i686-w64-mingw32-gcc
```

## Usage

Simply run the executable in Windows XP's `cmd.exe`:

```cmd
xpfetch.exe
```

That's it! No arguments, no configuration needed.

## Project Structure

```
xpfetch/
├── src/
│   ├── main.c           # Entry point and layout engine
│   ├── logo.h           # ASCII logo definitions
│   ├── console.h/c      # Win32 console color handling
│   ├── sysinfo.h        # System info function declarations
│   ├── sys_os.c         # OS version detection
│   ├── sys_kernel.c     # Kernel version info
│   ├── sys_cpu.c        # CPU info via CPUID
│   ├── sys_gpu.c        # GPU detection
│   ├── sys_mem.c        # Memory statistics
│   ├── sys_uptime.c     # System uptime
│   ├── sys_shell.c      # Shell information
│   ├── sys_disk.c       # Disk space info
│   ├── sys_display.c    # Screen resolution
│   └── sys_user.c       # Username and hostname
├── Makefile             # Build configuration
├── build.bat            # Windows build script
└── README.md            # This file
```

## Technical Details

### Win32 API Functions Used

- `GetVersionEx` / `RegQueryValueEx` - OS version and service pack info
- `EnumDisplayDevices` - GPU information
- `EnumDisplaySettings` - Display resolution and refresh rate
- `GetTickCount` - System uptime calculation
- `GetComputerName` / `GetUserName` - Hostname and username
- `GetSystemInfo` - CPU core count
- `GlobalMemoryStatusEx` / `GlobalMemoryStatus` - RAM usage (dynamic loading for XP compatibility)
- `GetDiskFreeSpaceEx` - Disk space information
- `GetConsoleScreenBufferInfo` / `SetConsoleTextAttribute` - Console colors
- `CPUID instruction` - CPU brand string and vendor detection
- Environment variables (`COMSPEC`) - Shell detection

### Compatibility

- Windows XP (all versions: RTM, SP1, SP2, SP3 - both 32-bit and 64-bit)
- Windows 2000 Professional/Server
- Windows Server 2003/2003 R2
- Newer Windows versions (Vista, 7, 8, 8.1, 10, 11)

**Note**: The program uses dynamic function loading for `GlobalMemoryStatusEx` to ensure compatibility with early Windows XP versions that lack this API. It automatically falls back to `GlobalMemoryStatus` on older systems.

### No Dependencies On

- .NET Framework
- PowerShell
- WMI (Windows Management Instrumentation)
- ANSI escape sequences
- External DLLs (statically linked)

## Customization

### Adding New Logos

Edit `src/logo.h` to add custom ASCII art:

```c
static const char *custom_logo[] = {
    "  .-'''-.  ",
    " /       \\ ",
    "|  o   o  |",
    " \\   ^   / ",
    "  '-...-'  "
};

static const int custom_logo_lines = 5;
```

Then modify `main.c` to use your logo.

### Changing Colors

Edit the color definitions in `src/console.h`:

```c
#define LOGO_COLOR (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define LABEL_COLOR (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
```

Available color flags:
- `FOREGROUND_RED`
- `FOREGROUND_GREEN`
- `FOREGROUND_BLUE`
- `FOREGROUND_INTENSITY` (bright)

## Known Limitations

- **Single monitor only** - Only detects primary display resolution
- **CPU detection requires CPUID** - May not work on very old CPUs (pre-Pentium)
- **System drive only** - Disk info shows C: drive (or Windows system drive)
- **English only** - No localization support yet
- **No network info** - Network adapter details not currently displayed

## License

MIT License - See LICENSE file for details

## Acknowledgments

Inspired by:
- [Neofetch](https://github.com/dylanaraps/neofetch)
- [Fastfetch](https://github.com/fastfetch-cli/fastfetch)

## Contributing

Contributions welcome! Areas for improvement:

- Network adapter information
- Battery status for laptops
- Customizable info display order
- Config file support
- More ASCII logos (Windows 2000, NT 4.0, etc.)
- Windows 98/ME support (if possible)
- Multi-monitor support
- Drive selection for disk info

## Contact

Issues and pull requests welcome on GitHub!

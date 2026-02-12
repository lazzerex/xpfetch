# Makefile for xpfetch
# Compatible with MinGW on Windows or cross-compilation on Linux

# Compiler
CC = gcc

# Target executable
TARGET = xpfetch.exe

# Compiler flags for Windows XP compatibility
CFLAGS = -Wall -O2 -std=c89 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501
LDFLAGS = -static -s

# Source files
SRCS = src/main.c \
       src/console.c \
       src/sys_os.c \
       src/sys_kernel.c \
       src/sys_cpu.c \
       src/sys_gpu.c \
       src/sys_mem.c \
       src/sys_uptime.c \
       src/sys_shell.c \
       src/sys_disk.c \
       src/sys_display.c \
       src/sys_user.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)
	@echo Build complete: $(TARGET)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild

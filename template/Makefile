# efi.h project template - Clang, MinGW-w64 GCC, and MSVC toolchains
#
# This builds all the .c files of your application against efi.h headers. 
#
# Usage:
#   make TOOLCHAIN=clang     (default)
#   make TOOLCHAIN=gcc
#   make TOOLCHAIN=msvc      (shells out to msbuild - Windows only)
#   make clean
#
# Point LIBEFI_INC at wherever you're consuming efi.h from. 
# Both amalgamated efi.h and tree of all headers are supported.

TOOLCHAIN  ?= clang
LIBEFI_INC ?= ../

OUT      := app.efi
ENTRY    := EfiMain

# Every .c file in the current directory becomes its own object file -
# add subdirectories to this wildcard if your app's source isn't flat.
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.obj)

VCXPROJ  := sample.vcxproj
CONFIG   := Release
PLATFORM := x64

CFLAGS_COMMON := -ffreestanding -fshort-wchar -mno-red-zone -I$(LIBEFI_INC)

ifeq ($(TOOLCHAIN),msvc)
	$(OUT):
		msbuild $(VCXPROJ) /p:Configuration=$(CONFIG) /p:Platform=$(PLATFORM)

else ifeq ($(TOOLCHAIN),clang)
	CC      := clang
	LD      := lld-link
	CFLAGS  := -target x86_64-pc-windows-msvc $(CFLAGS_COMMON)
	LDFLAGS := /subsystem:efi_application /entry:$(ENTRY) /nodefaultlib /out:$(OUT)

	$(OUT): $(OBJS)
		$(LD) $(LDFLAGS) $(OBJS)

else ifeq ($(TOOLCHAIN),gcc)
	CC      := x86_64-w64-mingw32-gcc
	LD      := x86_64-w64-mingw32-ld
	CFLAGS  := $(CFLAGS_COMMON)
	LDFLAGS := --subsystem=10 -e$(ENTRY) -nostdlib -o $(OUT)

	$(OUT): $(OBJS)
		$(LD) $(LDFLAGS) $(OBJS)

else
	$(error Unknown TOOLCHAIN "$(TOOLCHAIN)" - use "clang", "gcc", or "msvc")
endif

.PHONY: all clean
all: $(OUT)

%.obj: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)

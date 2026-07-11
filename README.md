# efi.h

A simple header-only UEFI library written from-scratch directly against
the UEFI 2.11 specification. Built as a clean alternative to gnu-efi and EDK2
for developers who want a simple drag-and-drop UEFI application development experience, 
and also a native development experience on Visual Studio.

## Why not gnu-efi or EDK2?
- **EDK2** is a complete platform-firmware build system, not just a set of
  headers. Bringing it in for a single bootloader or UEFI application means
  inheriting its build tooling, package structure, and conventions whether
  you need them or not.
- **gnu-efi** targets GCC on Linux by default and has to fake the Microsoft
  x64 calling convention UEFI requires via `__attribute__((ms_abi))` and a
  historically ELF-to-PE object conversion step. On MSVC, none of that is
  necessary as MSVC already support compiling UEFI applications natively.
  It also has a build step for itself.

> An idiot admires complexity, a genius admires simplicity.
>
> *— Terry A. Davis*

## Specification coverage
 
Sections 2 through 13 of the UEFI 2.11 specification are implemented:
 
- Base types and data structures (Section 2)
- EFI System Table and Configuration Table (Section 4)
- Boot Services - events, images, memory, protocol handling, TPL (Section 7)
- Runtime Services - time, variables, capsules, reset (Section 8)
- Loaded Image Protocol (Section 9)
- Device Path Protocol (Section 10) 
- UEFI Driver Model (Section 11)
- Console Support - Simple Text Input/Output, Simple Pointer, Absolute
  Pointer, Serial I/O, Graphics Output Protocol (Section 12)
- Media Access - Simple File System, File Protocol, Block I/O, Disk I/O,
  and the rest of Section 13's device/media protocols

The remaining of the specification is to be added in next updates.

## Getting started
 
`efi.h` can simply be used by copying the header file(s), setting include path, and 
including `efi.h` on source files.
 
`efi.h` exists in two variants, one as a single amalgamated header 
(distributed in releases, or do-it-yourself with `amalgamation.c`) and as a main include
file of a tree of headers (located in root of this repository) to be used with this source tree
(`efi` folder and `efi.h` on source file)

### A minimal application

```c
#include "efi.h"
 
EFI_STATUS EFIAPI EfiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
	return EFI_SUCCESS;
}
```

A Visual Studio template project, Makefile that compiles all .c files in the folder 
and a sample .c file is given in the `template` folder.

## Toolchain support
 
- MSVC
- Clang (`-target x86_64-pc-windows-msvc`) 
- GCC (MinGW)

## TODO
 
- [ ] `Print()` and other convenience helpers
- [ ] Support for ARM, RISC-V and Itanium
- [ ] Remaining sections of UEFI Specification
- [ ] Better formatting for headers

## A note to UEFI Forum and Intel Corporation
 
A number of genuine errors exist in the UEFI 2.11 specification's own code
listings that genuinely ridicules the UEFI and make Intel engineers look like
a bunch of amateurs. Some examples:
 
- Forgotten comma (`,`) characters in parameter lists (i.e. at `EFI_SD_MMC_PASS_THRU_COMMAND_PACKET`)
- Forgotten semicolon (`;`) characters in struct definitions (i.e. at `_EFI_SD_MMC_PASS_THRU_PROTOCOL`) 
- Double backslash (`\\`) in multi-line preprocessor macros (i.e. `EFI_ADAPTER_INFO_CDAT_TYPE_GUID` or `EFI_RT_PROPERTIES_TABLE_GUID`)
- Stray backslash before star (`\*`) in function typedefs (i.e. `EFI_SET_STATE`)
- Typedefs using field names instead of actual typedef names in all Runtime Services (Section 8) (i.e. `typedef EFI_STATUS (EFIAPI *GetVariable)` instead of `typedef EFI_STATUS (EFIAPI *EFI_GET_VARIABLE)`)
while Boot Services (Section 7) and other sections having proper typedefs.
- Mismatched delimiters in `SMBIOS3_TABLE_GUID`'s macro body
- `EFI_ACPI_20_TABLE_GUID` defined twice with conflicting bodies
- A stray trailing `*` in the `ACPI_10_TABLE_GUID` alias
- `UNIT16` typo (should be `UINT16`) in `EFI_SD_MMC_COMMAND_BLOCK`
- Inconsistent use of the legacy `EFI_DEVICE_PATH` name alongside the correct
  `EFI_DEVICE_PATH_PROTOCOL` within the same `EFI_RAM_DISK_REGISTER_RAMDISK`
  function signature

UEFI Forum is not an open source organisation of 3 volunteers getting paid over donations, 
it is a whole oligarch of a Special Interest Group consisting of 
Intel, Microsoft, Apple, AMD, AMI, ARM Ltd. and many computer manufacturers. 
After seeing such an amount of errors on the official specification, 
it no longer surprises how UEFI adaptation took too long and still haven't fully completed, 
and why UEFI specification is stagnated ever since it's first introduction. 
I genuinely like UEFI, but I can't tell the same for it's severely broken management.

Even asides all the mistakes, the absence of a simple UEFI development library that would enable
individuals to develop UEFI applications until today in its own already proves that things are messed up on UEFI scene.

## License

This project is BSD licensed. See `LICENSE.txt` for more information.
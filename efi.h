#pragma once

#include "types.h"
#include "protocols.h"
#include "bootservices.h"
#include "runtimeservices.h"
#include "systemtable.h"

// The Entry Point prototype, first thing the developer would use...
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_ENTRY_POINT) (
  IN EFI_HANDLE                  ImageHandle,
  IN EFI_SYSTEM_TABLE            *SystemTable
  );

#ifdef _MSC_VER
#pragma comment(linker, "/ENTRY:EfiMain /MANIFEST:NO /DYNAMICBASE:NO")
#endif
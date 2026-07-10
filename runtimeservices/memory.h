#pragma once
#include "types.h"

#define EFI_OPTIONAL_PTR          0x00000001

typedef EFI_STATUS(EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP)(
	IN UINTN                 MemoryMapSize,
	IN UINTN                 DescriptorSize,
	IN UINT32                DescriptorVersion,
	IN EFI_MEMORY_DESCRIPTOR *VirtualMap
);

typedef EFI_STATUS(EFIAPI *EFI_CONVERT_POINTER)(
	IN UINTN             DebugDisposition,
	IN VOID              **Address
);
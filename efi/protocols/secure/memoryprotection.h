#pragma once
#include "efi/types.h"

// UEFI Spec Section 37.7
#define EFI_MEMORY_ATTRIBUTE_PROTOCOL_GUID {0xf4560cf6, 0x40ec, 0x4b4a, 0xa1, 0x92, 0xbf, 0x1d, 0x57, 0xd0, 0xb1, 0x89}

typedef struct _EFI_MEMORY_ATTRIBUTE_PROTOCOL EFI_MEMORY_ATTRIBUTE_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_GET_MEMORY_ATTRIBUTES)(
	IN EFI_MEMORY_ATTRIBUTE_PROTOCOL  *This,
	IN EFI_PHYSICAL_ADDRESS           BaseAddress,
	IN UINT64                         Length,
	OUT UINT64                        *Attributes
	);

typedef EFI_STATUS(EFIAPI *EFI_SET_MEMORY_ATTRIBUTES)(
	IN EFI_MEMORY_ATTRIBUTE_PROTOCOL  *This,
	IN EFI_PHYSICAL_ADDRESS           BaseAddress,
	IN UINT64                         Length,
	IN UINT64                         Attributes
	);

typedef EFI_STATUS(EFIAPI *EFI_CLEAR_MEMORY_ATTRIBUTES)(
	IN EFI_MEMORY_ATTRIBUTE_PROTOCOL  *This,
	IN EFI_PHYSICAL_ADDRESS           BaseAddress,
	IN UINT64                         Length,
	IN UINT64                         Attributes
	);

struct _EFI_MEMORY_ATTRIBUTE_PROTOCOL {
	EFI_GET_MEMORY_ATTRIBUTES          GetMemoryAttributes;
	EFI_SET_MEMORY_ATTRIBUTES          SetMemoryAttributes;
	EFI_CLEAR_MEMORY_ATTRIBUTES        ClearMemoryAttributes;
};
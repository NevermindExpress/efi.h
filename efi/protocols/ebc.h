#pragma once
#include "efi/types.h"
#include "efi/bootservices/memory.h"

// UEFI Spec Section 22.11

#define EFI_EBC_PROTOCOL_GUID {0x13ac6dd1,0x73d0,0x11d4,{0xb0,0x6b,0x00,0xaa,0x00,0xbd,0x6d,0xe7}}

typedef struct _EFI_EBC_PROTOCOL EFI_EBC_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_EBC_CREATE_THUNK) (
	IN EFI_EBC_PROTOCOL         *This,
	IN EFI_HANDLE               ImageHandle,
	IN VOID                     *EbcEntryPoint,
	OUT VOID                    **Thunk
	);

typedef EFI_STATUS(EFIAPI *EFI_EBC_UNLOAD_IMAGE) (
	IN EFI_EBC_PROTOCOL         *This,
	IN EFI_HANDLE               ImageHandle
	);

typedef EFI_STATUS(*EBC_ICACHE_FLUSH) (
	IN EFI_PHYSICAL_ADDRESS     Start,
	IN UINT64                   Length
	);

typedef EFI_STATUS(*EFI_EBC_REGISTER_ICACHE_FLUSH) (
	IN EFI_EBC_PROTOCOL **This,
	IN EBC_ICACHE_FLUSH *Flush
	);

typedef EFI_STATUS(*EFI_EBC_GET_VERSION) (
	IN EFI_EBC_PROTOCOL      *This,
	OUT UINT64               *Version
	);

struct _EFI_EBC_PROTOCOL {
	EFI_EBC_CREATE_THUNK           CreateThunk;
	EFI_EBC_UNLOAD_IMAGE           UnloadImage;
	EFI_EBC_REGISTER_ICACHE_FLUSH  RegisterICacheFlush;
	EFI_EBC_GET_VERSION            GetVersion;
};
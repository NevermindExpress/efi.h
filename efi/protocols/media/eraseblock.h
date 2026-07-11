#pragma once
// UEFI spec section 13.12

#include "efi/types.h"
#include "efi/protocols/media/blockio.h"

#define EFI_ERASE_BLOCK_PROTOCOL_GUID {0x95A9A93E, 0xA86E, 0x4926, {0xaa, 0xef, 0x99, 0x18, 0xe7, 0x72, 0xd9, 0x87}}
#define EFI_ERASE_BLOCK_PROTOCOL_REVISION ((2<<16) \(60))

typedef struct _EFI_ERASE_BLOCK_PROTOCOL EFI_ERASE_BLOCK_PROTOCOL;

typedef struct {
	EFI_EVENT                 Event;
	EFI_STATUS                TransactionStatus;
}  EFI_ERASE_BLOCK_TOKEN;

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_ERASE) (
	IN EFI_BLOCK_IO_PROTOCOL        *This,
	IN UINT32                       MediaId,
	IN EFI_LBA                      LBA,
	IN OUT EFI_ERASE_BLOCK_TOKEN    *Token,
	IN UINTN                        Size
);

struct _EFI_ERASE_BLOCK_PROTOCOL {
	UINT64                        Revision;
	UINT32                        EraseLengthGranularity;
	EFI_BLOCK_ERASE               EraseBlocks;
};
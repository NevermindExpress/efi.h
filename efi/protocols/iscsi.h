#pragma once
#include "efi/types.h"

// UEFI Spec Section 16.2

#define EFI_ISCSI_INITIATOR_NAME_PROTOCOL_GUID {0x59324945, 0xec44, 0x4c0d,{0xb1, 0xcd, 0x9d, 0xb1, 0x39, 0xdf, 0x07, 0x0c}}

typedef struct _EFI_ISCSI_INITIATOR_NAME_PROTOCOL EFI_ISCSI_INITIATOR_NAME_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_ISCSI_INITIATOR_NAME_GET) (
	IN EFI_ISCSI_INITIATOR_NAME_PROTOCOL    *This,
	IN OUT UINTN                            *BufferSize,
	OUT VOID                                *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_ISCSI_INITIATOR_NAME_SET) (
	IN EFI_ISCSI_INITIATOR_NAME_PROTOCOL       *This,
	IN OUT UINTN                               *BufferSize,
	IN VOID                                    *Buffer
	);

struct _EFI_ISCSI_INITIATOR_NAME_PROTOCOL {
	EFI_ISCSI_INITIATOR_NAME_GET                    Get;
	EFI_ISCSI_INITIATOR_NAME_SET                    Set;
};

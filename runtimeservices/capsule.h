#pragma once
#include "types.h"

typedef struct {
	EFI_GUID             CapsuleGuid;
	UINT32               HeaderSize;
	UINT32               Flags;
	UINT32               CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef struct {
	UINT64                           Length;
	union {
		EFI_PHYSICAL_ADDRESS          DataBlock;
		EFI_PHYSICAL_ADDRESS          ContinuationPointer;
	}Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct {
	UINT32                  CapsuleArrayNumber;
	VOID*                   CapsulePtr[1];
} EFI_CAPSULE_TABLE;

typedef EFI_STATUS(EFIAPI *EFI_UPDATE_CAPSULE)(
	IN EFI_CAPSULE_HEADER      **CapsuleHeaderArray,
	IN UINTN                   CapsuleCount,
	IN EFI_PHYSICAL_ADDRESS    ScatterGatherList OPTIONAL
);

typedef EFI_STATUS(EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES)(
	IN EFI_CAPSULE_HEADER         **CapsuleHeaderArray,
	IN UINTN                      CapsuleCount,
	OUT UINT64                    *MaximumCapsuleSize,
	OUT EFI_RESET_TYPE            *ResetType
);
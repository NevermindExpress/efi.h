#pragma once
#pragma once
// UEFI spec section 13.19

#include "efi/types.h"

#define EFI_NVDIMM_LABEL_PROTOCOL_GUID {0xd40b6b80,0x97d5,0x4282, {0xbb,0x1d,0x22,0x3a,0x16,0x91,0x80,0x58}}

typedef struct  _EFI_NVDIMM_LABEL_PROTOCOL EFI_NVDIMM_LABEL_PROTOCOL; 
 
typedef EFI_STATUS(EFIAPI *EFI_NVDIMM_LABEL_STORAGE_INFORMATION) (
	IN EFI_NVDIMM_LABEL_PROTOCOL             *This,
	OUT UINT32                               *SizeOfLabelStorageArea,
	OUT UINT32                               *MaxTransferLength
);

typedef EFI_STATUS(EFIAPI *EFI_NVDIMM_LABEL_STORAGE_READ) (
	IN CONST EFI_NVDIMM_LABEL_PROTOCOL         *This,
	IN UINT32                                  Offset,
	IN UINT32                                  TransferLength,
	OUT UINT8                                  *LabelData
);

typedef EFI_STATUS(EFIAPI *EFI_NVDIMM_LABEL_STORAGE_WRITE) (
	IN CONST EFI_NVDIMM_LABEL_PROTOCOL              *This,
	IN UINT32                                      Offset,
	IN UINT32                                      TransferLength,
	IN UINT8                                       *LabelData
);

struct  _EFI_NVDIMM_LABEL_PROTOCOL {
	EFI_NVDIMM_LABEL_STORAGE_INFORMATION   LabelStorageInformation;
	EFI_NVDIMM_LABEL_STORAGE_READ          LabelStorageRead;
	EFI_NVDIMM_LABEL_STORAGE_WRITE         LabelStorageWrite;
};
#pragma once
// UEFI spec section 13.20

#include "efi/types.h"

#define EFI_UFS_DEVICE_CONFIG_GUID { 0xb81bfab0, 0xeb3, 0x4cf9, { 0x84, 0x65, 0x7f, 0xa9, 0x86, 0x36, 0x16, 0x64}}

typedef struct  _EFI_UFS_DEVICE_CONFIG_PROTOCOL EFI_UFS_DEVICE_CONFIG_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_UFS_DEVICE_CONFIG_RW_DESCRIPTOR) (
	IN EFI_UFS_DEVICE_CONFIG_PROTOCOL                *This,
	IN BOOLEAN                                       Read,
	IN UINT8                                         DescId,
	IN UINT8                                         Index,
	IN UINT8                                         Selector,
	IN OUT UINT8                                     Descriptor,
	IN OUT UINT32                                    *DescSize
);

typedef EFI_STATUS(EFIAPI *EFI_UFS_DEVICE_CONFIG_RW_FLAG) (
	IN EFI_UFS_DEVICE_CONFIG_PROTOCOL         *This,
	IN BOOLEAN                                Read,
	IN UINT8                                  FlagId,
	IN OUT UINT8                              *Flag
);

typedef EFI_STATUS(EFIAPI *EFI_UFS_DEVICE_CONFIG_RW_ATTRIBUTE) (
	IN EFI_UFS_DEVICE_CONFIG_PROTOCOL            *This,
	IN BOOLEAN                                   Read,
	IN UINT8                                     AttrId,
	IN UINT8                                     Index,
	IN UINT8                                     Selector,
	IN OUT UINT8                                 *Attribute,
	IN OUT UINT32                                *AttrSize
);

struct  _EFI_UFS_DEVICE_CONFIG_PROTOCOL {
	EFI_UFS_DEVICE_CONFIG_RW_DESCRIPTOR        RwUfsDescriptor;
	EFI_UFS_DEVICE_CONFIG_RW_FLAG              RwUfsFlag;
	EFI_UFS_DEVICE_CONFIG_RW_ATTRIBUTE         RwUfsAttribute;
};
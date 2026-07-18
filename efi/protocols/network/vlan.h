#pragma once
#include "efi/types.h"

// UEFI Spec Section 27.1

#define EFI_VLAN_CONFIG_PROTOCOL_GUID {0x9e23d768, 0xd2f3, 0x4366, {0x9f, 0xc3, 0x3a, 0x7a, 0xba, 0x86, 0x43, 0x74}}

// EFI_VLAN_FIND_DATA
typedef struct {
	UINT16               VlanId;
	UINT8                Priority;
}   EFI_VLAN_FIND_DATA;

typedef struct _EFI_VLAN_CONFIG_PROTOCOL EFI_VLAN_CONFIG_PROTOCOL;

typedef EFI_STATUS(EFIAPI * EFI_VLAN_CONFIG_SET) (
	IN EFI_VLAN_CONFIG_PROTOCOL          *This,
	IN UINT16                            VlanId,
	IN UINT8                             Priority
	);

typedef EFI_STATUS(EFIAPI *EFI_VLAN_CONFIG_FIND) (
	IN EFI_VLAN_CONFIG_PROTOCOL          *This,
	IN UINT16                            *VlanId, OPTIONAL
	OUT UINT16                           *NumberOfVlan,
	OUT EFI_VLAN_FIND_DATA               **Entries
	);

typedef EFI_STATUS(EFIAPI * EFI_VLAN_CONFIG_REMOVE) (
	IN EFI_VLAN_CONFIG_PROTOCOL             *This,
	IN UINT16                               VlanId
	);

struct _EFI_VLAN_CONFIG_PROTOCOL {
	EFI_VLAN_CONFIG_SET               Set;
	EFI_VLAN_CONFIG_FIND              Find;
	EFI_VLAN_CONFIG_REMOVE            Remove;
};
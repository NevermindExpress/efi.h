#pragma once
#include "efi/types.h"

// UEFI Spec Section 24.2

#define EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_GUID {0x1ACED566, 0x76ED, 0x4218,{0xBC, 0x81, 0x76, 0x7F, 0x1F, 0x97, 0x7A, 0x89}}

//*******************************************************
// EFI_NETWORK_INTERFACE_TYPE
//*******************************************************
typedef enum {
	EfiNetworkInterfaceUndi = 1
} EFI_NETWORK_INTERFACE_TYPE;

#define EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_REVISION 0x00020000

typedef struct {
	UINT64       Revision;
	UINT64       Id;
	UINT64       ImageAddr;
	UINT32       ImageSize;
	CHAR8        StringId[4];
	UINT8        Type;
	UINT8        MajorVer;
	UINT8        MinorVer;
	BOOLEAN      Ipv6Supported;
	UINT16       IfNum;
} EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL;
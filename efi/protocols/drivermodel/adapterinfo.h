#pragma once
// UEFI 2.11 Spec 11.12:
#include "efi/types.h"

#define EFI_ADAPTER_INFORMATION_PROTOCOL_GUID { 0xE5DD1403, 0xD622, 0xC24E, { 0x84, 0x88, 0xC7, 0x1B, 0x17, 0xF5, 0xE8, 0x02 }}

typedef struct _EFI_ADAPTER_INFORMATION_PROTOCOL EFI_ADAPTER_INFORMATION_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_ADAPTER_INFO_GET_INFO) (
	IN   EFI_ADAPTER_INFORMATION_PROTOCOL          *This,
	IN   EFI_GUID                                  *InformationType,
	OUT   VOID                                     **InformationBlock,
	OUT   UINTN                                    *InformationBlockSize
	);

typedef EFI_STATUS(EFIAPI *EFI_ADAPTER_INFO_SET_INFO) (
	IN   EFI_ADAPTER_INFORMATION_PROTOCOL       *This,
	IN   EFI_GUID                               *InformationType,
	IN   VOID                                   *InformationBlock,
	IN   UINTN                                  InformationBlockSize
	);

typedef EFI_STATUS(EFIAPI *EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES) (
	IN   EFI_ADAPTER_INFORMATION_PROTOCOL         *This,
	OUT  EFI_GUID                                 **InfoTypesBuffer,
	OUT  UINTN                                    *InfoTypesBufferCount
	);

struct _EFI_ADAPTER_INFORMATION_PROTOCOL {
	EFI_ADAPTER_INFO_GET_INFO                    GetInformation;
	EFI_ADAPTER_INFO_SET_INFO                    SetInformation;
	EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES         GetSupportedTypes;
};

#define EFI_ADAPTER_INFO_MEDIA_STATE_GUID {0xD7C74207, 0xA831, 0x4A26 {0xB1,0xF5,0xD1,0x93,0x06,0x5C,0xE8,0xB6}}

typedef struct {
	EFI_STATUS                    MediaState;
} EFI_ADAPTER_INFO_MEDIA_STATE;

#define EFI_ADAPTER_INFO_NETWORK_BOOT_GUID {0x1FBD2960, 0x4130, 0x41E5,{0x94,0xAC,0xD2, 0xCF, 0x03, 0x7F, 0xB3, 0x7C}}

typedef struct {
	BOOLEAN                   iSsciIpv4BootCapablity;
	BOOLEAN                   iScsiIpv6BootCapablity;
	BOOLEAN                   FCoeBootCapablity;
	BOOLEAN                   OffloadCapability;
	BOOLEAN                   iScsiMpioCapability;
	BOOLEAN                   iScsiIpv4Boot;
	BOOLEAN                   iScsiIpv6Boot;
	BOOLEAN                   FCoeBoot;
} EFI_ADAPTER_INFO_NETWORK_BOOT;

#define EFI_ADAPTER_INFO_SAN_MAC_ADDRESS_GUID {0x114da5ef, 0x2cf1, 0x4e12,{0x9b, 0xbb, 0xc4, 0x70, 0xb5, 0x52, 0x05, 0xd9}}

typedef struct {
	EFI_MAC_ADDRESS                     SanMacAddress;
} EFI_ADAPTER_INFO_SAN_MAC_ADDRESS;

#define EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT_GUID { 0x4bd56be3, 0x4975, 0x4d8a, {0xa0, 0xad, 0xc4, 0x91, 0x20, 0x4b, 0x5d, 0x4d}}

typedef struct {
	BOOLEAN  Ipv6Support;
} EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT;

#define EFI_ADAPTER_INFO_MEDIA_TYPE_GUID { 0x8484472f, 0x71ec, 0x411a, { 0xb3, 0x9c, 0x62, 0xcd, 0x94, 0xd9, 0x91, 0x6e }}

typedef struct {
	UINT8 MediaType;
} EFI_ADAPTER_INFO_MEDIA_TYPE;

#define EFI_ADAPTER_INFO_CDAT_TYPE_GUID {0x77af24d1, 0xb6f0, 0x42b9, {0x83, 0xf5, 0x8f, 0xe6, 0xe8, 0x3e, 0xb6, 0xf0}}

typedef struct {
	UINTN CdatSize;
	UINT8 Cdat[];
} EFI_ADAPTER_INFO_CDAT_TYPE_TYPE;
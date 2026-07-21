#pragma once
#include "efi/types.h"

// UEFI Spec Section 31.1.4

#define EFI_REDFISH_DISCOVER_PROTOCOL_GUID {0x5db12509, 0x4550, 0x4347,{ 0x96, 0xb3, 0x73, 0xc0, 0xff, 0x6e, 0x86, 0x9f }}

// EFI_REDFISH_DISCOVER_FLAG
#define EFI_REDFISH_DISCOVER_HOST_INTERFACE        0x00000001
#define EFI_REDFISH_DISCOVER_SSDP                  0x00000002
#define EFI_REDFISH_DISCOVER_SSDP_UDP6             0x00000004
#define EFI_REDFISH_DISCOVER_KEEP_ALIVE            0x00000008
#define EFI_REDFISH_DISCOVER_RENEW                 0x00000010
#define EFI_REDFISH_DISCOVER_VALIDATION            0x80000000
#define EFI_REDFISH_DISCOVER_DURATION_MASK         0x0f000000
typedef UINT32 EFI_REDFISH_DISCOVER_FLAG;

// EFI_REDFISH_DISCOVER_NETWORK_INTERFACE
typedef struct {
	EFI_MAC_ADDRESS                MacAddress;
	BOOLEAN                        IsIpv6;
	EFI_IP_ADDRESS                 SubnetId;
	UINT8                          SubnetPrefixLength;
	UINT16                         VlanId;
} EFI_REDFISH_DISCOVER_NETWORK_INTERFACE;

// EFI_REDFISH_DISCOVERED_INFORMATION
typedef struct {
	EFI_HANDLE                  RedfishRestExHandle;
	BOOLEAN                     IsIPv6;
	EFI_IP_ADDRESS              RedfishHostIpAddress;
	UINT16                      RedfishVersion;
	CHAR16                      *Location;
	CHAR16                      *Uuid;
	CHAR16                      *Os;
	CHAR16                      *OsVersion;
	CHAR16                      *Product;
	CHAR16                      *ProductVersion;
	BOOLEAN                     UseHttps;
}   EFI_REDFISH_DISCOVERED_INFORMATION;

// EFI_REDFISH_DISCOVERED_INSTANCE
typedef struct {
	EFI_STATUS                              Status;
	EFI_REDFISH_DISCOVERED_INFORMATION      Information;
}   EFI_REDFISH_DISCOVERED_INSTANCE;

// EFI_REDFISH_DISCOVERED_LIST
typedef struct {
	UINTN                                NumberOfServiceFound;
	EFI_REDFISH_DISCOVERED_INSTANCE      *RedfishInstances;
}   EFI_REDFISH_DISCOVERED_LIST;

// EFI_REDFISH_DISCOVERED_TOKEN
#define REDFISH_DISCOVER_TOKEN_SIGNATURE SIGNATURE_32 ('R', 'F', 'T', 'S')
typedef struct {
	UINT32                         Signature;
	EFI_REDFISH_DISCOVERED_LIST    DiscoveredList;
	EFI_EVENT                      Event;
	UINTN                          Timeout;
}   EFI_REDFISH_DISCOVERED_TOKEN;

typedef struct _EFI_REDFISH_DISCOVER_PROTOCOL EFI_REDFISH_DISCOVER_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_REDFISH_DISCOVER_NETWORK_LIST)(
	IN EFI_REDFISH_DISCOVER_PROTOCOL              *This,
	IN EFI_HANDLE                                 ImageHandle,
	OUT UINTN                                     *NumberOfNetworkInterfaces,
	OUT EFI_REDFISH_DISCOVER_NETWORK_INTERFACE    **NetworkInterfaces
	);

typedef EFI_STATUS(EFIAPI *EFI_REDFISH_DISCOVER_ACQUIRE_SERVICE)(
	IN EFI_REDFISH_DISCOVER_PROTOCOL               *This,
	IN EFI_HANDLE                                  ImageHandle,
	IN EFI_REDFISH_DISCOVER_NETWORK_INTERFACE      *TargetNetworkInterface OPTIONAL,
	IN EFI_REDFISH_DISCOVER_FLAG                   Flags,
	IN EFI_REDFISH_DISCOVERED_TOKEN                *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_REDFISH_DISCOVER_ABORT_ACQUIRE)(
	IN EFI_REDFISH_DISCOVER_PROTOCOL              *This,
	IN EFI_REDFISH_DISCOVER_NETWORK_INTERFACE    *TargetNetworkInterface OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_REDFISH_DISCOVER_RELEASE_SERVICE)(
	IN    EFI_REDFISH_DISCOVER_PROTOCOL        *This,
	IN    EFI_REDFISH_DISCOVERED_LIST          *List
	);

struct _EFI_REDFISH_DISCOVER_PROTOCOL {
	EFI_REDFISH_DISCOVER_NETWORK_LIST               GetNetworkInterfaceList;
	EFI_REDFISH_DISCOVER_ACQUIRE_SERVICE            AcquireRedfishService;
	EFI_REDFISH_DISCOVER_ABORT_ACQUIRE              AbortAcquireRedfishService;
	EFI_REDFISH_DISCOVER_RELEASE_SERVICE            ReleaseRedfishService;
};
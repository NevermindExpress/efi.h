#pragma once
#include "efi/types.h"

// UEFI Spec Section 29.4
#define EFI_DNS4_SERVICE_BINDING_PROTOCOL_GUID { 0xb625b186, 0xe063, 0x44f7,{ 0x89, 0x5, 0x6a, 0x74, 0xdc, 0x6f, 0x52, 0xb4}}
#define EFI_DNS4_PROTOCOL_GUID { 0xae3d28cc, 0xe05b, 0x4fa1,{0xa0, 0x11, 0x7e, 0xb5, 0x5a, 0x3f, 0x14, 0x1 }}

// EFI_DNS4_CONFIG_DATA
typedef struct {
	UINTN              DnsServerListCount;
	EFI_IPv4_ADDRESS   *DnsServerList;
	BOOLEAN            UseDefaultSetting;
	BOOLEAN            EnableDnsCache;
	UINT8              Protocol;
	EFI_IPv4_ADDRESS   StationIp;
	EFI_IPv4_ADDRESS   SubnetMask;
	UINT16             LocalPort;
	UINT32             RetryCount;
	UINT32             RetryInterval;
}  EFI_DNS4_CONFIG_DATA;

// EFI_DNS4_CACHE_ENTRY
typedef struct {
	CHAR16               *HostName;
	EFI_IPv4_ADDRESS     *IpAddress;
	UINT32              Timeout;
}  EFI_DNS4_CACHE_ENTRY;

// EFI_DNS4_MODE_DATA
typedef struct {
	EFI_DNS4_CONFIG_DATA       DnsConfigData;
	UINT32                     DnsServerCount;
	EFI_IPv4_ADDRESS           *DnsServerList;
	UINT32                     DnsCacheCount;
	EFI_DNS4_CACHE_ENTRY       *DnsCacheList;
}  EFI_DNS4_MODE_DATA;

// DNS_ADDR_TO_HOST_DATA
typedef struct {
	CHAR16                *HostName;
}  DNS_ADDR_TO_HOST_DATA;

// DNS_HOST_TO_ADDR_DATA
typedef struct {
	UINT32             IpCount;
	EFI_IPv4_ADDRESS   *IpList;
}  DNS_HOST_TO_ADDR_DATA;

// DNS_RESOURCE_RECORD
typedef struct {
	CHAR8        *QName;
	UINT16       QType;
	UINT16       QClass;
	UINT32       TTL;
	UINT16       DataLength;
	CHAR8        *RData;
}  DNS_RESOURCE_RECORD;

// DNS_GENERAL_LOOKUP_DATA
typedef struct {
	UINTN                 RRCount;
	DNS_RESOURCE_RECORD  *RRList;
}   DNS_GENERAL_LOOKUP_DATA;

// EFI_DNS4_COMPLETION_TOKEN
typedef struct {
	EFI_EVENT                    Event;
	EFI_STATUS                   Status;
	UINT32                       RetryCount;
	UINT32                       RetryInterval;
	union {
		DNS_HOST_TO_ADDR_DATA      *H2AData;
		DNS_ADDR_TO_HOST_DATA      *A2HData;
		DNS_GENERAL_LOOKUP_DATA    *GLookupData;
	}  RspData;
}   EFI_DNS4_COMPLETION_TOKEN;

typedef struct _EFI_DNS4_PROTOCOL EFI_DNS4_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_DNS4_GET_MODE_DATA)(
	IN EFI_DNS4_PROTOCOL             *This,
	OUT EFI_DNS4_MODE_DATA           *DnsModeData
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS4_CONFIGURE)(
	IN EFI_DNS4_PROTOCOL         *This,
	IN EFI_DNS4_CONFIG_DATA      *DnsConfigData
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS4_HOST_NAME_TO_IP) (
	IN EFI_DNS4_PROTOCOL           *This,
	IN CHAR16                      *HostName,
	IN EFI_DNS4_COMPLETION_TOKEN   *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS4_IP_TO_HOST_NAME) (
	IN EFI_DNS4_PROTOCOL             *This,
	IN EFI_IPv4_ADDRESS              IpAddress,
	IN EFI_DNS4_COMPLETION_TOKEN     *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS4_GENERAL_LOOKUP) (
	IN EFI_DNS4_PROTOCOL             *This,
	IN CHAR8                         *QName,
	IN UINT16                        QType,
	IN UINT16                        QClass,
	IN EFI_DNS4_COMPLETION_TOKEN     *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS4_UPDATE_DNS_CACHE) (
	IN EFI_DNS4_PROTOCOL             *This,
	IN BOOLEAN                       DeleteFlag,
	IN BOOLEAN                       Override,
	IN EFI_DNS4_CACHE_ENTRY          DnsCacheEntry
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS4_POLL) (IN EFI_DNS4_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_DNS4_CANCEL) (
	IN EFI_DNS4_PROTOCOL             *This,
	IN EFI_DNS4_COMPLETION_TOKEN     *Token
	);

struct _EFI_DNS4_PROTOCOL {
	EFI_DNS4_GET_MODE_DATA       GetModeData;
	EFI_DNS4_CONFIGURE           Configure;
	EFI_DNS4_HOST_NAME_TO_IP     HostNameToIp;
	EFI_DNS4_IP_TO_HOST_NAME     IpToHostName;
	EFI_DNS4_GENERAL_LOOKUP      GeneralLookUp;
	EFI_DNS4_UPDATE_DNS_CACHE    UpdateDnsCache;
	EFI_DNS4_POLL                Poll;
	EFI_DNS4_CANCEL              Cancel;
};

// UEFI Spec Section 29.5
#define EFI_DNS6_SERVICE_BINDING_PROTOCOL_GUID { 0x7f1647c8, 0xb76e, 0x44b2,{ 0xa5, 0x65, 0xf7, 0xf, 0xf1, 0x9c, 0xd1, 0x9e}}
#define EFI_DNS6_PROTOCOL_GUID { 0xca37bc1f, 0xa327, 0x4ae9,{ 0x82, 0x8a, 0x8c, 0x40, 0xd8, 0x50, 0x6a, 0x17 }}

// EFI_DNS6_CONFIG_DATA
typedef struct {
	BOOLEAN              EnableDnsCache;
	UINT8                Protocol;
	EFI_IPv6_ADDRESS     StationIp;
	UINT16               LocalPort;
	UINT32               DnsServerCount;
	EFI_IPv6_ADDRESS     *DnsServerList;
	UINT32               RetryCount;
	UINT32               RetryInterval;
}  EFI_DNS6_CONFIG_DATA;

// EFI_DNS6_CACHE_ENTRY
typedef struct {
	CHAR16               *HostName;
	EFI_IPv6_ADDRESS     *IpAddress;
	UINT32               Timeout;
}  EFI_DNS6_CACHE_ENTRY;

// EFI_DNS6_MODE_DATA
typedef struct {
	EFI_DNS6_CONFIG_DATA         DnsConfigData;
	UINT32                       DnsServerCount;
	EFI_IPv6_ADDRESS             *DnsServerList;
	UINT32                       DnsCacheCount;
	EFI_DNS6_CACHE_ENTRY         *DnsCacheList;
}  EFI_DNS6_MODE_DATA;

// DNS6_HOST_TO_ADDR_DATA
typedef struct {
	UINT32                 IpCount;
	EFI_IPv6_ADDRESS       *IpList;
}  DNS6_HOST_TO_ADDR_DATA;

// DNS6_ADDR_TO_HOST_DATA
typedef struct {
	CHAR16                  *HostName;
}  DNS6_ADDR_TO_HOST_DATA;

// DNS6_RESOURCE_RECORD
typedef struct {
	CHAR8                  *QName;
	UINT16                 QType;
	UINT16                 QClass;
	UINT32                 TTL;
	UINT16                 DataLength;
	CHAR8                  *RData;
}   DNS6_RESOURCE_RECORD;

// DNS6_GENERAL_LOOKUP_DATA
typedef struct {
	UINTN                  RRCount;
	DNS6_RESOURCE_RECORD   *RRList;
}   DNS6_GENERAL_LOOKUP_DATA;

// EFI_DNS6_COMPLETION_TOKEN
typedef struct {
	EFI_EVENT                Event;
	EFI_STATUS               Status;
	UINT32                   RetryCount;
	UINT32                   RetryInterval;
	union {
		DNS6_HOST_TO_ADDR_DATA     *H2AData;
		DNS6_ADDR_TO_HOST_DATA     *A2HData;
		DNS6_GENERAL_LOOKUP_DATA   *GLookupData;
	} RspData;
}  EFI_DNS6_COMPLETION_TOKEN;

typedef struct _EFI_DNS6_PROTOCOL EFI_DNS6_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_DNS6_GET_MODE_DATA)(
	IN EFI_DNS6_PROTOCOL             *This,
	OUT EFI_DNS6_MODE_DATA           *DnsModeData
	);

typedef EFI_STATUS(EFIAPI * EFI_DNS6_CONFIGURE)(
	IN EFI_DNS6_PROTOCOL         *This,
	IN EFI_DNS6_CONFIG_DATA      *DnsConfigData
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS6_HOST_NAME_TO_IP) (
	IN EFI_DNS6_PROTOCOL             *This,
	IN CHAR16                        *HostName,
	IN EFI_DNS6_COMPLETION_TOKEN     *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS6_IP_TO_HOST_NAME) (
	IN EFI_DNS6_PROTOCOL               *This,
	IN EFI_IPv6_ADDRESS                IpAddress,
	IN EFI_DNS6_COMPLETION_TOKEN       *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS6_GENERAL_LOOKUP) (
	IN EFI_DNS6_PROTOCOL          *This,
	IN CHAR8                      *QName,
	IN UINT16                     QType,
	IN UINT16                     QClass,
	IN EFI_DNS6_COMPLETION_TOKEN  *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS6_UPDATE_DNS_CACHE) (
	IN EFI_DNS6_PROTOCOL               *This,
	IN BOOLEAN                         DeleteFlag,
	IN BOOLEAN                         Override,
	IN EFI_DNS6_CACHE_ENTRY            DnsCacheEntry
	);

typedef EFI_STATUS(EFIAPI *EFI_DNS6_POLL) (IN EFI_DNS6_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_DNS6_CANCEL) (
	IN EFI_DNS6_PROTOCOL               *This,
	IN EFI_DNS6_COMPLETION_TOKEN       *Token
	);

struct _EFI_DNS6_PROTOCOL {
	EFI_DNS6_GET_MODE_DATA       GetModeData;
	EFI_DNS6_CONFIGURE           Configure;
	EFI_DNS6_HOST_NAME_TO_IP     HostNameToIp;
	EFI_DNS6_IP_TO_HOST_NAME     IpToHostName;
	EFI_DNS6_GENERAL_LOOKUP      GeneralLookUp;
	EFI_DNS6_UPDATE_DNS_CACHE    UpdateDnsCache;
	EFI_DNS6_POLL                Poll;
	EFI_DNS6_CANCEL              Cancel;
};
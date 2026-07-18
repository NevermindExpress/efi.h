#pragma once
#include "efi/types.h"

// UEFI Spec Section 28.3
#define EFI_IP4_SERVICE_BINDING_PROTOCOL_GUID {0xc51711e7,0xb4bf,0x404a,{0xbf,0xb8,0x0a,0x04,0x8e,0xf1,0xff,0xe4}}
#define EFI_IP4_PROTOCOL_GUID {0x41d94cd2,0x35b6,0x455a,{0x82,0x58,0xd4,0xe5,0x13,0x34,0xaa,0xdd}}

// EFI_IP4_CONFIG_DATA
typedef struct {
	UINT8              DefaultProtocol;
	BOOLEAN            AcceptAnyProtocol;
	BOOLEAN            AcceptIcmpErrors;
	BOOLEAN            AcceptBroadcast;
	BOOLEAN            AcceptPromiscuous;
	BOOLEAN            UseDefaultAddress;
	EFI_IPv4_ADDRESS   StationAddress;
	EFI_IPv4_ADDRESS   SubnetMask;
	UINT8              TypeOfService;
	UINT8              TimeToLive;
	BOOLEAN            DoNotFragment;
	BOOLEAN            RawData;
	UINT32             ReceiveTimeout;
	UINT32             TransmitTimeout;
} EFI_IP4_CONFIG_DATA;

// EFI_IP4_ROUTE_TABLE
typedef struct {
	EFI_IPv4_ADDRESS        SubnetAddress;
	EFI_IPv4_ADDRESS        SubnetMask;
	EFI_IPv4_ADDRESS        GatewayAddress;
}   EFI_IP4_ROUTE_TABLE;

// EFI_IP4_ICMP_TYPE
typedef struct {
	UINT8        Type;
	UINT8        Code;
}   EFI_IP4_ICMP_TYPE;

// EFI_IP4_MODE_DATA
typedef struct {
	BOOLEAN               IsStarted;
	UINT32                MaxPacketSize;
	EFI_IP4_CONFIG_DATA   ConfigData;
	BOOLEAN               IsConfigured;
	UINT32                GroupCount;
	EFI_IPv4_ADDRESS      *GroupTable;
	UINT32                RouteCount;
	EFI_IP4_ROUTE_TABLE   RouteTable;
	UINT32                IcmpTypeCount;
	EFI_IP4_ICMP_TYPE     *IcmpTypeList;
}   EFI_IP4_MODE_DATA;

// EFI_IP4_HEADER
#pragma pack(1)
typedef struct {
	UINT8              HeaderLength : 4;
	UINT8              Version : 4;
	UINT8              TypeOfService;
	UINT16             TotalLength;
	UINT16             Identification;
	UINT16             Fragmentation;
	UINT8              TimeToLive;
	UINT8              Protocol;
	UINT16             Checksum;
	EFI_IPv4_ADDRESS   SourceAddress;
	EFI_IPv4_ADDRESS   DestinationAddress;
}   EFI_IP4_HEADER;
#pragma pack()

// EFI_IP4_FRAGMENT_DATA
typedef struct {
	UINT32                FragmentLength;
	VOID                  *FragmentBuffer;
}   EFI_IP4_FRAGMENT_DATA;

// EFI_IP4_OVERRIDE_DATA
typedef struct {
	EFI_IPv4_ADDRESS         SourceAddress;
	EFI_IPv4_ADDRESS         GatewayAddress;
	UINT8                    Protocol;
	UINT8                    TypeOfService;
	UINT8                    TimeToLive;
	BOOLEAN                  DoNotFragment;
}   EFI_IP4_OVERRIDE_DATA;

// EFI_IP4_TRANSMIT_DATA
typedef struct {
	EFI_IPv4_ADDRESS         DestinationAddress;
	EFI_IP4_OVERRIDE_DATA    *OverrideData;
	UINT32                   OptionsLength;
	VOID                     *OptionsBuffer;
	UINT32                   TotalDataLength;
	UINT32                   FragmentCount;
	EFI_IP4_FRAGMENT_DATA    FragmentTable[1];
}   EFI_IP4_TRANSMIT_DATA;

// EFI_IP4_RECEIVE_DATA
typedef struct {
	EFI_TIME              TimeStamp;
	EFI_EVENT             RecycleSignal;
	UINT32                HeaderLength;
	EFI_IP4_HEADER        *Header;
	UINT32                OptionsLength;
	VOID                  *Options;
	UINT32                DataLength;
	UINT32                FragmentCount;
	EFI_IP4_FRAGMENT_DATA FragmentTable[1];
}   EFI_IP4_RECEIVE_DATA;

// EFI_IP4_COMPLETION_TOKEN
typedef struct {
	EFI_EVENT                  Event;
	EFI_STATUS                 Status;
	union {
		EFI_IP4_RECEIVE_DATA     *RxData;
		EFI_IP4_TRANSMIT_DATA    *TxData;
	}              Packet;
} EFI_IP4_COMPLETION_TOKEN;

typedef struct _EFI_IP4_PROTOCOL EFI_IP4_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_IP4_GET_MODE_DATA) (
	IN EFI_IP4_PROTOCOL                  *This,
	OUT EFI_IP4_MODE_DATA                *Ip4ModeData OPTIONAL,
	OUT EFI_MANAGED_NETWORK_CONFIG_DATA  *MnpConfigData OPTIONAL,
	OUT EFI_SIMPLE_NETWORK_MODE          *SnpModeData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_CONFIGURE) (
	IN EFI_IP4_PROTOCOL         *This,
	IN EFI_IP4_CONFIG_DATA      *IpConfigData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_GROUPS) (
	IN EFI_IP4_PROTOCOL      *This,
	IN BOOLEAN               JoinFlag,
	IN EFI_IPv4_ADDRESS      *GroupAddress OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_ROUTES) (
	IN EFI_IP4_PROTOCOL      *This,
	IN BOOLEAN               DeleteRoute,
	IN EFI_IPv4_ADDRESS      *SubnetAddress,
	IN EFI_IPv4_ADDRESS      *SubnetMask,
	IN EFI_IPv4_ADDRESS      *GatewayAddress
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_TRANSMIT) (
	IN EFI_IP4_PROTOCOL            *This,
	IN EFI_IP4_COMPLETION_TOKEN    *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_RECEIVE) (
	IN EFI_IP4_PROTOCOL            *This,
	IN EFI_IP4_COMPLETION_TOKEN    *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_CANCEL)(
	IN EFI_IP4_PROTOCOL            *This,
	IN EFI_IP4_COMPLETION_TOKEN    *Token OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_POLL) (IN EFI_IP4_PROTOCOL *This);

struct _EFI_IP4_PROTOCOL {
	EFI_IP4_GET_MODE_DATA       GetModeData;
	EFI_IP4_CONFIGURE           Configure;
	EFI_IP4_GROUPS              Groups;
	EFI_IP4_ROUTES              Routes;
	EFI_IP4_TRANSMIT            Transmit;
	EFI_IP4_RECEIVE             Receive;
	EFI_IP4_CANCEL              Cancel;
	EFI_IP4_POLL                Poll;
};

// UEFI Spec Section 28.4
#define EFI_IP4_CONFIG2_PROTOCOL_GUID { 0x5b446ed1, 0xe30b, 0x4faa,{ 0x87, 0x1a, 0x36, 0x54, 0xec, 0xa3, 0x60, 0x80 }}

#define EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE 32

// EFI_IP4_CONFIG2_DATA_TYPE
typedef enum {
	Ip4Config2DataTypeInterfaceInfo,
	Ip4Config2DataTypePolicy,
	Ip4Config2DataTypeManualAddress,
	Ip4Config2DataTypeGateway,
	Ip4Config2DataTypeDnsServer,
	Ip4Config2DataTypeMaximum
} EFI_IP4_CONFIG2_DATA_TYPE;

// EFI_IP4_CONFIG2_INTERFACE_INFO
typedef struct {
	CHAR16                           Name[EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE];
	UINT8                            IfType;
	UINT32                           HwAddressSize;
	EFI_MAC_ADDRESS                  HwAddress;
	EFI_IPv4_ADDRESS                 StationAddress;
	EFI_IPv4_ADDRESS                 SubnetMask;
	UINT32                           RouteTableSize;
	EFI_IP4_ROUTE_TABLE              *RouteTable OPTIONAL;
}   EFI_IP4_CONFIG2_INTERFACE_INFO;

// EFI_IP4_CONFIG2_POLICY
typedef enum {
	Ip4Config2PolicyStatic,
	Ip4Config2PolicyDhcp,
	Ip4Config2PolicyMax
}   EFI_IP4_CONFIG2_POLICY;

// EFI_IP4_CONFIG2_MANUAL_ADDRESS
typedef struct {
	EFI_IPv4_ADDRESS       Address;
	EFI_IPv4_ADDRESS       SubnetMask;
}   EFI_IP4_CONFIG2_MANUAL_ADDRESS;

typedef struct _EFI_IP4_CONFIG2_PROTOCOL EFI_IP4_CONFIG2_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_IP4_CONFIG2_SET_DATA) (
	IN EFI_IP4_CONFIG2_PROTOCOL    *This,
	IN EFI_IP4_CONFIG2_DATA_TYPE   DataType,
	IN UINTN                       DataSize,
	IN VOID                        *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_CONFIG2_GET_DATA) (
	IN EFI_IP4_CONFIG2_PROTOCOL    *This,
	IN EFI_IP4_CONFIG2_DATA_TYPE   DataType,
	IN OUT UINTN                   *DataSize,
	IN VOID                        *Data OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_CONFIG2_REGISTER_NOTIFY) (
	IN EFI_IP4_CONFIG2_PROTOCOL       *This,
	IN EFI_IP4_CONFIG2_DATA_TYPE      DataType,
	IN EFI_EVENT                        Event
	);

typedef EFI_STATUS(EFIAPI *EFI_IP4_CONFIG2_UNREGISTER_NOTIFY) (
	IN EFI_IP4_CONFIG2_PROTOCOL          *This,
	IN EFI_IP4_CONFIG2_DATA_TYPE         DataType,
	IN EFI_EVENT                         Event
	);

struct _EFI_IP4_CONFIG2_PROTOCOL {
	EFI_IP4_CONFIG2_SET_DATA             SetData;
	EFI_IP4_CONFIG2_GET_DATA             GetData;
	EFI_IP4_CONFIG2_REGISTER_NOTIFY      RegisterDataNotify;
	EFI_IP4_CONFIG2_UNREGISTER_NOTIFY    UnregisterDataNotify;
};

// UEFI Spec Section 28.5
#define EFI_IP6_SERVICE_BINDING_PROTOCOL_GUID {0xec835dd3,0xfe0f,0x617b,{0xa6,0x21,0xb3,0x50,0xc3,0xe1,0x33,0x88}}
#define EFI_IP6_PROTOCOL_GUID {0x2c8759d5,0x5c2d,0x66ef,{0x92,0x5f,0xb6,0x6c,0x10,0x19,0x57,0xe2}}

// ICMPv6 type definitions for error messages
#define ICMP_V6_DEST_UNREACHABLE    0x1
#define ICMP_V6_PACKET_TOO_BIG      0x2
#define ICMP_V6_TIME_EXCEEDED       0x3
#define ICMP_V6_PARAMETER_PROBLEM   0x4

// ICMPv6 type definition for informational messages
#define ICMP_V6_ECHO_REQUEST        0x80
#define ICMP_V6_ECHO_REPLY          0x81
#define ICMP_V6_LISTENER_QUERY      0x82
#define ICMP_V6_LISTENER_REPORT     0x83
#define ICMP_V6_LISTENER_DONE       0x84
#define ICMP_V6_ROUTER_SOLICIT      0x85
#define ICMP_V6_ROUTER_ADVERTISE    0x86
#define ICMP_V6_NEIGHBOR_SOLICIT    0x87
#define ICMP_V6_NEIGHBOR_ADVERTISE  0x88
#define ICMP_V6_REDIRECT            0x89
#define ICMP_V6_LISTENER_REPORT_2   0x8F

// ICMPv6 code definitions for ICMP_V6_DEST_UNREACHABLE
#define ICMP_V6_NO_ROUTE_TO_DEST    0x0
#define ICMP_V6_COMM_PROHIBITED     0x1
#define ICMP_V6_BEYOND_SCOPE        0x2
#define ICMP_V6_ADDR_UNREACHABLE    0x3
#define ICMP_V6_PORT_UNREACHABLE    0x4
#define ICMP_V6_SOURCE_ADDR_FAILED  0x5
#define ICMP_V6_ROUTE_REJECTED      0x6

// ICMPv6 code definitions for ICMP_V6_TIME_EXCEEDED
#define ICMP_V6_TIMEOUT_HOP_LIMIT   0x0
#define ICMP_V6_TIMEOUT_REASSEMBLE  0x1

// ICMPv6 code definitions for ICMP_V6_PARAMETER_PROBLEM
#define ICMP_V6_ERRONEOUS_HEADER      0x0
#define ICMP_V6_UNRECOGNIZE_NEXT_HDR  0x1
#define ICMP_V6_UNRECOGNIZE_OPTION    0x2

// EFI_IP6_CONFIG_DATA
typedef struct {
	UINT8              DefaultProtocol;
	BOOLEAN            AcceptAnyProtocol;
	BOOLEAN            AcceptIcmpErrors;
	BOOLEAN            AcceptPromiscuous;
	EFI_IPv6_ADDRESS   DestinationAddress;
	EFI_IPv6_ADDRESS   StationAddress;
	UINT8              TrafficClass;
	UINT8              HopLimit;
	UINT32             FlowLabel;
	UINT32             ReceiveTimeout;
	UINT32             TransmitTimeout;
} EFI_IP6_CONFIG_DATA;

// EFI_IP6_ADDRESS_INFO
typedef struct {
	EFI_IPv6_ADDRESS      Address;
	UINT8                 PrefixLength;
}   EFI_IP6_ADDRESS_INFO;

// EFI_IP6_ROUTE_TABLE
typedef struct {
	EFI_IPv6_ADDRESS      Gateway;
	EFI_IPv6_ADDRESS      Destination;
	UINT8                 PrefixLength;
}   EFI_IP6_ROUTE_TABLE;

// EFI_IP6_NEIGHBOR_STATE
typedef enum {
	EfiNeighborInComplete,
	EfiNeighborReachable,
	EfiNeighborStale,
	EfiNeighborDelay,
	EfiNeighborProbe
}   EFI_IP6_NEIGHBOR_STATE;

// EFI_IP6_NEIGHBOR_CACHE
typedef struct {
	EFI_IPv6_ADDRESS         Neighbor;
	EFI_MAC_ADDRESS          LinkAddress;
	EFI_IP6_NEIGHBOR_STATE   State;
}   EFI_IP6_NEIGHBOR_CACHE;

// EFI_IP6_ICMP_TYPE
typedef struct {
	UINT8       Type;
	UINT8       Code;
}   EFI_IP6_ICMP_TYPE;

// EFI_IP6_MODE_DATA
typedef struct {
	BOOLEAN                  IsStarted;
	UINT32                   MaxPacketSize;
	EFI_IP6_CONFIG_DATA      ConfigData;
	BOOLEAN                  IsConfigured;
	UINT32                   AddressCount;
	EFI_IP6_ADDRESS_INFO     *AddressList;
	UINT32                   GroupCount;
	EFI_IPv6_ADDRESS         *GroupTable;
	UINT32                   RouteCount;
	EFI_IP6_ROUTE_TABLE      *RouteTable;
	UINT32                   NeighborCount;
	EFI_IP6_NEIGHBOR_CACHE   *NeighborCache;
	UINT32                   PrefixCount;
	EFI_IP6_ADDRESS_INFO     *PrefixTable;
	UINT32                   IcmpTypeCount;
	EFI_IP6_ICMP_TYPE        *IcmpTypeList;
}   EFI_IP6_MODE_DATA;

// EFI_IP6_HEADER
#pragma pack(push,1)
typedef struct _EFI_IP6_HEADER {
	UINT8                TrafficClassH : 4;
	UINT8                Version : 4;
	UINT8                FlowLabelH : 4;
	UINT8                TrafficClassL : 4;
	UINT16               FlowLabelL;
	UINT16               PayloadLength;
	UINT8                NextHeader;
	UINT8                HopLimit;
	EFI_IPv6_ADDRESS     SourceAddress;
	EFI_IPv6_ADDRESS     DestinationAddress;
} EFI_IP6_HEADER;
#pragma pack(pop)

// EFI_IP6_FRAGMENT_DATA
typedef struct _EFI_IP6_FRAGMENT_DATA {
	UINT32                   FragmentLength;
	VOID                     *FragmentBuffer;
}   EFI_IP6_FRAGMENT_DATA;

// EFI_IP6_OVERRIDE_DATA
typedef struct _EFI_IP6_OVERRIDE_DATA {
	UINT8        Protocol;
	UINT8        HopLimit;
	UINT32       FlowLabel;
}   EFI_IP6_OVERRIDE_DATA;

// EFI_IP6_TRANSMIT_DATA
typedef struct _EFI_IP6_TRANSMIT_DATA {
	EFI_IPv6_ADDRESS            DestinationAddress;
	EFI_IP6_OVERRIDE_DATA       *OverrideData;
	UINT32                      ExtHdrsLength;
	VOID                        *ExtHdrs;
	UINT8                       NextHeader;
	UINT32                      DataLength;
	UINT32                      FragmentCount;
	EFI_IP6_FRAGMENT_DATA       FragmentTable[1];
}   EFI_IP6_TRANSMIT_DATA;

// EFI_IP6_RECEIVE_DATA
typedef struct _EFI_IP6_RECEIVE_DATA {
	EFI_TIME                 TimeStamp;
	EFI_EVENT                RecycleSignal;
	UINT32                   HeaderLength;
	EFI_IP6_HEADER           *Header;
	UINT32                   DataLength;
	UINT32                   FragmentCount;
	EFI_IP6_FRAGMENT_DATA    FragmentTable[1];
}   EFI_IP6_RECEIVE_DATA;

// EFI_IP6_COMPLETION_TOKEN
typedef struct {
	EFI_EVENT                   Event;
	EFI_STATUS                  Status;
	union {
		EFI_IP6_RECEIVE_DATA      *RxData;
		EFI_IP6_TRANSMIT_DATA     *TxData;
	}             Packet;
} EFI_IP6_COMPLETION_TOKEN;

typedef struct _EFI_IP6_PROTOCOL EFI_IP6_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_IP6_GET_MODE_DATA) (
	IN EFI_IP6_PROTOCOL                    *This,
	OUT EFI_IP6_MODE_DATA                  *Ip6ModeData OPTIONAL,
	OUT EFI_MANAGED_NETWORK_CONFIG_DATA    *MnpConfigData OPTIONAL,
	OUT EFI_SIMPLE_NETWORK_MODE            *SnpModeData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_CONFIGURE) (
	IN EFI_IP6_PROTOCOL            *This,
	IN EFI_IP6_CONFIG_DATA         *Ip6ConfigData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_GROUPS) (
	IN EFI_IP6_PROTOCOL      *This,
	IN BOOLEAN               JoinFlag,
	IN EFI_IPv6_ADDRESS      *GroupAddress OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_ROUTES) (
	IN EFI_IP6_PROTOCOL         *This,
	IN BOOLEAN                  DeleteRoute,
	IN EFI_IPv6_ADDRESS         *Destination OPTIONAL,
	IN UINT8                    PrefixLength,
	IN EFI_IPv6_ADDRESS         *GatewayAddress OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_NEIGHBORS) (
	IN EFI_IP6_PROTOCOL            *This,
	IN BOOLEAN                     DeleteFlag,
	IN EFI_IPv6_ADDRESS            *TargetIp6Address,
	IN EFI_MAC_ADDRESS             *TargetLinkAddress OPTIONAL,
	IN UINT32                      Timeout,
	IN BOOLEAN                     Override
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_TRANSMIT) (
	IN EFI_IP6_PROTOCOL            *This,
	IN EFI_IP6_COMPLETION_TOKEN    *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_RECEIVE) (
	IN EFI_IP6_PROTOCOL            *This,
	IN EFI_IP6_COMPLETION_TOKEN    *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_CANCEL)(
	IN EFI_IP6_PROTOCOL            *This,
	IN EFI_IP6_COMPLETION_TOKEN    *Token OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_POLL) (IN EFI_IP6_PROTOCOL *This);

struct _EFI_IP6_PROTOCOL {
	EFI_IP6_GET_MODE_DATA    GetModeData;
	EFI_IP6_CONFIGURE        Configure;
	EFI_IP6_GROUPS           Groups;
	EFI_IP6_ROUTES           Routes;
	EFI_IP6_NEIGHBORS        Neighbors;
	EFI_IP6_TRANSMIT         Transmit;
	EFI_IP6_RECEIVE          Receive;
	EFI_IP6_CANCEL           Cancel;
	EFI_IP6_POLL             Poll;
};

// UEFI Spec Section 28.6
#define EFI_IP6_CONFIG_PROTOCOL_GUID {0x937fe521,0x95ae,0x4d1a,{0x89,0x29,0x48,0xbc,0xd9,0x0a,0xd3,0x1a}}

// EFI_IP6_CONFIG_POLICY
typedef enum {
	Ip6ConfigPolicyManual,
	Ip6ConfigPolicyAutomatic
}   EFI_IP6_CONFIG_POLICY;

// EFI_IP6_CONFIG_DATA_TYPE
typedef enum {
	Ip6ConfigDataTypeInterfaceInfo,
	Ip6ConfigDataTypeAltInterfaceId,
	Ip6ConfigDataTypePolicy,
	Ip6ConfigDataTypeDupAddrDetectTransmits,
	Ip6ConfigDataTypeManualAddress,
	Ip6ConfigDataTypeGateway,
	Ip6ConfigDataTypeDnsServer,
	Ip6ConfigDataTypeMaximum
}   EFI_IP6_CONFIG_DATA_TYPE;

// EFI_IP6_CONFIG_INTERFACE_INFO
typedef struct {
	CHAR16                Name[32];
	UINT8                 IfType;
	UINT32                HwAddressSize;
	EFI_MAC_ADDRESS       HwAddress;
	UINT32                AddressInfoCount;
	EFI_IP6_ADDRESS_INFO  *AddressInfo;
	UINT32                RouteCount;
	EFI_IP6_ROUTE_TABLE   *RouteTable;
}   EFI_IP6_CONFIG_INTERFACE_INFO;

// EFI_IP6_CONFIG_INTERFACE_ID
typedef struct {
	UINT8           Id[8];
}   EFI_IP6_CONFIG_INTERFACE_ID;

// EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS
typedef struct {
	UINT32             DupAddrDetectTransmits;
}   EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS;

// EFI_IP6_CONFIG_MANUAL_ADDRESS
typedef struct {
	EFI_IPv6_ADDRESS      Address;
	BOOLEAN               IsAnycast;
	UINT8                 PrefixLength;
}   EFI_IP6_CONFIG_MANUAL_ADDRESS;

typedef struct _EFI_IP6_CONFIG_PROTOCOL EFI_IP6_CONFIG_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_IP6_CONFIG_SET_DATA) (
	IN EFI_IP6_CONFIG_PROTOCOL        *This,
	IN EFI_IP6_CONFIG_DATA_TYPE       DataType,
	IN UINTN                          DataSize,
	IN VOID                           *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_CONFIG_GET_DATA) (
	IN EFI_IP6_CONFIG_PROTOCOL        *This,
	IN EFI_IP6_CONFIG_DATA_TYPE       DataType,
	IN OUT UINTN                      *DataSize,
	IN VOID                           *Data OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_CONFIG_REGISTER_NOTIFY) (
	IN EFI_IP6_CONFIG_PROTOCOL       *This,
	IN EFI_IP6_CONFIG_DATA_TYPE      DataType,
	IN EFI_EVENT                     Event
	);

typedef EFI_STATUS(EFIAPI *EFI_IP6_CONFIG_UNREGISTER_NOTIFY) (
	IN EFI_IP6_CONFIG_PROTOCOL              *This,
	IN EFI_IP6_CONFIG_DATA_TYPE             DataType,
	IN EFI_EVENT                            Event
	);

struct _EFI_IP6_CONFIG_PROTOCOL {
	EFI_IP6_CONFIG_SET_DATA           SetData;
	EFI_IP6_CONFIG_GET_DATA           GetData;
	EFI_IP6_CONFIG_REGISTER_NOTIFY     RegisterDataNotify;
	EFI_IP6_CONFIG_UNREGISTER_NOTIFY  UnregisterDataNotify;
};
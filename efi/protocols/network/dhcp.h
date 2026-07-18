#pragma once
#include "efi/types.h"

// UEFI Spec Section 29.2
#define EFI_DHCP4_SERVICE_BINDING_PROTOCOL_GUID {0x9d9a39d8,0xbd42,0x4a73,{0xa4,0xd5,0x8e,0xe9,0x4b,0xe1,0x13,0x80}}
#define EFI_DHCP4_PROTOCOL_GUID {0x8a219718,0x4ef5,0x4761,{0x91,0xc8,0xc0,0xf0,0x4b,0xda,0x9e,0x56}}

// EFI_DHCP4_STATE
typedef enum {
	Dhcp4Stopped = 0x0,
	Dhcp4Init = 0x1,
	Dhcp4Selecting = 0x2,
	Dhcp4Requesting = 0x3,
	Dhcp4Bound = 0x4,
	Dhcp4Renewing = 0x5,
	Dhcp4Rebinding = 0x6,
	Dhcp4InitReboot = 0x7,
	Dhcp4Rebooting = 0x8
}  EFI_DHCP4_STATE;

// EFI_DHCP4_EVENT
typedef enum {
	Dhcp4SendDiscover = 0x01,
	Dhcp4RcvdOffer = 0x02,
	Dhcp4SelectOffer = 0x03,
	Dhcp4SendRequest = 0x04,
	Dhcp4RcvdAck = 0x05,
	Dhcp4RcvdNak = 0x06,
	Dhcp4SendDecline = 0x07,
	Dhcp4BoundCompleted = 0x08,
	Dhcp4EnterRenewing = 0x09,
	Dhcp4EnterRebinding = 0x0a,
	Dhcp4AddressLost = 0x0b,
	Dhcp4Fail = 0x0c
}  EFI_DHCP4_EVENT;

// EFI_DHCP4_HEADER
#pragma pack(1)
typedef struct {
	UINT8              OpCode;
	UINT8              HwType;
	UINT8              HwAddrLen;
	UINT8              Hops;
	UINT32             Xid;
	UINT16             Seconds;
	UINT16             Reserved;
	EFI_IPv4_ADDRESS   ClientAddr;
	EFI_IPv4_ADDRESS   YourAddr;
	EFI_IPv4_ADDRESS   ServerAddr;
	EFI_IPv4_ADDRESS   GatewayAddr;
	UINT8              ClientHwAddr[16];
	CHAR8              ServerName[64];
	CHAR8              BootFileName[128];
}   EFI_DHCP4_HEADER;
#pragma pack()

// EFI_DHCP4_PACKET
#pragma pack(push,1)
typedef struct {
	UINT32               Size;
	UINT32               Length;
	struct {
		EFI_DHCP4_HEADER   Header;
		UINT32             Magik;
		UINT8              Option[1];
	}  Dhcp4;
} EFI_DHCP4_PACKET;
#pragma pack(pop)

typedef struct _EFI_DHCP4_CONFIG_DATA EFI_DHCP4_CONFIG_DATA;

// EFI_DHCP4_MODE_DATA
typedef struct _EFI_DHCP4_MODE_DATA EFI_DHCP4_MODE_DATA; 

typedef struct _EFI_DHCP4_PROTOCOL EFI_DHCP4_PROTOCOL;

// EFI_DHCP4_CALLBACK
typedef EFI_STATUS(*EFI_DHCP4_CALLBACK)(
  IN EFI_DHCP4_PROTOCOL    *This,
  IN VOID                  *Context,
  IN EFI_DHCP4_STATE       CurrentState,
  IN EFI_DHCP4_EVENT       Dhcp4Event,
  IN EFI_DHCP4_PACKET      *Packet, OPTIONAL
  OUT EFI_DHCP4_PACKET     **NewPacket OPTIONAL
  );

// EFI_DHCP4_PACKET_OPTION
#pragma pack(1)
typedef struct {
	UINT8      OpCode;
	UINT8      Length;
	UINT8      Data[1];
}  EFI_DHCP4_PACKET_OPTION;
#pragma pack()

// EFI_DHCP4_CONFIG_DATA
struct _EFI_DHCP4_CONFIG_DATA {
	UINT32                   DiscoverTryCount;
	UINT32                   *DiscoverTimeout;
	UINT32                   RequestTryCount;
	UINT32                   *RequestTimeout;
	EFI_IPv4_ADDRESS         ClientAddress;
	EFI_DHCP4_CALLBACK       Dhcp4Callback;
	VOID                     *CallbackContext;
	UINT32                   OptionCount;
	EFI_DHCP4_PACKET_OPTION  **OptionList;
};

typedef struct _EFI_DHCP4_MODE_DATA {
	EFI_DHCP4_STATE            State;
	EFI_DHCP4_CONFIG_DATA      ConfigData;
	EFI_IPv4_ADDRESS           ClientAddress;
	EFI_MAC_ADDRESS            ClientMacAddress;
	EFI_IPv4_ADDRESS           ServerAddress;
	EFI_IPv4_ADDRESS           RouterAddress;
	EFI_IPv4_ADDRESS           SubnetMask;
	UINT32                     LeaseTime;
	EFI_DHCP4_PACKET           *ReplyPacket;
} EFI_DHCP4_MODE_DATA;

typedef EFI_STATUS(EFIAPI *EFI_DHCP4_GET_MODE_DATA)(
	IN EFI_DHCP4_PROTOCOL            *This,
	OUT EFI_DHCP4_MODE_DATA*          Dhcp4ModeData
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP4_CONFIGURE) (
	IN EFI_DHCP4_PROTOCOL            *This,
	IN EFI_DHCP4_CONFIG_DATA         *Dhcp4CfgData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP4_START) (
	IN EFI_DHCP4_PROTOCOL        *This,
	IN EFI_EVENT                 CompletionEvent OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP4_RENEW_REBIND) (
	IN EFI_DHCP4_PROTOCOL          *This,
	IN BOOLEAN                     RebindRequest,
	IN EFI_EVENT                   CompletionEvent OPTIONAL
	);

// EFI_DHCP4_LISTEN_POINT
typedef struct {
	EFI_IPv4_ADDRESS       ListenAddress;
	EFI_IPv4_ADDRESS       SubnetMask;
	UINT16                 ListenPort;
}  EFI_DHCP4_LISTEN_POINT;

// EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN
typedef struct {
	EFI_STATUS                     Status;
	EFI_EVENT                      CompletionEvent;
	EFI_IPv4_ADDRESS               RemoteAddress;
	UINT16                         RemotePort;
	EFI_IPv4_ADDRESS               GatewayAddress;
	UINT32                         ListenPointCount;
	EFI_DHCP4_LISTEN_POINT         *ListenPoints;
	UINT32                         TimeoutValue;
	EFI_DHCP4_PACKET               *Packet;
	UINT32                         ResponseCount;
	EFI_DHCP4_PACKET               *ResponseList;
}  EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN;

typedef EFI_STATUS(EFIAPI *EFI_DHCP4_RELEASE) (IN EFI_DHCP4_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_DHCP4_STOP) (IN EFI_DHCP4_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_DHCP4_BUILD) (
	IN EFI_DHCP4_PROTOCOL        *This,
	IN EFI_DHCP4_PACKET          *SeedPacket,
	IN UINT32                    DeleteCount,
	IN UINT8                     *DeleteList OPTIONAL,
	IN UINT32                    AppendCount,
	IN EFI_DHCP4_PACKET_OPTION   *AppendList[] OPTIONAL,
	OUT EFI_DHCP4_PACKET         **NewPacket
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP4_TRANSMIT_RECEIVE) (
	IN EFI_DHCP4_PROTOCOL                  *This,
	IN EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN    *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP4_PARSE) (
	IN EFI_DHCP4_PROTOCOL            *This,
	IN EFI_DHCP4_PACKET              *Packet,
	IN OUT UINT32                    *OptionCount,
	IN OUT EFI_DHCP4_PACKET_OPTION   *PacketOptionList[] OPTIONAL
	);

struct _EFI_DHCP4_PROTOCOL {
	EFI_DHCP4_GET_MODE_DATA        GetModeData;
	EFI_DHCP4_CONFIGURE            Configure;
	EFI_DHCP4_START                Start;
	EFI_DHCP4_RENEW_REBIND         RenewRebind;
	EFI_DHCP4_RELEASE              Release;
	EFI_DHCP4_STOP                 Stop;
	EFI_DHCP4_BUILD                Build;
	EFI_DHCP4_TRANSMIT_RECEIVE     TransmitReceive;
	EFI_DHCP4_PARSE                Parse;
};

// UEFI Spec Section 29.3
#define EFI_DHCP6_SERVICE_BINDING_PROTOCOL_GUID {0x9fb9a8a1,0x2f4a,0x43a6,{0x88,0x9c,0xd0,0xf7,0xb6,0xc4,0x7a,0xd5}}
#define EFI_DHCP6_PROTOCOL_GUID {0x87c8bad7,0x595,0x4053,{0x82,0x97,0xde,0xde,0x39,0x5f,0x5d,0x5b}}

#define EFI_DHCP6_IA_TYPE_NA 3
#define EFI_DHCP6_IA_TYPE_TA 4

// EFI_DHCP6_STATE
typedef enum {
	Dhcp6Init = 0x0,
	Dhcp6Selecting = 0x1,
	Dhcp6Requesting = 0x2,
	Dhcp6Declining = 0x3,
	Dhcp6Confirming = 0x4,
	Dhcp6Releasing = 0x5,
	Dhcp6Bound = 0x6,
	Dhcp6Renewing = 0x7,
	Dhcp6Rebinding = 0x8
}  EFI_DHCP6_STATE;

// EFI_DHCP6_EVENT
typedef enum {
	Dhcp6SendSolicit = 0x0,
	Dhcp6RcvdAdvertise = 0x1,
	Dhcp6SelectAdvertise = 0x2,
	Dhcp6SendRequest = 0x3,
	Dhcp6RcvdReply = 0x4,
	Dhcp6RcvdReconfigure = 0x5,
	Dhcp6SendDecline = 0x6,
	Dhcp6SendConfirm = 0x7,
	Dhcp6SendRelease = 0x8,
	Dhcp6SendRenew = 0x9,
	Dhcp6SendRebind = 0xa
}  EFI_DHCP6_EVENT;

// EFI_DHCP6_DUID
typedef struct {
	UINT16       Length;
	UINT8        Duid[1];
}  EFI_DHCP6_DUID;

// EFI_DHCP6_IA_DESCRIPTOR
typedef struct {
	UINT16           Type;
	UINT32           IaId;
}  EFI_DHCP6_IA_DESCRIPTOR;

// EFI_DHCP6_IA_ADDRESS
typedef struct {
	EFI_IPv6_ADDRESS       IpAddress;
	UINT32                 PreferredLifetime;
	UINT32                 ValidLifetime;
}  EFI_DHCP6_IA_ADDRESS;

// EFI_DHCP6_HEADER
#pragma pack(1)
typedef struct {
	UINT32         TransactionId : 24;
	UINT32         MessageType : 8;
}  EFI_DHCP6_HEADER;
#pragma pack()

// EFI_DHCP6_PACKET
#pragma pack(1)
typedef struct {
	UINT32               Size;
	UINT32               Length;
	struct {
		EFI_DHCP6_HEADER   Header;
		UINT8              Option[1];
	} Dhcp6;
} EFI_DHCP6_PACKET;
#pragma pack()

// EFI_DHCP6_IA
typedef struct {
	EFI_DHCP6_IA_DESCRIPTOR        Descriptor;
	EFI_DHCP6_STATE                State;
	EFI_DHCP6_PACKET              *ReplyPacket;
	UINT32                         IaAddressCount;
	EFI_DHCP6_IA_ADDRESS           IaAddress[1];
}  EFI_DHCP6_IA;

// EFI_DHCP6_MODE_DATA
typedef struct {
	EFI_DHCP6_DUID         *ClientId;
	EFI_DHCP6_IA           *Ia;
}  EFI_DHCP6_MODE_DATA;

typedef struct _EFI_DHCP6_PROTOCOL EFI_DHCP6_PROTOCOL;

// EFI_DHCP6_CALLBACK
typedef EFI_STATUS(EFIAPI *EFI_DHCP6_CALLBACK)(
  IN EFI_DHCP6_PROTOCOL      *This,
  IN VOID                    *Context,
  IN EFI_DHCP6_STATE         CurrentState,
  IN EFI_DHCP6_EVENT         Dhcp6Event,
  IN EFI_DHCP6_PACKET        *Packet,
  OUT EFI_DHCP6_PACKET       **NewPacket OPTIONAL
  );

// EFI_DHCP6_PACKET_OPTION
#pragma pack(1)
typedef struct {
	UINT16         OpCode;
	UINT16         OpLen;
	UINT8          Data[1];
}  EFI_DHCP6_PACKET_OPTION;
#pragma pack()

// EFI_DHCP6_RETRANSMISSION
typedef struct {
	UINT32     Irt;
	UINT32     Mrc;
	UINT32     Mrt;
	UINT32     Mrd;
}  EFI_DHCP6_RETRANSMISSION;

// EFI_DHCP6_CONFIG_DATA
typedef struct {
	EFI_DHCP6_CALLBACK         Dhcp6Callback;
	VOID                       *CallbackContext;
	UINT32                     OptionCount;
	EFI_DHCP6_PACKET_OPTION    **OptionList;
	EFI_DHCP6_IA_DESCRIPTOR    IaDescriptor;
	EFI_EVENT                  IaInfoEvent;
	BOOLEAN                    ReconfigureAccept;
	BOOLEAN                    RapidCommit;
	EFI_DHCP6_RETRANSMISSION   *SolicitRetransmission;
}  EFI_DHCP6_CONFIG_DATA;

// EFI_DHCP6_CALLBACK
typedef EFI_STATUS(EFIAPI *EFI_DHCP6_INFO_CALLBACK)(
	IN EFI_DHCP6_PROTOCOL      *This,
	IN VOID                    *Context,
	IN EFI_DHCP6_PACKET        *Packet
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP6_GET_MODE_DATA)(
	IN EFI_DHCP6_PROTOCOL        *This,
	OUT EFI_DHCP6_MODE_DATA      *Dhcp6ModeData OPTIONAL,
	OUT EFI_DHCP6_CONFIG_DATA    *Dhcp6ConfigData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP6_CONFIGURE) (
	IN EFI_DHCP6_PROTOCOL        *This,
	IN EFI_DHCP6_CONFIG_DATA     *Dhcp6CfgData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP6_START) (IN EFI_DHCP6_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_DHCP6_INFO_REQUEST) (
	IN EFI_DHCP6_PROTOCOL          *This,
	IN BOOLEAN                     SendClientId,
	IN EFI_DHCP6_PACKET_OPTION     *OptionRequest,
	IN UINT32                      OptionCount,
	IN EFI_DHCP6_PACKET_OPTION     *OptionList[] OPTIONAL,
	IN EFI_DHCP6_RETRANSMISSION    *Retransmission,
	IN EFI_EVENT                   TimeoutEvent OPTIONAL,
	IN EFI_DHCP6_INFO_CALLBACK     ReplyCallback,
	IN VOID                        *CallbackContext OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP6_RENEW_REBIND) (
	IN EFI_DHCP6_PROTOCOL          *This,
	IN BOOLEAN                     RebindRequest
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP6_DECLINE) (
	IN EFI_DHCP6_PROTOCOL        *This,
	IN UINT32                    AddressCount,
	IN EFI_IPv6_ADDRESS          *Addresses
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP6_RELEASE) (
	IN EFI_DHCP6_PROTOCOL            *This,
	IN UINT32                        AddressCount,
	IN EFI_IPv6_ADDRESS              *Addresses
	);

typedef EFI_STATUS(EFIAPI *EFI_DHCP6_STOP) (IN EFI_DHCP6_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_DHCP6_PARSE) (
	IN EFI_DHCP6_PROTOCOL        *This,
	IN EFI_DHCP6_PACKET          *Packet,
	IN OUT UINT32                *OptionCount,
	IN EFI_DHCP6_PACKET_OPTION   *PacketOptionList[] OPTIONAL
	);

struct _EFI_DHCP6_PROTOCOL {
	EFI_DHCP6_GET_MODE_DATA    GetModeData;
	EFI_DHCP6_CONFIGURE        Configure;
	EFI_DHCP6_START            Start;
	EFI_DHCP6_INFO_REQUEST     InfoRequest;
	EFI_DHCP6_RENEW_REBIND     RenewRebind;
	EFI_DHCP6_DECLINE          Decline;
	EFI_DHCP6_RELEASE          Release;
	EFI_DHCP6_STOP             Stop;
	EFI_DHCP6_PARSE            Parse;
};
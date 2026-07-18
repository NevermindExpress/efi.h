#pragma once
#include "efi/types.h"

// UEFI Spec Section 28.7

#define EFI_IPSEC_CONFIG_PROTOCOL_GUID {0xce5e5929,0xc7a3,0x4602,{0xad,0x9e,0xc9,0xda,0xf9,0x4e,0xbf,0xcf}}

#define MAX_PEERID_LEN 128

// EFI_IPSEC_CONFIG_DATA_TYPE
typedef enum {
	IPsecConfigDataTypeSpd,
	IPsecConfigDataTypeSad,
	IPsecConfigDataTypePad,
	IPsecConfigDataTypeMaximum
}   EFI_IPSEC_CONFIG_DATA_TYPE;

// EFI_IPSEC_AUTH_PROTOCOL
typedef enum {
	EfiIPsecAuthProtocolIKEv1,
	EfiIPsecAuthProtocolIKEv2,
	EfiIPsecAuthProtocolMaximum
}   EFI_IPSEC_AUTH_PROTOCOL_TYPE;

// EFI_IPSEC_AUTH_METHOD
typedef enum {
	EfiIPsecAuthMethodPreSharedSecret,
	EfiIPsecAuthMethodCertificates,
	EfiIPsecAuthMethodMaximum
}   EFI_IPSEC_AUTH_METHOD;

// EFI_IP_ADDRESS_INFO
typedef struct _EFI_IP_ADDRESS_INFO {
	EFI_IP_ADDRESS                      Address;
	UINT8                               PrefixLength;
}   EFI_IP_ADDRESS_INFO;

// EFI_IPSEC_SPD_SELECTOR
typedef struct _EFI_IPSEC_SPD_SELECTOR {
	UINT32                              LocalAddressCount;
	EFI_IP_ADDRESS_INFO                 *LocalAddress;
	UINT32                              RemoteAddressCount;
	EFI_IP_ADDRESS_INFO                 *RemoteAddress;
	UINT16                              NextLayerProtocol;

	// Several additional selectors depend on the ProtoFamily
	UINT16                               LocalPort;
	UINT16                               LocalPortRange;
	UINT16                               RemotePort;
	UINT16                               RemotePortRange;
}   EFI_IPSEC_SPD_SELECTOR;

// EFI_IPSEC_TRAFFIC_DIR
typedef enum {
	EfiIPsecInBound,
	EfiIPsecOutBound
} EFI_IPSEC_TRAFFIC_DIR;

// EFI_IPSEC_ACTION
typedef enum {
	EfiIPsecActionDiscard,
	EfiIPsecActionBypass,
	EfiIPsecActionProtect
}   EFI_IPSEC_ACTION;

// EFI_IPSEC_SA_LIFETIME
typedef struct _EFI_IPSEC_SA_LIFETIME {
	UINT64                   ByteCount;
	UINT64                   SoftLifetime;
	UINT64                   HardLifetime;
}   EFI_IPSEC_SA_LIFETIME;

// EFI_IPSEC_MODE
typedef enum {
	EfiIPsecTransport,
	EfiIPsecTunnel
}   EFI_IPSEC_MODE;

typedef enum {
	EfiIPsecTunnelClearDf,
	EfiIPsecTunnelSetDf,
	EfiIPsecTunnelCopyDf
}   EFI_IPSEC_TUNNEL_DF_OPTION;

// EFI_IPSEC_TUNNEL_OPTION
typedef struct _EFI_IPSEC_TUNNEL_OPTION {
	EFI_IP_ADDRESS              LocalTunnelAddress;
	EFI_IP_ADDRESS              RemoteTunnelAddress;
	EFI_IPSEC_TUNNEL_DF_OPTION  DF;
}   EFI_IPSEC_TUNNEL_OPTION;

// EFI_IPSEC_PROTOCOL_TYPE
typedef enum {
	EfiIPsecAH,
	EfiIPsecESP
}   EFI_IPSEC_PROTOCOL_TYPE;

// EFI_IPSEC_PROCESS_POLICY
typedef struct _EFI_IPSEC_PROCESS_POLICY {
	BOOLEAN                     ExtSeqNum;
	BOOLEAN                     SeqOverflow;
	BOOLEAN                     FragCheck;
	EFI_IPSEC_SA_LIFETIME       SaLifetime;
	EFI_IPSEC_MODE              Mode;
	EFI_IPSEC_TUNNEL_OPTION     *TunnelOption;
	EFI_IPSEC_PROTOCOL_TYPE     Proto;
	UINT8                       AuthAlgoId;
	UINT8                       EncAlgoId;
} EFI_IPSEC_PROCESS_POLICY;

// EFI_IPSEC_SA_ID
typedef struct _EFI_IPSEC_SA_ID {
	UINT32                         Spi;
	EFI_IPSEC_PROTOCOL_TYPE        Proto;
	EFI_IP_ADDRESS                 DestAddress;
}   EFI_IPSEC_SA_ID;

// EFI_IPSEC_SPD_DATA
typedef struct _EFI_IPSEC_SPD_DATA {
	UINT8                                *Name[MAX_PEERID_LEN];
	UINT32                               PackageFlag;
	EFI_IPSEC_TRAFFIC_DIR                TrafficDirection;
	EFI_IPSEC_ACTION                     Action;
	EFI_IPSEC_PROCESS_POLICY             *ProcessingPolicy;
	UINTN                                SaIdCount;
	EFI_IPSEC_SA_ID                      *SaId[1];
}   EFI_IPSEC_SPD_DATA;

// EFI_IPSEC_ESP_ALGO_INFO
typedef struct _EFI_IPSEC_ESP_ALGO_INFO {
	UINT8                 EncAlgoId;
	UINTN                 EncKeyLength;
	VOID                  *EncKey;
	UINT8                 AuthAlgoId;
	UINTN                 AuthKeyLength;
	VOID                  *AuthKey;
}   EFI_IPSEC_ESP_ALGO_INFO;

// EFI_IPSEC_AH_ALGO_INFO
typedef struct _EFI_IPSEC_AH_ALGO_INFO {
	UINT8                 AuthAlgoId;
	UINTN                 KeyLength;
	VOID                  *Key;
}   EFI_IPSEC_AH_ALGO_INFO;


// EFI_IPSEC_ALGO_INFO
typedef union {
	EFI_IPSEC_AH_ALGO_INFO               AhAlgoInfo;
	EFI_IPSEC_ESP_ALGO_INFO              EspAlgoInfo;
}   EFI_IPSEC_ALGO_INFO;
// EFI_IPSEC_SA_DATA2

typedef struct _EFI_IPSEC_SA_DATA2 {
	EFI_IPSEC_MODE                 Mode;
	UINT64                         SNCount;
	UINT8                          AntiReplayWindows;
	EFI_IPSEC_ALGO_INFO            AlgoInfo;
	EFI_IPSEC_SA_LIFETIME          SaLifetime;
	UINT32                         PathMTU;
	EFI_IPSEC_SPD_SELECTOR         *SpdSelector;
	BOOLEAN                        ManualSet;
	EFI_IP_ADDRESS                 TunnelSourceAddress;
	EFI_IP_ADDRESS                 TunnelDestinationAddress;
} EFI_IPSEC_SA_DATA2;

// EFI_IPSEC_SA_DATA
typedef struct _EFI_IPSEC_SA_DATA {
	EFI_IPSEC_MODE                 Mode;
	UINT64                         SNCount;
	UINT8                          AntiReplayWindows;
	EFI_IPSEC_ALGO_INFO            AlgoInfo;
	EFI_IPSEC_SA_LIFETIME          SaLifetime;
	UINT32                         PathMTU;
	EFI_IPSEC_SPD_SELECTOR         *SpdSelector;
	BOOLEAN                        ManualSet;
} EFI_IPSEC_SA_DATA;

// EFI_IPSEC_PAD_ID
typedef struct _EFI_IPSEC_PAD_ID {
	BOOLEAN                 PeerIdValid;
	union {
		EFI_IP_ADDRESS_INFO   IpAddress;
		UINT8                 PeerId[MAX_PEERID_LEN];
	} Id;
} EFI_IPSEC_PAD_ID;

// EFI_IPSEC_CONFIG_SELECTOR
typedef union {
	EFI_IPSEC_SPD_SELECTOR             SpdSelector;
	EFI_IPSEC_SA_ID                    SaId;
	EFI_IPSEC_PAD_ID                   PadId;
}   EFI_IPSEC_CONFIG_SELECTOR;

// EFI_IPSEC_PAD_DATA
typedef struct _EFI_IPSEC_PAD_DATA {
	EFI_IPSEC_AUTH_PROTOCOL_TYPE      AuthProtocol;
	EFI_IPSEC_AUTH_METHOD             AuthMethod;
	BOOLEAN                           IkeIdFlag;
	UINTN                             AuthDataSize;
	VOID                              *AuthData;
	UINTN                             RevocationDataSize;
	VOID                              *RevocationData;
}   EFI_IPSEC_PAD_DATA;

typedef struct _EFI_IPSEC_CONFIG_PROTOCOL EFI_IPSEC_CONFIG_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_IPSEC_CONFIG_SET_DATA) (
	IN EFI_IPSEC_CONFIG_PROTOCOL         *This,
	IN EFI_IPSEC_CONFIG_DATA_TYPE        DataType,
	IN EFI_IPSEC_CONFIG_SELECTOR         *Selector,
	IN VOID                              *Data,
	IN EFI_IPSEC_CONFIG_SELECTOR         *InsertBefore OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_IPSEC_CONFIG_GET_DATA) (
	IN EFI_IPSEC_CONFIG_PROTOCOL         *This,
	IN EFI_IPSEC_CONFIG_DATA_TYPE        DataType,
	IN EFI_IPSEC_CONFIG_SELECTOR         *Selector,
	IN OUT UINTN                         *DataSize,
	OUT VOID                             *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_IPSEC_CONFIG_GET_NEXT_SELECTOR) (
	IN EFI_IPSEC_CONFIG_PROTOCOL            *This,
	IN EFI_IPSEC_CONFIG_DATA_TYPE           DataType,
	IN OUT UINTN                            *SelectorSize,
	IN OUT EFI_IPSEC_CONFIG_SELECTOR        *Selector
	);

typedef EFI_STATUS(EFIAPI *EFI_IPSEC_CONFIG_REGISTER_NOTIFY) (
	IN EFI_IPSEC_CONFIG_PROTOCOL         *This,
	IN EFI_IPSEC_CONFIG_DATA_TYPE        DataType,
	IN EFI_EVENT                         Event
	);

typedef EFI_STATUS(EFIAPI *EFI_IPSEC_CONFIG_UNREGISTER_NOTIFY) (
	IN EFI_IPSEC_CONFIG_PROTOCOL           *This,
	IN EFI_IPSEC_CONFIG_DATA_TYPE          DataType,
	IN EFI_EVENT                           Event
	);

struct _EFI_IPSEC_CONFIG_PROTOCOL {
	EFI_IPSEC_CONFIG_SET_DATA               SetData;
	EFI_IPSEC_CONFIG_GET_DATA               GetData;
	EFI_IPSEC_CONFIG_GET_NEXT_SELECTOR      GetNextSelector;
	EFI_IPSEC_CONFIG_REGISTER_NOTIFY        RegisterDataNotify;
	EFI_IPSEC_CONFIG_UNREGISTER_NOTIFY      UnregisterDataNotify;
};

#define EFI_IPSEC_PROTOCOL_GUID {0xdfb386f7,0xe100,0x43ad,{0x9c,0x9a,0xed,0x90,0xd0,0x8a,0x5e,0x12 }}

// EFI_IPSEC_FRAGMENT_DATA
typedef struct _EFI_IPSEC_FRAGMENT_DATA {
	UINT32                FragmentLength;
	VOID                  *FragmentBuffer;
}   EFI_IPSEC_FRAGMENT_DATA;

typedef struct _EFI_IPSEC_PROTOCOL EFI_IPSEC_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_IPSEC_PROCESS) (
	IN EFI_IPSEC_PROTOCOL          *This,
	IN EFI_HANDLE                  NicHandle,
	IN UINT8                       IpVer,
	IN OUT VOID                    *IpHead,
	IN UINT8                       *LastHead,
	IN VOID                        *OptionsBuffer,
	IN UINT32                      OptionsLength,
	IN OUT EFI_IPSEC_FRAGMENT_DATA **FragmentTable,
	IN UINT32                      *FragmentCount,
	IN EFI_IPSEC_TRAFFIC_DIR       TrafficDirection,
	OUT EFI_EVENT                  *RecycleSignal
	);

struct _EFI_IPSEC_PROTOCOL {
	EFI_IPSEC_PROCESS           Process;
	EFI_EVENT                   DisabledEvent;
	BOOLEAN                     DisabledFlag;
};

#define EFI_IPSEC2_PROTOCOL_GUID {0xa3979e64, 0xace8, 0x4ddc, {0xbc, 0x07, 0x4d, 0x66, 0xb8, 0xfd, 0x09, 0x77}};

typedef struct _EFI_IPSEC2_PROTOCOL EFI_IPSEC2_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_IPSEC_PROCESSEXT) (
	IN EFI_IPSEC2_PROTOCOL           *This,
	IN EFI_HANDLE                    NicHandle,
	IN UINT8                         IpVer,
	IN OUT VOID                      *IpHead,
	IN OUT UINT8                     *LastHead,
	IN OUT VOID                      **OptionsBuffer,
	IN OUT UINT32                    *OptionsLength,
	IN OUT EFI_IPSEC_FRAGMENT_DATA   **FragmentTable,
	IN OUT UINT32                    *FragmentCount,
	IN EFI_IPSEC_TRAFFIC_DIR         TrafficDirection,
	OUT EFI_EVENT                    *RecycleSignal
	);

struct _EFI_IPSEC2_PROTOCOL {
	EFI_IPSEC_PROCESSEXT        ProcessExt;
	EFI_EVENT                   DisabledEvent;
	BOOLEAN                     DisabledFlag;
};
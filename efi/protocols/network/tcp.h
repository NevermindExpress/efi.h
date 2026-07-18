#pragma once
#include "efi/types.h"
#include "efi/protocols/network/snp.h"
#include "efi/protocols/network/managed.h"
#include "efi/protocols/network/ip.h"

// UEFI Spec Section 28.1

#define EFI_TCP4_SERVICE_BINDING_PROTOCOL_GUID {0x00720665,0x67EB,0x4a99,{0xBA,0xF7,0xD3,0xC3,0x3A,0x1C,0x7C,0xC9}}
#define EFI_TCP4_PROTOCOL_GUID {0x65530BC7,0xA359,0x410f,{0xB0,0x10,0x5A,0xAD,0xC7,0xEC,0x2B,0x62}}

// TCP4 Token Status definition
#define EFI_CONNECTION_FIN EFIERR      (104)
#define EFI_CONNECTION_RESET EFIERR    (105)
#define EFI_CONNECTION_REFUSED EFIERR  (106)

// EFI_TCP4_CONNECTION_STATE
typedef enum {
	Tcp4StateClosed = 0,
	Tcp4StateListen = 1,
	Tcp4StateSynSent = 2,
	Tcp4StateSynReceived = 3,
	Tcp4StateEstablished = 4,
	Tcp4StateFinWait1 = 5,
	Tcp4StateFinWait2 = 6,
	Tcp4StateClosing = 7,
	Tcp4StateTimeWait = 8,
	Tcp4StateCloseWait = 9,
	Tcp4StateLastAck = 10
}   EFI_TCP4_CONNECTION_STATE;

typedef struct {
	BOOLEAN               UseDefaultAddress;
	EFI_IPv4_ADDRESS      StationAddress;
	EFI_IPv4_ADDRESS      SubnetMask;
	UINT16                StationPort;
	EFI_IPv4_ADDRESS      RemoteAddress;
	UINT16                RemotePort;
	BOOLEAN               ActiveFlag;
}   EFI_TCP4_ACCESS_POINT;

typedef struct {
	UINT32             ReceiveBufferSize;
	UINT32             SendBufferSize;
	UINT32             MaxSynBackLog;
	UINT32             ConnectionTimeout;
	UINT32             DataRetries;
	UINT32             FinTimeout;
	UINT32             TimeWaitTimeout;
	UINT32             KeepAliveProbes;
	UINT32             KeepAliveTime;
	UINT32             KeepAliveInterval;
	BOOLEAN            EnableNagle;
	BOOLEAN            EnableTimeStamp;
	BOOLEAN            EnableWindowScaling;
	BOOLEAN            EnableSelectiveAck;
	BOOLEAN            EnablePathMtuDiscovery;
}   EFI_TCP4_OPTION;

// EFI_TCP4_CONFIG_DATA
typedef struct {
	// Receiving Filters
	// I/O parameters
	UINT8                    TypeOfService;
	UINT8                    TimeToLive;

	// Access Point
	EFI_TCP4_ACCESS_POINT    AccessPoint;

	// TCP Control Options
	EFI_TCP4_OPTION          ControlOption;

}   EFI_TCP4_CONFIG_DATA;

// EFI_TCP4_COMPLETION_TOKEN
typedef struct {
	EFI_EVENT                Event;
	EFI_STATUS               Status;
}   EFI_TCP4_COMPLETION_TOKEN;

// EFI_TCP4_CONNECTION_TOKEN
typedef struct {
	EFI_TCP4_COMPLETION_TOKEN      CompletionToken;
}   EFI_TCP4_CONNECTION_TOKEN;

// EFI_TCP4_LISTEN_TOKEN
typedef struct {
	EFI_TCP4_COMPLETION_TOKEN      CompletionToken;
	EFI_HANDLE                     NewChildHandle;
}   EFI_TCP4_LISTEN_TOKEN;

// EFI_TCP4_FRAGMENT_DATA
typedef struct {
	UINT32                FragmentLength;
	VOID                  *FragmentBuffer;
}   EFI_TCP4_FRAGMENT_DATA;

// EFI_TCP4_RECEIVE_DATA
typedef struct {
	BOOLEAN                    UrgentFlag;
	UINT32                     DataLength;
	UINT32                     FragmentCount;
	EFI_TCP4_FRAGMENT_DATA     FragmentTable[1];
}   EFI_TCP4_RECEIVE_DATA;

// EFI_TCP4_TRANSMIT_DATA
typedef struct {
	BOOLEAN                     Push;
	BOOLEAN                     Urgent;
	UINT32                      DataLength;
	UINT32                      FragmentCount;
	EFI_TCP4_FRAGMENT_DATA      FragmentTable[1];
}   EFI_TCP4_TRANSMIT_DATA;

// EFI_TCP4_IO_TOKEN
typedef struct {
	EFI_TCP4_COMPLETION_TOKEN    CompletionToken;
	union {
		EFI_TCP4_RECEIVE_DATA      *RxData;
		EFI_TCP4_TRANSMIT_DATA     *TxData;
	}                Packet;
} EFI_TCP4_IO_TOKEN;

// EFI_TCP4_CLOSE_TOKEN
typedef struct {
	EFI_TCP4_COMPLETION_TOKEN         CompletionToken;
	BOOLEAN                           AbortOnClose;
}   EFI_TCP4_CLOSE_TOKEN;

typedef struct _EFI_TCP4_PROTOCOL EFI_TCP4_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_TCP4_GET_MODE_DATA) (
	IN EFI_TCP4_PROTOCOL                 *This,
	OUT EFI_TCP4_CONNECTION_STATE        *Tcp4State OPTIONAL,
	OUT EFI_TCP4_CONFIG_DATA             *Tcp4ConfigData OPTIONAL,
	OUT EFI_IP4_MODE_DATA               *Ip4ModeData OPTIONAL,
	OUT EFI_MANAGED_NETWORK_CONFIG_DATA  *MnpConfigData OPTIONAL,
	OUT EFI_SIMPLE_NETWORK_MODE          *SnpModeData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP4_CONFIGURE) (
	IN EFI_TCP4_PROTOCOL           *This,
	IN EFI_TCP4_CONFIG_DATA        *TcpConfigData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP4_ROUTES) (
	IN EFI_TCP4_PROTOCOL  *This,
	IN BOOLEAN            DeleteRoute,
	IN EFI_IPv4_ADDRESS   *SubnetAddress,
	IN EFI_IPv4_ADDRESS   *SubnetMask,
	IN EFI_IPv4_ADDRESS   *GatewayAddress
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP4_CONNECT) (
	IN EFI_TCP4_PROTOCOL           *This,
	IN EFI_TCP4_CONNECTION_TOKEN   *ConnectionToken
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP4_ACCEPT) (
	IN EFI_TCP4_PROTOCOL        *This,
	IN EFI_TCP4_LISTEN_TOKEN    *ListenToken
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP4_TRANSMIT) (
	IN EFI_TCP4_PROTOCOL        *This,
	IN EFI_TCP4_IO_TOKEN        *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP4_RECEIVE) (
	IN EFI_TCP4_PROTOCOL        *This,
	IN EFI_TCP4_IO_TOKEN        *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP4_CLOSE)(
	IN EFI_TCP4_PROTOCOL             *This,
	IN EFI_TCP4_CLOSE_TOKEN          *CloseToken
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP4_CANCEL)(
	IN EFI_TCP4_PROTOCOL              *This,
	IN EFI_TCP4_COMPLETION_TOKEN      *Token OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP4_POLL) (IN EFI_TCP4_PROTOCOL *This);

struct _EFI_TCP4_PROTOCOL {
	EFI_TCP4_GET_MODE_DATA         GetModeData;
	EFI_TCP4_CONFIGURE             Configure;
	EFI_TCP4_ROUTES                Routes;
	EFI_TCP4_CONNECT               Connect;
	EFI_TCP4_ACCEPT                Accept;
	EFI_TCP4_TRANSMIT              Transmit;
	EFI_TCP4_RECEIVE               Receive;
	EFI_TCP4_CLOSE                 Close;
	EFI_TCP4_CANCEL                Cancel;
	EFI_TCP4_POLL                  Poll;
};

// UEFI Spec Section 28.2
#define EFI_TCP6_SERVICE_BINDING_PROTOCOL_GUID {0xec20eb79,0x6c1a,0x4664,{0x9a,0x0d,0xd2,0xe4,0xcc,0x16,0xd6, 0x64}}
#define EFI_TCP6_PROTOCOL_GUID {0x46e44855,0xbd60,0x4ab7,{0xab,0x0d,0xa6,0x79,0xb9,0x44,0x7d,0x77}}

typedef enum {
	Tcp6StateClosed = 0,
	Tcp6StateListen = 1,
	Tcp6StateSynSent = 2,
	Tcp6StateSynReceived = 3,
	Tcp6StateEstablished = 4,
	Tcp6StateFinWait1 = 5,
	Tcp6StateFinWait2 = 6,
	Tcp6StateClosing = 7,
	Tcp6StateTimeWait = 8,
	Tcp6StateCloseWait = 9,
	Tcp6StateLastAck = 10
}   EFI_TCP6_CONNECTION_STATE;

typedef struct {
	EFI_IPv6_ADDRESS         StationAddress;
	UINT16                   StationPort;
	EFI_IPv6_ADDRESS         RemoteAddress;
	UINT16                   RemotePort;
	BOOLEAN                  ActiveFlag;
}   EFI_TCP6_ACCESS_POINT;

// EFI_TCP6_OPTION
typedef struct {
	UINT32         ReceiveBufferSize;
	UINT32         SendBufferSize;
	UINT32         MaxSynBackLog;
	UINT32         ConnectionTimeout;
	UINT32         DataRetries;
	UINT32         FinTimeout;
	UINT32         TimeWaitTimeout;
	UINT32         KeepAliveProbes;
	UINT32         KeepAliveTime;
	UINT32         KeepAliveInterval;
	BOOLEAN        EnableNagle;
	BOOLEAN        EnableTimeStamp;
	BOOLEAN        EnableWindowScaling;
	BOOLEAN        EnableSelectiveAck;
	BOOLEAN        EnablePathMtuDiscovery;
}   EFI_TCP6_OPTION;

// EFI_TCP6_CONFIG_DATA
typedef struct {
	UINT8                    TrafficClass;
	UINT8                    HopLimit;
	EFI_TCP6_ACCESS_POINT    AccessPoint;
	EFI_TCP6_OPTION          *ControlOption;
}   EFI_TCP6_CONFIG_DATA;

// EFI_TCP6_COMPLETION_TOKEN
typedef struct {
	EFI_EVENT          Event;
	EFI_STATUS         Status;
}   EFI_TCP6_COMPLETION_TOKEN;

// EFI_TCP6_CONNECTION_TOKEN
typedef struct {
	EFI_TCP6_COMPLETION_TOKEN         CompletionToken;
}   EFI_TCP6_CONNECTION_TOKEN;

// EFI_TCP6_LISTEN_TOKEN
typedef struct {
	EFI_TCP6_COMPLETION_TOKEN      CompletionToken;
	EFI_HANDLE                     NewChildHandle;
}   EFI_TCP6_LISTEN_TOKEN;

// EFI_TCP6_FRAGMENT_DATA
typedef struct {
	UINT32             FragmentLength;
	VOID               *FragmentBuffer;
}   EFI_TCP6_FRAGMENT_DATA;

// EFI_TCP6_RECEIVE_DATA
typedef struct {
	BOOLEAN                  UrgentFlag;
	UINT32                   DataLength;
	UINT32                   FragmentCount;
	EFI_TCP6_FRAGMENT_DATA   FragmentTable[1];
}   EFI_TCP6_RECEIVE_DATA;

// EFI_TCP6_TRANSMIT_DATA
typedef struct {
	BOOLEAN                  Push;
	BOOLEAN                  Urgent;
	UINT32                   DataLength;
	UINT32                   FragmentCount;
	EFI_TCP6_FRAGMENT_DATA   FragmentTable[1];
}   EFI_TCP6_TRANSMIT_DATA;

// EFI_TCP6_IO_TOKEN
typedef struct {
	EFI_TCP6_COMPLETION_TOKEN     CompletionToken;
	union {
		EFI_TCP6_RECEIVE_DATA       *RxData;
		EFI_TCP6_TRANSMIT_DATA      *TxData;
	}                Packet;
}   EFI_TCP6_IO_TOKEN;

// EFI_TCP6_CLOSE_TOKEN
typedef struct {
	EFI_TCP6_COMPLETION_TOKEN   CompletionToken;
	BOOLEAN                     AbortOnClose;
}   EFI_TCP6_CLOSE_TOKEN;

typedef struct _EFI_TCP6_PROTOCOL EFI_TCP6_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_TCP6_GET_MODE_DATA) (
	IN EFI_TCP6_PROTOCOL                 *This,
	OUT EFI_TCP6_CONNECTION_STATE        *Tcp6State OPTIONAL,
	OUT EFI_TCP6_CONFIG_DATA             *Tcp6ConfigData OPTIONAL,
	OUT EFI_IP6_MODE_DATA               *Ip6ModeData OPTIONAL,
	OUT EFI_MANAGED_NETWORK_CONFIG_DATA  *MnpConfigData OPTIONAL,
	OUT EFI_SIMPLE_NETWORK_MODE          *SnpModeData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP6_CONFIGURE) (
	IN EFI_TCP6_PROTOCOL        *This,
	IN EFI_TCP6_CONFIG_DATA     *Tcp6ConfigData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP6_CONNECT) (
	IN EFI_TCP6_PROTOCOL              *This,
	IN EFI_TCP6_CONNECTION_TOKEN      *ConnectionToken
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP6_ACCEPT) (
	IN EFI_TCP6_PROTOCOL          *This,
	IN EFI_TCP6_LISTEN_TOKEN      *ListenToken
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP6_TRANSMIT) (
	IN EFI_TCP6_PROTOCOL           *This,
	IN EFI_TCP6_IO_TOKEN           *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP6_RECEIVE) (
	IN EFI_TCP6_PROTOCOL        *This,
	IN EFI_TCP6_IO_TOKEN        *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP6_CLOSE)(
	IN EFI_TCP6_PROTOCOL              *This,
	IN EFI_TCP6_CLOSE_TOKEN           *CloseToken
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP6_CANCEL)(
	IN EFI_TCP6_PROTOCOL              *This,
	IN EFI_TCP6_COMPLETION_TOKEN      *Token OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_TCP6_POLL) (IN EFI_TCP6_PROTOCOL *This);

struct _EFI_TCP6_PROTOCOL {
	EFI_TCP6_GET_MODE_DATA      GetModeData;
	EFI_TCP6_CONFIGURE          Configure;
	EFI_TCP6_CONNECT            Connect;
	EFI_TCP6_ACCEPT             Accept;
	EFI_TCP6_TRANSMIT           Transmit;
	EFI_TCP6_RECEIVE            Receive;
	EFI_TCP6_CLOSE              Close;
	EFI_TCP6_CANCEL             Cancel;
	EFI_TCP6_POLL               Poll;
};
#pragma once
#include "efi/types.h"

// UEFI Spec Section 24.1

#define EFI_SIMPLE_NETWORK_PROTOCOL_GUID {0xA19832B9,0xAC25,0x11D3,{0x9A,0x2D,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define EFI_SIMPLE_NETWORK_PROTOCOL_REVISION 0x00010000

//*******************************************************
// Bit Mask Values for ReceiveFilterSetting.
//
// Note that all other bit values are reserved.
//*******************************************************
#define EFI_SIMPLE_NETWORK_RECEIVE_UNICAST               0x01
#define EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST             0x02
#define EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST             0x04
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS           0x08
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST 0x10

// MAX_MCAST_FILTER_CNT
#define MAX_MCAST_FILTER_CNT                             16

//*******************************************************
// Interrupt Bit Mask Settings for InterruptStatus.
// Note that all other bit values are reserved.
//*******************************************************
#define EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT    0x01
#define EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT   0x02
#define EFI_SIMPLE_NETWORK_COMMAND_INTERRUPT    0x04
#define EFI_SIMPLE_NETWORK_SOFTWARE_INTERRUPT   0x08

// EFI_SIMPLE_NETWORK_STATE
typedef enum {
	EfiSimpleNetworkStopped,
	EfiSimpleNetworkStarted,
	EfiSimpleNetworkInitialized,
	EfiSimpleNetworkMaxState
} EFI_SIMPLE_NETWORK_STATE;

//******************************************************
// EFI_SIMPLE_NETWORK_MODE
//
// Note that the fields in this data structure are read-only
// and are updated by the code that produces the
// EFI_SIMPLE_NETWORK_PROTOCOL
// functions. All these fields must be discovered
// in a protocol instance of
// EFI_DRIVER_BINDING_PROTOCOL.Start().
//******************************************************
typedef struct {
	UINT32             State;
	UINT32             HwAddressSize;
	UINT32             MediaHeaderSize;
	UINT32             MaxPacketSize;
	UINT32             NvRamSize;
	UINT32             NvRamAccessSize;
	UINT32             ReceiveFilterMask;
	UINT32             ReceiveFilterSetting;
	UINT32             MaxMCastFilterCount;
	UINT32             MCastFilterCount;
	EFI_MAC_ADDRESS    MCastFilter[MAX_MCAST_FILTER_CNT];
	EFI_MAC_ADDRESS    CurrentAddress;
	EFI_MAC_ADDRESS    BroadcastAddress;
	EFI_MAC_ADDRESS    PermanentAddress;
	UINT8              IfType;
	BOOLEAN            MacAddressChangeable;
	BOOLEAN            MultipleTxSupported;
	BOOLEAN            MediaPresentSupported;
	BOOLEAN            MediaPresent;
}   EFI_SIMPLE_NETWORK_MODE;

//*******************************************************
// EFI_NETWORK_STATISTICS
//
// Any statistic value that is -1 is not available
// on the device and is to be ignored.
//*******************************************************
typedef struct {
	UINT64     RxTotalFrames;
	UINT64     RxGoodFrames;
	UINT64     RxUndersizeFrames;
	UINT64     RxOversizeFrames;
	UINT64     RxDroppedFrames;
	UINT64     RxUnicastFrames;
	UINT64     RxBroadcastFrames;
	UINT64     RxMulticastFrames;
	UINT64     RxCrcErrorFrames;
	UINT64     RxTotalBytes;
	UINT64     TxTotalFrames;
	UINT64     TxGoodFrames;
	UINT64     TxUndersizeFrames;
	UINT64     TxOversizeFrames;
	UINT64     TxDroppedFrames;
	UINT64     TxUnicastFrames;
	UINT64     TxBroadcastFrames;
	UINT64     TxMulticastFrames;
	UINT64     TxCrcErrorFrames;
	UINT64     TxTotalBytes;
	UINT64     Collisions;
	UINT64     UnsupportedProtocol;
	UINT64     RxDuplicatedFrames;
	UINT64     RxDecryptErrorFrames;
	UINT64     TxErrorFrames;
	UINT64     TxRetryFrames;
}   EFI_NETWORK_STATISTICS;

typedef struct _EFI_SIMPLE_NETWORK_PROTOCOL EFI_SIMPLE_NETWORK_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_START) (IN EFI_SIMPLE_NETWORK_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_STOP) (IN EFI_SIMPLE_NETWORK_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_INITIALIZE) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL        *This,
	IN UINTN                              ExtraRxBufferSize OPTIONAL,
	IN UINTN                              ExtraTxBufferSize OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_RESET) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL    *This,
	IN BOOLEAN                        ExtendedVerification
	);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_SHUTDOWN) (IN EFI_SIMPLE_NETWORK_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_RECEIVE_FILTERS) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL       *This,
	IN UINT32                            Enable,
	IN UINT32                            Disable,
	IN BOOLEAN                           ResetMCastFilter,
	IN UINTN                             MCastFilterCnt OPTIONAL,
	IN EFI_MAC_ADDRESS                   MCastFilter OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_STATION_ADDRESS) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL       *This,
	IN BOOLEAN                           Reset,
	IN EFI_MAC_ADDRESS                   *New OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_STATISTICS) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL       *This,
	IN BOOLEAN                           Reset,
	IN OUT UINTN                         *StatisticsSize OPTIONAL,
	OUT EFI_NETWORK_STATISTICS           *StatisticsTable OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL       *This,
	IN BOOLEAN                           IPv6,
	IN EFI_IP_ADDRESS                    *IP,
	OUT EFI_MAC_ADDRESS                  *MAC
	);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_NVDATA) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL    *This,
	IN BOOLEAN                        ReadWrite,
	IN UINTN                          Offset,
	IN UINTN                          BufferSize,
	IN OUT VOID                       *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_GET_STATUS) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL       *This,
	OUT UINT32                           *InterruptStatus OPTIONAL,
	OUT VOID                             **TxBuf OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_TRANSMIT) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL       *This,
	IN UINTN                             HeaderSize,
	IN UINTN                             BufferSize,
	IN VOID                              *Buffer,
	IN EFI_MAC_ADDRESS                   *SrcAddr OPTIONAL,
	IN EFI_MAC_ADDRESS                   *DestAddr OPTIONAL,
	IN UINT16                            *Protocol OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SIMPLE_NETWORK_RECEIVE) (
	IN EFI_SIMPLE_NETWORK_PROTOCOL       *This,
	OUT  UINTN                           *HeaderSize OPTIONAL,
	IN OUT UINTN                         *BufferSize,
	OUT  VOID                            *Buffer,
	OUT  EFI_MAC_ADDRESS                 *SrcAddr OPTIONAL,
	OUT  EFI_MAC_ADDRESS                 *DestAddr OPTIONAL,
	OUT  UINT16                          *Protocol OPTIONAL
	);

struct _EFI_SIMPLE_NETWORK_PROTOCOL {
	UINT64                               Revision;
	EFI_SIMPLE_NETWORK_START             Start;
	EFI_SIMPLE_NETWORK_STOP              Stop;
	EFI_SIMPLE_NETWORK_INITIALIZE        Initialize;
	EFI_SIMPLE_NETWORK_RESET             Reset;
	EFI_SIMPLE_NETWORK_SHUTDOWN          Shutdown;
	EFI_SIMPLE_NETWORK_RECEIVE_FILTERS   ReceiveFilters;
	EFI_SIMPLE_NETWORK_STATION_ADDRESS   StationAddress;
	EFI_SIMPLE_NETWORK_STATISTICS        Statistics;
	EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC   MCastIpToMac;
	EFI_SIMPLE_NETWORK_NVDATA            NvData;
	EFI_SIMPLE_NETWORK_GET_STATUS        GetStatus;
	EFI_SIMPLE_NETWORK_TRANSMIT          Transmit;
	EFI_SIMPLE_NETWORK_RECEIVE           Receive;
	EFI_EVENT                            WaitForPacket;
	EFI_SIMPLE_NETWORK_MODE              *Mode;
};
#pragma once
#include "efi/types.h"

// UEFI Spec Section 17.1

#define EFI_USB2_HC_PROTOCOL_GUID {0x3e745226,0x9818,0x45b6,{0xa2,0xac,0xd7,0xcd,0x0e,0x8b,0xa2,0xbc}}

typedef enum {
	EfiUsbHcStateHalt,
	EfiUsbHcStateOperational,
	EfiUsbHcStateSuspend,
	EfiUsbHcStateMaximum
}   EFI_USB_HC_STATE;

typedef enum {
	EfiUsbPortEnable = 1,
	EfiUsbPortSuspend = 2,
	EfiUsbPortReset = 4,
	EfiUsbPortPower = 8,
	EfiUsbPortOwner = 13,
	EfiUsbPortConnectChange = 16,
	EfiUsbPortEnableChange = 17,
	EfiUsbPortSuspendChange = 18,
	EfiUsbPortOverCurrentChange = 19,
	EfiUsbPortResetChange = 20
}  EFI_USB_PORT_FEATURE;

typedef enum {
	EfiUsbDataIn,
	EfiUsbDataOut,
	EfiUsbNoData
}   EFI_USB_DATA_DIRECTION;

typedef struct {
	UINT8                    TranslatorHubAddress;
	UINT8                    TranslatorPortNumber;
} EFI_USB2_HC_TRANSACTION_TRANSLATOR;

typedef struct {
	UINT16               PortStatus;
	UINT16               PortChangeStatus;
}  EFI_USB_PORT_STATUS;

typedef struct {
	UINT8                RequestType;
	UINT8                Request;
	UINT16               Value;
	UINT16               Index;
	UINT16               Length;
}   EFI_USB_DEVICE_REQUEST;

//
// Error code for USB Transfer Results
//
#define EFI_USB_NOERROR            0x0000
#define EFI_USB_ERR_NOTEXECUTE     0x0001
#define EFI_USB_ERR_STALL          0x0002
#define EFI_USB_ERR_BUFFER         0x0004
#define EFI_USB_ERR_BABBLE         0x0008
#define EFI_USB_ERR_NAK            0x0010
#define EFI_USB_ERR_CRC            0x0020
#define EFI_USB_ERR_TIMEOUT        0x0040
#define EFI_USB_ERR_BITSTUFF       0x0080
#define EFI_USB_ERR_SYSTEM         0x0100

#define EFI_USB_SPEED_FULL    0x0000
#define EFI_USB_SPEED_LOW     0x0001
#define EFI_USB_SPEED_HIGH    0x0002
#define EFI_USB_SPEED_SUPER   0x0003

#define EFI_USB_HC_RESET_GLOBAL              0x0001
#define EFI_USB_HC_RESET_HOST_CONTROLLER     0x0002
#define EFI_USB_HC_RESET_GLOBAL_WITH_DEBUG   0x0004
#define EFI_USB_HC_RESET_HOST_WITH_DEBUG     0x0008

#define EFI_USB_MAX_ISO_BUFFER_NUM 7
#define EFI_USB_MAX_ISO_BUFFER_NUM1 2

// EFI_USB_PORT_STATUS.PortStatus bit definition
#define USB_PORT_STAT_CONNECTION       0x0001
#define USB_PORT_STAT_ENABLE           0x0002
#define USB_PORT_STAT_SUSPEND          0x0004
#define USB_PORT_STAT_OVERCURRENT      0x0008
#define USB_PORT_STAT_RESET            0x0010
#define USB_PORT_STAT_POWER            0x0100
#define USB_PORT_STAT_LOW_SPEED        0x0200
#define USB_PORT_STAT_HIGH_SPEED       0x0400
#define USB_PORT_STAT_SUPER_SPEED      0x0800
#define USB_PORT_STAT_OWNER            0x2000


// EFI_USB_PORT_STATUS.PortChangeStatus bit definition
#define USB_PORT_STAT_C_CONNECTION     0x0001
#define USB_PORT_STAT_C_ENABLE         0x0002
#define USB_PORT_STAT_C_SUSPEND        0x0004
#define USB_PORT_STAT_C_OVERCURRENT    0x0008
#define USB_PORT_STAT_C_RESET          0x0010

#define EFI_USB_MAX_BULK_BUFFER_NUM  10

typedef EFI_STATUS(EFIAPI * EFI_ASYNC_USB_TRANSFER_CALLBACK) (
	IN VOID                *Data,
	IN UINTN               DataLength,
	IN VOID                *Context,
	IN UINT32              Status
	);

typedef struct _EFI_USB2_HC_PROTOCOL EFI_USB2_HC_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_GET_CAPABILITY) (
	IN EFI_USB2_HC_PROTOCOL          *This,
	OUT UINT8                        *MaxSpeed,
	OUT UINT8                        *PortNumber,
	OUT UINT8                        *Is64BitCapable
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_RESET) (
	IN EFI_USB2_HC_PROTOCOL            *This,
	IN UINT16                          Attributes
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_GET_STATE) (
	IN EFI_USB2_HC_PROTOCOL              *This,
	OUT EFI_USB_HC_STATE                 *State
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_SET_STATE) (
	IN EFI_USB2_HC_PROTOCOL          *This,
	IN EFI_USB_HC_STATE              State
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_CONTROL_TRANSFER) (
	IN EFI_USB2_HC_PROTOCOL                *This,
	IN UINT8                               DeviceAddress,
	IN UINT8                               DeviceSpeed,
	IN UINTN                               MaximumPacketLength,
	IN EFI_USB_DEVICE_REQUEST              *Request,
	IN EFI_USB_DATA_DIRECTION              TransferDirection,
	IN OUT VOID                            *Data OPTIONAL,
	IN OUT UINTN                           *DataLength OPTIONAL,
	IN UINTN                               TimeOut,
	IN EFI_USB2_HC_TRANSACTION_TRANSLATOR  *Translator,
	OUT UINT32                             *TransferResult
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_BULK_TRANSFER) (
	IN EFI_USB2_HC_PROTOCOL                *This,
	IN UINT8                               DeviceAddress,
	IN UINT8                               EndPointAddress,
	IN UINT8                               DeviceSpeed,
	IN UINTN                               MaximumPacketLength,
	IN UINT8                               DataBuffersNumber,
	IN OUT VOID                            *Data[EFI_USB_MAX_BULK_BUFFER_NUM],
	IN OUT UINTN                           *DataLength,
	IN OUT UINT8                           *DataToggle,
	IN UINTN                               TimeOut,
	IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
	OUT UINT32                             *TransferResult
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER) (
	IN EFI_USB2_HC_PROTOCOL                *This,
	IN UINT8                               DeviceAddress,
	IN UINT8                               EndPointAddress,
	IN UINT8                               DeviceSpeed,
	IN UINTN                               MaximumPacketLength,
	IN BOOLEAN                             IsNewTransfer,
	IN OUT UINT8                           *DataToggle,
	IN UINTN                               PollingInterval OPTIONAL,
	IN UINTN                               DataLength OPTIONAL,
	IN EFI_USB2_HC_TRANSACTION_TRANSLATOR  *Translator OPTIONAL,
	IN EFI_ASYNC_USB_TRANSFER_CALLBACK     CallBackFunction OPTIONAL,
	IN VOID                                *Context OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_SYNC_INTERRUPT_TRANSFER) (
	IN   EFI_USB2_HC_PROTOCOL                *This,
	IN   UINT8                               DeviceAddress,
	IN   UINT8                               EndPointAddress,
	IN   UINT8                               DeviceSpeed,
	IN   UINTN                               MaximumPacketLength,
	IN OUT VOID                              *Data,
	IN OUT UINTN                             *DataLength,
	IN OUT UINT8                             *DataToggle,
	IN   UINTN                                TimeOut,
	IN EFI_USB2_HC_TRANSACTION_TRANSLATOR    *Translator,
	OUT UINT32                               *TransferResult
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_ISOCHRONOUS_TRANSFER) (
	IN   EFI_USB2_HC_PROTOCOL                  *This,
	IN   UINT8                                 DeviceAddress,
	IN   UINT8                                 EndPointAddress,
	IN   UINT8                                 DeviceSpeed,
	IN   UINTN                                 MaximumPacketLength,
	IN   UINT8                                 DataBuffersNumber,
	IN OUT VOID                                *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
	IN   UINTN                                 DataLength,
	IN   EFI_USB2_HC_TRANSACTION_TRANSLATOR    *Translator,
	OUT  UINT32                                *TransferResult
	);

typedef EFI_STATUS(EFIAPI * EFI_USB2_HC_PROTOCOL_ASYNC_ISOCHRONOUS_TRANSFER) (
	IN   EFI_USB2_HC_PROTOCOL                *This,
	IN   UINT8                               DeviceAddress,
	IN   UINT8                               EndPointAddress,
	IN   UINT8                               DeviceSpeed,
	IN   UINTN                               MaximumPacketLength,
	IN   UINT8                               DataBuffersNumber,
	IN OUT VOID                              *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
	IN   UINTN                               DataLength,
	IN   EFI_USB2_HC_TRANSACTION_TRANSLATOR  *Translator,
	IN EFI_ASYNC_USB_TRANSFER_CALLBACK       IsochronousCallBack,
	IN VOID                                  *Context OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_GET_ROOTHUB_PORT_STATUS) (
	IN EFI_USB2_HC_PROTOCOL            *This,
	IN UINT8                           PortNumber,
	OUT EFI_USB_PORT_STATUS            *PortStatus
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_SET_ROOTHUB_PORT_FEATURE) (
	IN EFI_USB2_HC_PROTOCOL      *This,
	IN UINT8                     PortNumber,
	IN EFI_USB_PORT_FEATURE      PortFeature
	);

typedef EFI_STATUS(EFIAPI *EFI_USB2_HC_PROTOCOL_CLEAR_ROOTHUB_PORT_FEATURE) (
	IN EFI_USB2_HC_PROTOCOL      *This,
	IN UINT8                     PortNumber,
	IN EFI_USB_PORT_FEATURE      PortFeature
	);

struct _EFI_USB2_HC_PROTOCOL {
	EFI_USB2_HC_PROTOCOL_GET_CAPABILITY              GetCapability;
	EFI_USB2_HC_PROTOCOL_RESET                       Reset;
	EFI_USB2_HC_PROTOCOL_GET_STATE                   GetState;
	EFI_USB2_HC_PROTOCOL_SET_STATE                   SetState;
	EFI_USB2_HC_PROTOCOL_CONTROL_TRANSFER            ControlTransfer;
	EFI_USB2_HC_PROTOCOL_BULK_TRANSFER               BulkTransfer;
	EFI_USB2_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER    AsyncInterruptTransfer;
	EFI_USB2_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER    SyncInterruptTransfer;
	EFI_USB2_HC_PROTOCOL_ISOCHRONOUS_TRANSFER        IsochronousTransfer;
	EFI_USB2_HC_PROTOCOL_ASYNC_ISOCHRONOUS_TRANSFER  AsyncIsochronousTransfer;
	EFI_USB2_HC_PROTOCOL_GET_ROOTHUB_PORT_STATUS     GetRootHubPortStatus;
	EFI_USB2_HC_PROTOCOL_SET_ROOTHUB_PORT_FEATURE    SetRootHubPortFeature;
	EFI_USB2_HC_PROTOCOL_CLEAR_ROOTHUB_PORT_FEATURE  ClearRootHubPortFeature;
	UINT16                                           MajorRevision;
	UINT16                                           MinorRevision;
};
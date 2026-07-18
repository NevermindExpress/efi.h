#pragma once
#include "efi/types.h"

// UEFI Spec Section 26.1

#define EFI_BLUETOOTH_HC_PROTOCOL_GUID { 0xb3930571, 0xbeba, 0x4fc5,{ 0x92, 0x3, 0x94, 0x27, 0x24, 0x2e, 0x6a, 0x43 }}

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK) (
	IN VOID                     *Data,
	IN UINTN                    DataLength,
	IN VOID                     *Context
	);

typedef struct  _EFI_BLUETOOTH_HC_PROTOCOL EFI_BLUETOOTH_HC_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_SEND_COMMAND)(
	IN EFI_BLUETOOTH_HC_PROTOCOL            *This,
	IN OUT UINTN                            *BufferSize,
	IN VOID                                 *Buffer,
	IN UINTN                                Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_RECEIVE_EVENT)(
	IN EFI_BLUETOOTH_HC_PROTOCOL            *This,
	IN OUT UINTN                            *BufferSize,
	OUT VOID                                *Buffer,
	IN UINTN                                Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_ASYNC_RECEIVE_EVENT) (
	IN EFI_BLUETOOTH_HC_PROTOCOL               *This,
	IN BOOLEAN                                 IsNewTransfer,
	IN UINTN                                   PollingInterval,
	IN UINTN                                   DataLength,
	IN EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK    Callback,
	IN VOID                                    *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_SEND_ACL_DATA)(
	IN EFI_BLUETOOTH_HC_PROTOCOL   *This,
	IN OUT UINTN                   *BufferSize,
	IN VOID                        *Buffer,
	IN UINTN                       Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_RECEIVE_ACL_DATA)(
	IN EFI_BLUETOOTH_HC_PROTOCOL         *This,
	IN OUT UINTN                         *BufferSize,
	OUT VOID                             *Buffer,
	IN UINTN                             Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_ASYNC_RECEIVE_ACL_DATA) (
	IN EFI_BLUETOOTH_HC_PROTOCOL               *This,
	IN BOOLEAN                                 IsNewTransfer,
	IN UINTN                                   PollingInterval,
	IN UINTN                                   DataLength,
	IN EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK    Callback,
	IN VOID                                    *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_SEND_SCO_DATA)(
	IN EFI_BLUETOOTH_HC_PROTOCOL            *This,
	IN OUT UINTN                            *BufferSize,
	IN VOID                                 *Buffer,
	IN UINTN                                Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_RECEIVE_SCO_DATA)(
	IN EFI_BLUETOOTH_HC_PROTOCOL         *This,
	IN OUT UINTN                         *BufferSize,
	OUT VOID                             *Buffer,
	IN UINTN                             Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_HC_ASYNC_RECEIVE_SCO_DATA) (
	IN EFI_BLUETOOTH_HC_PROTOCOL               *This,
	IN BOOLEAN                                 IsNewTransfer,
	IN UINTN                                   PollingInterval,
	IN UINTN                                   DataLength,
	IN EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK    Callback,
	IN VOID                                    *Context
	);

struct  _EFI_BLUETOOTH_HC_PROTOCOL {
	EFI_BLUETOOTH_HC_SEND_COMMAND              SendCommand;
	EFI_BLUETOOTH_HC_RECEIVE_EVENT             ReceiveEvent;
	EFI_BLUETOOTH_HC_ASYNC_RECEIVE_EVENT       AsyncReceiveEvent;
	EFI_BLUETOOTH_HC_SEND_ACL_DATA             SendACLData;
	EFI_BLUETOOTH_HC_RECEIVE_ACL_DATA          ReceiveACLData;
	EFI_BLUETOOTH_HC_ASYNC_RECEIVE_ACL_DATA    AsyncReceiveACLData;
	EFI_BLUETOOTH_HC_SEND_SCO_DATA             SendSCOData;
	EFI_BLUETOOTH_HC_RECEIVE_SCO_DATA          ReceiveSCOData;
	EFI_BLUETOOTH_HC_ASYNC_RECEIVE_SCO_DATA    AsyncReceiveSCOData;
};

// UEFI Spec Section 26.2

#define EFI_BLUETOOTH_IO_SERVICE_BINDING_PROTOCOL_GUID { 0x388278d3, 0x7b85, 0x42f0,{ 0xab, 0xa9, 0xfb, 0x4b, 0xfd, 0x69, 0xf5, 0xab }
#define EFI_BLUETOOTH_IO_PROTOCOL_GUID { 0x467313de, 0x4e30, 0x43f1,{ 0x94, 0x3e, 0x32, 0x3f, 0x89, 0x84, 0x5d, 0xb5 }}

typedef struct {
	UINT8              Address[6];
} BLUETOOTH_ADDRESS;

typedef struct {
	UINT8              FormatType : 2;
	UINT8              MinorDeviceClass : 6;
	UINT16             MajorDeviceClass : 5;
	UINT16             MajorServiceClass : 11;
}   BLUETOOTH_CLASS_OF_DEVICE;

typedef struct {
	UINT32                     Version;
	BLUETOOTH_ADDRESS          BD_ADDR;
	UINT8                      PageScanRepetitionMode;
	BLUETOOTH_CLASS_OF_DEVICE  ClassOfDevice;
	UINT16                     ClockOffset;
	UINT8                      RSSI;
	UINT8                      ExtendedInquiryResponse[240];
}  EFI_BLUETOOTH_DEVICE_INFO;

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_ASYNC_FUNC_CALLBACK) (
	IN UINT16                         ChannelID,
	IN VOID                           *Data,
	IN UINTN                          DataLength,
	IN VOID                           *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_CHANNEL_SERVICE_CALLBACK) (
	IN VOID                    *Data,
	IN UINTN                   DataLength,
	IN VOID                    *Context
	);

typedef struct  _EFI_BLUETOOTH_IO_PROTOCOL EFI_BLUETOOTH_IO_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_GET_DEVICE_INFO)(
	IN EFI_BLUETOOTH_IO_PROTOCOL         *This,
	OUT UINTN                            *DeviceInfoSize,
	OUT VOID                             **DeviceInfo
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_GET_SDP_INFO)(
	IN EFI_BLUETOOTH_IO_PROTOCOL         *This,
	OUT UINTN                            *SdpInfoSize,
	OUT VOID                             **SdpInfo
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_L2CAP_RAW_SEND)(
	IN EFI_BLUETOOTH_IO_PROTOCOL         *This,
	IN OUT UINTN                         *BufferSize,
	IN VOID                              *Buffer,
	IN UINTN                             Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_L2CAP_RAW_RECEIVE)(
	IN EFI_BLUETOOTH_IO_PROTOCOL               *This,
	IN OUT UINTN                               *BufferSize,
	OUT VOID                                   *Buffer,
	IN UINTN                                   Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_L2CAP_RAW_ASYNC_RECEIVE)(
	IN EFI_BLUETOOTH_IO_PROTOCOL               *This,
	IN BOOLEAN                                 IsNewTransfer,
	IN UINTN                                   PollingInterval,
	IN UINTN                                   DataLength,
	IN EFI_BLUETOOTH_IO_ASYNC_FUNC_CALLBACK    Callback,
	IN VOID                                    *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_L2CAP_SEND)(
	IN EFI_BLUETOOTH_IO_PROTOCOL         *This,
	IN EFI_HANDLE                        Handle,
	IN OUT UINTN                         *BufferSize,
	IN VOID                              *Buffer,
	IN UINTN                             Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_L2CAP_RECEIVE)(
	IN EFI_BLUETOOTH_IO_PROTOCOL         *This,
	IN EFI_HANDLE                        Handle,
	OUT UINTN                            *BufferSize,
	OUT VOID                             **Buffer,
	IN UINTN                             Timeout
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_L2CAP_ASYNC_RECEIVE)(
	IN EFI_BLUETOOTH_IO_PROTOCOL                  *This,
	IN EFI_HANDLE                                 Handle,
	IN EFI_BLUETOOTH_IO_CHANNEL_SERVICE_CALLBACK  Callback,
	IN VOID                                       *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_L2CAP_CONNECT)(
	IN EFI_BLUETOOTH_IO_PROTOCOL                  *This,
	OUT EFI_HANDLE                                *Handle,
	IN UINT16                                     Psm,
	IN UINT16                                     Mtu,
	IN EFI_BLUETOOTH_IO_CHANNEL_SERVICE_CALLBACK  Callback,
	IN VOID                                       *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_L2CAP_DISCONNECT)(
	IN EFI_BLUETOOTH_IO_PROTOCOL     *This,
	IN EFI_HANDLE                    Handle
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_IO_L2CAP_REGISTER_SERVICE)(
	IN EFI_BLUETOOTH_IO_PROTOCOL                  *This,
	OUT EFI_HANDLE                                *Handle,
	IN UINT16                                     Psm,
	IN UINT16                                     Mtu,
	IN EFI_BLUETOOTH_IO_CHANNEL_SERVICE_CALLBACK  Callback,
	IN VOID                                       *Context
	);

struct  _EFI_BLUETOOTH_IO_PROTOCOL {
	EFI_BLUETOOTH_IO_GET_DEVICE_INFO           GetDeviceInfo;
	EFI_BLUETOOTH_IO_GET_SDP_INFO              GetSdpInfo;
	EFI_BLUETOOTH_IO_L2CAP_RAW_SEND            L2CapRawSend;
	EFI_BLUETOOTH_IO_L2CAP_RAW_RECEIVE         L2CapRawReceive;
	EFI_BLUETOOTH_IO_L2CAP_RAW_ASYNC_RECEIVE  L2CapRawAsyncReceive;
	EFI_BLUETOOTH_IO_L2CAP_SEND                L2CapSend;
	EFI_BLUETOOTH_IO_L2CAP_RECEIVE             L2CapReceive;
	EFI_BLUETOOTH_IO_L2CAP_ASYNC_RECEIVE       L2CapAsyncReceive;
	EFI_BLUETOOTH_IO_L2CAP_CONNECT             L2CapConnect;
	EFI_BLUETOOTH_IO_L2CAP_DISCONNECT          L2CapDisconnect;
	EFI_BLUETOOTH_IO_L2CAP_REGISTER_SERVICE   L2CapRegisterService;
};

// UEFI Spec Section 26.3

#define EFI_BLUETOOTH_CONFIG_PROTOCOL_GUID { 0x62960cf3, 0x40ff, 0x4263,{ 0xa7, 0x7c, 0xdf, 0xde, 0xbd, 0x19, 0x1b, 0x4b }}

#define BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE 248

#define EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_TYPE UINT32;
#define EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED 0x1
#define EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED 0x2

#define BLUETOOTH_HCI_LINK_KEY_SIZE 16

typedef enum {
	EfiBluetoothConfigDataTypeDeviceName,         /* Relevant for LE*/
	EfiBluetoothConfigDataTypeClassOfDevice,
	EfiBluetoothConfigDataTypeRemoteDeviceState,  /* Relevant for LE*/
	EfiBluetoothConfigDataTypeSdpInfo,
	EfiBluetoothConfigDataTypeBDADDR,             /* Relevant for LE*/
	EfiBluetoothConfigDataTypeDiscoverable,       /* Relevant for LE*/
	EfiBluetoothConfigDataTypeControllerStoredPairedDeviceList,
	EfiBluetoothConfigDataTypeAvailableDeviceList,
	EfiBluetoothConfigDataTypeRandomAddress,      /* Relevant for LE*/
	EfiBluetoothConfigDataTypeRSSI,               /* Relevant for LE*/
	EfiBluetoothConfigDataTypeAdvertisementData,  /* Relevant for LE*/
	EfiBluetoothConfigDataTypeIoCapability,       /* Relevant for LE*/
	EfiBluetoothConfigDataTypeOOBDataFlag,        /* Relevant for LE*/
	EfiBluetoothConfigDataTypeKeyType,            /* Relevant for LE*/
	EfiBluetoothConfigDataTypeEncKeySize,         /* Relevant for LE*/
	EfiBluetoothConfigDataTypeMax,
}   EFI_BLUETOOTH_CONFIG_DATA_TYPE;

typedef enum {
	EfiBluetoothCallbackTypeUserPasskeyNotification,
	EfiBluetoothCallbackTypeUserConfirmationRequest,
	EfiBluetoothCallbackTypeOOBDataRequest,
	EfiBluetoothCallbackTypePinCodeRequest,
	EfiBluetoothCallbackTypeMax,
} EFI_BLUETOOTH_PIN_CALLBACK_TYPE;

typedef enum {
	EfiBluetoothConnCallbackTypeDisconnected,
	EfiBluetoothConnCallbackTypeConnected,
	EfiBluetoothConnCallbackTypeAuthenticated,
	EfiBluetoothConnCallbackTypeEncrypted,
} EFI_BLUETOOTH_CONNECT_COMPLETE_CALLBACK_TYPE;

typedef struct {
	BLUETOOTH_ADDRESS                    BDAddr;
	UINT8                                RemoteDeviceState;
	BLUETOOTH_CLASS_OF_DEVICE            ClassOfDevice;
	UINT8                                RemoteDeviceName[BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE];
}  EFI_BLUETOOTH_SCAN_CALLBACK_INFORMATION;

typedef struct  _EFI_BLUETOOTH_CONFIG_PROTOCOL EFI_BLUETOOTH_CONFIG_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_SCAN_CALLBACK_FUNCTION) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL                *This,
	IN VOID                                         *Context,
	IN EFI_BLUETOOTH_SCAN_CALLBACK_INFORMATION      *CallbackInfo
);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_REGISTER_PIN_CALLBACK_FUNCTION)   (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL * *This,
	IN VOID * *Context,
	IN EFI_BLUETOOTH_PIN_CALLBACK_TYPE *CallbackType,
	IN VOID * *InputBuffer,
	IN UINTN *InputBufferSize,
	OUT VOID ** *OutputBuffer,
	OUT UINTN * *OutputBufferSize
	);

typedef EFI_STATUS(EFIAPI    *EFI_BLUETOOTH_CONFIG_REGISTER_GET_LINK_KEY_CALLBACK_FUNCTION) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL  *This,
	IN VOID                           *Context,
	IN BLUETOOTH_ADDRESS              *BDAddr,
	OUT UINT8                         LinkKey[BLUETOOTH_HCI_LINK_KEY_SIZE]
	);

typedef EFI_STATUS(EFIAPI    *EFI_BLUETOOTH_CONFIG_REGISTER_SET_LINK_KEY_CALLBACK_FUNCTION) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL        *This,
	IN VOID                                 *Context,
	IN BLUETOOTH_ADDRESS                    *BDAddr,
	IN UINT8                                LinkKey[BLUETOOTH_HCI_LINK_KEY_SIZE]
	);

typedef EFI_STATUS(EFIAPI    *EFI_BLUETOOTH_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK_FUNCTION) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL                 *This,
	IN VOID                                          *Context,
	IN EFI_BLUETOOTH_CONNECT_COMPLETE_CALLBACK_TYPE  CallbackType,
	IN BLUETOOTH_ADDRESS                             *BDAddr,
	IN VOID                                          *InputBuffer,
	IN UINTN                                         InputBufferSize
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_INIT)(IN EFI_BLUETOOTH_CONFIG_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_SCAN)(
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL                 *This,
	IN BOOLEAN                                       ReScan,
	IN UINT8                                         ScanType,
	IN EFI_BLUETOOTH_CONFIG_SCAN_CALLBACK_FUNCTION   Callback,
	IN VOID                                          *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_CONNECT)(
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL     *This,
	IN BLUETOOTH_ADDRESS                 *BD_ADDR
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_DISCONNECT)(
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL        *This,
	IN BLUETOOTH_ADDRESS                    *BD_ADDR,
	IN UINT8 *Reason
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_GET_DATA) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL           *This,
	IN EFI_BLUETOOTH_CONFIG_DATA_TYPE          DataType,
	IN OUT UINTN                               *DataSize,
	IN OUT VOID                                *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_SET_DATA) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL        *This,
	IN EFI_BLUETOOTH_CONFIG_DATA_TYPE       DataType,
	IN UINTN                                DataSize,
	IN VOID                                 *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_GET_REMOTE_DATA) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL           *This,
	IN EFI_BLUETOOTH_CONFIG_DATA_TYPE          DataType,
	IN BLUETOOTH_ADDRESS                       *BDAddr,
	IN OUT UINTN                               *DataSize,
	IN OUT VOID                                *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_REGISTER_PIN_CALLBACK) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL                       *This,
	IN EFI_BLUETOOTH_CONFIG_REGISTER_PIN_CALLBACK_FUNCTION *Callback,
	IN VOID                                                *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_REGISTER_GET_LINK_KEY_CALLBACK) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL                                   *This,
	IN EFI_BLUETOOTH_CONFIG_REGISTER_GET_LINK_KEY_CALLBACK_FUNCTION    Callback,
	IN VOID                                                            *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_REGISTER_SET_LINK_KEY_CALLBACK) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL       *This,
	IN EFI_BLUETOOTH_CONFIG_REGISTER_SET_LINK_KEY_CALLBACK_FUNCTION    *Callback,
	IN VOID                                *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK) (
	IN EFI_BLUETOOTH_CONFIG_PROTOCOL                                     *This,
	IN EFI_BLUETOOTH_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK_FUNCTION  Callback,
	IN VOID                                                              *Context
	);

struct  _EFI_BLUETOOTH_CONFIG_PROTOCOL {
	EFI_BLUETOOTH_CONFIG_INIT                  Init;
	EFI_BLUETOOTH_CONFIG_SCAN                  Scan;
	EFI_BLUETOOTH_CONFIG_CONNECT               Connect;
	EFI_BLUETOOTH_CONFIG_DISCONNECT            Disconnect;
	EFI_BLUETOOTH_CONFIG_GET_DATA              GetData;
	EFI_BLUETOOTH_CONFIG_SET_DATA              SetData;
	EFI_BLUETOOTH_CONFIG_GET_REMOTE_DATA       GetRemoteData;
	EFI_BLUETOOTH_CONFIG_REGISTER_PIN_CALLBACK                 RegisterPinCallback;
	EFI_BLUETOOTH_CONFIG_REGISTER_GET_LINK_KEY_CALLBACK        RegisterGetLinkKeyCallback;
	EFI_BLUETOOTH_CONFIG_REGISTER_SET_LINK_KEY_CALLBACK        RegisterSetLinkKeyCallback;
	EFI_BLUETOOTH_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK    RegisterLinkConnectCompleteCallback;
};

// UEFI Spec Section 26.4
#define EFI_BLUETOOTH_ATTRIBUTE_SERVICE_BINDING_PROTOCOL_GUID {0x5639867a, 0x8c8e, 0x408d, 0xac, 0x2f, 0x4b, 0x61, 0xbd, 0xc0, 0xbb, 0xbb }
#define EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL_GUID { 0x898890e9, 0x84b2, 0x4f3a, { 0x8c, 0x58, 0xd8, 0x57, 0x78, 0x13, 0xe0, 0xac }}

typedef struct {
	UINT16               AttributeHandle;
}                      EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_PARAMETER_NOTIFICATION;
typedef struct {
	UINT16               AttributeHandle;
}                      EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_PARAMETER_INDICATION;
typedef struct {
	UINT32               Version;
	UINT8                AttributeOpCode;
	union {
		EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_PARAMETER_NOTIFICATION    Notification;
		EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_PARAMETER_INDICATION      Indication;
	} Parameter;
} EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_PARAMETER;

typedef struct {
	UINT8           Length;
	union {
		UINT16        Uuid16;
		UINT32        Uuid32;
		UINT8         Uuid128[16];
	} Data;
} EFI_BLUETOOTH_UUID;

// Bluetooth Attribute Permission
typedef union {
	struct {
		UINT16     Readable : 1;
		UINT16     ReadEncryption : 1;
		UINT16     ReadAuthentication : 1;
		UINT16     ReadAuthorization : 1;
		UINT16     ReadKeySize : 5;
		UINT16     Reserved1 : 7;
		UINT16     Writeable : 1;
		UINT16     WriteEncryption : 1;
		UINT16     WriteAuthentication : 1;
		UINT16     WriteAuthorization : 1;
		UINT16     WriteKeySize : 5;
		UINT16     Reserved2 : 7;
	} Permission;
	UINT32 Data32;
} EFI_BLUETOOTH_ATTRIBUTE_PERMISSION;

typedef struct {
	EFI_BLUETOOTH_UUID                   Type;
	UINT16                               Length;
	UINT16                               AttributeHandle;
	EFI_BLUETOOTH_ATTRIBUTE_PERMISSION   AttributePermission;
} EFI_BLUETOOTH_ATTRIBUTE_HEADER;

typedef struct {
	EFI_BLUETOOTH_ATTRIBUTE_HEADER  Header;
	UINT16                          EndGroupHandle;
	EFI_BLUETOOTH_UUID              ServiceUuid;
}   EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO;

typedef struct {
	EFI_BLUETOOTH_ATTRIBUTE_HEADER     Header;
	UINT16                             StartGroupHandle;
	UINT16                             EndGroupHandle;
	EFI_BLUETOOTH_UUID                 ServiceUuid;
}  EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO;

typedef struct {
	EFI_BLUETOOTH_ATTRIBUTE_HEADER       Header;
	UINT8                                CharacteristicProperties;
	UINT16                               CharacteristicValueHandle;
	EFI_BLUETOOTH_UUID                   CharacteristicUuid;
} EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO;

typedef struct {
	EFI_BLUETOOTH_ATTRIBUTE_HEADER         Header;
	EFI_BLUETOOTH_UUID                     CharacteristicDescriptorUuid;
}  EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO;

typedef struct {
	UINT8                Address[6];
	UINT8                Type;
} BLUETOOTH_LE_ADDRESS;

typedef struct {
	UINT32                 Version;
	BLUETOOTH_LE_ADDRESS BD_ADDR;
	BLUETOOTH_LE_ADDRESS   DirectAddress;
	UINT8                  RSSI;
	UINTN                  AdvertismentDataSize;
	VOID                   *AdvertismentData;
}   EFI_BLUETOOTH_LE_DEVICE_INFO;

typedef struct  _EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION) (
	IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL       *This,
	IN VOID                                   *Data,
	IN UINTN                                  DataLength,
	IN VOID                                   *Context
	);


typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_ATTRIBUTE_SEND_REQUEST)(
	IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL             *This,
	IN VOID                                         *Data,
	IN UINTN                                        DataLength,
	IN EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION    Callback,
	IN VOID                                         *Context
	);

typedef EFI_STATUS (EFIAPI   *EFI_BLUETOOTH_ATTRIBUTE_REGISTER_FOR_SERVER_NOTIFICATION)(
	IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL             *This,
	IN EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_PARAMETER   *CallbackParameter,
	IN EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION    Callback,
	IN VOID                                         *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_ATTRIBUTE_GET_SERVICE_INFO)(
	IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL        *This,
	OUT UINTN                                  *ServiceInfoSize,
	OUT VOID                                   **ServiceInfo
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_ATTRIBUTE_GET_DEVICE_INFO)(
	IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL      *This,
	OUT UINTN                                *DeviceInfoSize,
	OUT VOID                                 **DeviceInfo
	);

struct  _EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL {
	EFI_BLUETOOTH_ATTRIBUTE_SEND_REQUEST          SendRequest;
	EFI_BLUETOOTH_ATTRIBUTE_REGISTER_FOR_SERVER_NOTIFICATION RegisterForServerNotification;
	EFI_BLUETOOTH_ATTRIBUTE_GET_SERVICE_INFO      GetServiceInfo;
	EFI_BLUETOOTH_ATTRIBUTE_GET_DEVICE_INFO       GetDeviceInfo;
};

// UEFI Spec Section 26.5

#define EFI_BLUETOOTH_LE_CONFIG_PROTOCOL_GUID { 0x8f76da58, 0x1f99, 0x4275, { 0xa4, 0xec, 0x47, 0x56, 0x51, 0x5b, 0x1c, 0xe8 }}

typedef enum {
	EfiBlutoothSmpAuthorizationRequestEvent,
	EfiBlutoothSmpPasskeyReadyEvent,
	EfiBlutoothSmpPasskeyRequestEvent,
	EfiBlutoothSmpOOBDataRequestEvent,
	EfiBlutoothSmpNumericComparisonEvent,
}   EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE;

typedef enum {
	// For local device only
	EfiBluetoothSmpLocalIR, /* If Key hierarchy is supported   */
	EfiBluetoothSmpLocalER, /* If Key hierarchy is supported   */
	EfiBluetoothSmpLocalDHK, /* If Key hierarchy is supported.  OPTIONAL */

	// For peer specific
	EfiBluetoothSmpKeysDistributed = 0x1000,
	EfiBluetoothSmpKeySize,
	EfiBluetoothSmpKeyType,
	EfiBluetoothSmpPeerLTK,
	EfiBluetoothSmpPeerIRK,
	EfiBluetoothSmpPeerCSRK,
	EfiBluetoothSmpPeerRand,
	EfiBluetoothSmpPeerEDIV,
	EfiBluetoothSmpPeerSignCounter,
	EfiBluetoothSmpLocalLTK, /* If Key hierarchy not supported   */
	EfiBluetoothSmpLocalIRK, /* If Key hierarchy not supported   */
	EfiBluetoothSmpLocalCSRK, /* If Key hierarchy not supported   */
	EfiBluetoothSmpLocalSignCounter,
	EfiBluetoothSmpLocalDIV,
	EfiBluetoothSmpPeerAddressList,
	EfiBluetoothSmpMax,
}   EFI_BLUETOOTH_LE_SMP_DATA_TYPE;

typedef struct {
	// Scan parameter
	UINT32                Version;
	UINT8                 ScanType;
	UINT16                ScanInterval;
	UINT16                ScanWindow;
	UINT8                 ScanningFilterPolicy;
	// Scan result filter
	UINT8                 AdvertisementFlagFilter;
} EFI_BLUETOOTH_LE_CONFIG_SCAN_PARAMETER;

typedef struct {
	BLUETOOTH_LE_ADDRESS              BDAddr;
	BLUETOOTH_LE_ADDRESS              DirectAddress;
	UINT8                             RemoteDeviceState;
	INT8                              RSSI;
	UINTN                             AdvertisementDataSize;
	VOID                              *AdvertisementData;
} EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION;

typedef struct {
	UINT32       Version;
	UINT16       ScanInterval;
	UINT16       ScanWindow;
	UINT16       ConnIntervalMin;
	UINT16       ConnIntervalMax;
	UINT16       ConnLatency;
	UINT16       SupervisionTimeout;
} EFI_BLUETOOTH_LE_CONFIG_CONNECT_PARAMETER;

typedef struct  _EFI_BLUETOOTH_LE_CONFIG_PROTOCOL EFI_BLUETOOTH_LE_CONFIG_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_SCAN_CALLBACK_FUNCTION) (
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL              *This,
	IN VOID                                          *Context,
	IN EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION    *CallbackInfo
	);

typedef
EFI_STATUS
(EFIAPI *EFI_BLUETOOTH_LE_SMP_CALLBACK) (
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL        *This,
	IN VOID                                    *Context,
	IN BLUETOOTH_LE_ADDRESS                    *BDAddr,
	IN EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE    EventDataType,
	IN UINTN                                   DataSize,
	IN VOID                                    *Data
	);

typedef
EFI_STATUS
(EFIAPI * EFI_BLUETOOTH_LE_CONFIG_SMP_GET_DATA_CALLBACK) (
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL            *This,
	IN VOID                                        *Context,
	IN BLUETOOTH_LE_ADDRESS                        *BDAddr,
	IN EFI_BLUETOOTH_LE_SMP_DATA_TYPE              DataType,
	IN OUT UINTN                                   *DataSize,
	OUT VOID                                       *Data
	);

typedef
EFI_STATUS
(EFIAPI * EFI_BLUETOOTH_LE_CONFIG_SMP_SET_DATA_CALLBACK) (
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                *This,
	IN VOID                                            *Context,
	IN BLUETOOTH_LE_ADDRESS                            *BDAddr,
	IN EFI_BLUETOOTH_LE_SMP_DATA_TYPE                  Type,
	IN UINTN                                           DataSize,
	IN VOID                                            *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_CONNECT_COMPLETE_CALLBACK) (
	IN  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL               *This,
	IN  VOID                                           *Context,
	IN  EFI_BLUETOOTH_CONNECT_COMPLETE_CALLBACK_TYPE   CallbackType,
	IN  BLUETOOTH_LE_ADDRESS                           *BDAddr,
	IN  VOID                                           *InputBuffer,
	IN  UINTN                                          InputBufferSize
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_INIT)(IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *This);

typedef
EFI_STATUS
(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_SCAN)(
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL               *This,
	IN BOOLEAN                                        ReScan,
	IN UINT32                                        Timeout,
	IN EFI_BLUETOOTH_LE_CONFIG_SCAN_PARAMETER         *ScanParameter, OPTIONAL
	IN EFI_BLUETOOTH_LE_CONFIG_SCAN_CALLBACK_FUNCTION Callback,
	IN VOID                                           *Context
);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_CONNECT)(
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL           *This,
	IN BOOLEAN                                    AutoReconnect,
	IN BOOLEAN                                    DoBonding,
	IN EFI_BLUETOOTH_LE_CONFIG_CONNECT_PARAMETER  *ConnectParameter, OPTIONAL
	IN BLUETOOTH_LE_ADDRESS                       *BD_ADDR
);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_DISCONNECT)(
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL  *This,
	IN BLUETOOTH_LE_ADDRESS              *BD_ADDR,
	IN UINT8                             Reason
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_GET_DATA) (
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL     *This,
	IN EFI_BLUETOOTH_CONFIG_DATA_TYPE       DataType,
	IN OUT UINTN                            *DataSize,
	IN OUT VOID                             *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_SET_DATA) (
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL        *This,
	IN EFI_BLUETOOTH_CONFIG_DATA_TYPE          DataType,
	IN UINTN                                   DataSize,
	IN VOID                                    *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_GET_REMOTE_DATA) (
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL     *This,
	IN EFI_BLUETOOTH_CONFIG_DATA_TYPE       DataType,
	IN BLUETOOTH_LE_ADDRESS                 *BDAddr,
	IN OUT UINTN                            *DataSize,
	IN OUT VOID                             *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_AUTH_CALLBACK)(
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL        *This,
	IN EFI_BLUETOOTH_LE_SMP_CALLBACK           Callback,
	IN VOID                                    *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_SEND_SMP_AUTH_DATA)(
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL        *This,
	IN BLUETOOTH_LE_ADDRESS                    *BDAddr,
	IN EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE    EventDataType,
	IN UINTN                                   DataSize,
	IN VOID                                    *Data
	);

typedef EFI_STATUS(EFIAPI * EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_GET_DATA_CALLBACK)(
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                *This,
	IN EFI_BLUETOOTH_LE_CONFIG_SMP_GET_DATA_CALLBACK   Callback,
	IN VOID                                            *Context
	);

typedef EFI_STATUS(EFIAPI * EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_SET_DATA_CALLBACK)(
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                  *This,
	IN EFI_BLUETOOTH_LE_CONFIG_SMP_SET_DATA_CALLBACK     Callback,
	IN VOID                                              *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_BLUETOOTH_LE_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK) (
	IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                      *This,
	IN EFI_BLUETOOTH_LE_CONFIG_CONNECT_COMPLETE_CALLBACK     Callback,
	IN VOID                                                  *Context
	);

struct  _EFI_BLUETOOTH_LE_CONFIG_PROTOCOL {
	EFI_BLUETOOTH_LE_CONFIG_INIT Init;
	EFI_BLUETOOTH_LE_CONFIG_SCAN Scan;
	EFI_BLUETOOTH_LE_CONFIG_CONNECT Connect;
	EFI_BLUETOOTH_LE_CONFIG_DISCONNECT Disconnect;
	EFI_BLUETOOTH_LE_CONFIG_GET_DATA GetData;
	EFI_BLUETOOTH_LE_CONFIG_SET_DATA SetData;
	EFI_BLUETOOTH_LE_CONFIG_GET_REMOTE_DATA GetRemoteData;
	EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_AUTH_CALLBACK RegisterSmpAuthCallback;
	EFI_BLUETOOTH_LE_CONFIG_SEND_SMP_AUTH_DATA SendSmpAuthData;
	EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_GET_DATA_CALLBACK    RegisterSmpGetDataCallback;
	EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_SET_DATA_CALLBACK    RegisterSmpSetDataCallback;
	EFI_BLUETOOTH_LE_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK RegisterLinkConnectCompleteCallback;
};
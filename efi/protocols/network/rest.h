#pragma once
#include "efi/types.h"
#include "efi/protocols/network/http.h"

// UEFI Spec Section 29.7
#define EFI_REST_PROTOCOL_GUID {0x0DB48A36, 0x4E54, 0xEA9C,{ 0x9B, 0x09, 0x1E, 0xA5, 0xBE, 0x3A, 0x66, 0x0B }}

typedef struct _EFI_REST_PROTOCOL EFI_REST_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_REST_SEND_RECEIVE)(
	IN EFI_REST_PROTOCOL             *This,
	IN EFI_HTTP_MESSAGE              *RequestMessage,
	OUT EFI_HTTP_MESSAGE             *ResponseMessage
	);

typedef EFI_STATUS(EFIAPI *EFI_REST_GET_TIME)(
	IN EFI_REST_PROTOCOL           *This,
	OUT EFI_TIME                   *Time
	);

struct _EFI_REST_PROTOCOL {
	EFI_REST_SEND_RECEIVE          SendReceive;
	EFI_REST_GET_TIME              GetServiceTime;
};

#define EFI_REST_EX_SERVICE_BINDING_PROTOCOL_GUID {0x456bbe01, 0x99d0, 0x45ea, {0xbb, 0x5f, 0x16, 0xd8, 0x4b, 0xed, 0xc5, 0x59}}
#define EFI_REST_EX_PROTOCOL_GUID {0x55648b91, 0xe7d, 0x40a3,{0xa9, 0xb3, 0xa8, 0x15, 0xd7, 0xea, 0xdf, 0x97}}

// EFI_REST_EX_SERVICE_TYPE
typedef enum {
	EFI_REST_EX_SERVICE_UNSPECIFIC = 1,
	EFI_REST_EX_SERVICE_REDFISH,
	EFI_REST_EX_SERVICE_ODATA,
	EFI_REST_EX_SERVICE_VENDOR_SPECIFIC = 0xff,
	EFI_REST_EX_SERVICE_TYPE_MAX
} EFI_REST_EX_SERVICE_TYPE;

// EFI_REST_EX_SERVICE_ACCESS_MODE
typedef enum {
	EFI_REST_EX_SERVICE_IN_BAND_ACCESS = 1,
	EFI_REST_EX_SERVICE_OUT_OF_BAND_ACCESS = 2,
	EFI_REST_EX_SERVICE_ACCESS_MODE_MAX
} EFI_REST_EX_SERVICE_ACCESS_MODE;

// EFI_REST_EX_CONFIG_TYPE
typedef enum {
	EFI_REST_EX_CONFIG_TYPE_HTTP,
	EFI_REST_EX_CONFIG_TYPE_UNSPECIFIC,
	EFI_REST_EX_CONFIG_TYPE_MAX
} EFI_REST_EX_CONFIG_TYPE;

//EFI_REST_EX_SERVICE_INFO_VER
typedef struct {
	UINT8                  Major;
	UINT8                  Minor;
} EFI_REST_EX_SERVICE_INFO_VER;

//EFI_REST_EX_SERVICE_INFO_HEADER
typedef struct {
	UINT32                           Length;
	EFI_REST_EX_SERVICE_INFO_VER     RestServiceInfoVer;
} EFI_REST_EX_SERVICE_INFO_HEADER;

//EFI_REST_EX_SERVICE_INFO v1.0
typedef struct {
	EFI_REST_EX_SERVICE_INFO_HEADER        EfiRestExServiceInfoHeader;
	EFI_REST_EX_SERVICE_TYPE               RestExServiceType;
	EFI_REST_EX_SERVICE_ACCESS_MODE        RestServiceAccessMode;
	EFI_GUID                               VendorRestServiceName;
	UINT32                                 VendorSpecificDataLength;
	UINT8                                  *VendorSpecifcData;
	EFI_REST_EX_CONFIG_TYPE                RestExConfigType;
	UINT8                                  RestExConfigDataLength;
}   EFI_REST_EX_SERVICE_INFO_V_1_0;

//EFI_REST_EX_SERVICE_INFO
typedef union {
	EFI_REST_EX_SERVICE_INFO_HEADER       EfiRestExServiceInfoHeader;
	EFI_REST_EX_SERVICE_INFO_V_1_0        EfiRestExServiceInfoV10;
} EFI_REST_EX_SERVICE_INFO;

// EFI_REST_EX_HTTP_CONFIG_DATA
typedef struct {
	EFI_HTTP_CONFIG_DATA             HttpConfigData;
	UINT32                           SendReceiveTimeout;
} EFI_REST_EX_HTTP_CONFIG_DATA;

//EFI_REST_EX_CONFIG_DATA
typedef UINT8 *EFI_REST_EX_CONFIG_DATA;

//EFI_REST_EX_TOKEN
typedef struct {
	EFI_EVENT                Event;
	EFI_STATUS               Status;
	EFI_HTTP_MESSAGE         *ResponseMessage;
} EFI_REST_EX_TOKEN;

typedef struct _EFI_REST_EX_PROTOCOL EFI_REST_EX_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_REST_EX_GET_SERVICE)(
	IN EFI_REST_EX_PROTOCOL          *This,
	OUT EFI_REST_EX_SERVICE_INFO     **RestExServiceInfo
	);

typedef EFI_STATUS(EFIAPI *EFI_REST_EX_GET_MODE_DATA)(
	IN EFI_REST_EX_PROTOCOL            *This,
	OUT EFI_REST_EX_CONFIG_DATA        *RestExConfigData
	);

typedef EFI_STATUS(EFIAPI *EFI_REST_EX_CONFIGURE)(
	IN EFI_REST_EX_PROTOCOL          *This,
	IN EFI_REST_EX_CONFIG_DATA       RestExConfigData
	);

typedef EFI_STATUS(EFIAPI *EFI_REST_EX_ASYNC_SEND_RECEIVE)(
	IN EFI_REST_EX_PROTOCOL              *This,
	IN EFI_HTTP_MESSAGE                  *RequestMessage OPTIONAL,
	IN EFI_REST_EX_TOKEN                 *RestExToken,
	IN UINTN                             *TimeOutInMilliSeconds OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_REST_EX_EVENT_SERVICE)(
	IN EFI_REST_EX_PROTOCOL                *This,
	IN EFI_HTTP_MESSAGE                    *RequestMessage OPTIONAL,
	IN EFI_REST_EX_TOKEN                   *RestExToken
	);

struct _EFI_REST_EX_PROTOCOL {
	EFI_REST_SEND_RECEIVE              SendReceive;
	EFI_REST_GET_TIME                  GetServiceTime;
	EFI_REST_EX_GET_SERVICE            GetService;
	EFI_REST_EX_GET_MODE_DATA          GetModeData;
	EFI_REST_EX_CONFIGURE              Configure;
	EFI_REST_EX_ASYNC_SEND_RECEIVE     AyncSendReceive;
	EFI_REST_EX_EVENT_SERVICE          EventService;
};

#define EFI_REST_JSON_STRUCTURE_PROTOCOL_GUID { 0xa9a048f6, 0x48a0, 0x4714, {0xb7, 0xda, 0xa9, 0xad,0x87, 0xd4, 0xda, 0xc9 }}

typedef CHAR8 *EFI_REST_JSON_RESOURCE_TYPE_DATATYPE;

// EFI_REST_JSON_RESOURCE_TYPE_NAMESPACE
typedef struct _EFI_REST_JSON_RESOURCE_TYPE_NAMESPACE {
	CHAR8        *ResourceTypeName;
	CHAR8        *MajorVersion;
	CHAR8        *MinorVersion;
	CHAR8        *ErrataVersion;
} EFI_REST_JSON_RESOURCE_TYPE_NAMESPACE;

// EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER
typedef struct _EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER {
	EFI_REST_JSON_RESOURCE_TYPE_NAMESPACE      Namespace;
	EFI_REST_JSON_RESOURCE_TYPE_DATATYPE       Datatype;
} EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER;

// EFI_REST_JSON_STRUCTURE_SUPPORTED
typedef struct _EFI_REST_JSON_STRUCTURE_SUPPORTED {
	struct _EFI_REST_JSON_STRUCTURE_SUPPORTED            *Next;
	EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER   JsonResourceType;
} EFI_REST_JSON_STRUCTURE_SUPPORTED;

// EFI_REST_JSON_STRUCTURE_HEADER
typedef struct _EFI_REST_JSON_STRUCTURE_HEADER {
	EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER     JsonRsrcIdentifier;
	//
	// Follow by a pointer points to JSON structure, the content in the
	// JSON structure is implementation-specific according to converter producer.
	//
	VOID                                     *JsonStructurePointer;
} EFI_REST_JSON_STRUCTURE_HEADER;

typedef struct _EFI_REST_JSON_STRUCTURE_PROTOCOL EFI_REST_JSON_STRUCTURE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_REST_JSON_STRUCTURE_TO_STRUCTURE)(
	IN   EFI_REST_JSON_STRUCTURE_PROTOCOL          *This,
	IN   EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER    *JsonRsrcIdentifier OPTIONAL,
	IN   CHAR8                                     *ResourceJsonText,
	OUT   EFI_REST_JSON_STRUCTURE_HEADER           **JsonStructure
);

typedef EFI_STATUS(EFIAPI *EFI_REST_JSON_STRUCTURE_TO_JSON)(
	IN EFI_REST_JSON_STRUCTURE_PROTOCOL        *This,
	IN EFI_REST_JSON_STRUCTURE_HEADER          *JsonStructureHeader,
	OUT CHAR8                                  **ResourceJsonText
	);

typedef EFI_STATUS(EFIAPI *EFI_REST_JSON_STRUCTURE_DESTROY_STRUCTURE)(
	IN EFI_REST_JSON_STRUCTURE_PROTOCOL        *This,
	IN EFI_REST_JSON_STRUCTURE_HEADER          *JsonStructureHeader
	);

typedef EFI_STATUS(EFIAPI *EFI_REST_JSON_STRUCTURE_REGISTER)(
	IN EFI_REST_JSON_STRUCTURE_PROTOCOL          *This,
	IN EFI_REST_JSON_STRUCTURE_SUPPORTED         *JsonStructureSupported,
	IN EFI_REST_JSON_STRUCTURE_TO_STRUCTURE      ToStructure,
	IN EFI_REST_JSON_STRUCTURE_TO_JSON           ToJson,
	IN EFI_REST_JSON_STRUCTURE_DESTROY_STRUCTURE           DestroyStructure
	);

struct _EFI_REST_JSON_STRUCTURE_PROTOCOL {
	EFI_REST_JSON_STRUCTURE_REGISTER             Register;
	EFI_REST_JSON_STRUCTURE_TO_STRUCTURE         ToStructure;
	EFI_REST_JSON_STRUCTURE_TO_JSON              ToJson;
	EFI_REST_JSON_STRUCTURE_DESTROY_STRUCTURE    DestoryStructure;
};
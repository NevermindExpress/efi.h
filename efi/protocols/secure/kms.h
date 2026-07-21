#pragma once
#include "efi/types.h"

// UEFI Spec Section 37.3
#define EFI_KMS_PROTOCOL_GUID {0xEC3A978D,0x7C4E, 0x48FA,{0x9A,0xBE,0x6A,0xD9,0x1C,0xC8,0xF8,0x11}}

#define EFI_KMS_DATA_TYPE_NONE      0
#define EFI_KMS_DATA_TYPE_BINARY    1
#define EFI_KMS_DATA_TYPE_ASCII     2
#define EFI_KMS_DATA_TYPE_UNICODE   4
#define EFI_KMS_DATA_TYPE_UTF8      8

#define EFI_KMS_ATTRIBUTE_TYPE_NONE          0x00
#define EFI_KMS_ATTRIBUTE_TYPE_INTEGER       0x01
#define EFI_KMS_ATTRIBUTE_TYPE_LONG_INTEGER  0x02
#define EFI_KMS_ATTRIBUTE_TYPE_BIG_INTEGER   0x03
#define EFI_KMS_ATTRIBUTE_TYPE_ENUMERATION   0x04
#define EFI_KMS_ATTRIBUTE_TYPE_BOOLEAN       0x05
#define EFI_KMS_ATTRIBUTE_TYPE_BYTE_STRING   0x06
#define EFI_KMS_ATTRIBUTE_TYPE_TEXT_STRING   0x07
#define EFI_KMS_ATTRIBUTE_TYPE_DATE_TIME     0x08
#define EFI_KMS_ATTRIBUTE_TYPE_INTERVAL      0x09
#define EFI_KMS_ATTRIBUTE_TYPE_STRUCTURE     0x0A
#define EFI_KMS_ATTRIBUTE_TYPE_DYNAMIC       0x0B

#define EFI_KMS_FORMAT_GENERIC_128_GUID			{0xec8a3d69, 0x6ddf, 0x4108, {0x94, 0x76, 0x73, 0x37, 0xfc, 0x52, 0x21, 0x36}}
#define EFI_KMS_FORMAT_GENERIC_160_GUID			{0xa3b3e6f8, 0xefca, 0x4bc1, {0x88, 0xfb, 0xcb, 0x87, 0x33, 0x9b, 0x25, 0x79}}
#define EFI_KMS_FORMAT_GENERIC_256_GUID			{0x70f64793, 0xc323, 0x4261, {0xac, 0x2c, 0xd8, 0x76, 0xf2, 0x7c, 0x53, 0x45}}
#define EFI_KMS_FORMAT_GENERIC_512_GUID			{0x978fe043, 0xd7af, 0x422e, {0x8a, 0x92, 0x2b, 0x48, 0xe4, 0x63, 0xbd, 0xe6}}
#define EFI_KMS_FORMAT_GENERIC_1024_GUID		{0x43be0b44, 0x874b, 0x4ead, {0xb0, 0x9c, 0x24, 0x1a, 0x4f, 0xbd, 0x7e, 0xb3}}
#define EFI_KMS_FORMAT_GENERIC_2048_GUID		{0x40093f23, 0x630c, 0x4626, {0x9c, 0x48, 0x40, 0x37, 0x3b, 0x19, 0xcb, 0xbe}}
#define EFI_KMS_FORMAT_GENERIC_3072_GUID		{0xb9237513, 0x6c44, 0x4411, {0xa9, 0x90, 0x21, 0xe5, 0x56, 0xe0, 0x5a, 0xde}}
#define EFI_KMS_FORMAT_GENERIC_DYNAMIC_GUID		{0x2156e996, 0x66de, 0x4b27, {0x9c, 0xc9, 0xb0, 0x9f, 0xac, 0x4d, 0x02, 0xbe}}

#define EFI_KMS_FORMAT_MD2_128_GUID				{0x78be11c4,0xee44,0x4a22,{0x9f,0x05,0x03,0x85,0x2e,0xc5,0xc9,0x78}}
#define EFI_KMS_FORMAT_MDC2_128_GUID			{0xf7ad60f8,0xefa8,0x44a3,{0x91,0x13,0x23,0x1f,0x39,0x9e,0xb4,0xc7}}
#define EFI_KMS_FORMAT_MD4_128_GUID				{0xd1c17aa1,0xcac5,0x400f,{0xbe,0x17,0xe2,0xa2,0xae,0x06,0x67,0x7c}}
#define EFI_KMS_FORMAT_MDC4_128_GUID			{0x3fa4f847,0xd8eb,0x4df4,{0xbd,0x49,0x10,0x3a,0x0a,0x84,0x7b,0xbc}}
#define EFI_KMS_FORMAT_MD5_128_GUID				{0xdcbc3662,0x9cda,0x4b52,{0xa0,0x4c,0x82,0xeb,0x1d,0x23,0x48,0xc7}}
#define EFI_KMS_FORMAT_MD5SHA_128_GUID			{0x1c178237,0x6897,0x459e,{0x9d,0x36,0x67,0xce,0x8e,0xf9,0x4f,0x76}}
#define EFI_KMS_FORMAT_SHA1_160_GUID			{0x453c5e5a,0x482d,0x43f0,{0x87,0xc9,0x59,0x41,0xf3,0xa3,0x8a,0xc2}}
#define EFI_KMS_FORMAT_SHA256_256_GUID			{0x6bb4f5cd,0x8022,0x448d,{0xbc,0x6d,0x77,0x1b,0xae,0x93,0x5f,0xc6}}
#define EFI_KMS_FORMAT_SHA512_512_GUID			{0x2f240e12,0xe14d,0x475c,{0x83,0xb0,0xef,0xff,0x22,0xd7,0x7b,0xe7}}

#define EFI_KMS_FORMAT_AESXTS_128_GUID			{0x4776e33f,0xdb47,0x479a,{0xa2,0x5f,0xa1,0xcd,0x0a,0xfa,0xb3,0x8b}}
#define EFI_KMS_FORMAT_AESXTS_256_GUID			{0xdc7e8613,0xc4bb,0x4db0,{0x84,0x62,0x13,0x51,0x13,0x57,0xab,0xe2}}
#define EFI_KMS_FORMAT_AESCBC_128_GUID			{0xa0e8ee6a,0x0e92,0x44d4,{0x86,0x1b,0x0e,0xaa,0x4a,0xca,0x44,0xa2}}
#define EFI_KMS_FORMAT_AESCBC_256_GUID			{0xd7e69789,0x1f68,0x45e8,{0x96,0xef,0x3b,0x64,0x07,0xa5,0xb2,0xdc}}
#define EFI_KMS_FORMAT_RSASHA1_1024_GUID		{0x56417bed,0x6bbe,0x4882,{0x86,0xa0,0x3a,0xe8,0xbb,0x17,0xf8,0xf9}}
#define EFI_KMS_FORMAT_RSASHA1_2048_GUID		{0xf66447d4,0x75a6,0x463e,{0xa8,0x19,0x07,0x7f,0x2d,0xda,0x05,0xe9}}
#define EFI_KMS_FORMAT_RSASHA256_2048_GUID		{0xa477af13,0x877d,0x4060,{0xba,0xa1,0x25,0xd1,0xbe,0xa0,0x8a,0xd3}}
#define EFI_KMS_FORMAT_RSASHA256_3072_GUID		{0x4e1356c2,0xeed, 0x463f,{0x81,0x47,0x99,0x33,0xab 0xdb,0xc7,0xd5}}

typedef struct {
	UINT16          ClientIdSize;
	VOID            *ClientId;
	UINT8           ClientNameType;
	UINT8           ClientNameCount;
	VOID            *ClientName;
} EFI_KMS_CLIENT_INFO;

typedef struct {
	UINT32          KeySize;
	UINT8           KeyData[1];
} EFI_KMS_FORMAT_GENERIC_DYNAMIC;

typedef struct {
	UINT8           KeyIdentifierType;
	UINT8           KeyIdentifierSize;
	VOID            *KeyIdentifier;
	EFI_GUID        KeyFormat;
	VOID            *KeyValue;
	EFI_STATUS      KeyStatus;
}   EFI_KMS_KEY_DESCRIPTOR;

typedef struct _EFI_KMS_SERVICE_PROTOCOL EFI_KMS_PROTOCOL;

typedef struct {
	UINT16         Tag;
	UINT16         Type;
	UINT32         Length;
	UINT8          KeyAttributeData[1];
} EFI_KMS_DYNAMIC_FIELD;

typedef struct {
	UINT32                                 FieldCount;
	EFI_KMS_DYNAMIC_FIELD                  Field[1];
} EFI_KMS_DYNAMIC_ATTRIBUTE;

typedef struct {
	UINT8              KeyAttributeIdentifierType;
	UINT8              KeyAttributeIdentifierCount;
	VOID               *KeyAttributeIdentifier;
	UINT16             KeyAttributeInstance;
	UINT16             KeyAttributeType;
	UINT16             KeyAttributeValueSize;
	VOID               *KeyAttributeValue;
	EFI_STATUS         KeyAttributeStatus;
} EFI_KMS_KEY_ATTRIBUTE;

typedef EFI_STATUS(EFIAPI *EFI_KMS_GET_SERVICE_STATUS) (IN EFI_KMS_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_KMS_REGISTER_CLIENT) (
	IN    EFI_KMS_PROTOCOL            *This,
	IN    EFI_KMS_CLIENT_INFO         *Client,
	IN OUT UINTN                      *ClientDataSize OPTIONAL,
	IN OUT VOID                       **ClientData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_KMS_CREATE_KEY) (
	IN   EFI_KMS_PROTOCOL             *This,
	IN   EFI_KMS_CLIENT_INFO          *Client,
	IN OUT UINT16                     *KeyDescriptorCount,
	IN OUT EFI_KMS_KEY_DESCRIPTOR     *KeyDescriptors,
	IN OUT UINTN                      *ClientDataSize OPTIONAL,
	IN OUT VOID                       **ClientData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_KMS_GET_KEY) (
	IN   EFI_KMS_PROTOCOL             *This,
	IN   EFI_KMS_CLIENT_INFO          *Client,
	IN OUT UINT16                     *KeyDescriptorCount,
	IN OUT EFI_KMS_KEY_DESCRIPTOR     *KeyDescriptors,
	IN OUT UINTN                      *ClientDataSize OPTIONAL,
	IN OUT VOID                       **ClientData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_KMS_ADD_KEY) (
	IN    EFI_KMS_PROTOCOL               *This,
	IN    EFI_KMS_CLIENT_INFO            *Client,
	IN OUT UINT16                        *KeyDescriptorCount,
	IN OUT EFI_KMS_KEY_DESCRIPTOR        *KeyDescriptors,
	IN OUT UINTN                         *ClientDataSize OPTIONAL,
	IN OUT VOID                          **ClientData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_KMS_DELETE_KEY) (
	IN    EFI_KMS_PROTOCOL                  *This,
	IN EFI_KMS_CLIENT_INFO                  *Client,
	IN OUT UINT16                           *KeyDescriptorCount,
	IN OUT EFI_KMS_KEY_DESCRIPTOR           *KeyDescriptors,
	IN OUT UINTN                            *ClientDataSize OPTIONAL,
	IN OUT VOID                             **ClientData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_KMS_GET_KEY_ATTRIBUTES) (
	IN  EFI_KMS_PROTOCOL                  *This,
	IN  EFI_KMS_CLIENT_INFO               *Client,
	IN  UINT8                             *KeyIdentifierSize,
	IN  CONST VOID                        *KeyIdentifier,
	IN OUT UINT16                         *KeyAttributesCount,
	IN OUT EFI_KMS_KEY_ATTRIBUTE          *KeyAttributes,
	IN OUT UINTN                          *ClientDataSize OPTIONAL,
	IN OUT VOID                           **ClientData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_KMS_ADD_KEY_ATTRIBUTES) (
	IN   EFI_KMS_PROTOCOL                   *This,
	IN   EFI_KMS_CLIENT_INFO                *Client,
	IN   UINT8                               *KeyIdentifierSize,
	IN   CONST VOID                         *KeyIdentifier,
	IN OUT UINT16                           *KeyAttributesCount,
	IN OUT EFI_KMS_KEY_ATTRIBUTE            *KeyAttributes,
	IN OUT UINTN                            *ClientDataSize OPTIONAL,
	IN OUT VOID                             **ClientData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_KMS_DELETE_KEY_ATTRIBUTES) (
	IN   EFI_KMS_PROTOCOL                *This,
	IN   EFI_KMS_CLIENT_INFO             *Client,
	IN   UINT8                           *KeyIdentifierSize,
	IN   CONST VOID                      *KeyIdentifier,
	IN OUT UINT16                        *KeyAttributesCount,
	IN OUT EFI_KMS_KEY_ATTRIBUTE         *KeyAttributes,
	IN OUT UINTN                         *ClientDataSize OPTIONAL,
	IN OUT VOID                          **ClientData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_KMS_GET_KEY_BY_ATTRIBUTES) (
	IN   EFI_KMS_PROTOCOL                  *This,
	IN   EFI_KMS_CLIENT_INFO               *Client,
	IN   UINTN                             *KeyAttributeCount,
	IN OUT EFI_KMS_KEY_ATTRIBUTE           *KeyAttributes,
	IN OUT UINTN                           *KeyDescriptorCount,
	IN OUT EFI_KMS_KEY_DESCRIPTOR          *KeyDescriptors,
	IN OUT UINTN                           *ClientDataSize OPTIONAL,
	IN OUT VOID                            **ClientData OPTIONAL
	);

struct _EFI_KMS_SERVICE_PROTOCOL {
	EFI_KMS_GET_SERVICE_STATUS        GetServiceStatus;
	EFI_KMS_REGISTER_CLIENT           RegisterClient;
	EFI_KMS_CREATE_KEY                CreateKey;
	EFI_KMS_GET_KEY                   GetKey;
	EFI_KMS_ADD_KEY                   AddKey;
	EFI_KMS_DELETE_KEY                DeleteKey;
	EFI_KMS_GET_KEY_ATTRIBUTES        GetKeyAttributes;
	EFI_KMS_ADD_KEY_ATTRIBUTES        AddKeyAttributes;
	EFI_KMS_DELETE_KEY_ATTRIBUTES     DeleteKeyAttributes;
	EFI_KMS_GET_KEY_BY_ATTRIBUTES     GetKeyByAttributes;
	UINT32                            ProtocolVersion;
	EFI_GUID                          ServiceId;
	CHAR16                            *ServiceName;
	UINT32                            ServiceVersion;
	BOOLEAN                           ServiceAvailable;
	BOOLEAN                           ClientIdSupported;
	BOOLEAN                           ClientIdRequired;
	UINT16                            ClientIdMaxSize;
	UINT8                             ClientNameStringTypes;
	BOOLEAN                           ClientNameRequired;
	UINT16                            ClientNameMaxCount;
	BOOLEAN                           ClientDataSupported;
	UINTN                             ClientDataMaxSize;
	BOOLEAN                           KeyIdVariableLenSupported;
	UINTN                             KeyIdMaxSize;
	UINTN                             KeyFormatsCount;
	EFI_GUID                          *KeyFormats;
	BOOLEAN                           KeyAttributesSupported;
	UINT8                             KeyAttributeIdStringTypes;
	UINT16                            KeyAttributeIdMaxCount;
	UINTN                             KeyAttributesCount;
	EFI_KMS_KEY_ATTRIBUTE             *KeyAttributes;
};
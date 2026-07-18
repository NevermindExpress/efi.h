#pragma once
#include "efi/types.h"

// UEFI Spec Section 28.9
#define EFI_TLS_SERVICE_BINDING_PROTOCOL_GUID {0x952cb795, 0xff36, 0x48cf, 0xa2, 0x49, 0x4d, 0xf4, 0x86, 0xd6, 0xab, 0x8d}
#define EFI_TLS_PROTOCOL_GUID { 0xca959f, 0x6cfa, 0x4db1,{0x95, 0xbc, 0xe4, 0x6c, 0x47, 0x51, 0x43, 0x90 }}

// EFI_TLS_VERIFY
typedef UINT32 EFI_TLS_VERIFY;
#define EFI_TLS_VERIFY_NONE                  0x0
#define EFI_TLS_VERIFY_PEER                  0x1
#define EFI_TLS_VERIFY_FAIL_IF_NO_PEER_CERT  0x2
#define EFI_TLS_VERIFY_CLIENT_ONCE           0x4

// EFI_TLS_VERIFY_HOST_FLAG
typedef UINT32 EFI_TLS_VERIFY_HOST_FLAG;
#define EFI_TLS_VERIFY_FLAG_NONE                      0x00
#define EFI_TLS_VERIFY_FLAG_ALWAYS_CHECK_SUBJECT      0x01
#define EFI_TLS_VERIFY_FLAG_NO_WILDCARDS              0x02
#define EFI_TLS_VERIFY_FLAG_NO_PARTIAL_WILDCARDS      0x04
#define EFI_TLS_VERIFY_FLAG_MULTI_LABEL_WILDCARDS     0x08
#define EFI_TLS_VERIFY_FLAG_SINGLE_LABEL_SUBDOMAINS   0x10
#define EFI_TLS_VERIFY_FLAG_NEVER_CHECK_SUBJECT       0x20

#define MAX_TLS_SESSION_ID_LENGTH 32

// EFI_TLS_SESSION_DATA_TYPE
typedef enum {
	EfiTlsVersion,
	EfiTlsConnectionEnd,
	EfiTlsCipherList,
	EfiTlsCompressionMethod,
	EfiTlsExtensionData,
	EfiTlsVerifyMethod,
	EfiTlsSessionID,
	EfiTlsSessionState,
	EfiTlsClientRandom,
	EfiTlsServerRandom,
	EfiTlsKeyMaterial,
	EfiTlsVerifyHost,
	EfiTlsSessionDataTypeMaximum
} EFI_TLS_SESSION_DATA_TYPE;

// EFI_TLS_CONNECTION_END
typedef enum {
	EfiTlsClient,
	EfiTlsServer,
} EFI_TLS_CONNECTION_END;

// EFI_TLS_SESSION_STATE
typedef enum {
	EfiTlsSessionNotStarted,
	EfiTlsSessionHandShaking,
	EfiTlsSessionDataTransferring,
	EfiTlsSessionClosing,
	EfiTlsSessionError,
	EfiTlsSessionStateMaximum
}   EFI_TLS_SESSION_STATE;

// EFI_TLS_CRYPT_MODE
typedef enum {
	EfiTlsEncrypt,
	EfiTlsDecrypt,
}   EFI_TLS_CRYPT_MODE;

// EFI_TLS_COMPRESSION
typedef UINT8 EFI_TLS_COMPRESSION;

// EFI_TLS_VERSION
typedef struct {
	UINT8        Major;
	UINT8        Minor;
}  EFI_TLS_VERSION;

// EFI_TLS_CIPHER
typedef struct {
	UINT8             Data1;
	UINT8             Data2;
} EFI_TLS_CIPHER;

// EFI_TLS_EXTENSION
typedef struct {
	UINT16       ExtensionType;
	UINT16       Length;
	UINT8        Data[];
} EFI_TLS_EXTENSION;

// EFI_TLS_VERIFY_HOST
typedef struct {
	EFI_TLS_VERIFY_HOST_FLAG         Flags;
	CHAR8                            *HostName;
}   EFI_TLS_VERIFY_HOST;

// EFI_TLS_RANDOM
typedef struct {
	UINT32          GmtUnixTime;
	UINT8           RandomBytes[28];
}   EFI_TLS_RANDOM;

// EFI_TLS_MASTER_SECRET
typedef struct {
	UINT8 *Data[48];
}   EFI_TLS_MASTER_SECRET;

// EFI_TLS_SESSION_ID
typedef struct {
	UINT16             Length;
	UINT8              Data[MAX_TLS_SESSION_ID_LENGTH];
}   EFI_TLS_SESSION_ID;

// EFI_TLS_FRAGMENT_DATA
typedef struct {
	UINT32       FragmentLength;
	VOID         *FragmentBuffer;
}   EFI_TLS_FRAGMENT_DATA;

typedef struct _EFI_TLS_PROTOCOL EFI_TLS_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_TLS_SET_SESSION_DATA)(
	IN EFI_TLS_PROTOCOL               *This,
	IN EFI_TLS_SESSION_DATA_TYPE      DataType,
	IN VOID                           *Data,
	IN UINTN                          DataSize
	);

typedef EFI_STATUS(EFIAPI *EFI_TLS_GET_SESSION_DATA)(
	IN EFI_TLS_PROTOCOL            *This,
	IN EFI_TLS_SESSION_DATA_TYPE   DataType,
	IN OUT VOID                    *Data, OPTIONAL
	IN OUT UINTN                   *DataSize
	);

typedef EFI_STATUS(EFIAPI *EFI_TLS_BUILD_RESPONSE_PACKET)(
	IN EFI_TLS_PROTOCOL         *This,
	IN UINT8                    *RequestBuffer, OPTIONAL
	IN UINTN                    RequestSize, OPTIONAL
	OUT UINT8                   *Buffer, OPTIONAL
	IN OUT UINTN                *BufferSize
	);

typedef EFI_STATUS(EFIAPI *EFI_TLS_PROCESS_PACKET)(
	IN EFI_TLS_PROTOCOL                 *This,
	IN OUT EFI_TLS_FRAGMENT_DATA        **FragmentTable,
	IN UINT32                           *FragmentCount,
	IN EFI_TLS_CRYPT_MODE               CryptMode
	);

struct _EFI_TLS_PROTOCOL {
	EFI_TLS_SET_SESSION_DATA          SetSessionData;
	EFI_TLS_GET_SESSION_DATA          GetSessionData;
	EFI_TLS_BUILD_RESPONSE_PACKET     BuildResponsePacket;
	EFI_TLS_PROCESS_PACKET            ProcessPacket;
};

#define EFI_TLS_CONFIGURATION_PROTOCOL_GUID { 0x1682fe44, 0xbd7a, 0x4407, {0xb7, 0xc7, 0xdc, 0xa3, 0x7c, 0xa3, 0x92, 0x2d }}

// EFI_TLS_CONFIG_DATA_TYPE
typedef enum {
	EfiTlsConfigDataTypeHostPublicCert,
	EfiTlsConfigDataTypeHostPrivateKey,
	EfiTlsConfigDataTypeCACertificate,
	EfiTlsConfigDataTypeCertRevocationList,
	EfiTlsConfigDataTypeMaximum
} EFI_TLS_CONFIG_DATA_TYPE;

typedef struct _EFI_TLS_CONFIGURATION_PROTOCOL EFI_TLS_CONFIGURATION_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_TLS_CONFIGURATION_SET_DATA)(
	IN EFI_TLS_CONFIGURATION_PROTOCOL       *This,
	IN EFI_TLS_CONFIG_DATA_TYPE              DataType,
	IN VOID                                 *Data,
	IN UINTN                                DataSize
	);

typedef EFI_STATUS(EFIAPI *EFI_TLS_CONFIGURATION_GET_DATA)(
	IN EFI_TLS_CONFIGURATION_PROTOCOL          *This,
	IN EFI_TLS_CONFIG_DATA_TYPE                DataType,
	IN OUT VOID                                *Data, OPTIONAL
	IN OUT UINTN                               *DataSize
	);

struct _EFI_TLS_CONFIGURATION_PROTOCOL {
	EFI_TLS_CONFIGURATION_SET_DATA          SetData;
	EFI_TLS_CONFIGURATION_GET_DATA          GetData;
};
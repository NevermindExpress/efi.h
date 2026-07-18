#pragma once
#include "efi/types.h"

// UEFI Spec Section 27.2

#define EFI_EAP_PROTOCOL_GUID { 0x5d9f96db, 0xe731, 0x4caa,{0xa0, 0x0d, 0x72, 0xe1, 0x87, 0xcd, 0x77, 0x62 }}

//
// Type for the identification number assigned to the Port by the
// System in which the Port resides.
//
typedef VOID * EFI_PORT_HANDLE;

//
// EAP Authentication Method Type (RFC 3748)
//
#define EFI_EAP_TYPE_TLS 13 /* REQUIRED - RFC 5216 */

typedef EFI_STATUS(EFIAPI *EFI_EAP_BUILD_RESPONSE_PACKET) (
	IN EFI_PORT_HANDLE         PortNumber,
	IN UINT8                   *RequestBuffer,
	IN UINTN                   RequestSize,
	IN UINT8                   *Buffer,
	IN OUT UINTN               *BufferSize
	);

typedef struct _EFI_EAP_PROTOCOL EFI_EAP_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_EAP_SET_DESIRED_AUTHENTICATION_METHOD) (
	IN struct _EFI_EAP_PROTOCOL          *This,
	IN UINT8                             EapAuthType
	);

typedef EFI_STATUS(EFIAPI *EFI_EAP_REGISTER_AUTHENTICATION_METHOD) (
	IN struct _EFI_EAP_PROTOCOL          *This,
	IN UINT8                             EapAuthType,
	IN EFI_EAP_BUILD_RESPONSE_PACKET     Handler
	);

struct _EFI_EAP_PROTOCOL {
	EFI_EAP_SET_DESIRED_AUTHENTICATION_METHOD    SetDesiredAuthMethod;
	EFI_EAP_REGISTER_AUTHENTICATION_METHOD       RegisterAuthMethod;
};

#define EFI_EAP_MANAGEMENT_PROTOCOL_GUID { 0xbb62e663, 0x625d, 0x40b2, { 0xa0, 0x88, 0xbb, 0xe8, 0x36, 0x23, 0xa2, 0x45 }

// PAE Capabilities
#define PAE_SUPPORT_AUTHENTICATOR   0x01
#define PAE_SUPPORT_SUPPLICANT      0x02

// Definitions for ValidFieldMask
#define AUTH_PERIOD_FIELD_VALID      0x01
#define HELD_PERIOD_FIELD_VALID      0x02
#define START_PERIOD_FIELD_VALID     0x04
#define MAX_START_FIELD_VALID        0x08

// Supplicant PAE state machine (IEEE Std 802.1X Section 8.5.10)
typedef enum _EFI_EAPOL_SUPPLICANT_PAE_STATE {
	Logoff,
	Disconnected,
	Connecting,
	Acquired,
	Authenticating,
	Held,
	Authenticated,
	MaxSupplicantPaeState
}   EFI_EAPOL_SUPPLICANT_PAE_STATE;

typedef struct _EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION {
	UINT8                              ValidFieldMask;
	UINTN                              AuthPeriod;
	UINTN                              HeldPeriod;
	UINTN                              StartPeriod;
	UINTN                              MaxStart;
}   EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION;

typedef struct _EFI_EAPOL_PORT_INFO {
	EFI_PORT_HANDLE                   PortNumber;
	UINT8                             ProtocolVersion;
	UINT8                             PaeCapabilities;
}   EFI_EAPOL_PORT_INFO;

// Supplicant Statistics (IEEE Std 802.1X Section 9.5.2)
typedef struct _EFI_EAPOL_SUPPLICANT_PAE_STATISTICS {
	UINTN  EapolFramesReceived;
	UINTN  EapolFramesTransmitted;
	UINTN  EapolStartFramesTransmitted;
	UINTN  EapolLogoffFramesTransmitted;
	UINTN  EapRespIdFramesTransmitted;
	UINTN  EapResponseFramesTransmitted;
	UINTN  EapReqIdFramesReceived;
	UINTN  EapRequestFramesReceived;
	UINTN  InvalidEapolFramesReceived;
	UINTN  EapLengthErrorFramesReceived;
	UINTN  LastEapolFrameVersion;
	UINTN  LastEapolFrameSource;
}   EFI_EAPOL_SUPPLICANT_PAE_STATISTICS;

typedef struct _EFI_EAP_MANAGEMENT_PROTOCOL EFI_EAP_MANAGEMENT_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_EAP_GET_SYSTEM_CONFIGURATION) (
	IN struct _EFI_EAP_MANAGEMENT_PROTOCOL  *This,
	OUT BOOLEAN                             *SystemAuthControl,
	OUT EFI_EAPOL_PORT_INFO                 *PortInfo OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_EAP_SET_SYSTEM_CONFIGURATION) (
	IN struct _EFI_EAP_MANAGEMENT_PROTOCOL    *This,
	IN BOOLEAN                                SystemAuthControl
	);

typedef EFI_STATUS(EFIAPI *EFI_EAP_INITIALIZE_PORT) (IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_EAP_USER_LOGON) (IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_EAP_USER_LOGOFF) (IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_EAP_GET_SUPPLICANT_STATUS) (
	IN struct _EFI_EAP_MANAGEMENT_PROTOCOL           *This,
	OUT EFI_EAPOL_SUPPLICANT_PAE_STATE               *CurrentState,
	IN OUT EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION    *Configuration OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_EAP_SET_SUPPLICANT_CONFIGURATION) (
	IN struct _EFI_EAP_MANAGEMENT_PROTOCOL        *This,
	IN EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION     *Configuration
	);

typedef EFI_STATUS(EFIAPI *EFI_EAP_GET_SUPPLICANT_STATISTICS) (
	IN struct _EFI_EAP_MANAGEMENT_PROTOCOL        *This,
	OUT EFI_EAPOL_SUPPLICANT_PAE_STATISTICS       *Statistics
	);

struct _EFI_EAP_MANAGEMENT_PROTOCOL {
	EFI_EAP_GET_SYSTEM_CONFIGURATION        GetSystemConfiguration;
	EFI_EAP_SET_SYSTEM_CONFIGURATION        SetSystemConfiguration;
	EFI_EAP_INITIALIZE_PORT                 InitializePort;
	EFI_EAP_USER_LOGON                      UserLogon;
	EFI_EAP_USER_LOGOFF                     UserLogoff;
	EFI_EAP_GET_SUPPLICANT_STATUS           GetSupplicantStatus;
	EFI_EAP_SET_SUPPLICANT_CONFIGURATION    SetSupplicantConfiguration;
	EFI_EAP_GET_SUPPLICANT_STATISTICS       GetSupplicantStatistics;
};

#define EFI_EAP_MANAGEMENT2_PROTOCOL_GUID { 0x5e93c847, 0x456d, 0x40b3, { 0xa6, 0xb4, 0x78, 0xb0, 0xc9, 0xcf, 0x7f, 0x20 }}

typedef struct _EFI_EAP_MANAGEMENT2_PROTOCOL EFI_EAP_MANAGEMENT2_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_EAP_GET_KEY)(
	IN EFI_EAP_MANAGEMENT2_PROTOCOL   *This,
	IN OUT UINT8                      *Msk,
	IN OUT UINTN                      *MskSize,
	IN OUT UINT8                      *Emsk,
	IN OUT UINT8                      *EmskSize
	);

struct _EFI_EAP_MANAGEMENT2_PROTOCOL {
	EFI_EAP_GET_SYSTEM_CONFIGURATION        GetSystemConfiguration;
	EFI_EAP_SET_SYSTEM_CONFIGURATION        SetSystemConfiguration;
	EFI_EAP_INITIALIZE_PORT                 InitializePort;
	EFI_EAP_USER_LOGON                      UserLogon;
	EFI_EAP_USER_LOGOFF                     UserLogoff;
	EFI_EAP_GET_SUPPLICANT_STATUS           GetSupplicantStatus;
	EFI_EAP_SET_SUPPLICANT_CONFIGURATION    SetSupplicantConfiguration;
	EFI_EAP_GET_SUPPLICANT_STATISTICS       GetSupplicantStatistics;
	EFI_EAP_GET_KEY                        GetKey;
};

#define EFI_EAP_CONFIGURATION_PROTOCOL_GUID { 0xe5b58dbb, 0x7688, 0x44b4,{ 0x97, 0xbf, 0x5f, 0x1d, 0x4b, 0x7c, 0xc8, 0xdb }}

// EFI_EAP_TYPE
typedef UINT8 EFI_EAP_TYPE;
#define EFI_EAP_TYPE_ATTRIBUTE     0
#define EFI_EAP_TYPE_IDENTITY      1
#define EFI_EAP_TYPE_NOTIFICATION  2
#define EFI_EAP_TYPE_NAK           3
#define EFI_EAP_TYPE_MD5CHALLENGE  4
#define EFI_EAP_TYPE_OTP           5
#define EFI_EAP_TYPE_GTC           6
#define EFI_EAP_TYPE_EAPTLS        13
#define EFI_EAP_TYPE_EAPSIM        18
#define EFI_EAP_TYPE_TTLS          21
#define EFI_EAP_TYPE_PEAP          25
#define EFI_EAP_TYPE_MSCHAPV2      26
#define EFI_EAP_TYPE_EAP_EXTENSION 33

typedef enum {
	// EFI_EAP_TYPE_ATTRIBUTE
	EfiEapConfigEapAuthMethod,
	EfiEapConfigEapSupportedAuthMethod,
	// EapTypeIdentity
	EfiEapConfigIdentityString,
	// EapTypeEAPTLS/EapTypePEAP
	EfiEapConfigEapTlsCACert,
	EfiEapConfigEapTlsClientCert,
	EfiEapConfigEapTlsClientPrivateKeyFile,
	EfiEapConfigEapTlsClientPrivateKeyFilePassword, 
	// ASCII format, Volatile
	EfiEapConfigEapTlsCipherSuite,
	EfiEapConfigEapTlsSupportedCipherSuite,
	// EapTypeMSChapV2
	EfiEapConfigEapMSChapV2Password, // UNICODE format, Volatile
	// EapTypePEAP
	EfiEapConfigEap2ndAuthMethod,
	// More...
} EFI_EAP_CONFIG_DATA_TYPE;


typedef struct _EFI_EAP_CONFIGURATION_PROTOCOL EFI_EAP_CONFIGURATION_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_EAP_CONFIGURATION_SET_DATA)(
	IN EFI_EAP_CONFIGURATION_PROTOCOL    *This,
	IN EFI_EAP_TYPE                      EapType,
	IN EFI_EAP_CONFIG_DATA_TYPE          DataType,
	IN VOID                              *Data,
	IN UINTN                             DataSize
	);

typedef EFI_STATUS(EFIAPI *EFI_EAP_CONFIGURATION_GET_DATA)(
	IN EFI_EAP_CONFIGURATION_PROTOCOL      *This,
	IN EFI_EAP_TYPE                         EapType,
	IN EFI_EAP_CONFIG_DATA_TYPE             DataType,
	IN OUT VOID                             *Data,
	IN OUT UINTN                            *DataSize
	);

struct _EFI_EAP_CONFIGURATION_PROTOCOL {
	EFI_EAP_CONFIGURATION_SET_DATA          SetData;
	EFI_EAP_CONFIGURATION_GET_DATA          GetData;
};
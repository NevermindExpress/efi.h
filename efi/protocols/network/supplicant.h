#pragma once
#include "efi/types.h"
#include "efi/protocols/network/wifi.h"

// UEFI Spec Section 27.5
#define EFI_SUPPLICANT_PROTOCOL_GUID { 0x54fcc43e, 0xaa89, 0x4333, { 0x9a, 0x85, 0xcd, 0xea, 0x24, 0x5, 0x1e, 0x9e }}

#define EFI_MAX_KEY_LEN 64

// EFI_SUPPLICANT_CRYPT_MODE
typedef enum {
	EfiSupplicantEncrypt,
	EfiSupplicantDecrypt,
}   EFI_SUPPLICANT_CRYPT_MODE;

// EFI_SUPPLICANT_DATA_TYPE
typedef enum {
	//
	// Session Configuration
	//
	EfiSupplicant80211AKMSuite,
	EfiSupplicant80211GroupDataCipherSuite,
	EfiSupplicant80211PairwiseCipherSuite,
	EfiSupplicant80211PskPassword,
	EfiSupplicant80211TargetSSIDName,
	EfiSupplicant80211StationMac,
	EfiSupplicant80211TargetSSIDMac,
	//
	// Session Information
	//
	EfiSupplicant80211PTK,
	EfiSupplicant80211GTK,
	EfiSupplicantState,
	EfiSupplicant80211LinkState,
	EfiSupplicantKeyRefresh,

	//
	// Session Configuration
	//
	EfiSupplicant80211SupportedAKMSuites,
	EfiSupplicant80211SupportedSoftwareCipherSuites,
	EfiSupplicant80211SupportedHardwareCipherSuites,

	//
	// Session Information
	//
	EfiSupplicant80211IGTK,
	EfiSupplicant80211PMK,
	EfiSupplicantDataTypeMaximum

} EFI_SUPPLICANT_DATA_TYPE;

// EFI_80211_LINK_STATE
typedef enum {
	Ieee80211UnauthenticatedUnassociated,
	Ieee80211AuthenticatedUnassociated,
	Ieee80211PendingRSNAuthentication,
	Ieee80211AuthenticatedAssociated
}   EFI_80211_LINK_STATE;

//**********************************************
// EFI_SUPPLICANT_KEY_TYPE (IEEE Std 802.11
//         Section 6.3.19.1.2)
//**********************************************
typedef enum {
	Group,
	Pairwise,
	PeerKey,
	IGTK
}   EFI_SUPPLICANT_KEY_TYPE;

//**********************************************
// EFI_SUPPLICANT_KEY_DIRECTION (IEEE Std 802.11
//       Section 6.3.19.1.2)
//**********************************************
typedef enum {
	Receive,
	Transmit,
	Both
}   EFI_SUPPLICANT_KEY_DIRECTION;

// EFI_SUPPLICANT_FRAGMENT_DATA
typedef struct {
	UINT32                FragmentLength;
	VOID                  *FragmentBuffer;
}   EFI_SUPPLICANT_FRAGMENT_DATA;

// EFI_SUPPLICANT_KEY_REFRESH
typedef struct {
	BOOLEAN                  GTKRefresh;
}   EFI_SUPPLICANT_KEY_REFRESH;

// EFI_SUPPLICANT_KEY
typedef struct {
	UINT8                        Key[EFI_MAX_KEY_LEN];
	UINT8                        KeyLen;
	UINT8                        KeyId;
	EFI_SUPPLICANT_KEY_TYPE      KeyType;
	EFI_80211_MAC_ADDRESS        Addr;
	UINT8                        Rsc[8];
	UINT8                        RscLen;
	BOOLEAN                      IsAuthenticator;
	EFI_80211_SUITE_SELECTOR     CipherSuite;
	EFI_SUPPLICANT_KEY_DIRECTION Direction;
}   EFI_SUPPLICANT_KEY;

// EFI_SUPPLICANT_GTK_LIST
typedef struct {
	UINT8                     GTKCount;
	EFI_SUPPLICANT_KEY        GTKList[1];
} EFI_SUPPLICANT_GTK_LIST;

typedef struct _EFI_SUPPLICANT_PROTOCOL EFI_SUPPLICANT_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_SUPPLICANT_BUILD_RESPONSE_PACKET)(
	IN EFI_SUPPLICANT_PROTOCOL           *This,
	IN UINT8                             *RequestBuffer, OPTIONAL
	IN UINTN                             RequestBufferSize, OPTIONAL
	OUT UINT8                            *Buffer,
	IN OUT UINTN                         *BufferSize
	);

typedef EFI_STATUS(EFIAPI *EFI_SUPPLICANT_PROCESS_PACKET)(
	IN EFI_SUPPLICANT_PROTOCOL            *This,
	IN OUT EFI_SUPPLICANT_FRAGMENT_DATA   **FragmentTable,
	IN UINT32                             *FragmentCount,
	IN EFI_SUPPLICANT_CRYPT_MODE          CryptMode
	);

typedef EFI_STATUS(EFIAPI *EFI_SUPPLICANT_SET_DATA)(
	IN EFI_SUPPLICANT_PROTOCOL        *This,
	IN EFI_SUPPLICANT_DATA_TYPE       DataType,
	IN VOID                           *Data,
	IN UINTN                          DataSize
	);

typedef EFI_STATUS(EFIAPI *EFI_SUPPLICANT_GET_DATA)(
	IN EFI_SUPPLICANT_PROTOCOL        *This,
	IN EFI_SUPPLICANT_DATA_TYPE       DataType,
	OUT UINT8                         *Data, OPTIONAL
	IN OUT UINTN                      *DataSize
	);

struct _EFI_SUPPLICANT_PROTOCOL {
	EFI_SUPPLICANT_BUILD_RESPONSE_PACKET     BuildResponsePacket;
	EFI_SUPPLICANT_PROCESS_PACKET            ProcessPacket;
	EFI_SUPPLICANT_SET_DATA                  SetData;
	EFI_SUPPLICANT_GET_DATA                  GetData;
};
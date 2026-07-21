#pragma once
#include "efi/types.h"

// UEFI Spec Section 37.6

#define EFI_SMART_CARD_READER_PROTOCOL_GUID {0x2a4d1adf, 0x21dc, 0x4b81,{0xa4, 0x2f, 0x8b, 0x8e, 0xe2, 0x38, 0x00, 0x60}}

// Codes for access mode
#define SCARD_AM_READER 0x0001 // Exclusive access to reader
#define SCARD_AM_CARD 0x0002 // Exclusive access to card

// Codes for card action
#define SCARD_CA_NORESET 0x0000 // Don’t reset card
#define SCARD_CA_COLDRESET 0x0001 // Perform a cold reset
#define SCARD_CA_WARMRESET 0x0002 // Perform a warm reset
#define SCARD_CA_UNPOWER 0x0003 // Power off the card
#define SCARD_CA_EJECT 0x0004 // Eject the card

// Protocol types
#define SCARD_PROTOCOL_UNDEFINED 0x0000
#define SCARD_PROTOCOL_T0 0x0001
#define SCARD_PROTOCOL_T1 0x0002
#define SCARD_PROTOCOL_RAW 0x0004

// Codes for state type
#define SCARD_UNKNOWN 0x0000 /* state is unknown */
#define SCARD_ABSENT 0x0001 /* Card is absent */
#define SCARD_INACTIVE 0x0002 /* Card is present and not powered*/
#define SCARD_ACTIVE 0x0003 /* Card is present and powered */

// Macro to generate a ControlCode & PC/SC part 10 control code
#define SCARD_CTL_CODE(code) (0x42000000 + (code))
#define CM_IOCTL_GET_FEATURE_REQUEST SCARD_CTL_CODE(3400)

typedef struct _EFI_SMART_CARD_READER_PROTOCOL EFI_SMART_CARD_READER_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_READER_PROTOCOL_CONNECT) (
	IN EFI_SMART_CARD_READER_PROTOCOL       *This,
	IN UINT32                               AccessMode,
	IN UINT32                               CardAction,
	IN UINT32                               PreferredProtocols,
	OUT UINT32                              *ActiveProtocol
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_READER_PROTOCOL_DISCONNECT) (
	IN EFI_SMART_CARD_READER_PROTOCOL         *This,
	IN UINT32                                 CardAction
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_READER_PROTOCOL_STATUS) (
	IN EFI_SMART_CARD_READER_PROTOCOL         *This,
	OUT CHAR16                                *ReaderName OPTIONAL,
	IN OUT UINTN                              *ReaderNameLength OPTIONAL,
	OUT UINT32                                *State OPTIONAL,
	OUT UINT32                                *CardProtocol OPTIONAL,
	OUT UINT8                                 *Atr OPTIONAL,
	IN OUT UINTN                              *AtrLength OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_READER_PROTOCOL_TRANSMIT) (
	IN EFI_SMART_CARD_READER_PROTOCOL            *This,
	IN UINT8                                     *CAPDU,
	IN UINTN                                     CAPDULength,
	OUT UINT8                                    *RAPDU,
	IN OUT UINTN                                 *RAPDULength
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_READER_PROTOCOL_CONTROL) (
	IN EFI_SMART_CARD_READER_PROTOCOL         *This,
	IN UINT32                                 ControlCode,
	IN UINT8                                  *InBuffer OPTIONAL,
	IN UINTN                                  InBufferLength OPTIONAL,
	OUT UINT8                                 *OutBuffer OPTIONAL,
	IN OUT UINTN                              *OutBufferLength OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_READER_PROTOCOL_GET_ATTRIB) (
	IN EFI_SMART_CARD_READER_PROTOCOL         *This,
	IN UINT32                                 Attrib,
	OUT UINT8                                 *OutBuffer,
	IN OUT UINTN                              *OutBufferLength
	);

struct _EFI_SMART_CARD_READER_PROTOCOL {
	EFI_SMART_CARD_READER_PROTOCOL_CONNECT           SCardConnect;
	EFI_SMART_CARD_READER_PROTOCOL_DISCONNECT        SCardDisconnect;
	EFI_SMART_CARD_READER_PROTOCOL_STATUS            SCardStatus;
	EFI_SMART_CARD_READER_PROTOCOL_TRANSMIT          SCardTransmit;
	EFI_SMART_CARD_READER_PROTOCOL_CONTROL           SCardControl;
	EFI_SMART_CARD_READER_PROTOCOL_GET_ATTRIB        SCardGetAttrib;
};

#define EFI_SMART_CARD_EDGE_PROTOCOL_GUID { 0xd317f29b, 0xa325, 0x4712,{ 0x9b, 0xf1, 0xc6, 0x19, 0x54, 0xdc, 0x19, 0x8c }}

// Maximum size for a Smart Card AID (Application IDentifier)
#define SCARD_AID_MAXSIZE 0x0010

// Size of CSN (Card Serial Number)
#define SCARD_CSN_SIZE 0x0010

//Current specification version 1.00
#define SMART_CARD_EDGE_PROTOCOL_VERSION_1 0x00000100

// Parameters type definition
typedef UINT8 SMART_CARD_AID[SCARD_AID_MAXSIZE];
typedef UINT8 SMART_CARD_CSN[SCARD_CSN_SIZE];

//Type of data elements in credentials list
#define SC_EDGE_TAG_HEADER 0x0000 \
        // value of tag field for header,
	  // the number of containers
#define SC_EDGE_TAG_CERT 0x0001 // value of tag field for certificate
#define SC_EDGE_TAG_KEY_ID 0x0002 // value of tag field for key index
		 // associated with certificate
#define SC_EDGE_TAG_KEY_TYPE 0x0003 // value of tag field for key type
#define SC_EDGE_TAG_KEY_SIZE 0x0004 // value of tag field for key size

//Length of L fields of TLV items
#define SC_EDGE_L_SIZE_HEADER 1 // size of L field for header
#define SC_EDGE_L_SIZE_CERT 2 // size of L field for certificate (big endian)
#define SC_EDGE_L_SIZE_KEY_ID 1 // size of L field for key index
#define SC_EDGE_L_SIZE_KEY_TYPE 1 // size of L field for key type
#define SC_EDGE_L_SIZE_KEY_SIZE 2 // size of L field for key size (big endian)

//Some TLV items have a fixed value for L field
#define SC_EDGE_L_VALUE_HEADER 1 // value of L field for header
#define SC_EDGE_L_VALUE_KEY_ID 1 // value of L field for key index
#define SC_EDGE_L_VALUE_KEY_TYPE 1 // value of L field for key type
#define SC_EDGE_L_VALUE_KEY_SIZE 2 // value of L field for key size

//Possible values for key type
#define SC_EDGE_RSA_EXCHANGE 0x01 //RSA decryption
#define SC_EDGE_RSA_SIGNATURE 0x02 //RSA signature
#define SC_EDGE_ECDSA_256 0x03 //ECDSA signature
#define SC_EDGE_ECDSA_384 0x04 //ECDSA signature
#define SC_EDGE_ECDSA_521 0x05 //ECDSA signature
#define SC_EDGE_ECDH_256 0x06 //ECDH agreement
#define SC_EDGE_ECDH_384 0x07 //ECDH agreement
#define SC_EDGE_ECDH_521 0x08 //ECDH agreement

// Padding methods GUIDs for signature

// RSASSA- PKCS#1-V1.5 padding method, for signature
#define EFI_PADDING_RSASSA_PKCS1V1P5_GUID {0x9317ec24,0x7cb0,0x4d0e,{0x8b,0x32,0x2e,0xd9,0x20,0x9c,0xd8,0xaf}}

// RSASSA-PSS padding method, for signature
#define EFI_PADDING_RSASSA_PSS_GUID {0x7b2349e0,0x522d,0x4f8e,{0xb9,0x27,0x69,0xd9,0x7c,0x9e,0x79,0x5f}}

// Padding methods GUIDs for decryption

// No padding, for decryption
#define EFI_PADDING_NONE_GUID \
{0x3629ddb1,0x228c,0x452e,\
{0xb6,0x16,0x09,0xed,0x31,0x6a,0x97,0x00}}

//
// RSAES-PKCS#1-V1.5 padding, for decryption
//
#define EFI_PADDING_RSAES_PKCS1V1P5_GUID \
{0xe1c1d0a9,0x40b1,0x4632,\
{0xbd,0xcc,0xd9,0xd6,0xe5,0x29,0x56,0x31}}

//
// RSAES-OAEP padding, for decryption
//
#define EFI_PADDING_RSAES_OAEP_GUID \
{0xc1e63ac4,0xd0cf,0x4ce6,\
{0x83,0x5b,0xee,0xd0,0xe6,0xa8,0xa4,0x5b}}

typedef struct _EFI_SMART_CARD_EDGE_PROTOCOL EFI_SMART_CARD_EDGE_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_GET_CONTEXT) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL         *This,
	OUT UINTN                               *NumberAidSupported,
	IN OUT UINTN                            *AidTableSize OPTIONAL,
	OUT SMART_CARD_AID                      *AidTable OPTIONAL,
	OUT UINTN                               *NumberSCPresent,
	IN OUT UINTN                            *CsnTableSize OPTIONAL,
	OUT SMART_CARD_CSN                      *CsnTable OPTIONAL,
	OUT UINT32                              *VersionScEdgeProtocol OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_CONNECT) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL      *This,
	OUT EFI_HANDLE                       *SCardHandle,
	IN UINT8                             *ScardCsn OPTIONAL,
	OUT UINT8                            *ScardAid OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_DISCONNECT) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL      *This,
	IN EFI_HANDLE                        SCardHandle
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_GET_CSN) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL      *This,
	IN EFI_HANDLE                        SCardHandle,
	OUT UINT8                            Csn[SCARD_CSN_SIZE]
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_GET_READER_NAME) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL                  *This,
	IN EFI_HANDLE                                    SCardHandle,
	IN OUT UINTN                                     *ReaderNameLength,
	OUT CHAR16                                       *ReaderName OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_VERIFY_PIN) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL         *This,
	IN EFI_HANDLE                           SCardHandle,
	IN INT32                                PinSize,
	IN UINT8                                *PinCode,
	OUT BOOLEAN                             *PinResult,
	OUT UINT32                              *RemainingAttempts OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_GET_PIN_REMAINING) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL      *This,
	IN EFI_HANDLE                        SCardHandle,
	OUT UINT32                           *RemainingAttempts
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_GET_DATA) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL      *This,
	IN EFI_HANDLE                        SCardHandle,
	IN EFI_GUID                          *DataId,
	IN OUT UINTN                         *DataSize,
	OUT VOID                             *Data OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_GET_CREDENTIAL) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL         *This,
	IN EFI_HANDLE                           SCardHandle,
	IN OUT UINTN                            *CredentialSize,
	OUT UINT8                               *CredentialList OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_SIGN_DATA) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL   *This,
	IN EFI_HANDLE                     SCardHandle,
	IN UINTN                          KeyId,
	IN UINTN                          KeyType,
	IN EFI_GUID                       *HashAlgorithm,
	IN EFI_GUID                       *PaddingMethod,
	IN UINT8                          *HashedData,
	OUT UINT8                         *SignatureData
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_DECRYPT_DATA) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL      *This,
	IN EFI_HANDLE                        SCardHandle,
	IN UINTN                             KeyId,
	IN EFI_GUID                          *HashAlgorithm,
	IN EFI_GUID                          *PaddingMethod,
	IN UINTN                             EncryptedSize,
	IN UINT8                             *EncryptedData,
	IN OUT UINTN                         *PlaintextSize,
	OUT UINT8                            *PlaintextData
	);

typedef EFI_STATUS(EFIAPI *EFI_SMART_CARD_EDGE_BUILD_DH_AGREEMENT) (
	IN EFI_SMART_CARD_EDGE_PROTOCOL      *This,
	IN EFI_HANDLE                        SCardHandle,
	IN UINTN                             KeyId,
	IN UINT8                             *dataQx,
	IN UINT8                             *dataQy,
	OUT UINT8                            *DHAgreement
	);

struct _EFI_SMART_CARD_EDGE_PROTOCOL {
	EFI_SMART_CARD_EDGE_GET_CONTEXT         GetContext;
	EFI_SMART_CARD_EDGE_CONNECT             Connect;
	EFI_SMART_CARD_EDGE_DISCONNECT          Disconnect;
	EFI_SMART_CARD_EDGE_GET_CSN             GetCsn;
	EFI_SMART_CARD_EDGE_GET_READER_NAME     GetReaderName;
	EFI_SMART_CARD_EDGE_VERIFY_PIN          VerifyPin;
	EFI_SMART_CARD_EDGE_GET_PIN_REMAINING   GetPinRemaining;
	EFI_SMART_CARD_EDGE_GET_DATA            GetData;
	EFI_SMART_CARD_EDGE_GET_CREDENTIAL      GetCredential;
	EFI_SMART_CARD_EDGE_SIGN_DATA           SignData;
	EFI_SMART_CARD_EDGE_DECRYPT_DATA        DecryptData;
	EFI_SMART_CARD_EDGE_BUILD_DH_AGREEMENT  BuildDHAgreement;
};
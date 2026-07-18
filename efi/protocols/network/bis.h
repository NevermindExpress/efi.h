#pragma once
#include "efi/types.h"

// UEFI Spec Section 24.5

#define EFI_BIS_PROTOCOL_GUID {0x0b64aab0,0x5429,0x11d4,{0x98,0x16,0x00,0xa0,0xc9,0x1f,0xad,0xcf}}

//******************************************************
// EFI_BIS_VERSION predefined values
// Use these values to initialize EFI_BIS_VERSION.Major
// and to interpret results of Initialize.
//******************************************************
#define BIS_CURRENT_VERSION_MAJOR      BIS_VERSION_1
#define BIS_VERSION_1                  1

//******************************************************
// BIS_GET_SIGINFO_COUNT macro
//   Tells how many EFI_BIS_SIGNATURE_INFO elements are contained
//   in a EFI_BIS_DATA struct pointed to by the provided
//   EFI_BIS_DATA*.
//******************************************************
#define BIS_GET_SIGINFO_COUNT(BisDataPtr) ((BisDataPtr)->Length/sizeof(EFI_BIS_SIGNATURE_INFO))

//*******************************************************
// BIS_GET_SIGINFO_ARRAY macro
//   Produces a EFI_BIS_SIGNATURE_INFO* from a given
//   EFI_BIS_DATA.*
//*******************************************************
#define BIS_GET_SIGINFO_ARRAY(BisDataPtr) ((EFI_BIS_SIGNATURE_INFO*)(BisDataPtr)->Data)

//*******************************************************
// BIS_CERT_ID predefined values
//   Currently defined values for EFI_BIS_SIGNATURE_INFO.
//   CertificateId.
//*******************************************************
#define BIS_CERT_ID_DSA   BIS_ALG_DSA   //CSSM_ALGID_DSA
#define BIS_CERT_ID_RSA_MD5  BIS_ALG_RSA_MD5   //CSSM_ALGID_MD5_WITH_RSA

//*******************************************************
// BIS_CERT_ID_MASK
//   The following is a mask value that gets applied to the
//   truncated hash of a platform Boot Object Authorization
//   Certificate to create the CertificateId. A CertificateId
//   must not have any bits set to the value 1 other than bits in
//   this mask.
//*******************************************************
#define BIS_CERT_ID_MASK (0xFF7F7FFF)

//*******************************************************
// BIS_ALG_ID predefined values
//  Currently defined values for EFI_BIS_SIGNATURE_INFO.
//  AlgorithmID. The exact numeric values come from "Common
//  Data Security Architecture (CDSA) Specification."
//*******************************************************
#define BIS_ALG_DSA  (41)   //CSSM_ALGID_DSA
#define BIS_ALG_RSA_MD5  (42)   //CSSM_ALGID_MD5_WITH_RSA

// BIS_ALG_ID
typedef UINT16 BIS_ALG_ID;

// BIS_CERT_ID
typedef UINT32      BIS_CERT_ID;

// BIS_APPLICATION_HANDLE
typedef VOID   *BIS_APPLICATION_HANDLE;

// EFI_BIS_VERSION
typedef struct _EFI_BIS_VERSION{
  UINT32          Major;
  UINT32          Minor;
}   EFI_BIS_VERSION;

//******************************************************
// EFI_BIS_DATA
//
// EFI_BIS_DATA instances obtained from BIS must be freed by
// calling `EFI_BIS_PROTOCOL.Free()`_.
//******************************************************
typedef struct _EFI_BIS_DATA{
  UINT32             Length;
  UINT8              *Data;
}   EFI_BIS_DATA;

// EFI_BIS_SIGNATURE_INFO
typedef struct _EFI_BIS_SIGNATURE_INFO{
  BIS_CERT_ID           CertificateID;
  BIS_ALG_ID            AlgorithmID;
  UINT16                KeyLength;
}   EFI_BIS_SIGNATURE_INFO;

typedef struct _EFI_BIS_PROTOCOL EFI_BIS_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_BIS_INITIALIZE)(
	IN EFI_BIS_PROTOCOL              *This,
	OUT BIS_APPLICATION_HANDLE       *AppHandle,
	IN OUT EFI_BIS_VERSION           *InterfaceVersion,
	IN EFI_BIS_DATA                  *TargetAddress
	);

typedef EFI_STATUS(EFIAPI *EFI_BIS_SHUTDOWN)(IN BIS_APPLICATION_HANDLE    AppHandle);

typedef EFI_STATUS(EFIAPI *EFI_BIS_FREE)(
	IN BIS_APPLICATION_HANDLE   AppHandle,
	IN EFI_BIS_DATA             *ToFree
	);

typedef EFI_STATUS(EFIAPI *EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_CERTIFICATE)(
	IN BIS_APPLICATION_HANDLE         AppHandle,
	OUT EFI_BIS_DATA                  **Certificate
	);

typedef EFI_STATUS(EFIAPI *EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_CHECKFLAG)(
	IN BIS_APPLICATION_HANDLE         AppHandle,
	OUT BOOLEAN                       *CheckIsRequired
	);

typedef EFI_STATUS(EFIAPI *EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_UPDATE_TOKEN)(
	IN BIS_APPLICATION_HANDLE            AppHandle,
	OUT EFI_BIS_DATA                     **UpdateToken
	);

typedef EFI_STATUS(EFIAPI *EFI_BIS_GET_SIGNATURE_INFO)(
	IN BIS_APPLICATION_HANDLE            AppHandle,
	OUT EFI_BIS_DATA                     **SignatureInfo
	);

typedef EFI_STATUS(EFIAPI *EFI_BIS_UPDATE_BOOT_OBJECT_AUTHORIZATION)(
	IN BIS_APPLICATION_HANDLE      AppHandle,
	IN EFI_BIS_DATA                *RequestCredential,
	OUT EFI_BIS_DATA               **NewUpdateToken
	);

typedef EFI_STATUS(EFIAPI *EFI_BIS_VERIFY_BOOT_OBJECT)(
	IN BIS_APPLICATION_HANDLE      AppHandle,
	IN EFI_BIS_DATA                *Credentials,
	IN EFI_BIS_DATA                *DataObject,
	OUT BOOLEAN                    *IsVerified
	);

typedef EFI_STATUS(EFIAPI *EFI_BIS_VERIFY_OBJECT_WITH_CREDENTIAL)(
	IN BIS_APPLICATION_HANDLE         AppHandle,
	IN EFI_BIS_DATA                   *Credentials,
	IN EFI_BIS_DATA                   *DataObject,
	IN EFI_BIS_DATA                   *SectionName,
	IN EFI_BIS_DATA                   *AuthorityCertificate,
	OUT BOOLEAN                       *IsVerified
	);

struct _EFI_BIS_PROTOCOL {
  EFI_BIS_INITIALIZE                                  Initialize;
  EFI_BIS_SHUTDOWN                                    Shutdown;
  EFI_BIS_FREE                                        Free;
  EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_CERTIFICATE   GetBootObjectAuthorizationCertificate;
  EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_CHECKFLAG     GetBootObjectAuthorizationCheckFlag;
  EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_UPDATE_TOKEN  GetBootObjectAuthorizationUpdateToken;
  EFI_BIS_GET_SIGNATURE_INFO                          GetSignatureInfo;
  EFI_BIS_UPDATE_BOOT_OBJECT_AUTHORIZATION            UpdateBootObjectAuthorization;
  EFI_BIS_VERIFY_BOOT_OBJECT                          VerifyBootObject;
  EFI_BIS_VERIFY_OBJECT_WITH_CREDENTIAL               VerifyObjectWithCredential;
};
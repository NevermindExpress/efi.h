#pragma once
#include "efi/types.h"

// UEFI Spec Section 37.4
#define EFI_PKCS7_VERIFY_PROTOCOL_GUID { 0x47889fb2, 0xd671, 0x4fab,{ 0xa0, 0xca, 0xdf, 0xe, 0x44, 0xdf, 0x70, 0xd6 }}

typedef struct _EFI_PKCS7_VERIFY_PROTOCOL EFI_PKCS7_VERIFY_PROTOCOL;

typedef struct {
	/// Type of the signature. GUID signature types are defined in below.
	EFI_GUID    SignatureType;
	/// Total size of the signature list, including this header.
	UINT32      SignatureListSize;
	/// Size of the signature header which precedes the array of signatures.
	UINT32      SignatureHeaderSize;
	/// Size of each signature.
	UINT32      SignatureSize;
	/// Header before the array of signatures. The format of this header is specified
	/// by the SignatureType.
	/// UINT8           SignatureHeader[SignatureHeaderSize];
	///
	/// An array of signatures. Each signature is SignatureSize bytes in length.
	/// EFI_SIGNATURE_DATA Signatures[][SignatureSize];
} EFI_SIGNATURE_LIST;

typedef EFI_STATUS(EFIAPI *EFI_PKCS7_VERIFY_BUFFER)(
	IN EFI_PKCS7_VERIFY_PROTOCOL         *This,
	IN VOID                              *SignedData,
	IN UINTN                             SignedDataSize,
	IN VOID                              *InData OPTIONAL,
	IN UINTN                             InDataSize,
	IN EFI_SIGNATURE_LIST                **AllowedDb,
	IN EFI_SIGNATURE_LIST                **RevokedDb OPTIONAL,
	IN EFI_SIGNATURE_LIST                **TimeStampDb OPTIONAL,
	OUT VOID                             *Content OPTIONAL,
	IN OUT UINTN                         *ContentSize
	);

typedef EFI_STATUS(EFIAPI *EFI_PKCS7_VERIFY_SIGNATURE)(
	IN EFI_PKCS7_VERIFY_PROTOCOL      *This,
	IN VOID                           *Signature,
	IN UINTN                          SignatureSize,
	IN VOID                           *InHash,
	IN UINTN                          InHashSize,
	IN EFI_SIGNATURE_LIST             **AllowedDb,
	IN EFI_SIGNATURE_LIST             **RevokedDb OPTIONAL,
	IN EFI_SIGNATURE_LIST             **TimeStampDb OPTIONAL
	);

struct _EFI_PKCS7_VERIFY_PROTOCOL {
	EFI_PKCS7_VERIFY_BUFFER          *VerifyBuffer;
	EFI_PKCS7_VERIFY_SIGNATURE       *VerifySignature;
};
#pragma once
#include "efi/types.h"

// UEFI Spec Section 21.1
#define EFI_UNICODE_COLLATION_PROTOCOL2_GUID {0xa4c751fc, 0x23ae, 0x4c3e,{0x92, 0xe9, 0x49, 0x64, 0xcf, 0x63, 0xf3, 0x49}}

typedef struct _EFI_UNICODE_COLLATION_PROTOCOL EFI_UNICODE_COLLATION_PROTOCOL;

typedef INTN(EFIAPI *EFI_UNICODE_COLLATION_STRICOLL) (
	IN EFI_UNICODE_COLLATION_PROTOCOL    *This,
	IN CHAR16                            *s1,
	IN CHAR16                            *s2
	);

typedef BOOLEAN(EFIAPI *EFI_UNICODE_COLLATION_METAIMATCH) (
	IN EFI_UNICODE_COLLATION_PROTOCOL       *This,
	IN CHAR16                               *String,
	IN CHAR16                               *Pattern
	);

typedef VOID(EFIAPI *EFI_UNICODE_COLLATION_STRLWR) (
	IN EFI_UNICODE_COLLATION_PROTOCOL       *This,
	IN OUT CHAR16                           *String
	);

typedef VOID(EFIAPI *EFI_UNICODE_COLLATION_STRUPR) (
	IN EFI_UNICODE_COLLATION_PROTOCOL      *This,
	IN OUT CHAR16                          *String
	);

typedef VOID(EFIAPI *EFI_UNICODE_COLLATION_FATTOSTR) (
	IN EFI_UNICODE_COLLATION_PROTOCOL       *This,
	IN UINTN                                FatSize,
	IN CHAR8                                *Fat,
	OUT CHAR16                              *String
	);

typedef BOOLEAN(EFIAPI *EFI_UNICODE_COLLATION_STRTOFAT) (
	IN EFI_UNICODE_COLLATION_PROTOCOL       *This,
	IN CHAR16                               *String,
	IN UINTN                                FatSize,
	OUT CHAR8                               *Fat
	);

struct _EFI_UNICODE_COLLATION_PROTOCOL {
	EFI_UNICODE_COLLATION_STRICOLL         StriColl;
	EFI_UNICODE_COLLATION_METAIMATCH       MetaiMatch;
	EFI_UNICODE_COLLATION_STRLWR           StrLwr;
	EFI_UNICODE_COLLATION_STRUPR           StrUpr;
	EFI_UNICODE_COLLATION_FATTOSTR         FatToStr;
	EFI_UNICODE_COLLATION_STRTOFAT         StrToFat;
	CHAR8                                  *SupportedLanguages;
};

// UEFI Spec Section 21.2
#define EFI_REGULAR_EXPRESSION_PROTOCOL_GUID { 0xB3F79D9A, 0x436C, 0xDC11,{ 0xB0, 0x52, 0xCD, 0x85, 0xDF, 0x52, 0x4C, 0xE6 }}

typedef struct {
	CONST CHAR16       *CapturePtr;
	UINTN              Length;
}  EFI_REGEX_CAPTURE;

// Regex Syntax Types
typedef EFI_GUID EFI_REGEX_SYNTAX_TYPE;
#define EFI_REGEX_SYNTAX_TYPE_POSIX_EXTENDED_GUID {0x5F05B20F, 0x4A56, 0xC231,{ 0xFA, 0x0B, 0xA7, 0xB1, 0xF1, 0x10, 0x04, 0x1D }}
#define EFI_REGEX_SYNTAX_TYPE_PERL_GUID {0x63E60A51, 0x497D, 0xD427,{ 0xC4, 0xA5, 0xB8, 0xAB, 0xDC, 0x3A, 0xAE, 0xB6 }}
#define EFI_REGEX_SYNTAX_TYPE_ECMA_262_GUID { 0x9A473A4A, 0x4CEB, 0xB95A, 0x41,{ 0x5E, 0x5B, 0xA0, 0xBC, 0x63, 0x9B, 0x2E }}
#define EFI_REGEX_SYNTAX_TYPE_POSIX_EXTENDED_ASCII_GUID {0x3FD32128, 0x4BB1, 0xF632, { 0xBE, 0x4F, 0xBA, 0xBF, 0x85, 0xC9, 0x36, 0x76 }}
#define EFI_REGEX_SYNTAX_TYPE_PERL_ASCII_GUID {0x87DFB76D, 0x4B58, 0xEF3A, { 0xF7, 0xC6, 0x16, 0xA4, 0x2A, 0x68, 0x28, 0x10 }}
#define EFI_REGEX_SYNTAX_TYPE_ECMA_262_ASCII_GUID { 0xB2284A2F, 0x4491, 0x6D9D, { 0xEA, 0xB7, 0x11, 0xB0, 0x67, 0xD4, 0x9B, 0x9A }}

typedef struct _EFI_REGULAR_EXPRESSION_PROTOCOL EFI_REGULAR_EXPRESSION_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_REGULAR_EXPRESSION_MATCH) (
	IN   EFI_REGULAR_EXPRESSION_PROTOCOL *This,
	IN   CHAR16                          *String,
	IN   CHAR16                          *Pattern,
	IN   EFI_REGEX_SYNTAX_TYPE           *SyntaxType, OPTIONAL
	OUT  BOOLEAN                         *Result,
	OUT  EFI_REGEX_CAPTURE               **Captures, OPTIONAL
	OUT UINTN                            *CapturesCount
);

typedef EFI_STATUS(EFIAPI *EFI_REGULAR_EXPRESSION_GET_INFO) (
	IN EFI_REGULAR_EXPRESSION_PROTOCOL         *This,
	IN OUT UINTN                               *RegExSyntaxTypeListSize,
	OUT EFI_REGEX_SYNTAX_TYPE                  *RegExSyntaxTypeList
);

struct _EFI_REGULAR_EXPRESSION_PROTOCOL {
	EFI_REGULAR_EXPRESSION_MATCH      MatchString;
	EFI_REGULAR_EXPRESSION_GET_INFO   GetInfo;
};
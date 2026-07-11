#pragma once
#include "efi/types.h"
#include "efi/protocols/console/common.h"

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID {0x387477c2,0x69c7,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// SIMPLE_TEXT_OUTPUT_MODE
typedef struct {
	INT32                              MaxMode;
	// current settings
	INT32                              Mode;
	INT32                              Attribute;
	INT32                              CursorColumn;
	INT32                              CursorRow;
	BOOLEAN                            CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef EFI_STATUS(EFIAPI *EFI_TEXT_RESET) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL       *This,
	IN BOOLEAN                               ExtendedVerification
	);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_STRING) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *This,
	IN CHAR16                             *String
	);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_TEST_STRING) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL       *This,
	IN CHAR16                                *String
	);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_QUERY_MODE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL          *This,
	IN UINTN                                    ModeNumber,
	OUT UINTN                                   *Columns,
	OUT UINTN                                   *Rows
	);

typedef EFI_STATUS(*EFIAPI EFI_TEXT_SET_MODE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL          *This,
	IN UINTN                                    ModeNumber
	);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
	IN UINTN                                  Attribute
	);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_CLEAR_SCREEN)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL             *This,
	IN UINTN                                       Column,
	IN UINTN                                       Row
	);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_ENABLE_CURSOR) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL             *This,
	IN BOOLEAN                                     Visible
	);

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	EFI_TEXT_RESET                           Reset;
	EFI_TEXT_STRING                          OutputString;
	EFI_TEXT_TEST_STRING                     TestString;
	EFI_TEXT_QUERY_MODE                      QueryMode;
	EFI_TEXT_SET_MODE                        SetMode;
	EFI_TEXT_SET_ATTRIBUTE                   SetAttribute;
	EFI_TEXT_CLEAR_SCREEN                    ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION             SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR                   EnableCursor;
	SIMPLE_TEXT_OUTPUT_MODE                  *Mode;
};
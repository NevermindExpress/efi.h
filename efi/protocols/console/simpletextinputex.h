#pragma once
#include "efi/types.h"
#include "efi/protocols/console/common.h"

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID {0xdd9e7534, 0x7762, 0x4698, {0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}}

#define EFI_TOGGLE_STATE_VALID 0x80
#define EFI_KEY_STATE_EXPOSED 0x40
#define EFI_SCROLL_LOCK_ACTIVE 0x01
#define EFI_NUM_LOCK_ACTIVE 0x02
#define EFI_CAPS_LOCK_ACTIVE 0x04

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

// EFI_KEY_NOTIFY
typedef EFI_STATUS(EFIAPI *EFI_KEY_NOTIFY_FUNCTION) (
 IN EFI_KEY_DATA                          *KeyData
 );

typedef EFI_STATUS(EFIAPI *EFI_INPUT_RESET_EX) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL        *This,
	IN BOOLEAN                                  ExtendedVerification
);

typedef EFI_STATUS(EFIAPI *EFI_INPUT_READ_KEY_EX) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *This,
	OUT EFI_KEY_DATA                         *KeyData
	);

typedef EFI_STATUS(EFIAPI *EFI_SET_STATE) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL         *This,
	IN EFI_KEY_TOGGLE_STATE                      *KeyToggleState
	);

typedef EFI_STATUS(EFIAPI *EFI_REGISTER_KEYSTROKE_NOTIFY) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL            *This,
	IN EFI_KEY_DATA                                 *KeyData,
	IN EFI_KEY_NOTIFY_FUNCTION                      KeyNotificationFunction,
	OUT VOID                                        **NotifyHandle
	);

typedef EFI_STATUS(EFIAPI *EFI_UNREGISTER_KEYSTROKE_NOTIFY) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
	IN VOID                              *NotificationHandle
	);

struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
	EFI_INPUT_RESET_EX                          Reset;
	EFI_INPUT_READ_KEY_EX                       ReadKeyStrokeEx;
	EFI_EVENT                                   WaitForKeyEx;
	EFI_SET_STATE                               SetState;
	EFI_REGISTER_KEYSTROKE_NOTIFY               RegisterKeyNotify;
	EFI_UNREGISTER_KEYSTROKE_NOTIFY             UnregisterKeyNotify;
};
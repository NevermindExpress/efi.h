#pragma once
#include "efi/types.h"

// UEFI Spec Section 39.1
#define EFI_TIMESTAMP_PROTOCOL_GUID { 0xafbfde41, 0x2e6e, 0x4262,{ 0xba, 0x65, 0x62, 0xb9, 0x23, 0x6e, 0x54, 0x95 }}

typedef struct {
	UINT64          Frequency;
	UINT64          EndValue;
} EFI_TIMESTAMP_PROPERTIES;

typedef struct _EFI_TIMESTAMP_PROTOCOL EFI_TIMESTAMP_PROTOCOL;

typedef UINT64(EFIAPI *TIMESTAMP_GET) (VOID);

typedef EFI_STATUS(EFIAPI *TIMESTAMP_GET_PROPERTIES) (OUT EFI_TIMESTAMP_PROPERTIES *Properties);

struct _EFI_TIMESTAMP_PROTOCOL {
	TIMESTAMP_GET                  GetTimestamp;
	TIMESTAMP_GET_PROPERTIES       GetProperties;
};

// UEFI Spec Section 39.2
#include "efi/systemtable.h"

#define EFI_RESET_NOTIFICATION_PROTOCOL_GUID { 0x9da34ae0, 0xeaf9, 0x4bbf, { 0x8e, 0xc3, 0xfd, 0x60, 0x22, 0x6c, 0x44, 0xbe}}

typedef struct _EFI_RESET_NOTIFICATION_PROTOCOL EFI_RESET_NOTIFICATION_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_REGISTER_RESET_NOTIFY) (
	IN EFI_RESET_NOTIFICATION_PROTOCOL         *This,
	IN EFI_RESET_SYSTEM                        *ResetFunction
);

typedef EFI_STATUS(EFIAPI *EFI_UNREGISTER_RESET_NOTIFY) (
	IN EFI_RESET_NOTIFICATION_PROTOCOL      *This,
	IN EFI_RESET_SYSTEM                     *ResetFunction
);

struct _EFI_RESET_NOTIFICATION_PROTOCOL {
	EFI_REGISTER_RESET_NOTIFY               RegisterResetNotify;
	EFI_UNREGISTER_RESET_NOTIFY             UnRegisterResetNotify;
};
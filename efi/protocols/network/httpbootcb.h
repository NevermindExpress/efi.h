#pragma once
#include "efi/types.h"

// UEFI Spec Section 24.7

#define EFI_HTTP_BOOT_CALLBACK_PROTOCOL_GUID {0xba23b311, 0x343d, 0x11e6, {0x91, 0x85, 0x58,0x20, 0xb1, 0xd6, 0x52, 0x99}}

// EFI_HTTP_BOOT_CALLBACK_DATA_TYPE
typedef enum {
	HttpBootDhcp4,
	HttpBootDhcp6,
	HttpBootHttpRequest,
	HttpBootHttpResponse,
	HttpBootHttpEntityBody,
	HttpBootHttpAuthInfo,
	HttpBootTypeMax
}   EFI_HTTP_BOOT_CALLBACK_DATA_TYPE;

typedef struct _EFI_HTTP_BOOT_CALLBACK_PROTOCOL EFI_HTTP_BOOT_CALLBACK_PROTOCOL; 

typedef
EFI_STATUS
(EFIAPI *EFI_HTTP_BOOT_CALLBACK) (
	IN EFI_HTTP_BOOT_CALLBACK_PROTOCOL   *This,
	IN EFI_HTTP_BOOT_CALLBACK_DATA_TYPE  DataType,
	IN BOOLEAN                           Received,
	IN UINT32                            DataLength,
	IN VOID                              *Data OPTIONAL
	);

struct _EFI_HTTP_BOOT_CALLBACK_PROTOCOL {
  EFI_HTTP_BOOT_CALLBACK         Callback;
} ;
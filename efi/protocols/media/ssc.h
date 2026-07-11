#pragma once
// UEFI spec section 13.14

#include "efi/types.h"

#define EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID {0xc88b0b6d, 0x0dfc, 0x49a7,{0x9c, 0xb4, 0x49, 0x7, 0x4b, 0x4c, 0x3a, 0x78}}

typedef struct _EFI_STORAGE_SECURITY_COMMAND_PROTOCOL EFI_STORAGE_SECURITY_COMMAND_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_STORAGE_SECURITY_RECEIVE_DATA) (
	IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
	IN UINT32                  MediaId,
	IN UINT64                  Timeout,
	IN UINT8                   SecurityProtocol,
	IN UINT16                  SecurityProtocolSpecificData,
	IN UINTN                   PayloadBufferSize,
	OUT VOID                   *PayloadBuffer,
	OUT UINTN               *PayloadTransferSize
);

typedef EFI_STATUS(EFIAPI *EFI_STORAGE_SECURITY_SEND_DATA) (
	IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
	IN UINT32                     MediaId,
	IN UINT64                     Timeout,
	IN UINT8                      SecurityProtocolId,
	IN UINT16                     SecurityProtocolSpecificData,
	IN UINTN                      PayloadBufferSize,
	IN VOID                       *PayloadBuffer
);

struct _EFI_STORAGE_SECURITY_COMMAND_PROTOCOL {
	EFI_STORAGE_SECURITY_RECEIVE_DATA      ReceiveData;
	EFI_STORAGE_SECURITY_SEND_DATA         SendData;
};
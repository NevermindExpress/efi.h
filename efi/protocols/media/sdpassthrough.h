#pragma once
// UEFI spec section 13.16

#include "efi/types.h"
#include "efi/protocols/devicepath.h"

#define EFI_SD_MMC_PASS_THRU_PROTOCOL_GUID { 0x716ef0d9, 0xff83, 0x4f69, { 0x81, 0xe9, 0x51, 0x8b, 0xd3, 0x9a, 0x8e, 0x70 }}

typedef struct {
	UINT16     CommandIndex;
	UINT32     CommandArgument;
	UINT32     CommandType; // One of the EFI_SD_MMC_COMMAND_TYPE values
	UINT32     ResponseType; // One of the EFI_SD_MMC_RESPONSE_TYPE values
} EFI_SD_MMC_COMMAND_BLOCK;

typedef struct {
	UINT32     Resp0;
	UINT32     Resp1;
	UINT32     Resp2;
	UINT32     Resp3;
} EFI_SD_MMC_STATUS_BLOCK;

typedef enum {
	SdMmcCommandTypeBc,   // Broadcast commands, no response
	SdMmcCommandTypeBcr,  // Broadcast commands with response
	SdMmcCommandTypeAc,   // Addressed(point-to-point) commands
	SdMmcCommandTypeAdtc  // Addressed(point-to-point) data transfer
				// commands
} EFI_SD_MMC_COMMAND_TYPE;

typedef enum {
	SdMmcResponceTypeR1,
	SdMmcResponceTypeR1b,
	SdMmcResponceTypeR2,
	SdMmcResponceTypeR3,
	SdMmcResponceTypeR4,
	SdMmcResponceTypeR5,
	SdMmcResponceTypeR5b,
	SdMmcResponceTypeR6,
	SdMmcResponceTypeR7
} EFI_SD_MMC_RESPONSE_TYPE;

typedef struct {
	EFI_SD_MMC_COMMAND_BLOCK             *SdMmcCmdBlk;
	EFI_SD_MMC_STATUS_BLOCK              *SdMmcStatusBlk;
	UINT64                               Timeout;
	VOID                                 *InDataBuffer;
	VOID                                 *OutDataBuffer;
	UINT32                               InTransferLength;
	UINT32                               OutTransferLength;
	EFI_STATUS                           TransactionStatus;
} EFI_SD_MMC_PASS_THRU_COMMAND_PACKET;

typedef struct _EFI_SD_MMC_PASS_THRU_PROTOCOL EFI_SD_MMC_PASS_THRU_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_SD_MMC_PASS_THRU_PASSTHRU) (
  IN EFI_SD_MMC_PASS_THRU_PROTOCOL                   *This,
  IN UINT8                                           Slot,
  IN OUT EFI_SD_MMC_PASS_THRU_COMMAND_PACKET         *Packet,
  IN EFI_EVENT                                       Event OPTIONAL
 );

typedef EFI_STATUS(EFIAPI *EFI_SD_MMC_PASS_THRU_GET_NEXT_SLOT) (
	IN EFI_SD_MMC_PASS_THRU_PROTOCOL             *This,
	IN OUT UINT8                                 *Slot
);

typedef EFI_STATUS(EFIAPI *EFI_SD_MMC_PASS_THRU_BUILD_DEVICE_PATH) (
	IN EFI_SD_MMC_PASS_THRU_PROTOCOL               *This,
	IN UINT8                                       Slot,
	OUT EFI_DEVICE_PATH_PROTOCOL                   **DevicePath
);

typedef EFI_STATUS(EFIAPI *EFI_SD_MMC_PASS_THRU_GET_SLOT_NUMBER) (
	IN EFI_SD_MMC_PASS_THRU_PROTOCOL             *This,
	IN EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
	OUT UINT8                                    *Slot
);

typedef EFI_STATUS(EFIAPI *EFI_SD_MMC_PASS_THRU_RESET_DEVICE) (
	IN EFI_SD_MMC_PASS_THRU_PROTOCOL               *This,
	IN UINT8                                       Slot
);

struct _EFI_SD_MMC_PASS_THRU_PROTOCOL {
	UINTN                                               IoAlign;
	EFI_SD_MMC_PASS_THRU_PASSTHRU                       PassThru;
	EFI_SD_MMC_PASS_THRU_GET_NEXT_SLOT                  GetNextSlot;
	EFI_SD_MMC_PASS_THRU_BUILD_DEVICE_PATH              BuildDevicePath;
	EFI_SD_MMC_PASS_THRU_GET_SLOT_NUMBER                GetSlotNumber;
	EFI_SD_MMC_PASS_THRU_RESET_DEVICE                   ResetDevice;
};
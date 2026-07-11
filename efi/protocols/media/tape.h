#pragma once
// UEFI spec section 13.6

#include "efi/types.h"

#define EFI_TAPE_IO_PROTOCOL_GUID {0x1e93e633,0xd65a,0x459e, {0xab,0x84,0x93,0xd9,0xec,0x26,0x6d,0x18}}

typedef struct _EFI_TAPE_IO_PROTOCOL EFI_TAPE_IO_PROTOCOL;

typedef struct EFI_TAPE_HEADER {
	UINT64           Signature;
	UINT32           Revision;
	UINT32           BootDescSize;
	UINT32           BootDescCRC;
	EFI_GUID         TapeGUID;
	EFI_GUID         TapeType;
	EFI_GUID         TapeUnique;
	UINT32           BLLocation;
	UINT32           BLBlocksize;
	UINT32           BLFilesize;
	CHAR8            OSVersion[40];
	CHAR8            AppVersion[40];
	CHAR8            CreationDate[10];
	CHAR8            CreationTime[10];
	CHAR8            SystemName[256]; // UTF-8
	CHAR8            TapeTitle[120]; // UTF-8
	CHAR8            pad[468]; // pad to 1024
} EFI_TAPE_HEADER;

typedef EFI_STATUS(EFIAPI *EFI_TAPE_READ) (
	IN EFI_TAPE_IO_PROTOCOL         *This,
	IN OUT UINTN                    *BufferSize,
	OUT VOID                        *Buffer
	);

typedef EFI_STATUS (EFIAPI *EFI_TAPE_WRITE) (
	IN EFI_TAPE_IO_PROTOCOL          *This,
	IN UINTN                         *BufferSize,
	IN VOID                          *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_TAPE_REWIND)(IN EFI_TAPE_IO_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_TAPE_SPACE) (
	IN EFI_TAPE_IO_PROTOCOL       *This,
	IN INTN                       Direction,
	IN UINTN                      Type
	);

typedef EFI_STATUS(EFIAPI *EFI_TAPE_WRITEFM) (
	IN EFI_TAPE_IO_PROTOCOL      *This,
	IN UINTN                     Count
	);

typedef EFI_STATUS(EFIAPI *EFI_TAPE_RESET) (
	IN EFI_TAPE_IO_PROTOCOL   *This,
	IN BOOLEAN                ExtendedVerification
	);

struct _EFI_TAPE_IO_PROTOCOL {
  EFI_TAPE_READ        TapeRead;
  EFI_TAPE_WRITE       TapeWrite;
  EFI_TAPE_REWIND      TapeRewind;
  EFI_TAPE_SPACE       TapeSpace;
  EFI_TAPE_WRITEFM     TapeWriteFM;
  EFI_TAPE_RESET       TapeReset;
};
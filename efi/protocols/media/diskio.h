#pragma once
// UEFI spec section 13.7

#include "efi/types.h"

#define EFI_DISK_IO_PROTOCOL_GUID {0xCE345171,0xBA0B,0x11d2,{0x8e,0x4F,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_DISK_IO_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_DISK_IO_PROTOCOL EFI_DISK_IO_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_DISK_READ) (
	IN EFI_DISK_IO_PROTOCOL        *This,
	IN UINT32                      MediaId,
	IN UINT64                      Offset,
	IN UINTN                       BufferSize,
	OUT VOID                       *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_DISK_WRITE) (
	IN EFI_DISK_IO_PROTOCOL    *This,
	IN UINT32                  MediaId,
	IN UINT64                  Offset,
	IN UINTN                   BufferSize,
	IN VOID                    *Buffer
	);

struct _EFI_DISK_IO_PROTOCOL {
	UINT64                         Revision;
	EFI_DISK_READ                  ReadDisk;
	EFI_DISK_WRITE                 WriteDisk;
};

// UEFI spec section 13.8

#define EFI_DISK_IO2_PROTOCOL_GUID { 0x151c8eae, 0x7f2c, 0x472c, {0x9e, 0x54, 0x98, 0x28, 0x19, 0x4f, 0x6a, 0x88 }}

#define EFI_DISK_IO2_PROTOCOL_REVISION 0x00020000

typedef struct {
	EFI_EVENT               Event;
	EFI_STATUS              TransactionStatus;
} EFI_DISK_IO2_TOKEN;

typedef struct _EFI_DISK_IO2_PROTOCOL EFI_DISK_IO2_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_DISK_CANCEL_EX) (IN EFI_DISK_IO2_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_DISK_READ_EX) (
	IN EFI_DISK_IO2_PROTOCOL      *This,
	IN UINT32                     MediaId,
	IN UINT64                     Offset,
	IN OUT EFI_DISK_IO2_TOKEN     *Token,
	IN UINTN                      BufferSize,
	OUT VOID                      *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_DISK_WRITE_EX) (
	IN EFI_DISK_IO2_PROTOCOL          *This,
	IN UINT32                         MediaId,
	IN UINT64                         Offset,
	IN OUT EFI_DISK_IO2_TOKEN         *Token,
	IN UINTN                          BufferSize,
	IN VOID                           *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_DISK_FLUSH_EX) (
	IN EFI_DISK_IO2_PROTOCOL          *This,
	IN OUT EFI_DISK_IO2_TOKEN         *Token
	);

struct _EFI_DISK_IO2_PROTOCOL {
	UINT64                              Revision;
	EFI_DISK_CANCEL_EX                  Cancel;
	EFI_DISK_READ_EX                    ReadDiskEx;
	EFI_DISK_WRITE_EX                   WriteDiskEx;
	EFI_DISK_FLUSH_EX                   FlushDiskEx;
} ;
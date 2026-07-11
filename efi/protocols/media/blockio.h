#pragma once
// UEFI spec section 13.9

#include "efi/types.h"

#define EFI_BLOCK_IO_PROTOCOL_GUID {0x964e5b21,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_BLOCK_IO_PROTOCOL_REVISION2   0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3   ((2<<16) | (31))

// EFI_BLOCK_IO_MEDIA
typedef struct {
	UINT32                    MediaId;
	BOOLEAN                   RemovableMedia;
	BOOLEAN                   MediaPresent;
	BOOLEAN                   LogicalPartition;
	BOOLEAN                   ReadOnly;
	BOOLEAN                   WriteCaching;
	UINT32                    BlockSize;
	UINT32                    IoAlign;
	EFI_LBA                   LastBlock;

	EFI_LBA                 LowestAlignedLba; //added in Revision 2
	UINT32                  LogicalBlocksPerPhysicalBlock; //added in Revision 2
	UINT32 OptimalTransferLengthGranularity; // added in Revision 3
} EFI_BLOCK_IO_MEDIA;

// EFI_LBA
typedef UINT64 EFI_LBA;

typedef struct _EFI_BLOCK_IO_PROTOCOL EFI_BLOCK_IO_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_RESET) (
	IN EFI_BLOCK_IO_PROTOCOL    *This,
	IN BOOLEAN                  ExtendedVerification
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_READ) (
	IN EFI_BLOCK_IO_PROTOCOL    *This,
	IN UINT32                   MediaId,
	IN EFI_LBA                  LBA,
	IN UINTN                    BufferSize,
	OUT VOID                    *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_WRITE) (
	IN EFI_BLOCK_IO_PROTOCOL       *This,
	IN UINT32                      MediaId,
	IN EFI_LBA                     LBA,
	IN UINTN                       BufferSize,
	IN VOID                        *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_FLUSH) (IN EFI_BLOCK_IO_PROTOCOL *This);

struct _EFI_BLOCK_IO_PROTOCOL {
	UINT64                         Revision;
	EFI_BLOCK_IO_MEDIA             *Media;
	EFI_BLOCK_RESET                Reset;
	EFI_BLOCK_READ                 ReadBlocks;
	EFI_BLOCK_WRITE                WriteBlocks;
	EFI_BLOCK_FLUSH                FlushBlocks;
} ;

// UEFI spec section 13.10


#define EFI_BLOCK_IO2_PROTOCOL_GUID {0xa77b2472, 0xe282, 0x4e9f, {0xa2, 0x45, 0xc2, 0xc0, 0xe2, 0x7b, 0xbc, 0xc1}}

typedef struct {
	EFI_EVENT          Event;
	EFI_STATUS         TransactionStatus;
} EFI_BLOCK_IO2_TOKEN;

typedef struct _EFI_BLOCK_IO2_PROTOCOL EFI_BLOCK_IO2_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_RESET_EX) (
	IN EFI_BLOCK_IO2_PROTOCOL   *This,
	IN BOOLEAN                  ExtendedVerification
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_READ_EX) (
	IN EFI_BLOCK_IO2_PROTOCOL      *This,
	IN UINT32                      MediaId,
	IN EFI_LBA                     LBA,
	IN OUT EFI_BLOCK_IO2_TOKEN     *Token,
	IN UINTN                       BufferSize,
	OUT VOID                       *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_WRITE_EX) (
	IN EFI_BLOCK_IO2_PROTOCOL   *This,
	IN UINT32                   MediaId,
	IN EFI_LBA                  LBA,
	IN OUT EFI_BLOCK_IO2_TOKEN  *Token,
	IN UINTN                    BufferSize,
	IN VOID                     *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_FLUSH_EX) (
	IN EFI_BLOCK_IO2_PROTOCOL         *This,
	IN OUT EFI_BLOCK_IO2_TOKEN        *Token
	);

struct _EFI_BLOCK_IO2_PROTOCOL {
	EFI_BLOCK_IO_MEDIA       *Media;
	EFI_BLOCK_RESET_EX       Reset;
	EFI_BLOCK_READ_EX        ReadBlocksEx;
	EFI_BLOCK_WRITE_EX       WriteBlocksEx;
	EFI_BLOCK_FLUSH_EX       FlushBlocksEx;
};
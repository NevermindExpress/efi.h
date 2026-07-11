#pragma once
// UEFI spec section 13.18

#include "efi/types.h"

#define EFI_PARTITION_INFO_PROTOCOL_GUID {0x8cf2f62c, 0xbc9b, 0x4821, {0x80, 0x8d, 0xec, 0x9e,0xc4, 0x21, 0xa1, 0xa0}}

#define EFI_PARTITION_INFO_PROTOCOL_REVISION 0x0001000
#define PARTITION_TYPE_OTHER 0x00
#define PARTITION_TYPE_MBR 0x01
#define PARTITION_TYPE_GPT 0x02

#pragma pack(1)
///
/// MBR Partition Entry
///
typedef struct {
	UINT8         BootIndicator;
	UINT8         StartHead;
	UINT8         StartSector;
	UINT8         StartTrack;
	UINT8         OSIndicator;
	UINT8         EndHead;
	UINT8         EndSector;
	UINT8         EndTrack;
	UINT8         StartingLBA[4];
	UINT8         SizeInLBA[4];
}    MBR_PARTITION_RECORD;

///
/// MBR Partition Table
///
typedef struct {
	UINT8         BootStrapCode[440];
	UINT8         UniqueMbrSignature[4];
	UINT8         Unknown[2];
	MBR_PARTITION_RECORD Partition[4];
	UINT16        Signature;
}   MASTER_BOOT_RECORD;

///
/// GPT Partition Entry.
///
typedef struct {
	EFI_GUID     PartitionTypeGUID;
	EFI_GUID     UniquePartitionGUID;
	EFI_LBA      StartingLBA;
	EFI_LBA      EndingLBA;
	UINT64       Attributes;
	CHAR16       PartitionName[36];
}   EFI_PARTITION_ENTRY;

typedef struct {

	UINT32         Revision;
	UINT32         Type;
	UINT8          System;
	UINT8          Reserved[7];
	union {
		///
		/// MBR data
		///
		MBR_PARTITION_RECORD Mbr;

		///
		/// GPT data
		///
		EFI_PARTITION_ENTRY Gpt;
	} Info;
} EFI_PARTITION_INFO_PROTOCOL;
#pragma pack()

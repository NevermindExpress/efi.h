#pragma once
#include "efi/types.h"

// UEFI Spec Section 38.2
#define EFI_CC_MEASUREMENT_PROTOCOL_GUID {0x96751a3d, 0x72f4, 0x41a6, {0xa7, 0x94, 0xed, 0x5d, 0xe, 0x67, 0xae, 0x6b }}

#define EFI_CC_TYPE_NONE 0 // 1~0xFF: CC vendor specific. Please refer to 38.4
#define EFI_CC_BOOT_HASH_ALG_SHA384     0x00000004
#define EFI_CC_EVENT_LOG_FORMAT_TCG_2   0x00000002

// This bit is shall be set when an event shall be extended
// but not logged.
#define EFI_CC_FLAG_EXTEND_ONLY    0x0000000000000001

// This bit shall be set when the intent is to measure
// a PE/COFF image.
#define EFI_CC_FLAG_PE_COFF_IMAGE  0x0000000000000010

#define EFI_CC_TYPE_INTEL_TDX    2
#define EFI_CC_TYPE_RISCV_APTEE    3

#define HASH_COUNT  5
#define MD5_DIGEST_SIZE  16
#define SHA1_DIGEST_SIZE  20
#define SHA256_DIGEST_SIZE  32
#define SHA384_DIGEST_SIZE  48
#define SHA512_DIGEST_SIZE  64
#define SM3_256_DIGEST_SIZE  32
#define TDES_BLOCK_SIZE  8
#define AES_BLOCK_SIZE  16

typedef UINT32	EFI_CC_EVENT_LOG_BITMAP;
typedef UINT32	EFI_CC_EVENT_ALGORITHM_BITMAP;
typedef UINT32	EFI_CC_EVENT_LOG_FORMAT;
typedef UINT32 EFI_CC_MR_INDEX;
typedef UINT32 TCG_PCRINDEX;
typedef UINT16 TPM_ALG_ID;

typedef TPM_ALG_ID TPMI_ALG_HASH;

typedef struct {
	UINT8 Major;
	UINT8 Minor;
} EFI_CC_VERSION;

typedef struct {
	UINT8 Type;
	UINT8 SubType;
} EFI_CC_TYPE;

typedef struct {
	//
	// Allocated size of the structure
	//
	UINT8                            Size;
	//
	// Version of the EFI_CC_BOOT_SERVICE_CAPABILITY structure.
	// For this version of the protocol,
	// the Major version shall be set to 1
	// and the Minor version shall be set to 0.
	//
	EFI_CC_VERSION                   StructureVersion;
	//
	// Version of the EFI CC MEASUREMENT protocol.
	// For this version of the protocol,
	// the Major version shall be set to 1
	// and the Minor version shall be set to 0.
	//
	EFI_CC_VERSION                   ProtocolVersion;
	//
	// Supported hash algorithms
	//
	EFI_CC_EVENT_ALGORITHM_BITMAP    HashAlgorithmBitmap;
	//
	// Bitmap of supported event log formats
	//
	EFI_CC_EVENT_LOG_BITMAP          SupportedEventLogs;

	//
	// Indicate CC type
	//
	EFI_CC_TYPE                      CcType;
} EFI_CC_BOOT_SERVICE_CAPABILITY;

#pragma pack(1)
typedef struct {
	//
	// Size of the event header itself.
	//
	UINT32            HeaderSize;
	//
	// Header version. For this version of this specification,
	// the value shall be 1.
	//
	UINT16            HeaderVersion;
	//
	// Index of the MR that shall be extended.
	//
	EFI_CC_MR_INDEX   MrIndex;
	//
	// Type of the event that shall be extended
	// (and optionally logged).
	//
	UINT32            EventType;
} EFI_CC_EVENT_HEADER;

typedef struct {
	//
	// Total size of the event including the Size component,
	// the header and the Event data.
	//
	UINT32                Size;
	EFI_CC_EVENT_HEADER   Header;
	UINT8                 Event[1];
} EFI_CC_EVENT;
#pragma pack()

typedef struct _EFI_CC_MEASUREMENT_PROTOCOL EFI_CC_MEASUREMENT_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_CC_GET_CAPABILITY)(
	IN EFI_CC_MEASUREMENT_PROTOCOL        *This,
	IN OUT EFI_CC_BOOT_SERVICE_CAPABILITY *ProtocolCapability
	);

typedef EFI_STATUS(EFIAPI *EFI_CC_GET_EVENT_LOG)(
	IN EFI_CC_MEASUREMENT_PROTOCOL        *This,
	IN EFI_CC_EVENT_LOG_FORMAT            EventLogFormat,
	OUT EFI_PHYSICAL_ADDRESS              *EventLogLocation,
	OUT EFI_PHYSICAL_ADDRESS              *EventLogLastEntry,
	OUT BOOLEAN                           *EventLogTruncated
	);

typedef EFI_STATUS(EFIAPI *EFI_CC_HASH_LOG_EXTEND_EVENT)(
	IN EFI_CC_MEASUREMENT_PROTOCOL        *This,
	IN UINT64                             Flags,
	IN EFI_PHYSICAL_ADDRESS               DataToHash,
	IN UINT64                             DataToHashLen,
	IN EFI_CC_EVENT                       *EfiTdEvent
	);

typedef EFI_STATUS(EFIAPI *EFI_CC_MAP_PCR_TO_MR_INDEX)(
	IN EFI_CC_MEASUREMENT_PROTOCOL        *This,
	IN TCG_PCRINDEX                       PcrIndex,
	OUT EFI_CC_MR_INDEX                   *MrIndex
	);

struct _EFI_CC_MEASUREMENT_PROTOCOL {
	EFI_CC_GET_CAPABILITY          GetCapability;
	EFI_CC_GET_EVENT_LOG           GetEventLog;
	EFI_CC_HASH_LOG_EXTEND_EVENT   HashLogExtendEvent;
	EFI_CC_MAP_PCR_TO_MR_INDEX     MapPcrToMrIndex;
};

// UEFI Spec Section 38.3
#define EFI_CC_FINAL_EVENTS_TABLE_GUID {0xdd4a4648, 0x2de7, 0x4665, {0x96, 0x4d, 0x21, 0xd9, 0xef, 0x5f, 0xb4, 0x46}}

typedef union {
	BYTE sha1[SHA1_DIGEST_SIZE];
	BYTE sha256[SHA256_DIGEST_SIZE];
	BYTE sm3_256[SM3_256_DIGEST_SIZE];
	BYTE sha384[SHA384_DIGEST_SIZE];
	BYTE sha512[SHA512_DIGEST_SIZE];
} TPMU_HA;

typedef struct {
	TPMI_ALG_HASH    hashAlg;
	TPMU_HA          digest;
} TPMT_HA;

typedef struct {
	UINT32     count;
	TPMT_HA    digests[HASH_COUNT];
} TPML_DIGEST_VALUES;

typedef struct {
	//
	// The version of this structure. It shall be set to 1.
	//
	UINT64                  Version;
	//
	// Number of events recorded after invocation of GetEventLog API
	//
	UINT64                  NumberOfEvents;
	//
	// List of events of type CC_EVENT.
	//
	//CC_EVENT              Event[1];
} EFI_CC_FINAL_EVENTS_TABLE;

#pragma pack(1)
//
// Crypto Agile Log Entry Format.
// It is similar with TCG_PCR_EVENT2 except MrIndex.
//
typedef struct {
	EFI_CC_MR_INDEX     MrIndex;
	UINT32              EventType;
	TPML_DIGEST_VALUES  Digests;
	UINT32              EventSize;
	UINT8               Event[1];
} CC_EVENT;

#pragma pack()
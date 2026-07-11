#pragma once
// UEFI spec section 13.11

#include "efi/types.h"
#include "efi/protocols/media/blockio.h"

#define EFI_BLOCK_IO_CRYPTO_PROTOCOL_GUID {0xa00490ba,0x3f1a,0x4b4c,{0xab,0x90,0x4f,0xa9,0x97,0x26,0xa1,0xe8}}
#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_XTS {0x2f87ba6a,0x5c04,0x4385,0xa7,0x80,0xf3,0xbf,0x78,0xa9,0x7b,0xec}
#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_CBC_MICROSOFT_BITLOCKER {0x689e4c62,0x70bf,0x4cf3,0x88,0xbb,0x33,0xb3,0x18,0x26,0x86,0x70}

typedef struct {
	EFI_GUID        Algorithm;
	UINT64          KeySize;
	UINT64          CryptoBlockSizeBitMask;
} EFI_BLOCK_IO_CRYPTO_CAPABILITY;

typedef struct {
	UINT64                             Index;
	EFI_GUID                           KeyOwnerGuid;
	EFI_BLOCK_IO_CRYPTO_CAPABILITY     Capability;
}  EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY;

typedef struct {
	UINT64                             Index;
	EFI_GUID                           KeyOwnerGuid;
	EFI_BLOCK_IO_CRYPTO_CAPABILITY     Capability;
	VOID                               *CryptoKey;
} EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY;

typedef struct {
	UINT64                 InputSize;
}  EFI_BLOCK_IO_CRYPTO_IV_INPUT;

typedef struct {
	EFI_BLOCK_IO_CRYPTO_IV_INPUT   Header;
	UINT64                         CryptoBlockByteOffset;
	UINT64                         CryptoBlockByteSize;
} EFI_BLOCK_IO_CRYPTO_IV_INPUT_AES_CBC_MICROSOFT_BITLOCKER;

typedef struct {
	EFI_BLOCK_IO_CRYPTO_IV_INPUT    Header;
	UINT64                          CryptoBlockNumber;
	UINT64                          CryptoBlockByteSize;
} EFI_BLOCK_IO_CRYPTO_IV_INPUT_AES_XTS;

typedef struct {
	EFI_EVENT             Event;
	EFI_STATUS            TransactionStatus;
}  EFI_BLOCK_IO_CRYPTO_TOKEN;

typedef struct _EFI_BLOCK_IO_CRYPTO_PROTOCOL EFI_BLOCK_IO_CRYPTO_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_IO_CRYPTO_RESET) (
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL     *This,
	IN BOOLEAN                          ExtendedVerification
);

typedef struct { 
	BOOLEAN                         Supported;
	UINT64                          KeyCount;
	UINT64                          CapabilityCount;
	EFI_BLOCK_IO_CRYPTO_CAPABILITY*  Capabilities// flexible array of the singular type
} EFI_BLOCK_IO_CRYPTO_CAPABILITIES;

typedef EFI_STATUS (EFIAPI *EFI_BLOCK_IO_CRYPTO_GET_CAPABILITIES) (
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL         *This,
	OUT EFI_BLOCK_IO_CRYPTO_CAPABILITIES    *Capabilities
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_IO_CRYPTO_SET_CONFIGURATION) (
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL                    *This,
	IN UINT64                                          ConfigurationCount,
	IN EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY   *ConfigurationTable,
	OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY
	*ResultingTable  OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_IO_CRYPTO_GET_CONFIGURATION) (
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL            *This,
	IN UINT64                                  StartIndex,
	IN UINT64                                  ConfigurationCount,
	IN EFI_GUID                                *KeyOwnerGuid OPTIONAL,
	OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY *ConfigurationTable
);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_IO_CRYPTO_READ_EXTENDED) (
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL    *This,
	IN UINT32                          MediaId,
	IN EFI_LBA                         LBA,
	IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN   *Token,
	IN UINT64                          BufferSize,
	OUT VOID                           *Buffer,
	IN UINT64                          *Index OPTIONAL,
	IN VOID                            *CryptoIvInput OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_IO_CRYPTO_WRITE_EXTENDED) (
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL        *This,
	IN UINT32                              MediaId,
	IN EFI_LBA                             LBA,
	IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN       *Token,
	IN UINT64                              BufferSize,
	IN VOID                                *Buffer,
	IN UINT64                              *Index, OPTIONAL
	IN VOID                                *CryptoIvInput OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_BLOCK_IO_CRYPTO_FLUSH) (
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL        *This,
	IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN       *Token
	);

struct _EFI_BLOCK_IO_CRYPTO_PROTOCOL {
	EFI_BLOCK_IO_MEDIA                          *Media;
	EFI_BLOCK_IO_CRYPTO_RESET                   Reset;
	EFI_BLOCK_IO_CRYPTO_GET_CAPABILITIES        GetCapabilities;
	EFI_BLOCK_IO_CRYPTO_SET_CONFIGURATION       SetConfiguration;
	EFI_BLOCK_IO_CRYPTO_GET_CONFIGURATION       GetConfiguration;
	EFI_BLOCK_IO_CRYPTO_READ_EXTENDED    ReadExtended;
	EFI_BLOCK_IO_CRYPTO_WRITE_EXTENDED   WriteExtended;
	EFI_BLOCK_IO_CRYPTO_FLUSH                   FlushBlocks;
} ;
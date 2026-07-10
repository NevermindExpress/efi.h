#pragma once

#include "types.h"

//EFI_ALLOCATE_TYPE
typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

//EFI_MEMORY_TYPE
// These type values are discussed in Memory Type Usage before ExitBootServices()  and  Memory Type Usage after ExitBootServices().
typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiUnacceptedMemoryType,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

// Memory Attribute Definitions
// These types can be "ORed" together as needed.
#define EFI_MEMORY_UC              0x0000000000000001
#define EFI_MEMORY_WC              0x0000000000000002
#define EFI_MEMORY_WT              0x0000000000000004
#define EFI_MEMORY_WB              0x0000000000000008
#define EFI_MEMORY_UCE             0x0000000000000010
#define EFI_MEMORY_WP              0x0000000000001000
#define EFI_MEMORY_RP              0x0000000000002000
#define EFI_MEMORY_XP              0x0000000000004000
#define EFI_MEMORY_NV              0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE   0x0000000000010000
#define EFI_MEMORY_RO              0x0000000000020000
#define EFI_MEMORY_SP              0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO      0x0000000000080000
#define EFI_MEMORY_HOT_PLUGGABLE   0x0000000000100000
#define EFI_MEMORY_RUNTIME         0x8000000000000000
#define EFI_MEMORY_ISA_VALID       0x4000000000000000
#define EFI_MEMORY_ISA_MASK        0x0FFFF00000000000

//EFI_PHYSICAL_ADDRESS
typedef UINT64 EFI_PHYSICAL_ADDRESS;

//EFI_VIRTUAL_ADDRESS
typedef UINT64 EFI_VIRTUAL_ADDRESS;

// Memory Descriptor Version Number
#define EFI_MEMORY_DESCRIPTOR_VERSION 1

//EFI_MEMORY_DESCRIPTOR
typedef struct {
	UINT32                     Type;
	EFI_PHYSICAL_ADDRESS       PhysicalStart;
	EFI_VIRTUAL_ADDRESS        VirtualStart;
	UINT64                     NumberOfPages;
	UINT64                     Attribute;
} EFI_MEMORY_DESCRIPTOR;

// Function definitions
typedef EFI_STATUS(EFIAPI *EFI_ALLOCATE_PAGES) (
	IN EFI_ALLOCATE_TYPE		Type,
	IN EFI_MEMORY_TYPE			MemoryType,
	IN UINTN					Pages,
	IN OUT EFI_PHYSICAL_ADDRESS	*Memory
	);

typedef EFI_STATUS(EFIAPI *EFI_FREE_PAGES) (
	IN EFI_PHYSICAL_ADDRESS	Memory,
	IN UINTN				Pages
	);

typedef EFI_STATUS(EFIAPI *EFI_GET_MEMORY_MAP) (
	IN OUT UINTN				*MemoryMapSize,
	OUT EFI_MEMORY_DESCRIPTOR	*MemoryMap,
	OUT UINTN					*MapKey,
	OUT UINTN					*DescriptorSize,
	OUT UINT32					*DescriptorVersion
	);

typedef EFI_STATUS(EFIAPI  *EFI_ALLOCATE_POOL) (
	IN EFI_MEMORY_TYPE	PoolType,
	IN UINTN			Size,
	OUT VOID			**Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_FREE_POOL)(IN VOID *Buffer);
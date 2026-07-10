#pragma once
#include "types.h"

typedef EFI_STATUS(EFIAPI *EFI_SET_WATCHDOG_TIMER) (
	IN UINTN                          Timeout,
	IN UINT64                         WatchdogCode,
	IN UINTN                          DataSize,
	IN CHAR16                         *WatchdogData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_STALL) (IN UINTN Microseconds);

typedef VOID(EFIAPI *EFI_COPY_MEM) (
	IN VOID                       *Destination,
	IN VOID                       *Source,
	IN UINTN                      Length
	);

typedef VOID(EFIAPI *EFI_SET_MEM) (
	IN VOID                             *Buffer,
	IN UINTN                            Size,
	IN UINT8                            Value
);

typedef EFI_STATUS(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
	OUT UINT64                       *Count
	);

typedef EFI_STATUS(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (
	IN EFI_GUID                               *Guid,
	IN VOID                                   *Table
	);

typedef EFI_STATUS(EFIAPI *EFI_CALCULATE_CRC32) (
	IN VOID                          *Data,
	IN UINTN                         DataSize,
	OUT UINT32                       *Crc32
);


#pragma once
#include "efi/types.h"

typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
}   EFI_RESET_TYPE;

typedef VOID(EFIAPI *EFI_RESET_SYSTEM) (
	IN EFI_RESET_TYPE          ResetType,
	IN EFI_STATUS              ResetStatus,
	IN UINTN                   DataSize,
	IN VOID                    *ResetData OPTIONAL
 );

typedef EFI_STATUS(EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT)(OUT UINT32 *HighCount);
#pragma once
#include "efi/types.h"

typedef EFI_STATUS(EFIAPI *EFI_IMAGE_LOAD) (
	IN BOOLEAN                          BootPolicy,
	IN EFI_HANDLE                       ParentImageHandle,
	IN EFI_DEVICE_PATH_PROTOCOL         *DevicePath   OPTIONAL,
	IN VOID                             *SourceBuffer OPTIONAL,
	IN UINTN                            SourceSize,
	OUT EFI_HANDLE                      *ImageHandle
	);

typedef EFI_STATUS(EFIAPI *EFI_IMAGE_START) (
	IN EFI_HANDLE                             ImageHandle,
	OUT UINTN                                 *ExitDataSize,
	OUT CHAR16                                **ExitData OPTIONAL
	);

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_UNLOAD) (IN EFI_HANDLE ImageHandle);

typedef EFI_STATUS(EFIAPI *EFI_EXIT) (
	IN EFI_HANDLE                      ImageHandle,
	IN EFI_STATUS                      ExitStatus,
	IN UINTN                           ExitDataSize,
	IN CHAR16                          *ExitData OPTIONAL
	);

typedef EFI_STATUS (EFIAPI *EFI_EXIT_BOOT_SERVICES) (
	IN EFI_HANDLE                       ImageHandle,
	IN UINTN                            MapKey
	);
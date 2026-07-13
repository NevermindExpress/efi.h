#pragma once
#include "efi/types.h"

// UEFI Spec Section 20

#define EFI_ACPI_TABLE_PROTOCOL_GUID {0xffe06bdd, 0x6107, 0x46a6,{0x7b, 0xb2, 0x5a, 0x9c, 0x7e, 0xc5, 0x27, 0x5c}}

typedef struct _EFI_ACPI_TABLE_PROTOCOL EFI_ACPI_TABLE_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_ACPI_TABLE_INSTALL_ACPI_TABLE) (
	IN EFI_ACPI_TABLE_PROTOCOL                   *This,
	IN VOID                                      *AcpiTableBuffer,
	IN UINTN                                     AcpiTableBufferSize,
	OUT UINTN                                    *TableKey
	);

typedef EFI_STATUS(EFIAPI *EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE) (
	IN EFI_ACPI_TABLE_PROTOCOL             *This,
	IN UINTN                               TableKey
	);

struct _EFI_ACPI_TABLE_PROTOCOL {
	EFI_ACPI_TABLE_INSTALL_ACPI_TABLE       InstallAcpiTable;
	EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE     UninstallAcpiTable;
};
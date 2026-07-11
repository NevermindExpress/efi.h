#pragma once
#include "efi/types.h"

#define EFI_DRIVER_DIAGNOSTICS_PROTOCOL_GUID {0x4d330321,0x025f,0x4aac,{0x90,0xd8,0x5e,0xd9,0x00,0x17,0x3b,0x63}}

// EFI_DRIVER_DIAGNOSTIC_TYPE
typedef enum {
	EfiDriverDiagnosticTypeStandard = 0,
	EfiDriverDiagnosticTypeExtended = 1,
	EfiDriverDiagnosticTypeManufacturing = 2,
	EfiDriverDiagnosticTypeCancel = 3,
	EfiDriverDiagnosticTypeMaximum
} EFI_DRIVER_DIAGNOSTIC_TYPE;

typedef struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL EFI_DRIVER_DIAGNOSTICS2_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS) (
 IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL               *This,
 IN EFI_HANDLE                                     ControllerHandle,
 IN EFI_HANDLE                                     ChildHandle OPTIONAL,
 IN EFI_DRIVER_DIAGNOSTIC_TYPE                     DiagnosticType,
 IN CHAR8                                          *Language,
 OUT EFI_GUID                                      **ErrorType,
 OUT UINTN                                         *BufferSize,
 OUT CHAR16                                        **Buffer
 );

struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL {
	EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS       RunDiagnostics;
	CHAR8                                         *SupportedLanguages;
};
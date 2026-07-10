#pragma once
#include "types.h"

// Variable Attributes
#define EFI_VARIABLE_NON_VOLATILE                           0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                     0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS                         0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                  0x00000008 //This attribute is identified by the mnemonic 'HR' elsewhere in this specification.
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS  0x00000020
#define EFI_VARIABLE_APPEND_WRITE                           0x00000040
#define EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS          0x00000080	//This attribute indicates that the variable payload begins
																		//with an EFI_VARIABLE_AUTHENTICATION_3 structure, and
																		//potentially more structures as indicated by fields of this
																		//structure. See definition below and in SetVariable().

typedef EFI_STATUS (EFIAPI *EFI_GET_VARIABLE)(
	IN CHAR16           *VariableName,
	IN EFI_GUID         *VendorGuid,
	OUT UINT32          *Attributes OPTIONAL,
	IN OUT UINTN        *DataSize,
	OUT VOID            *Data OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_GET_NEXT_VARIABLE_NAME)(
	IN OUT UINTN           *VariableNameSize,
	IN OUT CHAR16          *VariableName,
	IN OUT EFI_GUID        *VendorGuid
);

typedef EFI_STATUS(EFIAPI *EFI_SET_VARIABLE)(
	IN CHAR16            *VariableName,
	IN EFI_GUID          *VendorGuid,
	IN UINT32            Attributes,
	IN UINTN             DataSize,
	IN VOID              *Data
);

typedef EFI_STATUS(EFIAPI *EFI_QUERY_VARIABLE_INFO)(
	IN UINT32             Attributes,
	OUT UINT64            *MaximumVariableStorageSize,
	OUT UINT64            *RemainingVariableStorageSize,
	OUT UINT64            *MaximumVariableSize
);


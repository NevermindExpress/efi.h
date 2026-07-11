#pragma once
#include "efi/types.h"

#define EFI_DRIVER_HEALTH_PROTOCOL_GUID {0x2a534210,0x9280,0x41d8,{0xae,0x79,0xca,0xda,0x01,0xa2,0xb1,0x27 }}

typedef VOID    *EFI_HII_HANDLE;
typedef UINT16  EFI_STRING_ID;

// EFI_DRIVER_HEALTH_STATUS
typedef enum {
	EfiDriverHealthStatusHealthy,
	EfiDriverHealthStatusRepairRequired,
	EfiDriverHealthStatusConfigurationRequired,
	EfiDriverHealthStatusFailed,
	EfiDriverHealthStatusReconnectRequired,
	EfiDriverHealthStatusRebootRequired
}  EFI_DRIVER_HEALTH_STATUS;

// EFI_DRIVER_HEALTH_HII_MESSAGE
typedef struct {
	EFI_HII_HANDLE HiiHandle;
	EFI_STRING_ID StringId;
	UINT64 MessageCode;
} EFI_DRIVER_HEALTH_HII_MESSAGE;

// EFI_DRIVER_HEALTH_REPAIR_NOTIFY
typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_HEALTH_REPAIR_NOTIFY) (
 IN UINTN                                  Value,
 IN UINTN                                  Limit
 );

typedef struct _EFI_DRIVER_HEALTH_PROTOCOL EFI_DRIVER_HEALTH_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_DRIVER_HEALTH_GET_HEALTH_STATUS) (
	IN EFI_DRIVER_HEALTH_PROTOCOL           *This,
	IN EFI_HANDLE                           ControllerHandle, OPTIONAL
	IN EFI_HANDLE                           ChildHandle, OPTIONAL
	OUT EFI_DRIVER_HEALTH_STATUS            *HealthStatus,
	OUT EFI_DRIVER_HEALTH_HII_MESSAGE       **MessageList, OPTIONAL
	OUT EFI_HII_HANDLE                      *FormHiiHandle OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_DRIVER_HEALTH_REPAIR) (
	IN EFI_DRIVER_HEALTH_PROTOCOL               *This,
	IN EFI_HANDLE                               ControllerHandle,
	IN EFI_HANDLE                               ChildHandle OPTIONAL,
	IN EFI_DRIVER_HEALTH_REPAIR_NOTIFY          RepairNotify OPTIONAL
	);

struct _EFI_DRIVER_HEALTH_PROTOCOL {
	EFI_DRIVER_HEALTH_GET_HEALTH_STATUS       GetHealthStatus;
	EFI_DRIVER_HEALTH_REPAIR                Repair;
};
#pragma once
#include "efi/types.h"
#include "efi/protocols/devicepath.h"

#define EFI_DRIVER_BINDING_PROTOCOL_GUID {0x18A031AB,0xB443,0x4D1A,{0xA5,0xC0,0x0C,0x09,0x26,0x1E,0x9F,0x71}}

typedef struct _EFI_DRIVER_BINDING_PROTOCOL EFI_DRIVER_BINDING_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED) (
	IN EFI_DRIVER_BINDING_PROTOCOL              *This,
	IN EFI_HANDLE                               ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL                 *RemainingDevicePath OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_START) (
	IN EFI_DRIVER_BINDING_PROTOCOL         *This,
	IN EFI_HANDLE                          ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL            *RemainingDevicePath OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_STOP) (
	IN EFI_DRIVER_BINDING_PROTOCOL           *This,
	IN EFI_HANDLE                            ControllerHandle,
	IN UINTN                                 NumberOfChildren,
	IN EFI_HANDLE                            *ChildHandleBuffer OPTIONAL
	);

struct _EFI_DRIVER_BINDING_PROTOCOL {
	EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED        Supported;
	EFI_DRIVER_BINDING_PROTOCOL_START            Start;
	EFI_DRIVER_BINDING_PROTOCOL_STOP             Stop;
	UINT32                                       Version;
	EFI_HANDLE                                  ImageHandle;
	EFI_HANDLE                                   DriverBindingHandle;
};

typedef struct _EFI_SERVICE_BINDING_PROTOCOL EFI_SERVICE_BINDING_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_SERVICE_BINDING_CREATE_CHILD) (
	IN EFI_SERVICE_BINDING_PROTOCOL                   *This,
	IN OUT EFI_HANDLE                                 *ChildHandle
);

typedef EFI_STATUS(EFIAPI *EFI_SERVICE_BINDING_DESTROY_CHILD) (
	IN EFI_SERVICE_BINDING_PROTOCOL             *This,
	IN EFI_HANDLE                               ChildHandle
	);

struct _EFI_SERVICE_BINDING_PROTOCOL {
	EFI_SERVICE_BINDING_CREATE_CHILD            CreateChild;
	EFI_SERVICE_BINDING_DESTROY_CHILD           DestroyChild;
};
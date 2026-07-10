#pragma once

#include "types.h"

typedef enum {
	EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef enum {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef struct {
	EFI_HANDLE                          AgentHandle;
	EFI_HANDLE                          ControllerHandle;
	UINT32                              Attributes;
	UINT32                              OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef EFI_STATUS(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
	IN OUT EFI_HANDLE             *Handle,
	IN EFI_GUID                   *Protocol,
	IN EFI_INTERFACE_TYPE         InterfaceType,
	IN VOID                       *Interface
	);

typedef EFI_STATUS(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE        Handle,
	IN EFI_GUID          *Protocol,
	IN VOID              *Interface
	);

typedef EFI_STATUS(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE           Handle,
	IN EFI_GUID             *Protocol,
	IN VOID                 *OldInterface,
	IN VOID                 *NewInterface
	);

typedef EFI_STATUS(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
	IN EFI_GUID                         *Protocol,
	IN EFI_EVENT                        Event,
	OUT VOID                            **Registration
	);

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_HANDLE) (
	IN EFI_LOCATE_SEARCH_TYPE                 SearchType,
	IN EFI_GUID                               *Protocol OPTIONAL,
	IN VOID                                   *SearchKey OPTIONAL,
	IN OUT UINTN                              *BufferSize,
	OUT EFI_HANDLE                            *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_HANDLE_PROTOCOL) (
	IN EFI_HANDLE                    Handle,
	IN EFI_GUID                      *Protocol,
	OUT VOID                         **Interface
	);

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_DEVICE_PATH) (
	IN EFI_GUID                         *Protocol,
	IN OUT EFI_DEVICE_PATH_PROTOCOL     **DevicePath,
	OUT EFI_HANDLE                      *Device
	);

typedef EFI_STATUS(EFIAPI *EFI_OPEN_PROTOCOL) (
	IN EFI_HANDLE                    Handle,
	IN EFI_GUID                      *Protocol,
	OUT VOID                         **Interface OPTIONAL,
	IN EFI_HANDLE                    AgentHandle,
	IN EFI_HANDLE                    ControllerHandle,
	IN UINT32                        Attributes
	);

typedef EFI_STATUS(EFIAPI *EFI_CLOSE_PROTOCOL) (
	IN EFI_HANDLE                 Handle,
	IN EFI_GUID                   *Protocol,
	IN EFI_HANDLE                 AgentHandle,
	IN EFI_HANDLE                 ControllerHandle
	);

typedef EFI_STATUS(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
	IN EFI_HANDLE                             Handle,
	IN EFI_GUID                               *Protocol,
	OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY   **EntryBuffer,
	OUT UINTN                                 *EntryCount
	);

typedef EFI_STATUS(EFIAPI *EFI_CONNECT_CONTROLLER) (
	IN EFI_HANDLE                       ControllerHandle,
	IN EFI_HANDLE                       *DriverImageHandle OPTIONAL,
	IN EFI_DEVICE_PATH_PROTOCOL         *RemainingDevicePath OPTIONAL,
	IN BOOLEAN Recursive
	);

typedef EFI_STATUS(EFIAPI *EFI_DISCONNECT_CONTROLLER) (
	IN EFI_HANDLE                       ControllerHandle,
	IN EFI_HANDLE                       DriverImageHandle OPTIONAL,
	IN EFI_HANDLE                       ChildHandle OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
	IN EFI_HANDLE                             Handle,
	OUT EFI_GUID                              ***ProtocolBuffer,
	OUT UINTN                                 *ProtocolBufferCount
	);

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
	IN EFI_LOCATE_SEARCH_TYPE                    SearchType,
	IN EFI_GUID                                  *Protocol OPTIONAL,
	IN VOID                                      *SearchKey OPTIONAL,
	OUT UINTN                                    *NoHandles,
	OUT EFI_HANDLE                               **Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_LOCATE_PROTOCOL) (
	IN EFI_GUID                            *Protocol,
	IN VOID                                *Registration OPTIONAL,
	OUT VOID                               **Interface
	);

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN OUT EFI_HANDLE	*Handle,
	...
);

typedef EFI_STATUS(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN EFI_HANDLE Handle,
	...
);


#pragma once
// UEFI spec section 13.17

#include "efi/types.h"
#include "efi/protocols/devicepath.h"

#define EFI_RAM_DISK_PROTOCOL_GUID { 0xab38a0df, 0x6873, 0x44a9, { 0x87, 0xe6, 0xd4, 0xeb, 0x56, 0x14, 0x84, 0x49 }}

typedef struct  _EFI_RAM_DISK_PROTOCOL EFI_RAM_DISK_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_RAM_DISK_REGISTER_RAMDISK) (
  IN UINT64                              RamDiskBase,
  IN UINT64                              RamDiskSize,
  IN EFI_GUID                            *RamDiskType,
  IN EFI_DEVICE_PATH_PROTOCOL  *ParentDevicePath OPTIONAL, // shitheads at intel wrote EFI_DEVICE_PATH there instead, that is invalid. you have no idea how much thousand times i saw errors on THE UEFI SPEC RELEASED BY UEFI FORM AND INTEL THEMSELVES
  OUT EFI_DEVICE_PATH_PROTOCOL           **DevicePath
);

typedef EFI_STATUS(EFIAPI *EFI_RAM_DISK_UNREGISTER_RAMDISK) (
	IN EFI_DEVICE_PATH_PROTOCOL              *DevicePath
);

struct  _EFI_RAM_DISK_PROTOCOL {
	EFI_RAM_DISK_REGISTER_RAMDISK              Register;
	EFI_RAM_DISK_UNREGISTER_RAMDISK            Unregister;
};
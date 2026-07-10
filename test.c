#include "efi.h"
#include <vcruntime.h>

EFI_STATUS EFIAPI EfiMain(IN EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	EFI_BOOT_SERVICES* bs = SystemTable->BootServices;
	EFI_RUNTIME_SERVICES* rt = SystemTable->RuntimeServices;
	rt->ResetSystem(0, 0, 0, 0);
}
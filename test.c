#include "efi-amalgamation.h"
#include <vcruntime.h>

EFI_STATUS EFIAPI EfiMain(IN EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	EFI_BOOT_SERVICES* bs = SystemTable->BootServices;
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	UINTN        HandleCount;
	EFI_HANDLE   *HandleBuffer = NULL;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

	EFI_STATUS Status = bs->LocateHandleBuffer(ByProtocol, &gopGuid, NULL, &HandleCount, &HandleBuffer);

	for (size_t i = 0; i < HandleCount; i++) {
		bs->HandleProtocol(HandleBuffer[i], &gopGuid, (VOID **)&gop);
		gop->SetMode(gop, 0);
	}

	int j = 0;
	while (1) {
		if (j > 255) j = 0;

		for (size_t i = 0; i < HandleCount; i++) {
			bs->HandleProtocol(HandleBuffer[i], &gopGuid, (VOID **)&gop);
			char* fb = gop->Mode->FrameBufferBase;

			for (size_t k = 0; k < gop->Mode->FrameBufferSize; k++) {
				fb[k] = j;
			}
		}

		j++;
	}
}
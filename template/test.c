#include "efi.h"

EFI_STATUS EFIAPI EfiMain(IN EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	_Static_assert(sizeof(EFI_GUID) == 16, "EFI_GUID size mismatch");
	_Static_assert(sizeof(EFI_TABLE_HEADER) == 24, "EFI_TABLE_HEADER size mismatch");
	EFI_BOOT_SERVICES* bs = SystemTable->BootServices;
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	UINTN        HandleCount;
	EFI_HANDLE   *HandleBuffer = 0;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

	EFI_STATUS Status = bs->LocateHandleBuffer(ByProtocol, &gopGuid, 0, &HandleCount, &HandleBuffer);

	for (UINT64 i = 0; i < HandleCount; i++) {
		bs->HandleProtocol(HandleBuffer[i], &gopGuid, (VOID **)&gop);
		gop->SetMode(gop, 0);
	}

	int j = 0;
	while (1) {
		if (j > 255) j = 0;

		for (UINT64 i = 0; i < HandleCount; i++) {
			bs->HandleProtocol(HandleBuffer[i], &gopGuid, (VOID **)&gop);
			char* fb = (char*)gop->Mode->FrameBufferBase;

			for (UINT64 k = 0; k < gop->Mode->FrameBufferSize; k++) {
				fb[k] = j;
			}
		}

		j+=10;
	}
}
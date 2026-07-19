#define EFI_H_HELPER_IMPLEMENTATION
#include "efi.h"

EFI_STATUS EFIAPI EfiMain(IN EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	_Static_assert(sizeof(EFI_GUID) == 16, "EFI_GUID size mismatch");
	_Static_assert(sizeof(EFI_TABLE_HEADER) == 24, "EFI_TABLE_HEADER size mismatch");

	EfiHInitHelpers(SystemTable);

	ClearScreen();
	Print(L"%a %s %d\r\n", "Stacey", L"Stacey", -5);
	Print(L"Hello, Firmware!\r\nPress any key to continue...");
	WaitForKey();	

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

	unsigned char j = 0;
	while (1) {

		for (UINT64 i = 0; i < HandleCount; i++) {
			bs->HandleProtocol(HandleBuffer[i], &gopGuid, (VOID **)&gop);
			char* fb = (char*)gop->Mode->FrameBufferBase;

			bs->SetMem(fb, gop->Mode->FrameBufferSize, j);
		}

		j+=1;
	}
}
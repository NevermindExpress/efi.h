#pragma once
#include "efi/types.h"

//******************************************************
// EFI_TPL
//******************************************************
typedef UINTN EFI_TPL;

//******************************************************
// Task Priority Levels
//******************************************************
#define TPL_APPLICATION    4
#define TPL_CALLBACK       8
#define TPL_NOTIFY         16
#define TPL_HIGH_LEVEL     31

typedef EFI_TPL (EFIAPI *EFI_RAISE_TPL)(IN EFI_TPL NewTpl);
typedef VOID(EFIAPI *EFI_RESTORE_TPL)(IN EFI_TPL OldTpl);
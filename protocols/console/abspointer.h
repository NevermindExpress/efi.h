#pragma once
#include "types.h"
#include "common.h"

#define EFI_ABSOLUTE_POINTER_PROTOCOL_GUID {0x8D59D32B, 0xC655, 0x4AE9, {0x9B, 0x15, 0xF2, 0x59, 0x04, 0x99, 0x2A, 0x43}}
typedef struct _EFI_ABSOLUTE_POINTER_PROTOCOL EFI_ABSOLUTE_POINTER_PROTOCOL;

// EFI_ABSOLUTE_POINTER_MODE
typedef struct {
	UINT64                     AbsoluteMinX;
	UINT64                     AbsoluteMinY;
	UINT64                     AbsoluteMinZ;
	UINT64                     AbsoluteMaxX;
	UINT64                     AbsoluteMaxY;
	UINT64                     AbsoluteMaxZ;
	UINT32                     Attributes;
} EFI_ABSOLUTE_POINTER_MODE;

// EFI_ABSOLUTE_POINTER_STATE
typedef struct {
	UINT64                 CurrentX;
	UINT64                 CurrentY;
	UINT64                 CurrentZ;
	UINT32                 ActiveButtons;
} EFI_ABSOLUTE_POINTER_STATE;

// EFI_ABSOLUTE_POINTER_PROTOCOL
#define EFI_ABSP_SupportsAltActive     0x00000001
#define EFI_ABSP_SupportsPressureAsZ   0x00000002
#define EFI_ABSP_TouchActive     0x00000001
#define EFI_ABS_AltActive        0x00000002

typedef EFI_STATUS(EFIAPI *EFI_ABSOLUTE_POINTER_RESET) (
	IN EFI_ABSOLUTE_POINTER_PROTOCOL            *This,
	IN BOOLEAN                                  ExtendedVerification
	);

typedef EFI_STATUS(EFIAPI *EFI_ABSOLUTE_POINTER_GET_STATE) (
	IN EFI_ABSOLUTE_POINTER_PROTOCOL            *This,
	OUT EFI_ABSOLUTE_POINTER_STATE              *State
	);

struct _EFI_ABSOLUTE_POINTER_PROTOCOL {
	EFI_ABSOLUTE_POINTER_RESET                     Reset;
	EFI_ABSOLUTE_POINTER_GET_STATE                 GetState;
	EFI_EVENT                                      WaitForInput;
	EFI_ABSOLUTE_POINTER_MODE                      *Mode;
};
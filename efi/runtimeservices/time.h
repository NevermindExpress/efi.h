#pragma once
#include "efi/types.h"

// EFI_TIME_CAPABILITIES
// This provides the capabilities of the
// real time clock device as exposed through the EFI interfaces.
typedef struct {
	UINT32                  Resolution;
	UINT32                  Accuracy;
	BOOLEAN                 SetsToZero;
}   EFI_TIME_CAPABILITIES;

// Bit Definitions for EFI_TIME.Daylight. See below.
#define EFI_TIME_ADJUST_DAYLIGHT   0x01
#define EFI_TIME_IN_DAYLIGHT       0x02

// Value Definition for EFI_TIME.TimeZone. See below.
#define EFI_UNSPECIFIED_TIMEZONE   0x07FF

typedef EFI_STATUS(EFIAPI *EFI_GET_TIME)(
	OUT EFI_TIME                  *Time,
	OUT EFI_TIME_CAPABILITIES     *Capabilities OPTIONAL
);

typedef EFI_STATUS(EFIAPI *EFI_SET_TIME)(IN EFI_TIME *Time);

typedef EFI_STATUS(EFIAPI *EFI_GET_WAKEUP_TIME)(
	OUT BOOLEAN            *Enabled,
	OUT BOOLEAN            *Pending,
	OUT EFI_TIME           *Time
);

typedef EFI_STATUS(EFIAPI *EFI_SET_WAKEUP_TIME)(
	IN BOOLEAN         Enable,
	IN EFI_TIME        *Time OPTIONAL
);
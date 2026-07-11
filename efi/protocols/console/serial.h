#pragma once
#include "efi/types.h"

#define EFI_SERIAL_IO_PROTOCOL_REVISION      0x00010000
#define EFI_SERIAL_IO_PROTOCOL_REVISION1p1   0x00010001

#define EFI_SERIAL_IO_PROTOCOL_GUID {0xBB25CF6F,0xF1D4,0x11D2, {0x9a,0x0c,0x00,0x90,0x27,0x3f,0xc1,0xfd}}
#define EFI_SERIAL_TERMINAL_DEVICE_TYPE_GUID { 0x6ad9a60f, 0x5815, 0x4c7c, { 0x8a, 0x10, 0x50, 0x53, 0xd2, 0xbf, 0x7a, 0x1b } }

// CONTROL BITS
#define EFI_SERIAL_CLEAR_TO_SEND                0x0010
#define EFI_SERIAL_DATA_SET_READY               0x0020
#define EFI_SERIAL_RING_INDICATE                0x0040
#define EFI_SERIAL_CARRIER_DETECT               0x0080
#define EFI_SERIAL_REQUEST_TO_SEND              0x0002
#define EFI_SERIAL_DATA_TERMINAL_READY          0x0001
#define EFI_SERIAL_INPUT_BUFFER_EMPTY           0x0100
#define EFI_SERIAL_OUTPUT_BUFFER_EMPTY          0x0200
#define EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE     0x1000
#define EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE     0x2000
#define EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE 0x4000

typedef struct _EFI_SERIAL_IO_PROTOCOL EFI_SERIAL_IO_PROTOCOL;

// SERIAL_IO_MODE
typedef struct {
	UINT32 ControlMask;

	// current Attributes
	UINT32            Timeout;
	UINT64            BaudRate;
	UINT32            ReceiveFifoDepth;
	UINT32            DataBits;
	UINT32            Parity;
	UINT32            StopBits;
} SERIAL_IO_MODE;

// EFI_PARITY_TYPE
typedef enum {
	DefaultParity,
	NoParity,
	EvenParity,
	OddParity,
	MarkParity,
	SpaceParity
} EFI_PARITY_TYPE;

// EFI_STOP_BITS_TYPE
typedef enum {
	DefaultStopBits,
	OneStopBit,         // 1 stop bit
	OneFiveStopBits,    // 1.5 stop bits
	TwoStopBits         // 2 stop bits
} EFI_STOP_BITS_TYPE;

typedef EFI_STATUS(EFIAPI *EFI_SERIAL_RESET)(IN EFI_SERIAL_IO_PROTOCOL *This);

typedef EFI_STATUS (EFIAPI *EFI_SERIAL_SET_ATTRIBUTES) (
	IN EFI_SERIAL_IO_PROTOCOL              *This,
	IN UINT64                              BaudRate,
	IN UINT32                              ReceiveFifoDepth,
	IN UINT32                              Timeout,
	IN EFI_PARITY_TYPE                     Parity,
	IN UINT8                               DataBits,
	IN EFI_STOP_BITS_TYPE                  StopBits
	);

typedef EFI_STATUS(EFIAPI *EFI_SERIAL_SET_CONTROL_BITS) (
	IN EFI_SERIAL_IO_PROTOCOL                   *This,
	IN UINT32                                   Control
	);

typedef EFI_STATUS (EFIAPI *EFI_SERIAL_GET_CONTROL_BITS) (
	IN EFI_SERIAL_IO_PROTOCOL             *This,
	OUT UINT32                            *Control
	);

typedef EFI_STATUS(EFIAPI *EFI_SERIAL_WRITE) (
	IN EFI_SERIAL_IO_PROTOCOL             *This,
	IN OUT UINTN                          *BufferSize,
	IN VOID                               *Buffer
	);

typedef EFI_STATUS(EFIAPI *EFI_SERIAL_READ) (
	IN EFI_SERIAL_IO_PROTOCOL           *This,
	IN OUT UINTN                        *BufferSize,
	OUT VOID                            *Buffer
	);

struct _EFI_SERIAL_IO_PROTOCOL {
	UINT32                       Revision;
	EFI_SERIAL_RESET             Reset;
	EFI_SERIAL_SET_ATTRIBUTES    SetAttributes;
	EFI_SERIAL_SET_CONTROL_BITS  SetControl;
	EFI_SERIAL_GET_CONTROL_BITS  GetControl;
	EFI_SERIAL_WRITE             Write;
	EFI_SERIAL_READ              Read;
	SERIAL_IO_MODE               *Mode;
	CONST EFI_GUID               *DeviceTypeGuid; // Revision 1.1
};
#pragma once
#include "efi/types.h"

// UEFI Spec Section 28.8

#define EFI_FTP4_SERVICE_BINDING_PROTOCOL_GUID {0xfaaecb1, 0x226e, 0x4782,{0xaa, 0xce, 0x7d, 0xb9, 0xbc, 0xbf, 0x4d, 0xaf}}
#define EFI_FTP4_PROTOCOL_GUID {0xeb338826, 0x681b, 0x4295,{0xb3, 0x56, 0x2b, 0x36, 0x4c, 0x75, 0x7b, 0x09}}

// EFI_FTP4_CONNECTION_TOKEN
typedef struct {
	EFI_EVENT               Event;
	EFI_STATUS              Status;
}   EFI_FTP4_CONNECTION_TOKEN;

// EFI_FTP4_CONFIG_DATA
typedef struct {
	UINT8              *Username;
	UINT8              *Password;
	BOOLEAN            Active;
	BOOLEAN            UseDefaultSetting;
	EFI_IPv4_ADDRESS   StationIp;
	EFI_IPv4_ADDRESS   SubnetMask;
	EFI_IPv4_ADDRESS   GatewayIp;
	EFI_IPv4_ADDRESS   ServerIp;
	UINT16             ServerPort;
	UINT16             AltDataPort;
	UINT8              RepType;
	UINT8              FileStruct;
	UINT8              TransMode;
}   EFI_FTP4_CONFIG_DATA;

typedef struct _EFI_FTP4_COMMAND_TOKEN EFI_FTP4_COMMAND_TOKEN;
typedef struct _EFI_FTP4_PROTOCOL EFI_FTP4_PROTOCOL;

// EFI_FTP4_DATA_CALLBACK
typedef EFI_STATUS(EFIAPI *EFI_FTP4_DATA_CALLBACK)(
	IN EFI_FTP4_COMMAND_TOKEN   *Token,
	IN EFI_FTP4_PROTOCOL        *This
	);

// EFI_FTP4_COMMAND_TOKEN
struct _EFI_FTP4_COMMAND_TOKEN {
	EFI_EVENT                Event;
	UINT8                    *Pathname;
	UINT64                   DataBufferSize;
	VOID                     *DataBuffer;
	EFI_FTP4_DATA_CALLBACK   DataCallback;
	VOID                     *Context;
	EFI_STATUS               Status;
};

// EFI_FTP4_DATA_CALLBACK
typedef EFI_STATUS(EFIAPI *EFI_FTP4_DATA_CALLBACK)(
	IN EFI_FTP4_COMMAND_TOKEN   *Token,
	IN EFI_FTP4_PROTOCOL        *This
	);

typedef EFI_STATUS(EFIAPI *EFI_FTP4_GET_MODE_DATA)(
	IN EFI_FTP4_PROTOCOL              *This,
	OUT EFI_FTP4_CONFIG_DATA          *ModeData
	);

typedef EFI_STATUS(EFIAPI *EFI_FTP4_CONNECT) (
	IN EFI_FTP4_PROTOCOL           *This,
	IN EFI_FTP4_CONNECTION_TOKEN   *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_FTP4_CLOSE)(
	IN EFI_FTP4_PROTOCOL           *This,
	IN EFI_FTP4_CONNECTION_TOKEN   *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_FTP4_CONFIGURE) (
	IN EFI_FTP4_PROTOCOL           *This,
	IN EFI_FTP4_CONFIG_DATA        *FtpConfigData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_FTP4_READ_FILE)(
	IN EFI_FTP4_PROTOCOL          *This,
	IN EFI_FTP4_COMMAND_TOKEN     *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_FTP4_WRITE_FILE)(
	IN EFI_FTP4_PROTOCOL           *This,
	IN EFI_FTP4_COMMAND_TOKEN      *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_FTP4_READ_DIRECTORY) (
	IN EFI_FTP4_PROTOCOL              *This,
	IN EFI_FTP4_COMMAND_TOKEN         *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_FTP4_POLL) (IN EFI_FTP4_PROTOCOL *This);

struct _EFI_FTP4_PROTOCOL {
	EFI_FTP4_GET_MODE_DATA      GetModeData;
	EFI_FTP4_CONNECT            Connect;
	EFI_FTP4_CLOSE              Close;
	EFI_FTP4_CONFIGURE          Configure;
	EFI_FTP4_READ_FILE          ReadFile;
	EFI_FTP4_WRITE_FILE         WriteFile;
	EFI_FTP4_READ_DIRECTORY     ReadDirectory;
	EFI_FTP4_POLL               Poll;
};
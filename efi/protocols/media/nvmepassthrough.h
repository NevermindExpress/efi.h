#pragma once
// UEFI spec section 13.15

#include "efi/types.h"
#include "efi/protocols/devicepath.h"

#define EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID { 0x52c78312, 0x8edc, 0x4233,{ 0x98, 0xf2, 0x1a, 0x1a, 0xa5, 0xe3, 0x88, 0xa5 }};

typedef struct {
	UINT32          Attributes;
	UINT32          IoAlign;
	UINT32          NvmeVersion;
}  EFI_NVM_EXPRESS_PASS_THRU_MODE;

#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL    0x0001
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_LOGICAL     0x0002
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_NONBLOCKIO  0x0004
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVM 0x0008

typedef struct {
	UINT32 OpCode : 8;
	UINT32 FusedOperation : 2;
	UINT32 Reserved : 22;
} NVME_CDW0;

// FusedOperation*
#define NORMAL_CMD 0x00
#define FUSED_FIRST_CMD 0x01
#define FUSED_SECOND_CMD 0x02

typedef struct {
	NVME_CDW0 Cdw0;
	UINT8 Flags;
	UINT32 Nsid;
	UINT32 Cdw2;
	UINT32 Cdw3;
	UINT32 Cdw10;
	UINT32 Cdw11;
	UINT32 Cdw12;
	UINT32 Cdw13;
	UINT32 Cdw14;
	UINT32 Cdw15;
} EFI_NVM_EXPRESS_COMMAND;

// Flags
#define CDW2_VALID 0x01
#define CDW3_VALID 0x02
#define CDW10_VALID 0x04
#define CDW11_VALID 0x08
#define CDW12_VALID 0x10
#define CDW13_VALID 0x20
#define CDW14_VALID 0x40
#define CDW15_VALID 0x80

//
// This structure maps to the NVM Express specification Completion Queue Entry
//
typedef struct {
	UINT32 DW0;
	UINT32 DW1;
	UINT32 DW2;
	UINT32 DW3;
} EFI_NVM_EXPRESS_COMPLETION;


typedef struct {
	UINT64                       CommandTimeout;
	VOID                         TransferBuffer OPTIONAL;
	UINT32                       TransferLength OPTIONAL;
	VOID                         *MetaDataBuffer OPTIONAL;
	UINT32                       MetadataLength OPTIONAL;
	UINT8                        QueueType;
	EFI_NVM_EXPRESS_COMMAND      *NvmeCmd;
	EFI_NVM_EXPRESS_COMPLETION   *NvmeCompletion;
}  EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET;

typedef struct  _EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL; 

typedef EFI_STATUS(EFIAPI *EFI_NVM_EXPRESS_PASS_THRU_PASSTHRU) (
	IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL             This,
	IN UINT32                                         NamespaceId,
	IN OUT EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET   *Packet,
	IN EFI_EVENT                                      Event OPTIONAL
);

typedef EFI_STATUS(EFIAPI *EFI_NVM_EXPRESS_PASS_THRU_GET_NEXT_NAMESPACE) (
	IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL                   *This,
	IN OUT UINT32                                           *NamespaceId
);

typedef EFI_STATUS(EFIAPI *EFI_NVM_EXPRESS_PASS_THRU_BUILD_DEVICE_PATH) (
	IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL        *This,
	IN UINT32                                   NamespaceId,
	OUT EFI_DEVICE_PATH_PROTOCOL                **DevicePath
);

typedef EFI_STATUS(EFIAPI *EFI_NVM_EXPRESS_PASS_THRU_GET_NAMESPACE) (
	IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL                 *This,
	IN EFI_DEVICE_PATH_PROTOCOL                           *DevicePath,
	OUT UINT32                                            *NamespaceId
);

struct  _EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL {
	EFI_NVM_EXPRESS_PASS_THRU_MODE                    *Mode;
	EFI_NVM_EXPRESS_PASS_THRU_PASSTHRU                PassThru;
	EFI_NVM_EXPRESS_PASS_THRU_GET_NEXT_NAMESPACE      GetNextNamespace;
	EFI_NVM_EXPRESS_PASS_THRU_BUILD_DEVICE_PATH       BuildDevicePath;
	EFI_NVM_EXPRESS_PASS_THRU_GET_NAMESPACE           GetNamespace;
};
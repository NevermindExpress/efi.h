#pragma once
#include "efi/types.h"

// UEFI Spec Section 30.3
#define EFI_MTFTP4_SERVICE_BINDING_PROTOCOL_GUID {0x2e800be,0x8f01,0x4aa6,{0x94,0x6b,0xd7,0x13,0x88,0xe1,0x83,0x3f}}
#define EFI_MTFTP4_PROTOCOL_GUID {0x78247c57,0x63db,0x4708,{0x99,0xc2,0xa8,0xb4,0xa9,0xa6,0x1f,0x6b}}

// MTFTP Packet OpCodes
#define EFI_MTFTP4_OPCODE_RRQ    1
#define EFI_MTFTP4_OPCODE_WRQ    2
#define EFI_MTFTP4_OPCODE_DATA   3
#define EFI_MTFTP4_OPCODE_ACK    4
#define EFI_MTFTP4_OPCODE_ERROR  5
#define EFI_MTFTP4_OPCODE_OACK   6
#define EFI_MTFTP4_OPCODE_DIR    7
//This field should be ignored and treated as reserved.
#define EFI_MTFTP4_OPCODE_DATA8  8
//This field should be ignored and treated as reserved.
#define EFI_MTFTP4_OPCODE_ACK8   9

// MTFTP ERROR Packet ErrorCodes
#define EFI_MTFTP4_ERRORCODE_NOT_DEFINED         0
#define EFI_MTFTP4_ERRORCODE_FILE_NOT_FOUND      1
#define EFI_MTFTP4_ERRORCODE_ACCESS_VIOLATION    2
#define EFI_MTFTP4_ERRORCODE_DISK_FULL           3
#define EFI_MTFTP4_ERRORCODE_ILLEGAL_OPERATION   4
#define EFI_MTFTP4_ERRORCODE_UNKNOWN_TRANSFER_ID 5
#define EFI_MTFTP4_ERRORCODE_FILE_ALREADY_EXISTS 6
#define EFI_MTFTP4_ERRORCODE_NO_SUCH_USER        7
#define EFI_MTFTP4_ERRORCODE_REQUEST_DENIED      8

// EFI_MTFTP4_CONFIG_DATA
typedef struct {
	BOOLEAN              UseDefaultSetting;
	EFI_IPv4_ADDRESS     StationIp;
	EFI_IPv4_ADDRESS     SubnetMask;
	UINT16               LocalPort;
	EFI_IPv4_ADDRESS     GatewayIp;
	EFI_IPv4_ADDRESS     ServerIp;
	UINT16               InitialServerPort;
	UINT16               TryCount;
	UINT16               TimeoutValue;
}  EFI_MTFTP4_CONFIG_DATA;

// EFI_MTFTP4_MODE_DATA
typedef struct {
	EFI_MTFTP4_CONFIG_DATA   ConfigData;
	UINT8                    SupportedOptionCount;
	UINT8                    **SupportedOptions;
	UINT8                    UnsupportedOptionCount;
	UINT8                    **UnsupportedOptions;
}  EFI_MTFTP4_MODE_DATA;

// EFI_MTFTP_OVERRIDE_DATA
typedef struct {
	EFI_IPv4_ADDRESS       GatewayIp;
	EFI_IPv4_ADDRESS       ServerIp;
	UINT16                 ServerPort;
	UINT16                 TryCount;
	UINT16                 TimeoutValue;
}  EFI_MTFTP4_OVERRIDE_DATA;

// EFI_MTFTP4_OPTION
typedef struct {
	UINT8            *OptionStr;
	UINT8            *ValueStr;
}  EFI_MTFTP4_OPTION;

#pragma pack(push,1)
//*********************************************
// EFI_MTFTP4_REQ_HEADER
//*********************************************
typedef struct {
	UINT16                     OpCode;
	UINT8                      Filename[1];
} EFI_MTFTP4_REQ_HEADER;

//*********************************************
// EFI_MTFTP4_OACK_HEADER
//*********************************************
typedef struct {
	UINT16                     OpCode;
	UINT8                      Data[1];
}  EFI_MTFTP4_OACK_HEADER;

//*********************************************
// EFI_MTFTP4_DATA_HEADER
//*********************************************
typedef struct {
	UINT16                     OpCode;
	UINT16                     Block;
	UINT8                      Data[1];
}  EFI_MTFTP4_DATA_HEADER;

//*********************************************
// EFI_MTFTP4_ACK_HEADER
//*********************************************
typedef struct {
	UINT16                     OpCode;
	UINT16                     Block[1];
}  EFI_MTFTP4_ACK_HEADER;

//*********************************************
// EFI_MTFTP4_DATA8_HEADER
// This field should be ignored and treated as reserved
//*********************************************
typedef struct {
	UINT16                     OpCode;
	UINT64                     Block;
	UINT8                      Data[1];
}  EFI_MTFTP4_DATA8_HEADER;

//*********************************************
// EFI_MTFTP4_ACK8_HEADER
// This field should be ignored and treated as reserved
//*********************************************
typedef struct {
	UINT16                     OpCode;
	UINT64                     Block[1];
}  EFI_MTFTP4_ACK8_HEADER;

//*********************************************
// EFI_MTFTP4_ERROR_HEADER
//*********************************************
typedef struct {
	UINT16                     OpCode;
	UINT16                     ErrorCode;
	UINT8                      ErrorMessage[1];
}  EFI_MTFTP4_ERROR_HEADER;


// EFI_MTFTP4_PACKET
typedef union {
	UINT16                     OpCode;
	EFI_MTFTP4_REQ_HEADER      Rrq, Wrq;
	EFI_MTFTP4_OACK_HEADER     Oack;
	EFI_MTFTP4_DATA_HEADER     Data;
	EFI_MTFTP4_ACK_HEADER      Ack;
	// This field should be ignored and treated as reserved
	EFI_MTFTP4_DATA8_HEADER     Data8;
	// This field should be ignored and treated as reserved
	EFI_MTFTP4_ACK8_HEADER     Ack8;
	EFI_MTFTP4_ERROR_HEADER    Error;
}  EFI_MTFTP4_PACKET;
#pragma pack(pop)

typedef struct _EFI_MTFTP4_PROTOCOL EFI_MTFTP4_PROTOCOL;

// EFI_MTFTP4_TOKEN
typedef struct _EFI_MTFTP4_TOKEN EFI_MTFTP4_TOKEN;

// EFI_MTFTP4_CHECK_PACKET
typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_CHECK_PACKET)(
	IN EFI_MTFTP4_PROTOCOL       *This,
	IN EFI_MTFTP4_TOKEN          *Token,
	IN UINT16                    PacketLen,
	IN EFI_MTFTP4_PACKET         *Packet
	);

// EFI_MTFTP4_TIMEOUT_CALLBACK
typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_TIMEOUT_CALLBACK)(
	IN EFI_MTFTP4_PROTOCOL         *This,
	IN EFI_MTFTP4_TOKEN            *Token
	);

// EFI_MTFTP4_PACKET_NEEDED
typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_PACKET_NEEDED)(
	IN EFI_MTFTP4_PROTOCOL         *This,
	IN EFI_MTFTP4_TOKEN            *Token,
	IN OUT UINT16                  *Length,
	OUT VOID                       **Buffer
	);

struct _EFI_MTFTP4_TOKEN {
	EFI_STATUS                  Status;
	EFI_EVENT                   Event;
	EFI_MTFTP4_OVERRIDE_DATA    *OverrideData;
	UINT8                       *Filename;
	UINT8                       *ModeStr;
	UINT32                      OptionCount;
	EFI_MTFTP4_OPTION           *OptionList;
	UINT64                      BufferSize;
	VOID                        *Buffer;
	VOID                        *Context;
	EFI_MTFTP4_CHECK_PACKET     CheckPacket;
	EFI_MTFTP4_TIMEOUT_CALLBACK TimeoutCallback;
	EFI_MTFTP4_PACKET_NEEDED    PacketNeeded;
};

typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_GET_MODE_DATA)(
	IN EFI_MTFTP4_PROTOCOL         *This,
	OUT EFI_MTFTP4_MODE_DATA       *ModeData
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_CONFIGURE)(
	IN EFI_MTFTP4_PROTOCOL         *This,
	IN EFI_MTFTP4_CONFIG_DATA      *MtftpConfigData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_GET_INFO)(
	IN EFI_MTFTP4_PROTOCOL         *This,
	IN EFI_MTFTP4_OVERRIDE_DATA    *OverrideData OPTIONAL,
	IN UINT8                       *Filename,
	IN UINT8                       *ModeStr OPTIONAL,
	IN UINT8                       OptionCount,
	IN EFI_MTFTP4_OPTION           *OptionList OPTIONAL,
	OUT UINT32                     *PacketLength,
	OUT EFI_MTFTP4_PACKET          **Packet OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_PARSE_OPTIONS)(
	IN EFI_MTFTP4_PROTOCOL       *This,
	IN UINT32                    PacketLen,
	IN EFI_MTFTP4_PACKET         *Packet,
	OUT UINT32                   *OptionCount,
	OUT EFI_MTFTP4_OPTION        **OptionList OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_READ_FILE)(
	IN EFI_MTFTP4_PROTOCOL       *This,
	IN EFI_MTFTP4_TOKEN          *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_WRITE_FILE)(
	IN EFI_MTFTP4_PROTOCOL       *This,
	IN EFI_MTFTP4_TOKEN          *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_READ_DIRECTORY)(
	IN EFI_MTFTP4_PROTOCOL       *This,
	IN EFI_MTFTP4_TOKEN          *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP4_POLL) (IN EFI_MTFTP4_PROTOCOL *This);

struct _EFI_MTFTP4_PROTOCOL {
	EFI_MTFTP4_GET_MODE_DATA     GetModeData;
	EFI_MTFTP4_CONFIGURE         Configure;
	EFI_MTFTP4_GET_INFO          GetInfo;
	EFI_MTFTP4_PARSE_OPTIONS     ParseOptions;
	EFI_MTFTP4_READ_FILE         ReadFile;
	EFI_MTFTP4_WRITE_FILE        WriteFile;
	EFI_MTFTP4_READ_DIRECTORY    ReadDirectory;
	EFI_MTFTP4_POLL              Poll;
};

// UEFI Spec Section 30.4
#define EFI_MTFTP6_PROTOCOL_GUID {0xbf0a78ba,0xec29,0x49cf,{0xa1,0xc9,0x7a,0xe5,0x4e,0xab,0x6a,0x51}}

// MTFTP Packet OpCodes
#define EFI_MTFTP6_OPCODE_RRQ    1
#define EFI_MTFTP6_OPCODE_WRQ    2
#define EFI_MTFTP6_OPCODE_DATA   3
#define EFI_MTFTP6_OPCODE_ACK    4
#define EFI_MTFTP6_OPCODE_ERROR  5
#define EFI_MTFTP6_OPCODE_OACK   6
#define EFI_MTFTP6_OPCODE_DIR    7
//This field should be ignored and treated as reserved.
#define EFI_MTFTP6_OPCODE_DATA8  8
//This field should be ignored and treated as reserved.
#define EFI_MTFTP6_OPCODE_ACK8   9

// MTFTP ERROR Packet ErrorCodes
#define EFI_MTFTP6_ERRORCODE_NOT_DEFINED         0
#define EFI_MTFTP6_ERRORCODE_FILE_NOT_FOUND      1
#define EFI_MTFTP6_ERRORCODE_ACCESS_VIOLATION    2
#define EFI_MTFTP6_ERRORCODE_DISK_FULL           3
#define EFI_MTFTP6_ERRORCODE_ILLEGAL_OPERATION   4
#define EFI_MTFTP6_ERRORCODE_UNKNOWN_TRANSFER_ID 5
#define EFI_MTFTP6_ERRORCODE_FILE_ALREADY_EXISTS 6
#define EFI_MTFTP6_ERRORCODE_NO_SUCH_USER        7
#define EFI_MTFTP6_ERRORCODE_REQUEST_DENIED      8

// EFI_MTFTP6_CONFIG_DATA
typedef struct {
	EFI_IPv6_ADDRESS     StationIp;
	UINT16               LocalPort;
	EFI_IPv6_ADDRESS     ServerIp;
	UINT16               InitialServerPort;
	UINT16               TryCount;
	UINT16               TimeoutValue;
}  EFI_MTFTP6_CONFIG_DATA;

// EFI_MTFTP6_MODE_DATA
typedef struct {
	EFI_MTFTP6_CONFIG_DATA     ConfigData;
	UINT8                      SupportedOptionCount;
	UINT8                      **SupportedOptions;
}  EFI_MTFTP6_MODE_DATA;

// EFI_MTFTP6_OVERRIDE_DATA
typedef struct {
	EFI_IPv6_ADDRESS       ServerIp;
	UINT16                 ServerPort;
	UINT16                 TryCount;
	UINT16                 TimeoutValue;
}  EFI_MTFTP6_OVERRIDE_DATA;

// EFI_MTFTP6_OPTION
typedef struct {
	UINT8           *OptionStr;
	UINT8           *ValueStr;
}   EFI_MTFTP6_OPTION;

#pragma pack(push,1)
// EFI_MTFTP6_REQ_HEADER
typedef struct {
	UINT16         OpCode;
	UINT8          Filename[1];
}  EFI_MTFTP6_REQ_HEADER;

// EFI_MTFTP6_OACK_HEADER
typedef struct {
	UINT16         OpCode;
	UINT8          Data[1];
}  EFI_MTFTP6_OACK_HEADER;

// EFI_MTFTP6_DATA_HEADER
typedef struct {
	UINT16         OpCode;
	UINT16         Block;
	UINT8          Data[1];
}  EFI_MTFTP6_DATA_HEADER;

// EFI_MTFTP6_ACK_HEADER
typedef struct {
	UINT16         OpCode;
	UINT16         Block[1];
}  EFI_MTFTP6_ACK_HEADER;

//*********************************************
// EFI_MTFTP6_DATA8_HEADER
// This field should be ignored and treated as reserved.
//*********************************************
typedef struct {
	UINT16         OpCode;
	UINT64         Block;
	UINT8          Data[1];
}  EFI_MTFTP6_DATA8_HEADER;

// EFI_MTFTP6_ACK8_HEADER
typedef struct {
	UINT16         OpCode;
	UINT64         Block[1];
}  EFI_MTFTP6_ACK8_HEADER;

// EFI_MTFTP6_ERROR_HEADER
typedef struct {
	UINT16         OpCode;
	UINT16         ErrorCode;
	UINT8          ErrorMessage[1];
}  EFI_MTFTP6_ERROR_HEADER;

// EFI_MTFTP6_PACKET
typedef union _EFI_MTFTP6_PACKET {
	UINT16                   OpCode;
	EFI_MTFTP6_REQ_HEADER    Rrq;
	EFI_MTFTP6_REQ_HEADER    Wrq;
	EFI_MTFTP6_OACK_HEADER   Oack;
	EFI_MTFTP6_DATA_HEADER   Data;
	EFI_MTFTP6_ACK_HEADER    Ack;
	// This field should be ignored and treated as reserved.
	EFI_MTFTP6_DATA8_HEADER  Data8;
	// This field should be ignored and treated as reserved.
	EFI_MTFTP6_ACK8_HEADER   Ack8;
	EFI_MTFTP6_ERROR_HEADER    Error;
}  EFI_MTFTP6_PACKET;
#pragma pack(pop)

typedef struct _EFI_MTFTP6_PROTOCOL EFI_MTFTP6_PROTOCOL;

// EFI_MTFTP6_TOKEN
typedef struct _EFI_MTFTP6_TOKEN EFI_MTFTP6_TOKEN;

// EFI_MTFTP6_CHECK_PACKET
typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_CHECK_PACKET)(
  IN EFI_MTFTP6_PROTOCOL       *This,
  IN EFI_MTFTP6_TOKEN          *Token,
  IN UINT16                    PacketLen,
  IN EFI_MTFTP6_PACKET         *Packet
  );

// EFI_MTFTP6_TIMEOUT_CALLBACK
typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_TIMEOUT_CALLBACK)(
  IN EFI_MTFTP6_PROTOCOL           *This,
  IN EFI_MTFTP6_TOKEN              *Token
  );

// EFI_MTFTP6_PACKET_NEEDED
typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_PACKET_NEEDED)(
	IN EFI_MTFTP6_PROTOCOL       *This,
	IN EFI_MTFTP6_TOKEN          *Token,
	IN OUT UINT16                *Length,
	OUT VOID                     **Buffer
	);

struct _EFI_MTFTP6_TOKEN {
	EFI_STATUS                  Status;
	EFI_EVENT                   Event;
	EFI_MTFTP6_OVERRIDE_DATA    OverrideData;
	UINT8                       *Filename;
	UINT8                       *ModeStr;
	UINT32                      OptionCount;
	EFI_MTFTP6_OPTION           OptionList;
	UINT64                      BufferSize;
	VOID                        *Buffer;
	VOID                        *Context;
	EFI_MTFTP6_CHECK_PACKET     CheckPacket;
	EFI_MTFTP6_TIMEOUT_CALLBACK TimeoutCallback;
	EFI_MTFTP6_PACKET_NEEDED    PacketNeeded;
};

typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_GET_MODE_DATA)(
	IN EFI_MTFTP6_PROTOCOL          *This,
	OUT EFI_MTFTP6_MODE_DATA      *ModeData
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_CONFIGURE)(
	IN EFI_MTFTP6_PROTOCOL       *This,
	IN EFI_MTFTP6_CONFIG_DATA    *MtftpConfigData OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_GET_INFO)(
	IN EFI_MTFTP6_PROTOCOL       *This,
	IN EFI_MTFTP6_OVERRIDE_DATA  *OverrideData OPTIONAL,
	IN UINT8                     *Filename,
	IN UINT8                     *ModeStr OPTIONAL,
	IN UINT8                     OptionCount,
	IN EFI_MTFTP6_OPTION         *OptionList OPTIONAL,
	OUT UINT32                   *PacketLength,
	OUT EFI_MTFTP6_PACKET        **Packet OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_PARSE_OPTIONS)(
	IN EFI_MTFTP6_PROTOCOL           *This,
	IN UINT32                        PacketLen,
	IN EFI_MTFTP6_PACKET             *Packet,
	OUT UINT32                       *OptionCount,
	OUT EFI_MTFTP6_OPTION            **OptionList OPTIONAL
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_READ_FILE)(
	IN EFI_MTFTP6_PROTOCOL       *This,
	IN EFI_MTFTP6_TOKEN          *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_WRITE_FILE)(
	IN EFI_MTFTP6_PROTOCOL       *This,
	IN EFI_MTFTP6_TOKEN          *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_READ_DIRECTORY)(
	IN EFI_MTFTP6_PROTOCOL           *This,
	IN EFI_MTFTP6_TOKEN              *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_MTFTP6_POLL) (IN EFI_MTFTP6_PROTOCOL *This);

struct _EFI_MTFTP6_PROTOCOL {
	EFI_MTFTP6_GET_MODE_DATA   GetModeData;
	EFI_MTFTP6_CONFIGURE       Configure;
	EFI_MTFTP6_GET_INFO        GetInfo;
	EFI_MTFTP6_PARSE_OPTIONS   ParseOptions;
	EFI_MTFTP6_READ_FILE       ReadFile;
	EFI_MTFTP6_WRITE_FILE      WriteFile;
	EFI_MTFTP6_READ_DIRECTORY  ReadDirectory;
	EFI_MTFTP6_POLL            Poll;
};
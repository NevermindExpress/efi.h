#pragma once

// INTN
#ifdef _M_IX86
	typedef long INTN;
	typedef unsigned long UINTN;
#elif defined(_M_AMD64)
	typedef long long INTN;
	typedef unsigned long long UINTN;
#endif

// Integers
typedef unsigned char BOOLEAN;
typedef char INT8;
typedef unsigned char UINT8;
typedef short INT16;
typedef unsigned short UINT16;
typedef long INT32;
typedef unsigned long UINT32;
typedef __int64 INT64;
typedef unsigned __int64 UINT64;
// typedef __int128 UINT128;
// typedef __int128 UINT128;
typedef char CHAR8;
typedef short CHAR16;
typedef void VOID;

// Types
typedef struct {
	UINT32  Data1;
	UINT16  Data2;
	UINT16  Data3;
	UINT8   Data4[8];
} EFI_GUID;

//EFI_TIME
// This represents the current time information
typedef struct {
	UINT16      Year;       // 1998 - 20XX
	UINT8       Month;      // 1 - 12
	UINT8       Day;        // 1 - 31
	UINT8       Hour;       // 0 - 23
	UINT8       Minute;     // 0 - 59
	UINT8       Second;     // 0 - 59
	UINT8       Pad1;
	UINT32      Nanosecond; // 0 - 999,999,999
	INT16       TimeZone;   // -1440 to 1440 or 2047
	UINT8       Daylight;
	UINT8       Pad2;
} EFI_TIME;

typedef struct {
	UINT8                   Addr[4];
} EFI_IPv4_ADDRESS;

typedef struct {
	UINT8                   Addr[16];
} EFI_IPv6_ADDRESS;

typedef struct {
	UINT8                   Addr[32];
} EFI_MAC_ADDRESS;
typedef EFI_IPv6_ADDRESS EFI_IP_ADDRESS;

typedef UINTN EFI_STATUS;
typedef VOID* EFI_HANDLE;
typedef VOID* EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

typedef struct {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;

// Semantical modifiers
#ifdef __Shirley__
	// ...
#elif defined(_MSC_VER)
	#include <sal.h>
	#define IN _In_
	#define OUT _Out_
	#define OPTIONAL
#else
	#define IN
	#define OUT
	#define OPTIONAL
#endif 

#define CONST const

// Calling conventions
#ifdef _M_IX86
	#define EFIAPI __cdecl
#elif defined(_M_AMD64)
	#if defined(_MSC_VER) || defined(__Shirley__)
		#define EFIAPI // Already always Microsoft x64 ABI
	#else
		#define EFIAPI __attribute__((__ms_abi__))
	#endif
#endif
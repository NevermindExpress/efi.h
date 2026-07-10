#pragma once
#include "types.h"

// Event Types
// These types can be "ORed" together as needed - for example,
// EVT_TIMER might be "Ored" with EVT_NOTIFY_WAIT or EVT_NOTIFY_SIGNAL.
#define EVT_TIMER                            0x80000000
#define EVT_RUNTIME                          0x40000000

#define EVT_NOTIFY_WAIT                      0x00000100
#define EVT_NOTIFY_SIGNAL                    0x00000200

#define EVT_SIGNAL_EXIT_BOOT_SERVICES        0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE    0x60000202

//EFI_TIMER_DELAY
typedef enum {
	TimerCancel,
	TimerPeriodic,
	TimerRelative
} EFI_TIMER_DELAY;

#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES \
 {0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf}}

#define EFI_EVENT_GROUP_BEFORE_EXIT_BOOT_SERVICES \
  { 0x8be0e274, 0x3970, 0x4b44, { 0x80, 0xc5, 0x1a, 0xb9, 0x50, 0x2f, 0x3b, 0xfc } }

#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE \
  {0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96}

#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE \
 {0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, 0xf0, 0xd7, 0xab}

#define EFI_EVENT_GROUP_READY_TO_BOOT \
 {0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5,0xd, 0x2b}

#define EFI_EVENT_GROUP_AFTER_READY_TO_BOOT \
{ 0x3a2a00ad, 0x98b9, 0x4cdf, { 0xa4, 0x78, 0x70, 0x27, 0x77, 0xf1, 0xc1, 0xb } }

#define EFI_EVENT_GROUP_RESET_SYSTEM \
{ 0x62da6a56, 0x13fb, 0x485a, { 0xa8, 0xda, 0xa3, 0xdd, 0x79, 0x12, 0xcb, 0x6b} }

typedef VOID *EFI_EVENT;

typedef VOID(EFIAPI *EFI_EVENT_NOTIFY) (
	IN EFI_EVENT          Event,
	IN VOID              *Context
	);

typedef EFI_STATUS(EFIAPI *EFI_CREATE_EVENT) (
	IN UINT32                   Type,
	IN EFI_TPL                  NotifyTpl,
	IN EFI_EVENT_NOTIFY         NotifyFunction, OPTIONAL
	IN VOID                     *NotifyContext, OPTIONAL
	OUT EFI_EVENT               *Event
	);

typedef EFI_STATUS(EFIAPI *EFI_CREATE_EVENT_EX) (
	IN UINT32                  Type,
	IN EFI_TPL                 NotifyTpl,
	IN EFI_EVENT_NOTIFY        NotifyFunction OPTIONAL,
	IN CONST VOID              *NotifyContext OPTIONAL,
	IN CONST EFI_GUID          *EventGroup OPTIONAL,
	OUT EFI_EVENT              *Event
	);

typedef EFI_STATUS(EFIAPI *EFI_CLOSE_EVENT) (IN EFI_EVENT Event);
typedef EFI_STATUS(EFIAPI *EFI_SIGNAL_EVENT) (IN EFI_EVENT Event);
typedef EFI_STATUS(EFIAPI *EFI_CHECK_EVENT) (IN EFI_EVENT Event);

typedef EFI_STATUS(EFIAPI *EFI_WAIT_FOR_EVENT) (
	IN UINTN             NumberOfEvents,
	IN EFI_EVENT         *Event,
	OUT UINTN            *Index
	);

typedef EFI_STATUS(EFIAPI *EFI_SET_TIMER) (
	IN EFI_EVENT               Event,
	IN EFI_TIMER_DELAY         Type,
	IN UINT64                  TriggerTime
	);
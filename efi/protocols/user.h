#pragma once
#include "efi/types.h"
#include "efi/protocols/hii.h"
#include "efi/protocols/devicepath.h"

// UEFI Spec Section 36.3.1
#define EFI_USER_MANAGER_PROTOCOL_GUID { 0x6fd5b00c, 0xd426, 0x4283, { 0x98, 0x87, 0x6c, 0xf5, 0xcf, 0x1c, 0xb1, 0xfe }};

#define EFI_EVENT_GROUP_USER_PROFILE_CHANGED { 0xbaf1e6de, 0x209e, 0x4adb, { 0x8d, 0x96, 0xfd, 0x8b, 0x71, 0xf3, 0xf6, 0x83 }}

typedef UINT16 EFI_USER_INFO_ATTRIBS;
#define EFI_USER_INFO_STORAGE                0x000F
#define EFI_USER_INFO_STORAGE_VOLATILE       0x0000
#define EFI_USER_INFO_STORAGE_CREDENTIAL_NV  0x0001
#define EFI_USER_INFO_STORAGE_PLATFORM_NV    0x0002

#define EFI_USER_INFO_ACCESS                 0x0070
#define EFI_USER_INFO_PUBLIC                 0x0010
#define EFI_USER_INFO_PRIVATE                0x0020
#define EFI_USER_INFO_PROTECTED              0x0030
#define EFI_USER_INFO_EXCLUSIVE              0x0080

typedef VOID *EFI_USER_PROFILE_HANDLE;
typedef VOID *EFI_USER_INFO_HANDLE;

typedef struct {
	EFI_GUID                 Credential;
	UINT8                    InfoType;
	UINT8                    Reserved1;
	EFI_USER_INFO_ATTRIBS    InfoAttribs;
	UINT32                   InfoSize;
}   EFI_USER_INFO;

typedef struct _EFI_USER_MANAGER_PROTOCOL EFI_USER_MANAGER_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_CREATE) (
	IN CONST EFI_USER_MANAGER_PROTOCOL        *This,
	OUT EFI_USER_PROFILE_HANDLE               *User
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_DELETE) (
	IN CONST EFI_USER_MANAGER_PROTOCOL     *This,
	IN EFI_USER_PROFILE_HANDLE             User
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_GET_NEXT)(
	IN CONST EFI_USER_MANAGER_PROTOCOL      *This,
	IN OUT EFI_USER_PROFILE_HANDLE          *User
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_CURRENT)(
	IN CONST EFI_USER_MANAGER_PROTOCOL      *This,
	OUT EFI_USER_PROFILE_HANDLE             *CurrentUser
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_IDENTIFY) (
	IN CONST EFI_USER_MANAGER_PROTOCOL      *This,
	OUT EFI_USER_PROFILE_HANDLE             *User
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_FIND)(
	IN   CONST EFI_USER_MANAGER_PROTOCOL    *This,
	IN OUT EFI_USER_PROFILE_HANDLE          *User,
	IN OUT EFI_USER_INFO_HANDLE             *UserInfo OPTIONAL,
	IN   CONST EFI_USER_INFO                *Info,
	IN   UINTN                              InfoSize
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_NOTIFY)(
	IN  CONST EFI_USER_MANAGER_PROTOCOL      *This,
	IN  EFI_HANDLE                           Changed
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_GET_INFO)(
	IN   CONST EFI_USER_MANAGER_PROTOCOL       *This,
	IN   EFI_USER_PROFILE_HANDLE               User,
	IN   EFI_USER_INFO_HANDLE                  UserInfo,
	OUT   EFI_USER_INFO                        *Info,
	IN OUT UINTN                               *InfoSize
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_SET_INFO) (
	IN   CONST EFI_USER_MANAGER_PROTOCOL       *This,
	IN   EFI_USER_PROFILE_HANDLE               User,
	IN OUT EFI_USER_INFO_HANDLE                *UserInfo,
	IN   CONST EFI_USER_INFO                   *Info,
	IN   UINTN                                 InfoSize
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_DELETE_INFO) (
	IN   CONST EFI_USER_MANAGER_PROTOCOL      *This,
	IN   EFI_USER_PROFILE_HANDLE              User,
	IN   EFI_USER_INFO_HANDLE                 UserInfo
	);

typedef EFI_STATUS(EFIAPI *EFI_USER_PROFILE_GET_NEXT_INFO)(
	IN   CONST EFI_USER_MANAGER_PROTOCOL         *This,
	IN   EFI_USER_PROFILE_HANDLE                 User,
	IN OUT EFI_USER_INFO_HANDLE                  *UserInfo
	);

struct EFI_USER_MANAGER_PROTOCOL {
	EFI_USER_PROFILE_CREATE           Create;
	EFI_USER_PROFILE_DELETE           Delete;
	EFI_USER_PROFILE_GET_NEXT         GetNext;
	EFI_USER_PROFILE_CURRENT          Current;
	EFI_USER_PROFILE_IDENTIFY         Identify;
	EFI_USER_PROFILE_FIND             Find;
	EFI_USER_PROFILE_NOTIFY           Notify;
	EFI_USER_PROFILE_GET_INFO         GetInfo;
	EFI_USER_PROFILE_SET_INFO         SetInfo;
	EFI_USER_PROFILE_DELETE_INFO      DeleteInfo;
	EFI_USER_PROFILE_GET_NEXT_INFO    GetNextInfo;
};

// UEFI Spec Section 36.3.2
#define EFI_USER_CREDENTIAL2_PROTOCOL_GUID		{ 0xe98adb03, 0xb8b9, 0x4af8, { 0xba, 0x20, 0x26, 0xe9, 0x11, 0x4c, 0xbc, 0xe5 }}
#define EFI_USER_CREDENTIAL_CLASS_UNKNOWN		{ 0x5cf32e68, 0x7660, 0x449b, { 0x80, 0xe6, 0x7e, 0xa3, 0x6e, 0x03, 0xf6, 0xa8 }};
#define EFI_USER_CREDENTIAL_CLASS_PASSWORD		{ 0xf8e5058c, 0xccb6, 0x4714, { 0xb2, 0x20, 0x3f, 0x7e, 0x3a, 0x64, 0x0b, 0xd1 }};
#define EFI_USER_CREDENTIAL_CLASS_SMART_CARD	{ 0x5f03ba33, 0x8c6b, 0x4c24, { 0xaa, 0x2e, 0x14, 0xa2, 0x65, 0x7b, 0xd4, 0x54 }};
#define EFI_USER_CREDENTIAL_CLASS_FINGERPRINT	{ 0x32cba21f, 0xf308, 0x4cbc, { 0x9a, 0xb5, 0xf5, 0xa3, 0x69, 0x9f, 0x04, 0x4a }};
#define EFI_USER_CREDENTIAL_CLASS_HANDPRINT		{ 0x5917ef16, 0xf723, 0x4bb9, { 0xa6, 0x4b, 0xd8, 0xc5, 0x32, 0xf4, 0xd8, 0xb5 }};
#define EFI_USER_CREDENTIAL_CLASS_SECURE_CARD	{ 0x8a6b4a83, 0x42fe, 0x45d2, { 0xa2, 0xef, 0x46, 0xf0, 0x6c, 0x7d, 0x98, 0x52 }};

typedef UINT32 EFI_CREDENTIAL_LOGON_FLAGS;
#define EFI_CREDENTIAL_LOGON_FLAG_AUTO       0x00000001
#define EFI_CREDENTIAL_LOGON_FLAG_DEFAULT    0x00000002

typedef UINT64 EFI_CREDENTIAL_CAPABILITIES;
#define EFI_CREDENTIAL_CAPABILITIES_ENROLL 0x0000000000000001

#define EFI_USER_INFO_IDENTIFIER_RECORD 0x05
typedef UINT8 EFI_USER_INFO_IDENTIFIER[16];

typedef struct _EFI_USER_CREDENTIAL2_PROTOCOL EFI_USER_CREDENTIAL2_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_ENROLL)(
	IN CONST EFI_USER_CREDENTIAL2_PROTOCOL     *This,
	IN EFI_USER_PROFILE_HANDLE                 User
	);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_FORM)(
	IN CONST EFI_USER_CREDENTIAL2_PROTOCOL     *This,
	OUT EFI_HII_HANDLE                         *Hii,
	OUT EFI_GUID                               *FormSetId,
	OUT EFI_FORM_ID                            *FormId
	);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_TILE)(
	IN    CONST EFI_USER_CREDENTIAL2_PROTOCOL        *This,
	IN OUT UINTN                                     *Width,
	IN OUT UINTN                                     *Height,
	OUT   EFI_HII_HANDLE                             *Hii,
	OUT   EFI_IMAGE_ID                               *Image
	);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_TITLE)(
	IN    CONST EFI_USER_CREDENTIAL2_PROTOCOL     *This,
	OUT   EFI_HII_HANDLE                          *Hii,
	OUT   EFI_STRING_ID                           *String
	);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_USER)(
	IN   CONST EFI_USER_CREDENTIAL2_PROTOCOL      *This,
	IN   EFI_USER_PROFILE_HANDLE                  User,
	OUT  EFI_USER_INFO_IDENTIFIER                 *Identifier
	);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_SELECT)(
	IN CONST EFI_USER_CREDENTIAL2_PROTOCOL     *This,
	OUT EFI_CREDENTIAL_LOGON_FLAGS             *AutoLogon
	);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_DESELECT)(IN CONST EFI_USER_CREDENTIAL2_PROTOCOL *This);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_DEFAULT)(
	IN CONST EFI_USER_CREDENTIAL2_PROTOCOL     *This,
	OUT EFI_CREDENTIAL_LOGON_FLAGS             *AutoLogon
	);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_GET_INFO)(
	IN   CONST EFI_USER_CREDENTIAL2_PROTOCOL      *This,
	IN   EFI_USER_INFO_HANDLE                     UserInfo,
	OUT   EFI_USER_INFO                           *Info,
	IN OUT UINTN                                  *InfoSize
	);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_GET_NEXT_INFO)(
	IN   CONST EFI_USER_CREDENTIAL2_PROTOCOL      *This,
	IN OUT EFI_USER_INFO_HANDLE                   *UserInfo
	);

typedef EFI_STATUS(EFIAPI *EFI_CREDENTIAL_DELETE)(
	IN  CONST EFI_USER_CREDENTIAL2_PROTOCOL    *This,
	IN  EFI_USER_PROFILE_HANDLE                User
	);

struct _EFI_USER_CREDENTIAL2_PROTOCOL {
	EFI_GUID                       Identifier;
	EFI_GUID                       Type;
	EFI_CREDENTIAL_ENROLL          Enroll;
	EFI_CREDENTIAL_FORM            Form;
	EFI_CREDENTIAL_TILE            Tile;
	EFI_CREDENTIAL_TITLE           Title;
	EFI_CREDENTIAL_USER            User;
	EFI_CREDENTIAL_SELECT          Select;
	EFI_CREDENTIAL_DESELECT        Deselect;
	EFI_CREDENTIAL_DEFAULT         Default;
	EFI_CREDENTIAL_GET_INFO        GetInfo;
	EFI_CREDENTIAL_GET_NEXT_INFO   GetNextInfo;
	EFI_CREDENTIAL_CAPABILITIES    Capabilities;
	EFI_CREDENTIAL_DELETE          Delete;
};

// UEFI Spec Section 36.3.3

#define EFI_DEFERRED_IMAGE_LOAD_PROTOCOL_GUID { 0x15853d7c, 0x3ddf, 0x43e0, { 0xa1, 0xcb, 0xeb, 0xf8, 0x5b, 0x8f, 0x87, 0x2c }};

typedef struct _EFI_DEFERRED_IMAGE_LOAD_PROTOCOL EFI_DEFERRED_IMAGE_LOAD_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_DEFERRED_IMAGE_INFO)(
	IN EFI_DEFERRED_IMAGE_LOAD_PROTOCOL     *This,
	IN UINTN                                ImageIndex,
	OUT  EFI_DEVICE_PATH_PROTOCOL           **ImageDevicePath,
	OUT  VOID                               **Image,
	OUT  UINTN                              *ImageSize,
	OUT  BOOLEAN                            *BootOption
	);

struct _EFI_DEFERRED_IMAGE_LOAD_PROTOCOL {
	EFI_DEFERRED_IMAGE_INFO GetImageInfo;
};
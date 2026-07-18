#pragma once
#include "efi/types.h"

// UEFI Spec Section 27.3
#define EFI_WIRELESS_MAC_CONNECTION_PROTOCOL_GUID { 0xda55bc9, 0x45f8, 0x4bb4, { 0x87, 0x19, 0x52, 0x24, 0xf1, 0x8a, 0x4d, 0x45 }}

// EFI_80211_BSS_TYPE
typedef enum {
	IeeeInfrastructureBSS,
	IeeeIndependentBSS,
	IeeeMeshBSS,
	IeeeAnyBss
}  EFI_80211_BSS_TYPE;

// EFI_80211_ACC_NET_TYPE
typedef enum {
	IeeePrivate = 0,
	IeeePrivatewithGuest = 1,
	IeeeChargeablePublic = 2,
	IeeeFreePublic = 3,
	IeeePersonal = 4,
	IeeeEmergencyServOnly = 5,
	IeeeTestOrExp = 14,
	IeeeWildcard = 15
} EFI_80211_ACC_NET_TYPE;

// EFI_80211_SCAN_RESULT_CODE
typedef enum {
	ScanSuccess,
	ScanNotSupported
}  EFI_80211_SCAN_RESULT_CODE;

// EFI_80211_ASSOCIATE_RESULT_CODE
typedef enum {
	AssociateSuccess,
	AssociateRefusedReasonUnspecified,
	AssociateRefusedCapsMismatch,
	AssociateRefusedExtReason,
	AssociateRefusedAPOutOfMemory,
	AssociateRefusedBasicRatesMismatch,
	AssociateRejectedEmergencyServicesNotSupported,
	AssociateRefusedTemporarily
}   EFI_80211_ASSOCIATE_RESULT_CODE;

// EFI_80211_REASON_CODE
typedef enum {
	Ieee80211UnspecifiedReason = 1,
	Ieee80211PreviousAuthenticateInvalid = 2,
	Ieee80211DeauthenticatedSinceLeaving = 3,
	Ieee80211DisassociatedDueToInactive = 4,
	Ieee80211DisassociatedSinceApUnable = 5,
	Ieee80211Class2FrameNonauthenticated = 6,
	Ieee80211Class3FrameNonassociated = 7,
	Ieee80211DisassociatedSinceLeaving = 8,
	// ...
}   EFI_80211_REASON_CODE;

// EFI_80211_DISASSOCIATE_RESULT_CODE
typedef enum {
	DisassociateSuccess,
	DisassociateInvalidParameters
}   EFI_80211_DISASSOCIATE_RESULT_CODE;

// EFI_80211_AUTHENTICATION_TYPE
typedef enum {
	OpenSystem,
	SharedKey,
	FastBSSTransition,
	SAE
}   EFI_80211_AUTHENTICATION_TYPE;

// EFI_80211_AUTHENTICATION_RESULT_CODE
//**********************************************
typedef enum {
	AuthenticateSuccess,
	AuthenticateRefused,
	AuthenticateAnticLoggingTokenRequired,
	AuthenticateFiniteCyclicGroupNotSupported,
	AuthenticationRejected,
	AuthenticateInvalidParameter
}   EFI_80211_AUTHENTICATE_RESULT_CODE;

// EFI_80211_MAC_ADDRESS
typedef struct {
	UINT8 Addr[6];
}   EFI_80211_MAC_ADDRESS;

// EFI_80211_ELEMENT_HEADER
typedef struct {
	UINT8             ElementID;
	UINT8             Length;
}   EFI_80211_ELEMENT_HEADER;

// EFI_80211_ELEMENT_REQ
typedef struct {
	EFI_80211_ELEMENT_HEADER           Hdr;
	UINT8                              RequestIDs[1];
} EFI_80211_ELEMENT_REQ;

// EFI_80211_ELEMENT_SSID
typedef struct {
	EFI_80211_ELEMENT_HEADER   Hdr;
	UINT8                      SSId[32];
}   EFI_80211_ELEMENT_SSID;

// EFI_80211_SCAN_DATA
typedef struct {
	EFI_80211_BSS_TYPE            BSSType;
	EFI_80211_MAC_ADDRESS         BSSId;
	UINT8                         SSIdLen;
	UINT8                         *SSId;
	BOOLEAN                       PassiveMode;
	UINT32                        ProbeDelay;
	UINT32                        *ChannelList;
	UINT32                        MinChannelTime;
	UINT32                        MaxChannelTime;
	EFI_80211_ELEMENT_REQ         *RequestInformation;
	EFI_80211_ELEMENT_SSID        *SSIDList;
	EFI_80211_ACC_NET_TYPE        AccessNetworkType;
	UINT8                         *VendorSpecificInfo;
}   EFI_80211_SCAN_DATA;

// EFI_80211_COUNTRY_TRIPLET_SUBBAND
typedef struct {
	UINT8                     FirstChannelNum;
	UINT8                     NumOfChannels;
	UINT8                     MaxTxPowerLevel;
}   EFI_80211_COUNTRY_TRIPLET_SUBBAND;

// EFI_80211_COUNTRY_TRIPLET_OPERATE
typedef struct {
	UINT8                    OperatingExtId;
	UINT8                    OperatingClass;
	UINT8                    CoverageClass;
}   EFI_80211_COUNTRY_TRIPLET_OPERATE;

// EFI_80211_COUNTRY_TRIPLET
typedef union {
	EFI_80211_COUNTRY_TRIPLET_SUBBAND    Subband;
	EFI_80211_COUNTRY_TRIPLET_OPERATE    Operating;
}   EFI_80211_COUNTRY_TRIPLET;

// EFI_80211_ELEMENT_COUNTRY
typedef struct {
	EFI_80211_ELEMENT_HEADER       Hdr;
	UINT8                          CountryStr[3];
	EFI_80211_COUNTRY_TRIPLET      CountryTriplet[1];
}   EFI_80211_ELEMENT_COUNTRY;

// EFI_80211_ELEMENT_DATA_RSN
typedef struct {
	UINT16          Version;
	UINT32          GroupDataCipherSuite;
	//UINT16          PairwiseCipherSuiteCount;
	//UINT32          PairwiseCipherSuiteList [PairwiseCipherSuiteCount];
	//UINT16          AKMSuiteCount;
	//UINT32          AKMSuiteList [AKMSuiteCount];
	//UINT16          RSNCapabilities;
	//UINT16          PMKIDCount;
	//UINT8           PMKIDList [PMKIDCount][16];
	//UINT32          GroupManagementCipherSuite;
} EFI_80211_ELEMENT_DATA_RSN;

// EFI_80211_ELEMENT_EXT_CAP
//**********************************************
typedef struct {
	EFI_80211_ELEMENT_HEADER       Hdr;
	UINT8                          Capabilities[1];
}   EFI_80211_ELEMENT_EXT_CAP;

// EFI_80211_SUBELEMENT_INFO
typedef struct {
	UINT8        SubElementID;
	UINT8        Length;
	UINT8        Data[1];
}   EFI_80211_SUBELEMENT_INFO;

// EFI_80211_MULTIPLE_BSSID
typedef struct {
	EFI_80211_ELEMENT_HEADER     Hdr;
	UINT8                        Indicator;
	EFI_80211_SUBELEMENT_INFO    SubElement[1];
}   EFI_80211_MULTIPLE_BSSID;

// EFI_80211_BSS_DESP_PILOT
typedef struct {
	EFI_80211_MAC_ADDRESS    BSSId;
	EFI_80211_BSS_TYPE       BSSType;
	UINT8                    ConCapInfo;
	UINT8                    ConCountryStr[2];
	UINT8                    OperatingClass;
	UINT8                    Channel;
	UINT8                    Interval;
	EFI_80211_MULTIPLE_BSSID *MultipleBSSID;
	UINT8                    RCPIMeasurement;
	UINT8                    RSNIMeasurement;
}   EFI_80211_BSS_DESP_PILOT;

// EFI_80211_ELEMENT_RSN
typedef struct {
	EFI_80211_ELEMENT_HEADER    Hdr;
	EFI_80211_ELEMENT_DATA_RSN  *Data;
}   EFI_80211_ELEMENT_RSN;

// EFI_80211_BSS_DESCRIPTION
typedef struct {
	EFI_80211_MAC_ADDRESS *BSSId;
	UINT8                         *SSId;
	UINT8                         SSIdLen;
	EFI_80211_BSS_TYPE            BSSType;
	UINT16                        BeaconPeriod;
	UINT64                        Timestamp;
	UINT16                        CapabilityInfo;
	UINT8                         *BSSBasicRateSet;
	UINT8                         *OperationalRateSet;
	EFI_80211_ELEMENT_COUNTRY     *Country;
	EFI_80211_ELEMENT_RSN         RSN;
	UINT8                         RSSI;
	UINT8                         RCPIMeasurement;
	UINT8                         RSNIMeasurement;
	UINT8                         *RequestedElements;
	UINT8                         *BSSMembershipSelectorSet;
	EFI_80211_ELEMENT_EXT_CAP     *ExtCapElement;
}   EFI_80211_BSS_DESCRIPTION;

// EFI_80211_SCAN_RESULT
typedef struct {
	UINTN                       NumOfBSSDesp;
	EFI_80211_BSS_DESCRIPTION   **BSSDespSet;
	UINTN                       NumofBSSDespFromPilot;
	EFI_80211_BSS_DESP_PILOT    **BSSDespFromPilotSet;
	UINT8                       *VendorSpecificInfo;
}   EFI_80211_SCAN_RESULT;

// EFI_80211_SCAN_DATA_TOKEN
typedef struct {
	EFI_EVENT                   Event;
	EFI_STATUS                  Status;
	EFI_80211_SCAN_DATA         *Data;
	EFI_80211_SCAN_RESULT_CODE  ResultCode;
	EFI_80211_SCAN_RESULT       *Result;
}   EFI_80211_SCAN_DATA_TOKEN;

// EFI_80211_ELEMENT_SUPP_CHANNEL_TUPLE
typedef struct {
	UINT8        FirstChannelNumber;
	UINT8        NumberOfChannels;
}   EFI_80211_ELEMENT_SUPP_CHANNEL_TUPLE;

// EFI_80211_ELEMENT_SUPP_CHANNEL
typedef struct {
	EFI_80211_ELEMENT_HEADER               Hdr;
	EFI_80211_ELEMENT_SUPP_CHANNEL_TUPLE   Subband[1];
}   EFI_80211_ELEMENT_SUPP_CHANNEL;

// EFI_80211_ASSOCIATE_DATA
typedef struct {
	EFI_80211_MAC_ADDRESS           BSSId;
	UINT16                          CapabilityInfo;
	UINT32                          FailureTimeout;
	UINT32                          ListenInterval;
	EFI_80211_ELEMENT_SUPP_CHANNEL  *Channels;
	EFI_80211_ELEMENT_RSN           RSN;
	EFI_80211_ELEMENT_EXT_CAP       ExtCapElement;
	UINT8                           *VendorSpecificInfo;
}  EFI_80211_ASSOCIATE_DATA;

// EFI_80211_ELEMENT_TIMEOUT_VAL
typedef struct {
	EFI_80211_ELEMENT_HEADER       Hdr;
	UINT8                          Type;
	UINT32                         Value;
}   EFI_80211_ELEMENT_TIMEOUT_VAL;

// EFI_80211_ASSOCIATE_RESULT
typedef struct {
	EFI_80211_MAC_ADDRESS          BSSId;
	UINT16                         CapabilityInfo;
	UINT16                         AssociationID;
	UINT8                          RCPIValue;
	UINT8                          RSNIValue;
	EFI_80211_ELEMENT_EXT_CAP      *ExtCapElement;
	EFI_80211_ELEMENT_TIMEOUT_VAL  TimeoutInterval;
	UINT8                          *VendorSpecificInfo;
}  EFI_80211_ASSOCIATE_RESULT;

// EFI_80211_DISASSOCIATE_DATA
typedef struct {
	EFI_80211_MAC_ADDRESS          BSSId;
	EFI_80211_REASON_CODE          ReasonCode;
	UINT8                          *VendorSpecificInfo;
}   EFI_80211_DISASSOCIATE_DATA;

// EFI_80211_DISASSOCIATE_DATA_TOKEN
typedef struct {
	EFI_EVENT                           Event;
	EFI_STATUS                          Status;
	EFI_80211_DISASSOCIATE_DATA         *Data;
	EFI_80211_DISASSOCIATE_RESULT_CODE  ResultCode;
}   EFI_80211_DISASSOCIATE_DATA_TOKEN;

// EFI_80211_ASSOCIATE_DATA_TOKEN
typedef struct {
	EFI_EVENT                        Event;
	EFI_STATUS                       Status;
	EFI_80211_ASSOCIATE_DATA         Data;
	EFI_80211_ASSOCIATE_RESULT_CODE  ResultCode;
	EFI_80211_ASSOCIATE_RESULT       Result;
} EFI_80211_ASSOCIATE_DATA_TOKEN;

// EFI_80211_AUTHENTICATION_DATA
typedef struct {
	EFI_80211_MAC_ADDRESS            BSSId;
	EFI_80211_AUTHENTICATION_TYPE    AuthType;
	UINT32                           FailureTimeout;
	UINT8                            *FTContent;
	UINT8                            *SAEContent;
	UINT8                            *VendorSpecificInfo;
}   EFI_80211_AUTHENTICATE_DATA;

// EFI_80211_AUTHENTICATION_RESULT
//**********************************************
typedef struct {
	EFI_80211_MAC_ADDRESS    BSSId;
	UINT8                    *FTContent;
	UINT8                    *SAEContent;
	UINT8                    *VendorSpecificInfo;
}   EFI_80211_AUTHENTICATE_RESULT;

// EFI_80211_AUTHENTICATE_DATA_TOKEN
typedef struct {
	EFI_EVENT                          Event;
	EFI_STATUS                         Status;
	EFI_80211_AUTHENTICATE_DATA        *Data;
	EFI_80211_AUTHENTICATE_RESULT_CODE ResultCode;
	EFI_80211_AUTHENTICATE_RESULT      Result;
}   EFI_80211_AUTHENTICATE_DATA_TOKEN;

// EFI_80211_DEAUTHENTICATE_DATA
typedef struct {
	EFI_80211_MAC_ADDRESS    BSSId;
	EFI_80211_REASON_CODE    ReasonCode;
	UINT8                    *VendorSpecificInfo;
}   EFI_80211_DEAUTHENTICATE_DATA;

// EFI_80211_DEAUTHENTICATE_DATA_TOKEN
typedef struct {
	EFI_EVENT                        Event;
	EFI_STATUS                       Status;
	EFI_80211_DEAUTHENTICATE_DATA    *Data;
}   EFI_80211_DEAUTHENTICATE_DATA_TOKEN;

typedef struct _EFI_WIRELESS_MAC_CONNECTION_PROTOCOL EFI_WIRELESS_MAC_CONNECTION_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_WIRELESS_MAC_CONNECTION_SCAN)(
	IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL       *This,
	IN EFI_80211_SCAN_DATA_TOKEN                  *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_WIRELESS_MAC_CONNECTION_ASSOCIATE)(
	IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL         *This,
	IN EFI_80211_ASSOCIATE_DATA_TOKEN               *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_WIRELESS_MAC_CONNECTION_DISASSOCIATE)(
	IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL        *This,
	IN EFI_80211_DISASSOCIATE_DATA_TOKEN           *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_WIRELESS_MAC_CONNECTION_AUTHENTICATE)(
	IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL      *This,
	IN EFI_80211_AUTHENTICATE_DATA_TOKEN         *Data
	);

typedef EFI_STATUS(EFIAPI *EFI_WIRELESS_MAC_CONNECTION_DEAUTHENTICATE)(
	IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL      *This,
	IN EFI_80211_DEAUTHENTICATE_DATA_TOKEN       *Data
	);

struct _EFI_WIRELESS_MAC_CONNECTION_PROTOCOL {
	EFI_WIRELESS_MAC_CONNECTION_SCAN              Scan;
	EFI_WIRELESS_MAC_CONNECTION_ASSOCIATE         Associate;
	EFI_WIRELESS_MAC_CONNECTION_DISASSOCIATE      Disassociate;
	EFI_WIRELESS_MAC_CONNECTION_AUTHENTICATE      Authenticate;
	EFI_WIRELESS_MAC_CONNECTION_DEAUTHENTICATE    Deauthenticate;
};

// UEFI Spec Section 27.3
#define EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_GUID { 0x1b0fb9bf, 0x699d, 0x4fdd, { 0xa7, 0xc3, 0x25, 0x46, 0x68, 0x1b, 0xf6, 0x3b }}

#define EFI_MAX_SSID_LEN 32

// EFI_80211_SSID
typedef struct {
	UINT8       SSIdLen;
	UINT8       SSId[EFI_MAX_SSID_LEN];
}   EFI_80211_SSID;

// EFI_80211_GET_NETWORKS_DATA
typedef struct {
	UINT32            NumOfSSID;
	EFI_80211_SSID    SSIDList[1];
}   EFI_80211_GET_NETWORKS_DATA;

// EFI_80211_SUITE_SELECTOR
typedef struct {
	UINT8          Oui[3];
	UINT8          SuiteType;
}  EFI_80211_SUITE_SELECTOR;

// EFI_80211_AKM_SUITE_SELECTOR
typedef struct {
	UINT16                    AKMSuiteCount;
	EFI_80211_SUITE_SELECTOR  AKMSuiteList[1];
}   EFI_80211_AKM_SUITE_SELECTOR;

// EFI_80211_CIPHER_SUITE_SELECTOR
typedef struct {
	UINT16                    CipherSuiteCount;
	EFI_80211_SUITE_SELECTOR  CipherSuiteList[1];
}   EFI_80211_CIPHER_SUITE_SELECTOR;

// EFI_80211_NETWORK
typedef struct {
	EFI_80211_BSS_TYPE              BSSType;
	EFI_80211_SSID                  SSId;
	EFI_80211_AKM_SUITE_SELECTOR    *AKMSuite;
	EFI_80211_CIPHER_SUITE_SELECTOR *CipherSuite;
}   EFI_80211_NETWORK;

// EFI_80211_NETWORK_DESCRIPTION
typedef struct {
	EFI_80211_NETWORK       Network;
	UINT8                   NetworkQuality;
}   EFI_80211_NETWORK_DESCRIPTION;

// EFI_80211_GET_NETWORKS_RESULT
typedef struct {
	UINT8                           NumOfNetworkDesc;
	EFI_80211_NETWORK_DESCRIPTION   NetworkDesc[1];
}   EFI_80211_GET_NETWORKS_RESULT;

// EFI_80211_GET_NETWORKS_TOKEN
typedef struct {
	EFI_EVENT                     Event;
	EFI_STATUS                    Status;
	EFI_80211_GET_NETWORKS_DATA   *Data;
	EFI_80211_GET_NETWORKS_RESULT *Result;
}   EFI_80211_GET_NETWORKS_TOKEN;

// EFI_80211_CONNECT_NETWORK_DATA
typedef struct {
	EFI_80211_NETWORK         *Network;
	UINT32                    FailureTimeout;
}   EFI_80211_CONNECT_NETWORK_DATA;

// EFI_80211_CONNECT_NETWORK_RESULT_CODE
typedef enum {
	ConnectSuccess,
	ConnectRefused,
	ConnectFailed,
	ConnectFailureTimeout,
	ConnectFailedReasonUnspecified
}   EFI_80211_CONNECT_NETWORK_RESULT_CODE;

// EFI_80211_CONNECT_NETWORK_TOKEN
typedef struct {
	EFI_EVENT                              Event;
	EFI_STATUS                             Status;
	EFI_80211_CONNECT_NETWORK_DATA         *Data;
	EFI_80211_CONNECT_NETWORK_RESULT_CODE  ResultCode;
}  EFI_80211_CONNECT_NETWORK_TOKEN;

// EFI_80211_DISCONNECT_NETWORK_TOKEN
typedef struct {
	EFI_EVENT          Event;
	EFI_STATUS         Status;
}   EFI_80211_DISCONNECT_NETWORK_TOKEN;

typedef struct _EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL;

typedef EFI_STATUS(EFIAPI *EFI_WIRELESS_MAC_CONNECTION_II_GET_NETWORKS)(
	IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL     *This,
	IN EFI_80211_GET_NETWORKS_TOKEN                *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_WIRELESS_MAC_CONNECTION_II_CONNECT_NETWORK)(
	IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL      *This,
	IN EFI_80211_CONNECT_NETWORK_TOKEN              *Token
	);

typedef EFI_STATUS(EFIAPI *EFI_WIRELESS_MAC_CONNECTION_II_DISCONNECT_NETWORK)(
	IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL    *This,
	IN EFI_80211_DISCONNECT_NETWORK_TOKEN         *Token
	);

struct _EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL {
	EFI_WIRELESS_MAC_CONNECTION_II_GET_NETWORKS        GetNetworks;
	EFI_WIRELESS_MAC_CONNECTION_II_CONNECT_NETWORK     ConnectNetwork;
	EFI_WIRELESS_MAC_CONNECTION_II_DISCONNECT_NETWORK  DisconnectNetwork;
};
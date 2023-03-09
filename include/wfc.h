#pragma once
#if __has_include(<calico.h>)
#include <calico.h>
#elif __has_include(<nds.h>)
#include <nds.h>
#else
#error "Missing NDS platform lib"
#endif

typedef enum WfcStatus {
	WfcStatus_Disconnected = 0,
	WfcStatus_Connecting   = 1,
	WfcStatus_Connected    = 2,
} WfcStatus;

typedef enum WfcWepMode {
	WfcWepMode_Open   = 0,
	WfcWepMode_40bit  = 1,
	WfcWepMode_104bit = 2,
	WfcWepMode_128bit = 3,
} WfcWepMode;

typedef enum WfcConnType {
	WfcConnType_WepNormal = 0x00,
	WfcConnType_WepAoss   = 0x01,
	WfcConnType_WpaNormal = 0x10,
	WfcConnType_WpaWps    = 0x13,
	WfcConnType_Invalid   = 0xff,
} WfcConnType;

typedef enum WfcWpaMode {
	WfcWpaMode_Invalid       = 0,
	WfcWpaMode_WPA_PSK_TKIP  = 4,
	WfcWpaMode_WPA2_PSK_TKIP = 5,
	WfcWpaMode_WPA_PSK_AES   = 6,
	WfcWpaMode_WPA2_PSK_AES  = 7,
} WfcWpaMode;

typedef struct WfcConnSlot {
	char proxy_user[32];
	char proxy_password[32];
	char ssid[32];
	char aoss_ssid[32];
	u8   wep_keys[4][16];
	u32  ipv4_addr;
	u32  ipv4_gateway;
	u32  ipv4_dns[2];
	u8   ipv4_subnet;
	u8   wep_keys_aoss[4][5];
	u8   _pad_0xe5;
	u8   wep_mode     : 2; // WfcWepMode
	u8   wep_is_ascii : 1;
	u8   _pad_0xe6    : 5;
	u8   conn_type;        // WfcConnType
	u16  ssid_len;
	u16  mtu;
	u8   _pad_0xec[3];
	u8   config;
	u8   wfc_user_id[14];
	u16  crc16;
} WfcConnSlot;

typedef struct WfcConnSlotEx {
	WfcConnSlot base;
	u8   wpa_pmk[32];
	char wpa_psk[64];
	u8   _pad_0x160[33];
	u8   wpa_mode;       // WfcWpaMode
	u8   proxy_enable;
	u8   proxy_has_auth;
	char proxy_name[48];
	u8   _pad_0x1b4[52];
	u16  proxy_port;
	u8   _pad_0x1ea[20];
	u16  crc16;
} WfcConnSlotEx;

void wfcInit(void);

void wfcClearConnSlots(void);
void wfcLoadFromNvram(void);
bool wfcLoadSlot(const WfcConnSlot* slot);
bool wfcLoadSlotEx(const WfcConnSlotEx* slot);
unsigned wfcGetNumSlots(void);

void wfcBeginConnect(void);
WfcStatus wfcGetStatus(void);
WfcConnSlot* wfcGetActiveSlot(void);
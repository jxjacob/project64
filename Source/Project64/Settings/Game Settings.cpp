#include "stdafx.h"

int CGameSettings::m_RefCount = 0; 
bool CGameSettings::m_Registered = false; 

bool  CGameSettings::m_bUseTlb;
DWORD CGameSettings::m_CountPerOp = 2;
DWORD CGameSettings::m_ViRefreshRate = 1500;
DWORD CGameSettings::m_AiCountPerBytes = 500;
bool  CGameSettings::m_DelayDP = false;
bool  CGameSettings::m_DelaySI = false;
DWORD CGameSettings::m_RdramSize = 0;
bool  CGameSettings::m_bFixedAudio;  
bool  CGameSettings::m_bSyncToAudio; 
bool  CGameSettings::m_bFastSP;
bool  CGameSettings::m_b32Bit;
bool  CGameSettings::m_RspAudioSignal;

CGameSettings::CGameSettings()
{
	m_RefCount += 1;
	if (g_Settings && !m_Registered)
	{
		m_Registered = true;
		g_Settings->RegisterChangeCB(Game_UseTlb,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_ViRefreshRate,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_AiCountPerBytes,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_CounterFactor,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_RDRamSize,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_DelaySI,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_DelayDP,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_FixedAudio,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_SyncViaAudio,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_32Bit,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_FastSP,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->RegisterChangeCB(Game_RspAudioSignal,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		
		RefreshSettings();
	}
}

CGameSettings::~CGameSettings()
{
	m_RefCount -= 1;
	if (g_Settings && m_Registered && m_RefCount == 0)
	{
		g_Settings->UnregisterChangeCB(Game_UseTlb,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_ViRefreshRate,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_AiCountPerBytes,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_CounterFactor,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_RDRamSize,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_DelaySI,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_DelayDP,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_FixedAudio,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_SyncViaAudio,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_32Bit,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_FastSP,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);
		g_Settings->UnregisterChangeCB(Game_RspAudioSignal,this,(CSettings::SettingChangedFunc)StaticRefreshSettings);

		m_Registered = false;
	}
}

void CGameSettings::RefreshSettings()
{
	m_bUseTlb         = g_Settings->LoadBool(Game_UseTlb);
	m_ViRefreshRate   = g_Settings->LoadDword(Game_ViRefreshRate);
	m_AiCountPerBytes = g_Settings->LoadDword(Game_AiCountPerBytes);
	m_CountPerOp      = g_Settings->LoadDword(Game_CounterFactor);
	m_RdramSize       = g_Settings->LoadDword(Game_RDRamSize);
	m_DelaySI         = g_Settings->LoadBool(Game_DelaySI);
	m_DelayDP         = g_Settings->LoadBool(Game_DelayDP);
	m_bFixedAudio     = g_Settings->LoadBool(Game_FixedAudio);
	m_bSyncToAudio    = m_bFixedAudio ? g_Settings->LoadBool(Game_SyncViaAudio) : false;
	m_b32Bit          = g_Settings->LoadBool(Game_32Bit);
	m_bFastSP         = g_Settings->LoadBool(Game_FastSP);
	m_RspAudioSignal  = g_Settings->LoadBool(Game_RspAudioSignal);
}

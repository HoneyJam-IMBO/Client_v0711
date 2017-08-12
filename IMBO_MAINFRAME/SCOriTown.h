#pragma once

#include "Scene.h"

//object
#include "FreeCamera.h"

class CSCOriTown;
class CSCOriTown :public CScene{

public:
	CSCOriTown(SCENE_ID eID, CDirectXFramework* pFrameWork);
	~CSCOriTown();
public:
	//-----------------------------------scene--------------------------
	virtual bool Begin();
	virtual bool End();

	virtual void Animate(float fTimeElapsed);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void ProcessInput(float fTimeElapsed);
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient);
	
	//network
	void NetworkProc();
	VOID PROC_PT_FTOWN_READY_SC(DWORD dwProtocol, BYTE* Packet, DWORD dwPacketLength);
	//주기적 위치 동기화
	VOID PROC_PT_FREQUENCY_MOVE_SC(DWORD dwProtocol, BYTE *Packet, DWORD dwPacketLength);
	VOID PROC_PT_MOUSE_LEFT_ATTACK_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength);
	VOID PROC_PT_FTOWN_NPC_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength);
	VOID PROC_PT_FTOWN_NPC_READY_COMP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength);
	VOID PROC_PT_FTOWN_BOSS_ACTION_CAMERA_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength);
	VOID PROC_PT_FTOWN_BOSS_ACTION_CAMERA_READY_COMP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength);
	VOID PROC_PT_FTOWN_NPC2_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength);
	VOID PROC_PT_FTOWN_NPC2_READY_COMP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength);
	CGameObject* GetPlayer() { return m_ppPawn ? m_ppPawn[NETWORKMGR->GetSLOT_ID()] : nullptr; }
	//test
	//vector<XMFLOAT3> m_vPickPos;
private:
	CGameObject*	m_pBoss{ nullptr };
	void CreateBoss1();
	void KillBoss1();
	void FirstTownFly();
	void ReadMapData();

	void LoadSkillObjects();
	void CreateUI();

	bool m_bGameStart{ false };
	bool m_bFinalProc{ false };
private:
	//CGameObject* m_pObject{ nullptr };
	CGameObject** m_ppPawn{ nullptr };
	//CPlayer* m_pPlayer{ nullptr };
};
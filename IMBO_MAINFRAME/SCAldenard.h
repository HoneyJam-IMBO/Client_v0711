#pragma once
#include "Scene.h"
#include "FreeCamera.h"


class CSCAldenard :
	public CScene
{
public:
	CSCAldenard(SCENE_ID eID, CDirectXFramework* pFrameWork);
	virtual ~CSCAldenard();

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
	//�ֱ��� ��ġ ����ȭ
	VOID PROC_PT_FREQUENCY_MOVE_SC(DWORD dwProtocol, BYTE *Packet, DWORD dwPacketLength);
	VOID PROC_PT_MOUSE_LEFT_ATTACK_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength);

	CGameObject* GetPlayer() { return m_ppPawn ? m_ppPawn[NETWORKMGR->GetSLOT_ID()] : nullptr; }

private:
	void ReadMapData();
	void LoadSkillObjects();
	void CreateUI();

	bool m_bGameStart{ false };

private:
	CGameObject** m_ppPawn{ nullptr };
};

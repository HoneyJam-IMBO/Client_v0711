#include "stdafx.h"
#include "SCSarasen.h"
#include "ElfSkillArrow.h"
//#include "LesserGiant.h"

#include "Roisa.h"
#include "HpBar.h"
#include "ImageUI.h"

#include "Ranger.h"
#include "Knight.h"
#include "Dementor.h"
#include "Sister.h"
#include "Wizard.h"
#include "Bard.h"




bool CSCSarasen::Begin()
{

	//----------------------------------camera-------------------------------------
	m_pCamera = m_pFrameWork->GetCamera();
	ReadMapData();
	LoadSkillObjects();
	CreateUI();

	int nPawn = NETWORKMGR->GetServerPlayerInfos().size();//pawn�� ��ü ��

	m_ppPawn = new CGameObject*[nPawn];
	for (int i = 0; i < nPawn; ++i) {
		bool bSoul = (NETWORKMGR->GetSLOT_ID() == i);//slot_id�� i�� ������ ��Ʈ�� ���� ��ü
		INT CHARACTER = NETWORKMGR->GetServerPlayerInfo(i).CHARACTER;
		//pawn ����
		CGameObject* pWeapon = nullptr;
		switch (CHARACTER) {
		case 0:
			//�ü�
			//pWeapon = new CGameObject("Bow1", TAG_DYNAMIC_OBJECT);
			//pWeapon->Begin();
			m_ppPawn[i] = new CSister("Lup01M", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]���� [40, 10]���� ��ġ
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 1:
			//���
			pWeapon = new CGameObject("Bow1", TAG_DYNAMIC_OBJECT);
			pWeapon->Begin();
			m_ppPawn[i] = new CRanger("Elf01F", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(814, 0, 258, 0));//[10, 10]���� [40, 10]���� ��ġ
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			//m_ppPawn[i] = new CPawn("Hum01M", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			//m_ppPawn[i]->Begin();
			//m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]���� [40, 10]���� ��ġ
			//m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 2:
			//��������
			//m_ppPawn[i] = new CPawn("Hum03M", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			//m_ppPawn[i]->Begin();
			//m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]���� [40, 10]���� ��ġ
			//m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 3:
			//pWeapon = new CGameObject("Bow1", TAG_DYNAMIC_OBJECT);
			//pWeapon->Begin();
			//m_ppPawn[i] = new CPawn("Elf01F", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			//m_ppPawn[i]->Begin();
			//m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]���� [40, 10]���� ��ġ
			//m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 4:
			//
			//pWeapon = new CGameObject("Bow1", TAG_DYNAMIC_OBJECT);
			//pWeapon->Begin();
			//m_ppPawn[i] = new CPawn("Elf01F", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			//m_ppPawn[i]->Begin();
			//m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]���� [40, 10]���� ��ġ
			//m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 5:
			//����
			//m_ppPawn[i] = new CPawn("Hum02F", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			//m_ppPawn[i]->Begin();
			//m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]���� [40, 10]���� ��ġ
			//m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		}

		if (bSoul) {//player���� camera �����ֱ�
			m_ppPawn[i]->SetTerrainContainer(UPDATER->GetTerrainContainer());
			m_ppPawn[i]->SetUTag(utag::UTAG_PLAYER);
			//m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]���� [40, 10]���� ��ġ
			UPDATER->GetSpaceContainer()->AddObject(m_ppPawn[i]);
			m_ppPawn[i]->GetAnimater()->SetCurAnimationIndex(0);
			CAMMGR->SetTarget(CAM_FREE, m_ppPawn[i]);
			CAMMGR->GetCamera(CAM_FREE)->SetMode(MODE_FIX);
		}
		else {
			//�ٸ� player�� �浹ó���� ���� ������
			m_ppPawn[i]->SetUTag(utag::UTAG_DEFAULT);
			UPDATER->GetSpaceContainer()->AddObject(m_ppPawn[i]);
			m_ppPawn[i]->GetAnimater()->SetCurAnimationIndex(0);
		}

		//navi object
		if (false == CNaviObjectManager::GetNaviVertices().empty())
			m_ppPawn[i]->SetNaviMeshIndex();
	}


	//���� ����
	CGameObject*	pBoss = new CRoisa("Boss02R", TAG_DYNAMIC_OBJECT, m_ppPawn[0]);
	pBoss->SetUTag(utag::UTAG_BOSS1);
	pBoss->Begin();
	pBoss->SetTerrainContainer(UPDATER->GetTerrainContainer());
	pBoss->SetPosition(XMVectorSet(512, 0, 768, 0));
	pBoss->SetNaviMeshIndex();
	pBoss->SetScale(XMVectorSet(3, 3, 3, 1));
	UPDATER->GetSpaceContainer()->AddObject(pBoss);
	pBoss->GetAnimater()->SetCurAnimationIndex(0);

#ifdef NO_SERVER
	return CScene::Begin();
#endif
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	NETWORKMGR->WritePacket(PT_FTOWN_READY_CS, Packet, WRITE_PT_FTOWN_READY_CS(Packet));

	while (false == m_bGameStart) {
		NetworkProc();
		Sleep(100);
	}
	return CScene::Begin();
}

bool CSCSarasen::End()
{
	int nPawn = NETWORKMGR->GetServerPlayerInfos().size();
	for (int i = 0; i < nPawn; ++i)
	{
		if (m_ppPawn[i] == nullptr)
		{
			m_ppPawn[i]->End();
			delete m_ppPawn[i];
			m_ppPawn[i] = nullptr;
		}
	}

	return CScene::End();
}

void CSCSarasen::Animate(float fTimeElapsed)
{
	NetworkProc();
	CScene::Animate(fTimeElapsed);

	size_t iVecSize = m_vecUI.size();
	for (size_t i = 0; i < iVecSize; ++i)
	{
		m_vecUI[i]->Update(fTimeElapsed);
	}
	if (INPUTMGR->KeyBoardDown(VK_T))
	{
		SCENEMGR->ChangeScene(SCN_ORITOWN);
	}
}

void CSCSarasen::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		break;
	default:
		break;
	}
}

void CSCSarasen::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID) {
	case WM_KEYUP:
		switch (wParam) {
		case VK_F1:
		case VK_F2:
		case VK_F3:
			break;
		case VK_P:
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void CSCSarasen::ProcessInput(float fTimeElapsed)
{
	if (INPUTMGR->KeyDown(VK_P)) {
		INPUTMGR->SetDebugMode(static_cast<bool>((INPUTMGR->GetDebugMode() + 1) % 2));
	}
	m_pCamera->ProcessInput(fTimeElapsed);
}

CGameObject * CSCSarasen::PickObjectPointedByCursor(int xClient, int yClient)
{
	if (!m_pCamera) return(NULL);

	//Get screen pos -> Camera pos
	XMFLOAT4X4 xmf4x4Projection;
	XMStoreFloat4x4(&xmf4x4Projection, m_pCamera->GetProjectionMtx());
	D3D11_VIEWPORT d3dViewport = m_pCamera->GetViewport();

	//�� �̰� ȭ���� ���� ���� ī�޶� ��ǥ���� �༮�̰�
	XMFLOAT3 xmf3PickPosition;
	xmf3PickPosition.x = (((2.0f * xClient) / d3dViewport.Width) - 1) / xmf4x4Projection._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / d3dViewport.Height) - 1) / xmf4x4Projection._22;
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition;
	xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);
	XMMATRIX xmMtxViewInverse;
	xmMtxViewInverse = XMMatrixInverse(nullptr, m_pCamera->GetViewMtx());
	//picking pos�� camera inverse�� �������� �̰� picking pos�� world pos!
	xmvPickPosition = XMVector3TransformCoord(xmvPickPosition, xmMtxViewInverse);
	XMVECTOR xmvRayDir = xmvPickPosition - m_pCamera->GetPosition();

	CGameObject* pNearestObject = NULL;
	float fHitDistance = FLT_MAX;
	float fNearDistance = FLT_MAX;
	pNearestObject = UPDATER->PickObject(m_pCamera->GetPosition(), XMVector3Normalize(xmvRayDir), fHitDistance);

	fNearDistance = fHitDistance;

	return(pNearestObject);
}

void CSCSarasen::NetworkProc()
{
#ifdef NO_SERVER
	return;
#endif
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	DWORD dwProtocol = 0;
	DWORD dwPacketLength = 0;

	if (NETWORKMGR->GetClientSession()->ReadPacket(dwProtocol, Packet, dwPacketLength)) {
		switch (dwProtocol) {
		case PT_FTOWN_READY_SC:
			PROC_PT_FTOWN_READY_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_FREQUENCY_MOVE_SC:
			PROC_PT_FREQUENCY_MOVE_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_MOUSE_LEFT_ATTACK_SC:
			PROC_PT_MOUSE_LEFT_ATTACK_SC(dwProtocol, Packet, dwPacketLength);
		}
	}
}

VOID CSCSarasen::PROC_PT_FTOWN_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength)
{
	m_bGameStart = true;
	return VOID();
}

VOID CSCSarasen::PROC_PT_FREQUENCY_MOVE_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength)
{
	READ_PACKET(PT_FREQUENCY_MOVE_SC);

	DEBUGER->AddText(25, 10, 400 + Data.SLOT_ID * 50, YT_Color(), L"recv ID : %d", Data.SLOT_ID);
	DEBUGER->AddText(25, 10, 450 + Data.SLOT_ID * 50, YT_Color(), L"%f %f %f", Data.POSX, Data.POSY, Data.POSZ);
	DEBUGER->AddText(25, 10, 450 + Data.SLOT_ID * 50, YT_Color(), L"%f", Data.ANGLEY);

	PLAYR_FREQUENCY_DATA data;
	data.fPosX = Data.POSX;
	data.fPosY = Data.POSY;
	data.fPosZ = Data.POSZ;

	data.fAngleY = Data.ANGLEY;
	//CPawn* pPawn = (CPawn*)m_ppPawn[Data.SLOT_ID];
	//pPawn->NetworkInput(data.dwDirection, data.fAngleY);
	//network queue�� �Է��ϱ� ����Ѵ�.
	//NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].m_qFREQUENCY_DATA.push(data);
	NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].FREQUENCY_DATA = data;

	return VOID();
}

VOID CSCSarasen::PROC_PT_MOUSE_LEFT_ATTACK_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength)
{
	READ_PACKET(PT_MOUSE_LEFT_ATTACK_SC);

	NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].ATTACK = Data.ATTACK;

	return VOID();
}

void CSCSarasen::ReadMapData()
{
	//IMPORTER->Begin("../../Assets/SceneResource/Aldenard/Aldenard.scn");
	IMPORTER->Begin("../../Assets/SceneResource/Sarasen/Sarasen.scn");
	//output path
	wstring wsOutputPath = IMPORTER->ReadWstring();
	//scene name
	wstring wsSceneName = IMPORTER->ReadWstring();
	m_sName.assign(wsSceneName.cbegin(), wsSceneName.cend());

	UPDATER->LoadSpaceInfo();
	UPDATER->LoadTerrainInfo(wsOutputPath, wsSceneName);
	UPDATER->LoadObjectsInfo();
	//effect info
	RENDERER->LoadEffectInfo(wsOutputPath, wsSceneName);

	IMPORTER->End();
}

void CSCSarasen::LoadSkillObjects()
{

}

void CSCSarasen::CreateUI()
{
	CUIObject* pUI;
	pUI = CHpBar::Create(XMLoadFloat2(&XMFLOAT2(WINSIZEX * 0.24f, WINSIZEY * 0.77f)), XMLoadFloat2(&XMFLOAT2(190.f, 6.f)));
	m_vecUI.push_back(pUI);

	string sName = "Char_Select_0";
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(132.f, WINSIZEY * 0.8f)), XMLoadFloat2(&XMFLOAT2(50.f, 50.f)), sName, 10.f);
	m_vecUI.push_back(pUI);

	sName = "SkillBack";
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(217.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(30.f, 30.f)), sName, 9.f);
	m_vecUI.push_back(pUI);

	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(277.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(30.f, 30.f)), sName, 9.f);
	m_vecUI.push_back(pUI);

	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(337.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(30.f, 30.f)), sName, 9.f);
	m_vecUI.push_back(pUI);

	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(397.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(30.f, 30.f)), sName, 9.f);
	m_vecUI.push_back(pUI);

	sName = "skicon1";
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(217.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(23.f, 23.f)), sName, 9.5f);
	m_vecUI.push_back(pUI);

	sName = "skicon2";
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(277.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(23.f, 23.f)), sName, 9.5f);
	m_vecUI.push_back(pUI);

	sName = "skicon3";
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(337.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(23.f, 23.f)), sName, 9.5f);
	m_vecUI.push_back(pUI);

	sName = "skicon4";
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(397.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(23.f, 23.f)), sName, 9.5f);
	m_vecUI.push_back(pUI);
}

CSCSarasen::CSCSarasen(SCENE_ID eID, CDirectXFramework* pFrameWork) : CScene(eID) {
	m_pFrameWork = pFrameWork;
}
CSCSarasen::~CSCSarasen() {
}
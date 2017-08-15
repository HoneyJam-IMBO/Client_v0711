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

	int nPawn = NETWORKMGR->GetServerPlayerInfos().size();//pawn의 전체 수

	m_ppPawn = new CGameObject*[nPawn];
	for (int i = 0; i < nPawn; ++i) {
		bool bSoul = (NETWORKMGR->GetSLOT_ID() == i);//slot_id랑 i랑 같으면 컨트롤 가능 객체
		INT CHARACTER = NETWORKMGR->GetServerPlayerInfo(i).CHARACTER;
		//pawn 제작
		CGameObject* pWeapon = nullptr;
		switch (CHARACTER) {
		case 0:
			//궁수
			pWeapon = new CGameObject("Bow1", TAG_DYNAMIC_OBJECT);
			pWeapon->Begin();
			m_ppPawn[i] = new CRanger("Elf01F", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(15 * i + 690, 0, 10 * i + 430, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 1:
			//기사
			pWeapon = new CGameObject("OSW", TAG_DYNAMIC_OBJECT);
			pWeapon->Begin();
			m_ppPawn[i] = new CKnight("Hum01M", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(15 * i + 690, 0, 10 * i + 430, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 2:
			//공간술사
			m_ppPawn[i] = new CDementor("Hum03M", TAG_DYNAMIC_OBJECT, bSoul, nullptr, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(15 * i + 690, 0, 10 * i + 430, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 3:
			pWeapon = new CGameObject("THM", TAG_DYNAMIC_OBJECT);
			pWeapon->Begin();
			m_ppPawn[i] = new CSister("Lup01M", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(15 * i + 690, 0, 10 * i + 430, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 4:
			m_ppPawn[i] = new CWizard("Hum02F", TAG_DYNAMIC_OBJECT, bSoul, nullptr, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(15 * i + 690, 0, 10 * i + 430, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 5:
			//법사
			m_ppPawn[i] = new CBard("Hum04F", TAG_DYNAMIC_OBJECT, bSoul, nullptr, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(15 * i + 690, 0, 10 * i + 430, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		}

		if (bSoul) {//player에게 camera 붙혀주기
			m_ppPawn[i]->SetTerrainContainer(UPDATER->GetTerrainContainer());
			m_ppPawn[i]->SetUTag(utag::UTAG_PLAYER);
			//m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]부터 [40, 10]까지 배치
			UPDATER->GetSpaceContainer()->AddObject(m_ppPawn[i]);
			m_ppPawn[i]->GetAnimater()->SetCurAnimationIndex(0);
			CAMMGR->SetTarget(CAM_FREE, m_ppPawn[i]);
			CAMMGR->GetCamera(CAM_FREE)->SetMode(MODE_FIX);
		}
		else {
			//다른 player는 충돌처리를 허지 않으심
			m_ppPawn[i]->SetUTag(utag::UTAG_OTHERPLAYER);
			UPDATER->GetSpaceContainer()->AddObject(m_ppPawn[i]);
			m_ppPawn[i]->GetAnimater()->SetCurAnimationIndex(0);
		}

		//navi object
		if (false == CNaviObjectManager::GetNaviVertices().empty())
			m_ppPawn[i]->SetNaviMeshIndex();
	}

	ResetCollisionValue(XMFLOAT3(620, -161, 580), 20);
	CreateBoss2();

#ifdef NO_SERVER
	return CScene::Begin();
#endif
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	NETWORKMGR->WritePacket(PT_SARASEN_READY_CS, Packet, WRITE_PT_SARASEN_READY_CS(Packet, NETWORKMGR->GetROOM_ID()));

	while (false == m_bGameStart) {
		NetworkProc();
		Sleep(1);
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
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	int slot_id = NETWORKMGR->GetSLOT_ID();
	wchar_t wcPosition[126];
	XMFLOAT3 xmf3Pos;
	XMStoreFloat3(&xmf3Pos, m_ppPawn[slot_id]->GetPosition());
	int x = xmf3Pos.x;
	int y = xmf3Pos.y;
	int z = xmf3Pos.z;
	wsprintf(wcPosition, L"player_position : %d, %d, %d", x, y, z);
	DEBUGER->AddGameText(20, 100, 100, YT_Color(255, 255, 0), wcPosition);
#ifdef NO_SERVER

	//flag인 부분 충돌 처리
	if (FlagCollision(m_ppPawn[slot_id])) {
		StartBoss2ActionCam();
		//flag인 부분과 충돌했다면!
		m_ppPawn[slot_id]->SetbStay(true);//나 stay!
		m_ppPawn[slot_id]->GetAnimater()->SetCurAnimationIndex(ANIM_IDLE);
		


	}
	//보스캠 처리
	if (m_bStartBossCam) {
		if (false == m_pCamera->m_bActionCam) {
			m_ppPawn[slot_id]->SetbStay(false);//나 stay 해제!
			int boss_fight_start = 0; //보스 처음 움직임 무한루프 해제
			//싸움 시작
			//m_pBoss->SetFirstAction(false);
		}
	}
#else
	//flag인 부분 충돌 처리
	if (FlagCollision(m_ppPawn[slot_id])) {
	
		//flag인 부분과 충돌했다면!
		m_ppPawn[slot_id]->SetbStay(true);//나 stay!
		m_ppPawn[slot_id]->GetAnimater()->SetCurAnimationIndex(ANIM_IDLE);
		
		NETWORKMGR->WritePacket(PT_SARASEN_BOSS_START_CS, Packet, WRITE_PT_SARASEN_BOSS_START_CS(Packet, NETWORKMGR->GetROOM_ID(), NETWORKMGR->GetSLOT_ID()));
		NETWORKMGR->GetServerPlayerInfos()[NETWORKMGR->GetSLOT_ID()].READY = true;

	}
	if (INPUTMGR->KeyBoardDown(VK_R)) {
		NETWORKMGR->WritePacket(PT_SARASEN_BOSS_ACTION_CAMERA_READY_CS, Packet, WRITE_PT_SARASEN_BOSS_ACTION_CAMERA_READY_CS(Packet, NETWORKMGR->GetROOM_ID(), NETWORKMGR->GetSLOT_ID()));
		NETWORKMGR->GetServerPlayerInfos()[NETWORKMGR->GetSLOT_ID()].READY = true;
	}
	//보스캠 처리
	if (m_bStartBossCam) {
		if (false == m_pCamera->m_bActionCam) {
			m_ppPawn[slot_id]->SetbStay(false);//나 stay 해제!
			int boss_fight_start = 0; //보스 처음 움직임 무한루프 해제
			//싸움 시작
			//m_pBoss->SetFirstAction(false);
		}
	}
#endif
	for (int i = 0; i < 20; ++i)
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
	else if (INPUTMGR->KeyBoardDown(VK_Y)) {
		int slot_id = NETWORKMGR->GetSLOT_ID();
		char action_move_file_name[128];
		int action_move_id = slot_id + 1;
		if (action_move_id> 3) action_move_id = rand() % 3 + 1;
		sprintf(action_move_file_name, "Sarasen_Boss2", action_move_id);
		float fSpeed = CPositionInfoManager::GetActionSpeed(action_move_file_name);
		CPositionInfoManager::SetActoionSpeed(action_move_file_name, fSpeed + 1.f);
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

	//음 이건 화면을 찍은 점의 카메라 좌표계의 녀석이고
	XMFLOAT3 xmf3PickPosition;
	xmf3PickPosition.x = (((2.0f * xClient) / d3dViewport.Width) - 1) / xmf4x4Projection._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / d3dViewport.Height) - 1) / xmf4x4Projection._22;
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition;
	xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);
	XMMATRIX xmMtxViewInverse;
	xmMtxViewInverse = XMMatrixInverse(nullptr, m_pCamera->GetViewMtx());
	//picking pos에 camera inverse를 곱했으니 이건 picking pos의 world pos!
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
		case PT_FREQUENCY_MOVE_SC:
			PROC_PT_FREQUENCY_MOVE_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_BOSS_FREQUENCY_MOVE_SC:
			PROC_PT_BOSS_FREQUENCY_MOVE_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_MOUSE_LEFT_ATTACK_SC:
			PROC_PT_MOUSE_LEFT_ATTACK_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_SARASEN_READY_SC:
			PROC_PT_SARASEN_READY_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_SARASEN_BOSS_START_SC:
			PROC_PT_SARASEN_BOSS_START_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_SARASEN_BOSS_START_COMP_SC:
			PROC_PT_SARASEN_BOSS_START_COMP_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC:
			PROC_PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_SARASEN_BOSS_ACTION_CAMERA_READY_COMP_SC:
			PROC_PT_SARASEN_BOSS_ACTION_CAMERA_READY_COMP_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_BOSS_HP_SC:
			PROC_PT_BOSS_HP_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_PLAYER_HP_SC:
			PROC_PT_PLAYER_HP_SC(dwProtocol, Packet, dwPacketLength);
			break;
		}
	}
}

VOID CSCSarasen::PROC_PT_BOSS_HP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {
	READ_PACKET(PT_BOSS_HP_SC);

	NETWORKMGR->SetBossHP(Data.BOSS_HP);
	m_pBoss->SetCurHP(Data.BOSS_HP);
	m_pBoss->GetDemaged(0);
	return VOID();
}

VOID CSCSarasen::PROC_PT_PLAYER_HP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {
	READ_PACKET(PT_PLAYER_HP_SC);

	bool bHeal = false;
	if (NETWORKMGR->GetPlayerHP(Data.SLOT_ID) <= Data.PLAYER_HP)
		bHeal = true;
	NETWORKMGR->SetPlayerHP(Data.SLOT_ID, Data.PLAYER_HP);
	m_ppPawn[Data.SLOT_ID]->SetCurHP(Data.PLAYER_HP);
	if (NETWORKMGR->GetSLOT_ID() == Data.SLOT_ID && bHeal == false)
		m_ppPawn[Data.SLOT_ID]->GetDemaged(0);
	return VOID();
}

VOID CSCSarasen::PROC_PT_SARASEN_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength)
{
	m_bGameStart = true;
	return VOID();
}

VOID CSCSarasen::PROC_PT_SARASEN_BOSS_START_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength)
{
	READ_PACKET(PT_SARASEN_BOSS_START_SC);
	NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].READY = Data.READY;
	return VOID();
}

VOID CSCSarasen::PROC_PT_SARASEN_BOSS_START_COMP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength)
{
	for (int i = 0; i < NETWORKMGR->GetServerPlayerInfos().size(); ++i)
		NETWORKMGR->GetServerPlayerInfos()[i].READY = false;

	//
	//
	// 보스 액션 캠 시자가아아아아아아앙
	//
	//
	StartBoss2ActionCam();
	return VOID();
}
VOID CSCSarasen::PROC_PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength)
{
	READ_PACKET(PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC);
	NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].READY = Data.READY;
	return VOID();
}
VOID CSCSarasen::PROC_PT_SARASEN_BOSS_ACTION_CAMERA_READY_COMP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength)
{
	for (int i = 0; i < NETWORKMGR->GetServerPlayerInfos().size(); ++i)
		NETWORKMGR->GetServerPlayerInfos()[i].READY = false;

	//
	// 액션캠 끄고
	// 보스 전투 시작아아아아아ㅏ아아아
	//
	//
	//
	//
	m_pCamera->ActionCamEnd();

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
	data.iAnimNum = Data.ANIMNUM;
	//CPawn* pPawn = (CPawn*)m_ppPawn[Data.SLOT_ID];
	//pPawn->NetworkInput(data.dwDirection, data.fAngleY);
	//network queue에 입력하구 대기한다.
	//NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].m_qFREQUENCY_DATA.push(data);
	NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].FREQUENCY_DATA = data;

	return VOID();
}

VOID CSCSarasen::PROC_PT_BOSS_FREQUENCY_MOVE_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {
	READ_PACKET(PT_BOSS_FREQUENCY_MOVE_SC);


	BOSS_FREQUENCY_DATA data;
	data.fPosX = Data.POSX;
	data.fPosY = Data.POSY;
	data.fPosZ = Data.POSZ;

	data.fAngleY = Data.ANGLEY;
	data.iAnimNum = Data.ANIMNUM;
	//CPawn* pPawn = (CPawn*)m_ppPawn[Data.SLOT_ID];
	//pPawn->NetworkInput(data.dwDirection, data.fAngleY);
	//network queue에 입력하구 대기한다.
	//NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].m_qFREQUENCY_DATA.push(data);
	//DEBUGER->AddGameText(25, 10, 300, YT_Color(0, 0, 200), L"%f %f %f %f %f", data.fPosX, data.fPosY, data.fPosZ, data.fAngleY, data.iAnimNum);

	NETWORKMGR->SetBossInfo(data);
	//BYTE PacketT[MAX_BUFFER_LENGTH] = { 0, };
	//NETWORKMGR->WritePacket(PT_TEMP, PacketT, WRITE_PT_TEMP(PacketT));
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
	//RCSELLER->TestingRCAdd();
	CUIObject* pUI;
	pUI = CHpBar::Create(XMLoadFloat2(&XMFLOAT2(WINSIZEX * 0.24f, WINSIZEY * 0.77f)), XMLoadFloat2(&XMFLOAT2(190.f, 6.f)));
	m_vecUI.push_back(pUI);

	string sCharSelect;
	string sSkill1;
	string sSkill2;
	string sSkill3;
	string sSkill4;
	int nChracter = NETWORKMGR->GetServerPlayerInfo(NETWORKMGR->GetSLOT_ID()).CHARACTER;
	switch (nChracter) {
	case 0:
		sCharSelect = "Char_Select_0";
		sSkill1 = "ranger_skicon1";
		sSkill2 = "ranger_skicon2";
		sSkill3 = "ranger_skicon3";
		sSkill4 = "ranger_skicon4";

		break;
	case 1:
		sCharSelect = "Char_Select_1";
		sSkill1 = "knight_skicon1";
		sSkill2 = "knight_skicon2";
		sSkill3 = "knight_skicon3";
		sSkill4 = "knight_skicon4";
		break;
	case 2:
		sCharSelect = "Char_Select_2";
		sSkill1 = "dementor_skicon1";
		sSkill2 = "dementor_skicon2";
		sSkill3 = "dementor_skicon3";
		sSkill4 = "dementor_skicon4";
		break;
	case 3:
		sCharSelect = "Char_Select_3";
		sSkill1 = "sister_skicon1";
		sSkill2 = "sister_skicon2";
		sSkill3 = "sister_skicon3";
		sSkill4 = "sister_skicon4";
		break;
	case 4:
		sCharSelect = "Char_Select_4";
		sSkill1 = "wizard_skicon1";
		sSkill2 = "wizard_skicon2";
		sSkill3 = "wizard_skicon3";
		sSkill4 = "wizard_skicon4";
		break;
	case 5:
		sCharSelect = "Char_Select_5";
		sSkill1 = "bard_skicon1";
		sSkill2 = "bard_skicon2";
		sSkill3 = "bard_skicon3";
		sSkill4 = "bard_skicon4";
		break;
	default:
		break;
	}

	//player icon
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(132.f, WINSIZEY * 0.8f)), XMLoadFloat2(&XMFLOAT2(50.f, 50.f)), sCharSelect, 10.f);
	m_vecUI.push_back(pUI);

	//skill back
	string sSkillBack;
	sSkillBack = "SkillBack";
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(217.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(30.f, 30.f)), sSkillBack, 9.f);
	m_vecUI.push_back(pUI);
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(277.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(30.f, 30.f)), sSkillBack, 9.f);
	m_vecUI.push_back(pUI);
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(337.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(30.f, 30.f)), sSkillBack, 9.f);
	m_vecUI.push_back(pUI);
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(397.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(30.f, 30.f)), sSkillBack, 9.f);
	m_vecUI.push_back(pUI);

	//skill icon
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(217.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(23.f, 23.f)), sSkill1, 9.5f);
	m_vecUI.push_back(pUI);
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(277.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(23.f, 23.f)), sSkill2, 9.5f);
	m_vecUI.push_back(pUI);
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(337.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(23.f, 23.f)), sSkill3, 9.5f);
	m_vecUI.push_back(pUI);
	pUI = CImageUI::Create(XMLoadFloat2(&XMFLOAT2(397.f, WINSIZEY * 0.82f)), XMLoadFloat2(&XMFLOAT2(23.f, 23.f)), sSkill4, 9.5f);
	m_vecUI.push_back(pUI);
}

void CSCSarasen::StartBoss2ActionCam(){
	char BossActionCamFileName[128];
	//Sarasen_Boss%d
	sprintf(BossActionCamFileName, "Sarasen_Boss2", (rand() % 3) + 1);
	m_bStartBossCam = true;
	m_pCamera->ActionCamStart(BossActionCamFileName);
}

void CSCSarasen::CreateBoss2()
{
	//보스 제작
	m_pBoss = new CRoisa("Boss02R", TAG_DYNAMIC_OBJECT, m_ppPawn[0]);
	m_pBoss->SetUTag(utag::UTAG_BOSS1);
	m_pBoss->Begin();
	m_pBoss->SetTerrainContainer(UPDATER->GetTerrainContainer());
	m_pBoss->SetPosition(XMVectorSet(512, 0, 768, 0));
	m_pBoss->SetNaviMeshIndex();
	m_pBoss->SetScale(XMVectorSet(3, 3, 3, 1));
	UPDATER->GetSpaceContainer()->AddObject(m_pBoss);
	m_pBoss->GetAnimater()->SetCurAnimationIndex(0);
}

void CSCSarasen::KillBoss2()
{
	if (m_pBoss) m_pBoss->GetAnimater()->SetCurAnimationIndex(2);
}

CSCSarasen::CSCSarasen(SCENE_ID eID, CDirectXFramework* pFrameWork) : CScene(eID) {
	m_pFrameWork = pFrameWork;
}
CSCSarasen::~CSCSarasen() {
}
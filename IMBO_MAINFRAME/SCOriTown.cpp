#include "stdafx.h"
#include "SCOriTown.h"

#include "ElfSkillArrow.h"
#include "LesserGiant.h"
#include "HpBar.h"
#include "ImageUI.h"

//#include "Pawn.h"
#include "Ranger.h"
#include "Knight.h"
#include "Dementor.h"
#include "Sister.h"
#include "Wizard.h"
#include "Bard.h"

bool CSCOriTown::Begin() {
//#ifdef NO_SERVER
//	NETWORKMGR->AddServerPlayerInfo(0);
//#endif
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
			m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 1:
			//기사
			pWeapon = new CGameObject("OSW", TAG_DYNAMIC_OBJECT);
			pWeapon->Begin();
			m_ppPawn[i] = new CKnight("Hum01M", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 2:
			//공간술사
			m_ppPawn[i] = new CDementor("Hum03M", TAG_DYNAMIC_OBJECT, bSoul, nullptr, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 3:
			pWeapon = new CGameObject("THM", TAG_DYNAMIC_OBJECT);
			pWeapon->Begin();
			m_ppPawn[i] = new CSister("Lup01M", TAG_DYNAMIC_OBJECT, bSoul, pWeapon, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 4:
			m_ppPawn[i] = new CWizard("Hum02F", TAG_DYNAMIC_OBJECT, bSoul, nullptr, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]부터 [40, 10]까지 배치
			m_ppPawn[i]->SetScale(XMVectorSet(1, 1, 1, 1));
			break;
		case 5:
			//법사
			m_ppPawn[i] = new CBard("Hum04F", TAG_DYNAMIC_OBJECT, bSoul, nullptr, i);
			m_ppPawn[i]->Begin();
			m_ppPawn[i]->SetPosition(XMVectorSet(10 * i + 250, 0, 250, 0));//[10, 10]부터 [40, 10]까지 배치
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
			m_ppPawn[i]->SetUTag(utag::UTAG_DEFAULT);
			UPDATER->GetSpaceContainer()->AddObject(m_ppPawn[i]);
			m_ppPawn[i]->GetAnimater()->SetCurAnimationIndex(0);
		}

		//navi object
		if(false == CNaviObjectManager::GetNaviVertices().empty())
			m_ppPawn[i]->SetNaviMeshIndex();
	}

	//보스 제작
	//CGameObject*	pBoss = new CLesserGiant("Boss01L", TAG_DYNAMIC_OBJECT, m_ppPawn[0]);
	//pBoss->SetUTag(utag::UTAG_BOSS1);
	//pBoss->Begin();
	//pBoss->SetTerrainContainer(UPDATER->GetTerrainContainer());
	//pBoss->SetPosition(XMVectorSet(200, 0, 250, 0));
	//pBoss->SetNaviMeshIndex();
	//pBoss->SetScale(XMVectorSet(1, 1, 1, 1));
	//UPDATER->GetSpaceContainer()->AddObject(pBoss);
	//pBoss->GetAnimater()->SetCurAnimationIndex(0);

#ifdef NO_SERVER
	return CScene::Begin();
#endif
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	NETWORKMGR->WritePacket(PT_FTOWN_READY_CS, Packet, WRITE_PT_FTOWN_READY_CS(Packet, NETWORKMGR->GetROOM_ID()));

	while (false == m_bGameStart) {
		NetworkProc();
		Sleep(100);
	}
	return CScene::Begin();
}

bool CSCOriTown::End() {	
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
	//카메라는 Framework에 존재하는 것이기에 End()작업을 진행하지 않는다.
	//Safe_EndDelete(m_pObject);
	return CScene::End();
}

void CSCOriTown::Animate(float fTimeElapsed) {

	XMFLOAT3 xmf3Pos;
	int slot_id = NETWORKMGR->GetSLOT_ID();
	XMStoreFloat3(&xmf3Pos, m_ppPawn[slot_id]->GetPosition());
	DEBUGER->AddGameText(25, 100, 100, YT_Color(200, 200, 0), L"%d %d %d", (int)xmf3Pos.x , (int)xmf3Pos.y, (int)xmf3Pos.z);

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	int progress = 0;
	for (auto player_info : NETWORKMGR->GetServerPlayerInfos()) {

		if (player_info.READY) {
			DEBUGER->AddGameText(50, 10, 50 * progress, YT_Color(0, 255, 0), L"준비");
		}
		else {
			DEBUGER->AddGameText(50, 10, 50 * progress, YT_Color(0, 0, 255), L"대기");
			DEBUGER->AddGameText(25, 200, 50 * progress, YT_Color(200,200,200), L"%f %f %f", player_info.FREQUENCY_DATA.fPosX, player_info.FREQUENCY_DATA.fPosY, player_info.FREQUENCY_DATA.fPosZ);
		}
		progress++;
	}

	
	

	NetworkProc();
	CScene::Animate(fTimeElapsed);
	if (m_bStartBossCam) {
		if (false == m_pCamera->m_bActionCam) {
			int boss_fight_start = 0;
			m_pBoss->SetFirstAction(false);
		}
	}
	if (m_bFinalProc) {
		int slot_id = NETWORKMGR->GetSLOT_ID();
		if (false == m_ppPawn[slot_id]->m_bActionMove) {
			SCENEMGR->ChangeScene(SCN_ALDENAD);
		}
	}
	size_t iVecSize = m_vecUI.size();
	for (size_t i = 0; i < iVecSize; ++i)
	{
		m_vecUI[i]->Update(fTimeElapsed);
	}
#ifdef NO_SERVER
	if (INPUTMGR->KeyBoardDown(VK_R)) {
		StartBoss1ActionCam();
		CreateBoss1();
	}
	else if (INPUTMGR->KeyBoardDown(VK_K)) {
		KillBoss1();
	}
	else if (INPUTMGR->KeyBoardDown(VK_F)) {
		FirstTownFly();
	}

#else
	if (NETWORKMGR->GetServerPlayerInfos()[NETWORKMGR->GetSLOT_ID()].READY == false){
		if (INPUTMGR->KeyBoardDown(VK_R)) {
			//StartBoss1ActionCam();
			//CreateBoss1();
			if (NETWORKMGR->GetServerPlayerInfos()[NETWORKMGR->GetSLOT_ID()].ACTIONCAM == false)
				NETWORKMGR->WritePacket(PT_FTOWN_NPC_READY_CS, Packet, WRITE_PT_FTOWN_NPC_READY_CS(Packet, NETWORKMGR->GetROOM_ID(), NETWORKMGR->GetSLOT_ID()));
			else
				NETWORKMGR->WritePacket(PT_FTOWN_BOSS_ACTION_CAMERA_READY_CS, Packet, WRITE_PT_FTOWN_BOSS_ACTION_CAMERA_READY_CS(Packet, NETWORKMGR->GetROOM_ID(), NETWORKMGR->GetSLOT_ID()));

			NETWORKMGR->GetServerPlayerInfos()[NETWORKMGR->GetSLOT_ID()].READY = true;

		}
		else if (INPUTMGR->KeyBoardDown(VK_K)) {
			//KillBoss1();
			NETWORKMGR->WritePacket(PT_SKILL_COLLISION_TO_TARGET_CS, Packet, WRITE_PT_SKILL_COLLISION_TO_TARGET_CS(Packet,
				NETWORKMGR->GetROOM_ID(),
				NETWORKMGR->GetSLOT_ID(),
				9,
				NETWORKMGR->GetServerPlayerInfo(NETWORKMGR->GetSLOT_ID()).CHARACTER,
				99));
	
		}
		else if (INPUTMGR->KeyBoardDown(VK_F)) {
			//FirstTownFly();
			NETWORKMGR->WritePacket(PT_FTOWN_NPC2_READY_CS, Packet, WRITE_PT_FTOWN_NPC2_READY_CS(Packet, NETWORKMGR->GetROOM_ID(), NETWORKMGR->GetSLOT_ID()));
			NETWORKMGR->GetServerPlayerInfos()[NETWORKMGR->GetSLOT_ID()].READY = true;
		}
	}
#endif
	if (INPUTMGR->KeyBoardDown(VK_Y)) {
		int slot_id = NETWORKMGR->GetSLOT_ID();
		char action_move_file_name[128];
		int action_move_id = slot_id + 1;
		if (action_move_id> 3) action_move_id = rand() % 3 + 1;
		sprintf(action_move_file_name, "Firsttown_Fly%d", action_move_id);
		float fSpeed = CPositionInfoManager::GetActionSpeed(action_move_file_name);
		CPositionInfoManager::SetActoionSpeed(action_move_file_name, fSpeed + 1.f);
	}
	else if (INPUTMGR->KeyBoardDown(VK_T))
	{


#ifdef NO_SERVER
		SCENEMGR->ChangeScene(SCN_ALDENAD);
#else
		BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
		NETWORKMGR->WritePacket(PT_FTOWN_NPC2_READY_CS, Packet, WRITE_PT_FTOWN_NPC2_READY_CS(Packet, NETWORKMGR->GetROOM_ID(), NETWORKMGR->GetSLOT_ID()));
		NETWORKMGR->GetServerPlayerInfos()[NETWORKMGR->GetSLOT_ID()].READY = true;
#endif
		
		//
	}
}

void CSCOriTown::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		//POINT p = INPUTMGR->GetMousePoint();
		//m_pPickingObject = PickObjectPointedByCursor(p.x, p.y);
		//if (m_pPickingObject) {
		//	m_pPickingObject->PickingProc();
		//}
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		

	case WM_MOUSEMOVE:
		break;
	default:
		break;
	}
}
void CSCOriTown::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	
	//RCSELLER->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
	switch (nMessageID){
	case WM_KEYUP:
		switch (wParam){
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

void CSCOriTown::ProcessInput(float fTimeElapsed) {
	
	if (INPUTMGR->KeyDown(VK_P)) {
		INPUTMGR->SetDebugMode(static_cast<bool>((INPUTMGR->GetDebugMode() + 1) % 2));
	}
	////test
	//if (INPUTMGR->MouseLeftDown()) {
	//	int xClient = INPUTMGR->GetMousePoint().x;
	//	int yClient = INPUTMGR->GetMousePoint().y;
	//	XMFLOAT3 pickPos;
	//	if (GetPickPositionByCursor(xClient, yClient, pickPos)) {
	//		m_vPickPos.push_back(pickPos);
	//	}
	//}
	//for (auto Vertex : m_vPickPos) {
	//
	//	BoundingOrientedBox obb;
	//	obb.Center = Vertex;
	//	obb.Extents = XMFLOAT3(1.f, 1.f, 1.f);
	//	DEBUGER->RegistOBB(obb, UTAG_PLAYER);
	//}
	////test

	m_pCamera->ProcessInput(fTimeElapsed);
	//if (INPUTMGR->KeyDown(VK_1))
	//{
		//SCENEMGR->ChangeScene(SC_ORITOWN);
	//}
}


CGameObject* CSCOriTown::PickObjectPointedByCursor(int xClient, int yClient){

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

void CSCOriTown::NetworkProc(){
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
			break;
		case PT_FTOWN_NPC_READY_SC:
			PROC_PT_FTOWN_NPC_READY_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_FTOWN_NPC_READY_COMP_SC:
			PROC_PT_FTOWN_NPC_READY_COMP_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_FTOWN_NPC2_READY_SC:
			PROC_PT_FTOWN_NPC2_READY_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_FTOWN_NPC2_READY_COMP_SC:
			PROC_PT_FTOWN_NPC2_READY_COMP_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_FTOWN_BOSS_ACTION_CAMERA_READY_SC:
			PROC_PT_FTOWN_BOSS_ACTION_CAMERA_READY_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_FTOWN_BOSS_ACTION_CAMERA_READY_COMP_SC:
			PROC_PT_FTOWN_BOSS_ACTION_CAMERA_READY_COMP_SC(dwProtocol, Packet, dwPacketLength);
			break;
		case PT_BOSS_HP_SC:
			break;
		case PT_BOSS_CLEAR_SC:
			PROC_PT_BOSS_CLEAR_SC(dwProtocol, Packet, dwPacketLength);
			break;
		}
	}
}


VOID CSCOriTown::PROC_PT_BOSS_CLEAR_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {
	// 보스 죽음
	KillBoss1();

	return VOID();
}

VOID CSCOriTown::PROC_PT_FTOWN_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength){
	m_bGameStart = true;
	return VOID();
}

VOID CSCOriTown::PROC_PT_FREQUENCY_MOVE_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength){
	READ_PACKET(PT_FREQUENCY_MOVE_SC);

	DEBUGER->AddText(25, 10, 400 + Data.SLOT_ID * 50, YT_Color(), L"recv ID : %d", Data.SLOT_ID);
	DEBUGER->AddGameText(25, 10, 450 + Data.SLOT_ID * 50, YT_Color(200 ,200,200), L"%f %f %f", Data.POSX, Data.POSY, Data.POSZ);
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
	BYTE PacketT[MAX_BUFFER_LENGTH] = { 0, };
	NETWORKMGR->WritePacket(PT_TEMP, PacketT, WRITE_PT_TEMP(PacketT));
	return VOID();
}

void CSCOriTown::StartBoss1ActionCam(){
	m_bStartBossCam = true;
	m_pCamera->ActionCamStart("Firsttown_Boss2");
}

void CSCOriTown::CreateBoss1()
{
	//보스 제작
	m_pBoss = new CLesserGiant("Boss01L", TAG_DYNAMIC_OBJECT, m_ppPawn[0]);
	m_pBoss->SetUTag(utag::UTAG_BOSS1);
	m_pBoss->Begin();
	m_pBoss->SetTerrainContainer(UPDATER->GetTerrainContainer());
	m_pBoss->SetPosition(XMVectorSet(180, 0, 175, 0));
	m_pBoss->SetNaviMeshIndex();
	m_pBoss->SetScale(XMVectorSet(1, 1, 1, 1));
	UPDATER->GetSpaceContainer()->AddObject(m_pBoss);
	m_pBoss->SetFirstAction(true);
	m_pBoss->SetAnimNum(BOSS1_ANI_SKILL2);
	m_pBoss->GetAnimater()->SetCurAnimationIndex(BOSS1_ANI_SKILL2);
}

void CSCOriTown::KillBoss1(){
	if(m_pBoss) m_pBoss->GetAnimater()->SetCurAnimationIndex(BOSS1_ANI_DYING);
}

void CSCOriTown::FirstTownFly(){
	m_bFinalProc = true;//날면 마지막 단계임
	int slot_id = NETWORKMGR->GetSLOT_ID();
	m_ppPawn[slot_id]->ActionMoveEnd();

	char action_move_file_name[128];
	int action_move_id = slot_id + 1;
	if (action_move_id> 3) action_move_id = rand() % 3 + 1;
	sprintf(action_move_file_name, "Firsttown_Fly%d", action_move_id);

	m_ppPawn[slot_id]->ActionMoveStart(action_move_file_name);
}

VOID CSCOriTown::PROC_PT_MOUSE_LEFT_ATTACK_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {
	READ_PACKET(PT_MOUSE_LEFT_ATTACK_SC);

	NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].ATTACK = Data.ATTACK;

	return VOID();
}
VOID CSCOriTown::PROC_PT_FTOWN_NPC_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {
	READ_PACKET(PT_FTOWN_NPC_READY_SC);

	
	NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].READY = Data.READY;


	return VOID();
}

VOID CSCOriTown::PROC_PT_FTOWN_NPC_READY_COMP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {

	for (int i = 0; i < NETWORKMGR->GetServerPlayerInfos().size(); ++i) {
		NETWORKMGR->GetServerPlayerInfos()[i].READY = false;
		NETWORKMGR->GetServerPlayerInfos()[i].ACTIONCAM = true;
	}


	//
	//
	// 보스 액션캠므므믐므므ㅡ므므므므므
	//
	//
	StartBoss1ActionCam();
	CreateBoss1();

	return VOID();
}
VOID CSCOriTown::PROC_PT_FTOWN_BOSS_ACTION_CAMERA_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {
	READ_PACKET(PT_FTOWN_BOSS_ACTION_CAMERA_READY_SC);


	NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].READY = Data.READY;


	return VOID();
}
VOID CSCOriTown::PROC_PT_FTOWN_BOSS_ACTION_CAMERA_READY_COMP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {

	for (int i = 0; i < NETWORKMGR->GetServerPlayerInfos().size(); ++i) {
		NETWORKMGR->GetServerPlayerInfos()[i].READY = false;
		NETWORKMGR->GetServerPlayerInfos()[i].ACTIONCAM = true;
	}

	//
	//
	// 보스 전투 시작끄끄끄끄끄끄끄끄끄끄끄
	//
	//
	m_pCamera->ActionCamEnd();
	

	return VOID();
}


VOID CSCOriTown::PROC_PT_FTOWN_NPC2_READY_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {

	READ_PACKET(PT_FTOWN_NPC2_READY_SC);


	NETWORKMGR->GetServerPlayerInfos()[Data.SLOT_ID].READY = Data.READY;


	return VOID();
}

VOID CSCOriTown::PROC_PT_FTOWN_NPC2_READY_COMP_SC(DWORD dwProtocol, BYTE * Packet, DWORD dwPacketLength) {


	for (int i = 0; i < NETWORKMGR->GetServerPlayerInfos().size(); ++i)
		NETWORKMGR->GetServerPlayerInfos()[i].READY = false;


	//
	// 
	// ftown -> 알데나드로 출발!!!
	//
	//
	FirstTownFly();

	return VOID();
}


void CSCOriTown::ReadMapData()
{
	IMPORTER->Begin("../../Assets/SceneResource/test/test.scn");
	//IMPORTER->Begin("../../Assets/SceneResource/FirstTown/FirstTown.scn");
	//IMPORTER->Begin("../../Assets/SceneResource/Aldenard/Aldenard.scn");
	//IMPORTER->Begin("../../Assets/SceneResource/Sarasen/Sarasen.scn");
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

void CSCOriTown::LoadSkillObjects()
{
	//RCSELLER->TestingRCAdd();
	

}

void CSCOriTown::CreateUI()
{
	//RCSELLER->TestingRCAdd();
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

CSCOriTown::CSCOriTown(SCENE_ID eID, CDirectXFramework* pFrameWork) : CScene(eID) {
	m_pFrameWork = pFrameWork;
}
CSCOriTown::~CSCOriTown() {

}


#include "stdafx.h"
#include "Ranger.h"
#include "EffectMgr.h"
#include "ElfSkillArrow.h"

bool CRanger::Begin()
{
	CGameObject::Begin();
	return false;
}

void CRanger::Animate(float fTimeElapsed)
{
	if (true == m_bSprit && false == m_bDamaged)
			KeyInput(fTimeElapsed); //KeyInput(fTimeElapsed);
	else	GetServerData(fTimeElapsed);
	
	// �ִϸ��̼� ������Ʈ�Լ�
	if (m_pAnimater) m_pAnimater->Update(TIMEMGR->GetTimeElapsed());


	UpdateSkill();
	CGameObject::Animate(fTimeElapsed);

	SetWeapon();
	DEBUGER->AddText(30, 100, 600, YT_Color(255.f, 255.f, 255.f), L"animation %d", m_nAnimNum);
}

bool CRanger::End()
{
	if (m_pWeapon){
		delete m_pWeapon;
		m_pWeapon = nullptr;
	}
	return true;
}

void CRanger::KeyInput(float fDeltaTime)
{
	DWORD dwDirection = 0;
	m_xmvShift = XMVectorSet(0.0f, 0.0f, 0.0f, 0.f);

#ifdef NO_SERVER

#else
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	bool bAttack = true;
	NETWORKMGR->WritePacket(PT_MOUSE_LEFT_ATTACK_CS, Packet, WRITE_PT_MOUSE_LEFT_ATTACK_CS(Packet, bAttack));
#endif
	// ��ų �� ����
	if (false == m_bJump && false == m_bSkill)
	{
		if (INPUTMGR->MouseLeftDown()){					// �⺻���� ----------------------
			m_bSkill = true;
			m_nAnimNum = ANIM_ATTACK;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);

			size_t iArraySize = m_mapSkill["Arrow1"].size();
			for (size_t i = 0; i < iArraySize; ++i) {
				if (false == m_mapSkill["Arrow1"][i]->GetActive()) {
					m_mapSkill["Arrow1"][i]->SetActive(true);
					m_mapSkill["Arrow1"][i]->SetPosition(XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 3.f, m_xmf3Position.z, 1.f));
					m_mapSkill["Arrow1"][i]->Rotate(XMMatrixRotationY(m_fAngleY));
					m_mapSkill["Arrow1"][i]->SetScale(XMVectorSet(2.f, 2.f, 2.f, 1.f));
					
					((CElfSkillArrow*)m_mapSkill["Arrow1"][i])->GetTrail()->SetPosition(XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 3.f, m_xmf3Position.z, 1.f));
					break;
				}
			}
		}
		else if (INPUTMGR->KeyDown(VK_1)){				// ��ų 1 ------------------------
			m_bSkill = true;
			m_nAnimNum = ANIM_SKILL1_CHARGING;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
		}
		else if (INPUTMGR->KeyDown(VK_2)){				// ��ų 2 ------------------------
			m_bSkill = true;
			m_bSelRangeMode = true;
			m_nAnimNum = /*ANIM_SKILL2_FIRE*/ANIM_IDLE;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
		}
		else if (INPUTMGR->KeyDown(VK_3)){				// ��ų 3 ------------------------
			m_bSkill = true;
			m_nAnimNum = ANIM_SKILL3_FIRE;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
		}
		else if (INPUTMGR->KeyDown(VK_4)){				// ��ų 3 ------------------------
			m_bSkill = true;
			m_nAnimNum = ANIM_SKILL4_START;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
		}
	}

	// ��ų�� �̵� ����X
	if (true == m_bSkill) return;

	// ���콺 ��Ŭ��ȸ��
	if (true == INPUTMGR->MouseRightUp() && abs(m_pCamera->m_cxDelta + m_pCamera->m_cyDelta) > 1.f) {
		m_bIdle = false;
	}
	if (false == m_bIdle) {
		m_fAngleY = m_pCamera->m_fCurrentAngle[ANGLE_Y] + XM_PI;
		m_fAngleX = XM_PI * 2.f - m_pCamera->m_fCurrentAngle[ANGLE_X];

		m_xmatrixRotate = XMMatrixRotationX(m_fAngleX) *  XMMatrixRotationY(m_fAngleY);
		SetRotation(XMMatrixRotationY(m_fAngleY));
	}

	// �̵�
	if (INPUTMGR->OnlyKeyBoardDown(VK_W))		dwDirection |= DIR_FORWARD;
	if (INPUTMGR->OnlyKeyBoardDown(VK_S))		dwDirection |= DIR_BACKWARD;
	if (INPUTMGR->OnlyKeyBoardDown(VK_A))		dwDirection |= DIR_LEFT;
	if (INPUTMGR->OnlyKeyBoardDown(VK_D))		dwDirection |= DIR_RIGHT;
	// ����
	if (INPUTMGR->KeyBoardDown(VK_SPACE_))		m_bJump = true;

	if (true == INPUTMGR->MouseRightDown()) {
		m_bIdle = true;
	}

	SetupAnimation(dwDirection);
	//float fSpeed = 20.f;
	if (dwDirection) {
		float fSpdX = 1.f;
		if (dwDirection & DIR_RIGHT)		m_xmvShift += GetRight();
		if (dwDirection & DIR_LEFT)			m_xmvShift -= GetRight();
		if (dwDirection & DIR_FORWARD)		{ m_xmvShift += GetLook(); fSpdX = 1.f; }
		if (dwDirection & DIR_BACKWARD)		{ m_xmvShift -= GetLook(); fSpdX = 0.8f; }

		Move(XMVector3Normalize(m_xmvShift), (m_fSpeed * fSpdX) * fDeltaTime);

		m_bIdle = false;
	}
	else {
		if (false == m_bJump) {
			if (ANIM_JUMP_END != m_nAnimNum) {
				m_nAnimNum = ANIM_IDLE;
				m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
			}
		}
	}
	//����
	if (true == m_bJump)	Jumping(fDeltaTime);

#ifdef NO_SERVER
	return;
#endif 
	//60fps�� ������Ʈ, ��Ʈ��ũ ����
	m_fTranslateTime += fDeltaTime;
	if (m_fTranslateTime > 0.015) {
		m_fTranslateTime = 0;
		PushServerData(m_xmf3Position.x, m_xmf3Position.y, m_xmf3Position.z, m_fAngleY, dwDirection, m_bJump);
	}
}

void CRanger::PushServerData(float x, float y, float z, float fAngleY, DWORD dwDirection, bool bJump)
{
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	NETWORKMGR->WritePacket(PT_FREQUENCY_MOVE_CS, Packet, WRITE_PT_FREQUENCY_MOVE_CS(Packet, x, y, z, fAngleY, dwDirection, bJump));
}

void CRanger::GetServerData(float fTimeElapsed) {
#ifdef NO_SERVER
	return;
#endif
	//////
	PLAYR_FREQUENCY_DATA data = NETWORKMGR->GetPlayerFrequencyData(m_SLOT_ID);
	float fPosX = data.fPosX;
	float fPosY = data.fPosY;
	float fPosZ = data.fPosZ;

	float fAngleY = data.fAngleY;
	DWORD dwDirection = data.dwDirection;

	bool bAttack = NETWORKMGR->GetAttack(m_SLOT_ID);
	//////

	if (m_bJump == true && data.bJump == false) {
		m_nAnimNum = ANIM_JUMP_END;
		m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
	}
	m_bJump = data.bJump;

	SetPosition(XMVectorSet(fPosX, fPosY, fPosZ, 1.0f));
	SetRotation(XMMatrixRotationY(fAngleY));

	// ����
	//if (m_bSkill == false && m_bJump == false && bAttack == true && m_nAnimNum != ANIM_ATTACK) {
	//	CEffectMgr::GetInstance()->Play_Effect(L"Test2", XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 2.f, m_xmf3Position.z, 1.f),
	//		XMVectorSet(0.f, XMConvertToDegrees(m_fAngleY), 0.f, 0.f));
	//	m_nAnimNum = ANIM_ATTACK;
	//	m_pAnimater->SetCurAnimationIndex(m_nAnimNum);

	//	size_t iArraySize = m_mapSkill["Arrow"].size();
	//	for (size_t i = 0; i < iArraySize; ++i) {
	//		if (false == m_mapSkill["Arrow"][i]->GetActive()) {
	//			m_mapSkill["Arrow"][i]->SetActive(true);
	//			m_mapSkill["Arrow"][i]->SetPosition(XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 3.f, m_xmf3Position.z, 1.f));
	//			m_mapSkill["Arrow"][i]->Rotate(m_xmatrixRotate);
	//			break;
	//		}
	//	}
	//}

	SetupAnimation(dwDirection);
	if (dwDirection) {
		m_bIdle = false;
	}
	else {
		if (false == m_bJump) {
			if (ANIM_JUMP_END != m_nAnimNum) {
				m_nAnimNum = ANIM_IDLE;
				m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
			}
		}
	}
}

void CRanger::SetupAnimation(DWORD dwDirection)
{
	if (false == m_bJump)
	{
		if (dwDirection & DIR_FORWARD)		if (m_nAnimNum != ANIM_RUN_F) m_nAnimNum = ANIM_RUN_F;
		if (dwDirection & DIR_BACKWARD)		if (m_nAnimNum != ANIM_RUN_B) m_nAnimNum = ANIM_RUN_B;
		if (dwDirection & DIR_LEFT)			if (m_nAnimNum != ANIM_RUN_L) m_nAnimNum = ANIM_RUN_L;
		if (dwDirection & DIR_RIGHT)		if (m_nAnimNum != ANIM_RUN_R) m_nAnimNum = ANIM_RUN_R;

		if (dwDirection & DIR_FORWARD && dwDirection & DIR_LEFT)
			if (m_nAnimNum != ANIM_RUN_FL) m_nAnimNum = ANIM_RUN_FL;
		else if (dwDirection & DIR_FORWARD && dwDirection & DIR_RIGHT)
			if (m_nAnimNum != ANIM_RUN_FR) m_nAnimNum = ANIM_RUN_FR;
		else if (dwDirection & DIR_BACKWARD && dwDirection & DIR_LEFT)
			if (m_nAnimNum != ANIM_RUN_BL) m_nAnimNum = ANIM_RUN_BL;
		else if (dwDirection & DIR_BACKWARD && dwDirection & DIR_RIGHT)
			if (m_nAnimNum != ANIM_RUN_BR) m_nAnimNum = ANIM_RUN_BR;

		if (0 != dwDirection)
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
	}else{
		if (m_nAnimNum != ANIM_JUMP_START
			&& m_nAnimNum != ANIM_JUMP_LOOP)
		{
			m_nAnimNum = ANIM_JUMP_START;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
		}

		if (m_nAnimNum == ANIM_JUMP_START
			&& true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone())
		{
			m_nAnimNum = ANIM_JUMP_LOOP;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
		}
	}
	
}

void CRanger::Jumping(float fDeltaTime)
{
	m_fJumpTime += fDeltaTime;
	float fJumpValue = 1.3f * m_fJumpTime;
	float fJumpPower = 0.6f;

	m_xmf4x4World._42 += fJumpPower - fJumpValue;
	m_xmf3Position.y += fJumpPower - fJumpValue;

	if (m_xmf4x4World._42 < GetTerrainHeight())
	{
		m_fJumpTime = 0.f;
		m_bJump = false;

		m_xmf4x4World._42 = GetTerrainHeight();
		m_xmf3Position.y = GetTerrainHeight();

		m_nAnimNum = ANIM_JUMP_END;
		m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
	}
}

void CRanger::SetWeapon()
{
	if (m_pWeapon)
	{
		XMMATRIX xmmtxFrame = this->GetAnimater()->GetCurAnimationInfo()->GetCurFrameMtx(this->GetAnimater()->GetRHand());
		XMMATRIX xmmtxFinal = xmmtxFrame * this->GetAnimater()->GetMeshOffsetMtx() * this->GetWorldMtx();

		XMMATRIX xmmtxRotX = XMMatrixRotationX(90.f);
		XMMATRIX xmmtxRotZ = XMMatrixRotationZ(90.f);
		XMMATRIX xmmtxScale = XMMatrixScaling(10.f, 10.f, 10.f);

		m_pWeapon->SetWorldMtx(xmmtxScale* xmmtxRotX * xmmtxRotZ * xmmtxFinal);
	}
}

void CRanger::UpdateSkill()
{
	if (ANIM_SKILL1_CHARGING == m_nAnimNum)
	{
		if (true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone())
		{
			m_nAnimNum = ANIM_SKILL1_FIRE;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
		}
		return;
	}
	if (ANIM_SKILL4_START == m_nAnimNum)
	{
		if (true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone())
		{
			m_nAnimNum = ANIM_SKILL4_FIRE;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
		}
		return;
	}



	// ���� ������ IDLE��
	if (ANIM_JUMP_END == m_nAnimNum
		|| m_bSkill == true) {
		if (true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone()) {
			if (ANIM_HIT_F == m_nAnimNum) m_bDamaged = false;
			m_nAnimNum = ANIM_IDLE;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
			m_bSkill = false;
		}
	}

	if (true == m_bSelRangeMode)
	{
		CCamera* pCam = CCameraMgr::GetInstance()->GetCamera(CAM_FREE);
		pCam->SetFixCamera(false);

		if (true == m_bSkill && INPUTMGR->MouseLeftDown())
		{
			m_nAnimNum = ANIM_SKILL2_FIRE;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
			m_bSelRangeMode = false;
			pCam->SetFixCamera(true);
		}
		if (true == m_bSkill && INPUTMGR->MouseRightDown())
		{
			m_nAnimNum = ANIM_IDLE;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
			m_bSkill = false;
			m_bSelRangeMode = false;
			pCam->SetFixCamera(true);
		}
	}
}

void CRanger::RegistToContainer() {
	CGameObject::RegistToContainer();
	if (m_pWeapon) m_pWeapon->RegistToContainer();
}

void CRanger::PhisicsLogic(map<utag, list<CGameObject*>>& mlpObject, float fDeltaTime)
{
	for (auto pBoss : mlpObject[UTAG_BOSS1]) {
		if (true == IsCollision(pBoss))
		{
			//m_bDamaged = true;
			CEffectMgr::GetInstance()->Play_Effect(L"TestBlood", XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 2.f, m_xmf3Position.z, 1.f),
				XMVectorSet(0.f, 0.f, 0.f, 0.f), XMVectorSet(1.f, 1.f, 0.f, 1.f));

			//m_nAnimNum = ANIM_HIT_F;
			//m_pAnimater->SetCurAnimationIndex(m_nAnimNum);

			break;
		}
	}
	for (auto pObj : mlpObject[UTAG_COLLISION]) {
		if (true == IsCollision(pObj))
		{
			CEffectMgr::GetInstance()->Play_Effect(L"TestBlood", XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 2.f, m_xmf3Position.z, 1.f),
				XMVectorSet(0.f, 0.f, 0.f, 0.f), XMVectorSet(1.f, 1.f, 0.f, 1.f));

			break;
		}
	}
	//CAtlArray<CGameObject*>* lpCollsion;
	//pUtagObjectAtlMap->Lookup(utag::UTAG_COLLISION, lpCollsion);
	//// move player to mapmesh
	//
	//pUtagObjectAtlMap->Lookup(utag::UTAG_BOSS1, lpCollsion);
	//size_t iSize = lpCollsion->GetCount();
	//if (false == m_bDamaged) {
	//	for (size_t i = 0; i < iSize; ++i)
	//	{
	//		//if (false == (*lpCollsion)[i]->GetActive()) continue;
	//		if (true == IsCollision((*lpCollsion)[i]))
	//		{
	//			m_bDamaged = true;
	//			CEffectMgr::GetInstance()->Play_Effect(L"TestBlood", XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 2.f, m_xmf3Position.z, 1.f),
	//				XMVectorSet(0.f, 0.f, 0.f, 0.f), XMVectorSet(1.f, 1.f, 0.f, 1.f));
	//
	//			m_nAnimNum = ANIM_HIT_F;
	//			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
	//
	//			break;
	//		}
	//	}
	//}
}

CRanger::CRanger(string name, tag t, bool bSprit, CGameObject* pWeapon, INT slot_id)
	: CGameObject(name, t)
	, m_bSprit(bSprit)
	, m_pWeapon(pWeapon)
	, m_SLOT_ID(slot_id)
{
	m_fSpeed = 14.f;

	vector<CGameObject*> vecSkill;
	for (int i = 0; i < 10; ++i)
	{
		CGameObject* pObject = new CElfSkillArrow("Arrow1", TAG_DYNAMIC_OBJECT);
		pObject->SetActive(false);
		pObject->SetUTag(utag::UTAG_ARROW);
		pObject->Begin();
		pObject->SetPosition(XMVectorSet(0, 0, 0, 1));
		pObject->SetScale(XMVectorSet(5, 5, 5, 1));
		UPDATER->GetSpaceContainer()->AddObject(pObject);
		vecSkill.push_back(pObject);
	}
	m_mapSkill["Arrow1"] = vecSkill;
}

CRanger::~CRanger()
{
}

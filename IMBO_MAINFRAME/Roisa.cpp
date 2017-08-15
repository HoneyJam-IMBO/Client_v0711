#include "stdafx.h"
#include "Roisa.h"
#include "BossMeteo.h"
#include "BossExplosion.h"
#include "Blizzard.h"
#include "BlizzardEfc.h"


void CRoisa::ShootMeteo(float fAngle)
{
	size_t iArraySize = m_mapSkill["Meteo"].size();
	for (size_t i = 0; i < iArraySize; ++i) {
		if (false == m_mapSkill["Meteo"][i]->GetActive()) {
			m_mapSkill["Meteo"][i]->SetPosition(XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 4.f, m_xmf3Position.z, 1.f));
			m_mapSkill["Meteo"][i]->Rotate(XMMatrixRotationY(fAngle));
			float fSize = 1.5f;
			m_fMyAngle == fAngle ? fSize = 1.f : fSize = 1.5f;
			m_fMyAngle == fAngle ? m_mapSkill["Meteo"][i]->SetStrong(false) : m_mapSkill["Meteo"][i]->SetStrong(true);
			m_mapSkill["Meteo"][i]->SetScale(XMVectorSet(fSize, fSize, fSize, 1.f));
			m_mapSkill["Meteo"][i]->SetActive(true);

			//((CElfSkillArrow*)m_mapSkill["Arrow1"][i])->GetTrail()->SetPosition(XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 3.f, m_xmf3Position.z, 1.f));
			break;
		}
	}
}

void CRoisa::ShootExplosion()
{
	size_t iArraySize = m_mapSkill["Explosion"].size();
	for (size_t i = 0; i < iArraySize; ++i) {

		XMVECTOR xmDir = XMVectorSet(0.f, 0.f, 1.f, 1.f);
		xmDir = XMVector3TransformNormal(xmDir, XMMatrixRotationY((XM_2PI / iArraySize) * i));
		XMFLOAT3	xmPos;
		XMStoreFloat3(&xmPos, XMLoadFloat3(&m_xmf3Position) + xmDir * (rand() % 50 + 20));
		int randPosY = (rand() % 50 + 150);
		m_mapSkill["Explosion"][i]->SetPosition(XMVectorSet(xmPos.x, xmPos.y + randPosY, xmPos.z, 1.f));
		m_mapSkill["Explosion"][i]->Rotate(XMMatrixRotationY(XMConvertToRadians(rand() %360)));
		m_mapSkill["Explosion"][i]->SetScale(XMVectorSet(4.f, 4.f, 4.f, 1.f));
		m_mapSkill["Explosion"][i]->SetActive(true);

		CEffectMgr::GetInstance()->Play_Effect(L"boss2_sk2_efc", XMVectorSet(xmPos.x, 0.5f, xmPos.z, 1.f),
			XMVectorSet(0.f, 0.f, 0.f, 0.f), XMVectorSet(2.f, 2.f, 0.f, 1.f));

		//((CElfSkillArrow*)m_mapSkill["Arrow1"][i])->GetTrail()->SetPosition(XMVectorSet(m_xmf3Position.x, m_xmf3Position.y + 3.f, m_xmf3Position.z, 1.f));
	}
}

void CRoisa::ShootBlizzard()
{
	string strName = "Blizzard";
	size_t iArraySize = m_mapSkill[strName].size();
	for (size_t i = 0; i < iArraySize; ++i) {
		if (false == m_mapSkill[strName][i]->GetActive())
		{
			m_mapSkill[strName][i]->SetPosition(XMVectorSet(m_xmf3Position.x, m_xmf3Position.y, m_xmf3Position.z, 1.f));
			//m_mapSkill[strName][i]->Rotate(XMMatrixRotationY(m_fAngleY));
			m_mapSkill[strName][i]->SetActive(true);
			break;
		}
	}

	iArraySize = m_mapSkill["Blizzard_efc"].size();
	for (size_t i = 0; i < iArraySize; ++i) {
		XMVECTOR xmDir = XMVectorSet(0.f, 0.f, 1.f, 1.f);
		xmDir = XMVector3TransformNormal(xmDir, XMMatrixRotationY((XM_2PI / iArraySize) * i));
		XMFLOAT3	xmPos;
		XMStoreFloat3(&xmPos, XMLoadFloat3(&m_xmf3Position) + xmDir * (rand() % 50 + 20));
		m_mapSkill["Blizzard_efc"][i]->SetPosition(XMVectorSet(xmPos.x, xmPos.y, xmPos.z, 1.f));
		m_mapSkill["Blizzard_efc"][i]->SetScale(XMVectorSet(7.f, 7.f, 7.f, 1.f));
		m_mapSkill["Blizzard_efc"][i]->Rotate(XMMatrixRotationY(XMConvertToRadians( rand()%360)));
		m_mapSkill["Blizzard_efc"][i]->SetActive(true);
	}
}

CRoisa::CRoisa(string name, tag t, CGameObject* pTarget)
	: CGameObject(name, t)
{
	m_pTempPlayer = pTarget;
	m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
	m_xmf4RimColor = XMFLOAT4(1.f, 0.f, 1.f, 1.f);


	vector<CGameObject*> vecSkill;
	for (int i = 0; i < 18; ++i)
	{
		CGameObject* pObject = new CBossMeteo("Meteo", TAG_DYNAMIC_OBJECT);
		pObject->SetActive(false);
		pObject->SetUTag(UTAG_BOSS2);
		pObject->Begin();
		pObject->SetPosition(XMVectorSet(0, 0, 0, 1));
		UPDATER->GetSpaceContainer()->AddObject(pObject);
		vecSkill.push_back(pObject);
	}
	m_mapSkill["Meteo"] = vecSkill;

	vector<CGameObject*> vecSkill2;
	for (int i = 0; i < 36; ++i)
	{
		CGameObject* pObject = new CBossExplosion("boss2_sk2", TAG_STATIC_OBJECT);
		pObject->SetActive(false);
		pObject->SetUTag(UTAG_BOSS2);
		pObject->Begin();
		pObject->SetPosition(XMVectorSet(0, 0, 0, 1));
		UPDATER->GetSpaceContainer()->AddObject(pObject);
		vecSkill2.push_back(pObject);
	}
	m_mapSkill["Explosion"] = vecSkill2;

	vector<CGameObject*> vecSkill3;
	for (int i = 0; i < 2; ++i)
	{
		CGameObject* pObject = new CBlizzard("Boss2_sk3", TAG_STATIC_OBJECT);
		pObject->SetActive(false);
		pObject->SetUTag(UTAG_BOSS2);
		pObject->Begin();
		pObject->SetPosition(XMVectorSet(0, 0, 0, 1));
		UPDATER->GetSpaceContainer()->AddObject(pObject);
		vecSkill3.push_back(pObject);
	}
	m_mapSkill["Blizzard"] = vecSkill3;

	vector<CGameObject*> vecSkill3_2;
	for (int i = 0; i < 36; ++i)
	{
		int iRand = i % 3;
		CGameObject* pObject;
		if (iRand == 0) { pObject = new CBlizzardEfc("boss2_sk3_efc1", TAG_STATIC_OBJECT); }
		else if (iRand == 1) { pObject = new CBlizzardEfc("boss2_sk3_efc2", TAG_STATIC_OBJECT); }
		else if (iRand == 2) { pObject = new CBlizzardEfc("boss2_sk3_efc3", TAG_STATIC_OBJECT); }
		pObject->SetActive(false);
		pObject->SetUTag(UTAG_BOSS2);
		pObject->Begin();
		pObject->SetPosition(XMVectorSet(0, 0, 0, 1));
		UPDATER->GetSpaceContainer()->AddObject(pObject);
		vecSkill3_2.push_back(pObject);
	}
	m_mapSkill["Blizzard_efc"] = vecSkill3_2;
}

CRoisa::~CRoisa()
{

}

void CRoisa::Animate(float fTimeElapsed)
{
	if (false == m_bSkill)
		m_fAccSkillTime += fTimeElapsed;

	CGameObject::MappingRimLight(fTimeElapsed);

	UpdatePattern(fTimeElapsed);
	//Move(XMVector3Normalize(XMLoadFloat3(&m_f3Diraction)), (m_fSpeed)* fTimeElapsed);

	if (m_pAnimater) m_pAnimater->Update(TIMEMGR->GetTimeElapsed());
	ActionMoveProc();

	//모든 컴포넌트를 돌면서 Update실행
	for (auto i : m_mapComponents) {
		i.second->Update(fTimeElapsed);
	}

	DEBUGER->RegistCoordinateSys(GetWorldMtx());
}

void CRoisa::RegistToContainer()
{
	CGameObject::RegistToContainer();
}

bool CRoisa::GetDemaged(int iDemege) {

	return false;
}

void CRoisa::PhisicsLogic(map<utag, list<CGameObject*>>& mlpObject, float fDeltaTime)
{
	for (auto pArrow : mlpObject[utag::UTAG_ARROW]) {
		//내가쏜 화살만 데미지를 입음
		if (false == pArrow->GetActive()) continue;
		if (true == IsCollision(pArrow))
		{
			GetDemaged(100.f);
			pArrow->DisappearSkill();
			break;
		}
	}
	for (auto pArrow : mlpObject[utag::UTAG_OTHERPLAYER_ARROW]) {

		if (false == pArrow->GetActive()) continue;
		if (true == IsCollision(pArrow))
		{
			pArrow->DisappearSkill();
			break;
		}
	}
}

void CRoisa::GetSkilled(int nSkill)
{
	int slot_id = 5;
}

void CRoisa::UpdatePattern(float fTimeElapsed)
{
	m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
	float fDistance = 0.f;
	if (nullptr != m_pTempPlayer)
	{
		XMFLOAT3 xmf3PlayerPos, xmf3LasserPos;
		XMStoreFloat3(&xmf3PlayerPos, m_pTempPlayer->GetPosition());
		XMStoreFloat3(&xmf3LasserPos, XMLoadFloat3(&m_xmf3Position));
		xmf3PlayerPos.y = 0.f;		xmf3LasserPos.y = 0.f;

		XMStoreFloat3(&m_f3Diraction, XMLoadFloat3(&xmf3PlayerPos) - XMLoadFloat3(&xmf3LasserPos));
		XMFLOAT3 xmf3Distance;
		XMStoreFloat3(&xmf3Distance, XMVector3Length(XMLoadFloat3(&m_f3Diraction)));
		XMStoreFloat3(&m_f3Diraction, XMVector4Normalize(XMLoadFloat3(&m_f3Diraction)));

		XMFLOAT3 xmf3DotValue;
		XMStoreFloat3(&xmf3DotValue, XMVector3Dot(XMVectorSet(0.f, 0.f, 1.f, 0.f), XMLoadFloat3(&m_f3Diraction)));
		float fDirAngle = acosf(xmf3DotValue.x);
		if (m_f3Diraction.x < 0.f) fDirAngle = XM_PI * 2.f - fDirAngle;
		m_fMyAngle = fDirAngle;

		if (true == m_bSkill)
		{
			// 스킬중 해야하는 것
			if (BOSS1_ANI_SKILL2 == m_nAnimNum)
			{

			}
			else if (BOSS1_ANI_SKILL3 == m_nAnimNum)
			{

			}

			// 스킬이 끝났을경우 초기화
			if (true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone())
			{
				m_nAnimNum = BOSS2_ANI_IDLE;
				m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
				m_bSkill = false;
				m_fSk2Time = 0.f;
			}
			return;
		}
		else
			SetRotation(DirectX::XMMatrixRotationY(fDirAngle));

		///*test*/m_nPatternNum = 3;
		// x초마다 스킬 발동
		if (m_fAccSkillTime > 7.f)
		{
			m_fAccSkillTime = 0.f;
			m_bSkill = true;

			switch (m_nPatternNum) {
			case 0:
				m_nAnimNum = BOSS2_ANI_SKILL1;
				ShootMeteo(m_fMyAngle);
				break;
			case 1:
				m_nAnimNum = BOSS2_ANI_SKILL2;
				for (int i = 0; i < 18; ++i)
				{
					ShootMeteo((XM_2PI / 18.f) * i);
				}
				break;
			case 2:
				m_nAnimNum = BOSS2_ANI_SKILL3;
				ShootExplosion();
				break;
			case 3:
				m_nAnimNum = BOSS2_ANI_SKILL4;
				ShootBlizzard();
				break;
	/*		case 4:
				m_nAnimNum = BOSS2_ANI_SKILL5;
				break;
			case 5:
				m_nAnimNum = BOSS2_ANI_SKILL8;
				break;*/
			}
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
			++m_nPatternNum;
			if (m_nPatternNum == 4) m_nPatternNum = 0;
		}
	}
}




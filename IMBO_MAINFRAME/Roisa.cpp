#include "stdafx.h"
#include "Roisa.h"


CRoisa::CRoisa(string name, tag t, CGameObject* pTarget)
	: CGameObject(name, t)
{
	//m_pTempPlayer = pTarget;
	m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
}

CRoisa::~CRoisa()
{
}

void CRoisa::Animate(float fTimeElapsed)
{
	//if (false == m_bAttack && false == m_bSkill)
	//	m_fAccSkillTime += fTimeElapsed;

	//UpdatePattern(fTimeElapsed);
	Move(XMVector3Normalize(XMLoadFloat3(&m_f3Diraction)), (m_fSpeed)* fTimeElapsed);

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

bool CRoisa::GetDemaged(int iDemege){

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
}




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
	CGameObject::Animate(fTimeElapsed);
}

void CRoisa::RegistToContainer()
{
	CGameObject::RegistToContainer();
}

void CRoisa::PhisicsLogic(map<utag, list<CGameObject*>>& mlpObject, float fDeltaTime)
{
	for (auto pArrow : mlpObject[utag::UTAG_ARROW]) {

		if (false == pArrow->GetActive()) continue;
		if (true == IsCollision(pArrow))
		{
			//XMStoreFloat3(&m_xmf3Position, XMLoadFloat3(&m_xmf3Position) + ((XMVector3Normalize(m_xmvShift) * -m_fSpeed) * fDeltaTime));
			//SetPosition(XMLoadFloat3(&m_xmf3Position));
			pArrow->DisappearSkill();
			break;
		}
	}
}

void CRoisa::UpdatePattern(float fTimeElapsed)
{
}




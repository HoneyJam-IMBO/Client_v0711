#include "stdafx.h"
#include "LesserGiant.h"


CLesserGiant::CLesserGiant(string name, tag t)
	: CGameObject(name, t)
{
}

CLesserGiant::~CLesserGiant()
{
}

void CLesserGiant::Animate(float fTimeElapsed)
{
	if (m_pAnimater) m_pAnimater->Update(TIMEMGR->GetTimeElapsed() * 0.2f);
	CGameObject::Animate(fTimeElapsed);
}

void CLesserGiant::RegistToContainer()
{
	CGameObject::RegistToContainer();
}

void CLesserGiant::PhisicsLogic(map<utag, list<CGameObject*>>& mlpObject, float fDeltaTime)
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


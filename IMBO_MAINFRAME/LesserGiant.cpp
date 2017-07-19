#include "stdafx.h"
#include "LesserGiant.h"


CLesserGiant::CLesserGiant(string name, tag t, CGameObject* pTarget)
	: CGameObject(name, t)
{
	m_pTempPlayer = pTarget;
	m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
}

CLesserGiant::~CLesserGiant()
{
}

void CLesserGiant::Animate(float fTimeElapsed)
{

	if(false == m_bAttack && false == m_bSkill)
		m_fAccSkillTime += fTimeElapsed;

	UpdatePattern(fTimeElapsed);
	Move(XMVector3Normalize(XMLoadFloat3(&m_f3Diraction)), (m_fSpeed) * fTimeElapsed);

	if (m_pAnimater) m_pAnimater->Update(TIMEMGR->GetTimeElapsed());
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

void CLesserGiant::UpdatePattern(float fTimeElapsed)
{
	m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
	float fDistance = 0.f;
	m_fSpeed = 5.f;
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

		if (true == m_bSkill)
		{
			if( BOSS1_ANI_SKILL2 == m_nAnimNum)
				m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
			else if (BOSS1_ANI_SKILL3 == m_nAnimNum)
			{
				m_fSpeed = 0.f;
				m_fSk2Time += fTimeElapsed;
				if (m_fSk2Time < 3.3f &&m_fSk2Time > 2.3f)
				{
					XMStoreFloat3(&m_f3Diraction, XMLoadFloat3(&m_xmf3Sk2Dir));
					m_fSpeed = m_fSk2Speed * 0.9f;
				}
				else if(m_fSk2Time >= 3.3f)
				{
					m_fSpeed = 0.f;
				}
			}

			if (true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone())
			{
				m_nAnimNum = BOSS1_ANI_WALK;
				m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
				m_bSkill = false;
				m_fSk2Time = 0.f;
			}
			return;
		}

		if (m_fAccSkillTime > 2.f)
		{
			m_fAccSkillTime = 0.f;
			m_bSkill = true;
			SetRotation(DirectX::XMMatrixRotationY(fDirAngle));

			switch (m_nPatternNum) {
			case 0:
				m_nAnimNum = BOSS1_ANI_SKILL2;
				m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
				break;
			case 1:
				m_nAnimNum = BOSS1_ANI_SKILL3;
				m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
				m_fSk2Speed = xmf3Distance.x;
				XMStoreFloat3(&m_xmf3Sk2Dir, XMLoadFloat3(&m_f3Diraction));
				break;
			}			
			++m_nPatternNum;
			if (m_nPatternNum == 2) m_nPatternNum = 0;
		}
		
		// 거리가 10 이하면 스킬1 시전
		if (xmf3Distance.x < 7.f){
			if (true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone()){		// 스킬1 할때마다 위치 찾기.
				SetRotation(DirectX::XMMatrixRotationY(fDirAngle));
			}
			m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
			m_nAnimNum = BOSS1_ANI_SKILL1;
			m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
			m_bAttack = true;
		}
		else {
			if (true == m_bAttack)
			{
				m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
				if (true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone())
				{
					m_nAnimNum = BOSS1_ANI_WALK;
					m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
					m_bAttack = false;
				}
				return;
			}
			SetRotation(DirectX::XMMatrixRotationY(fDirAngle));
		}
	}

	//if (true == m_bAttack && true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone()) {
	//	m_nAnimNum = BOSS1_ANI_WALK;
	//	m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
	//	m_bAttack = false;
	//}
}


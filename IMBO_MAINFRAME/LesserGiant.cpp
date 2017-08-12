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
	ActionMoveProc();

	//모든 컴포넌트를 돌면서 Update실행
	for (auto i : m_mapComponents) {
		i.second->Update(fTimeElapsed);
	}

	DEBUGER->RegistCoordinateSys(GetWorldMtx());
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
	if (false == m_bCollision) {
		for (auto pPlayer : mlpObject[utag::UTAG_PLAYER]) {
			//pPlayer->Demaged();
			switch (m_nAnimNum) {
			case BOSS1_ANI_SKILL1:
				if (SkillCollision(pPlayer)) {
					pPlayer->GetDemaged(100.f);
					m_bCollision = true;
				}
				break;
			case BOSS1_ANI_SKILL2:
				if (SkillCollision(pPlayer)) {
					pPlayer->GetDemaged(100.f);
					m_bCollision = true;
				}
				break;
			case BOSS1_ANI_SKILL3:
				if (SkillCollision(pPlayer)) {
					pPlayer->GetDemaged(100.f);
					m_bCollision = true;
				}
				break;
			case BOSS1_ANI_SKILL4:
				if (SkillCollision(pPlayer)) {
					pPlayer->GetDemaged(100.f);
					m_bCollision = true;
				}
				break;
			default:
				break;
			}
		}
	}
	m_fCollisionTime += fDeltaTime;
	m_fAnimTime += fDeltaTime;
	if (m_fCollisionTime > 2.f) {
		m_fCollisionTime = 0.f;
		m_bCollision = false;//2초에 한번씩 다시 맞게 한다.
	}
}

void CLesserGiant::UpdatePattern(float fTimeElapsed)
{
	if (m_bFirstAction) return;//첫번째 액션중이면 return
	m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
	if (m_pAnimater->GetCurAnimationIndex() == BOSS1_ANI_DYING || m_pAnimater->GetCurAnimationIndex() == BOSS1_ANI_DIE) {
		if (m_pAnimater->GetCurAnimationInfo()->GetLoopDone()) {
			m_pAnimater->SetCurAnimationIndex(BOSS1_ANI_DIE);
		}
		m_bCollision = true;
		return;
	}

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
			else if (BOSS1_ANI_SKILL4 == m_nAnimNum)
			{
				SetRotation(DirectX::XMMatrixRotationY(fDirAngle));
				m_fSpeed = 0.f;
				if (m_fAnimTime < 7.0f &&m_fAnimTime > 1.f)
				{
					//XMStoreFloat3(&m_f3Diraction, XMLoadFloat3(&m_xmf3Sk2Dir));
					m_fSpeed = m_fSk2Speed * 0.2f;
				}
				//else if (m_fAnimTime >= 7.3f)
				//{
				//	m_fSpeed = 0.f;
				//}
			}

			if (true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone())
			{
				m_nAnimNum = BOSS1_ANI_WALK;
				m_pAnimater->SetCurAnimationIndex(m_nAnimNum);
				ResetCollisionValue(XMFLOAT3(0, 0, 0), 0, 0, 0);
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
				if (m_pAnimater->SetCurAnimationIndex(m_nAnimNum)) ResetCollisionValue(XMFLOAT3(0, 1, 5), 4.1, 4.6, 5);
				break;
			case 1:
				m_nAnimNum = BOSS1_ANI_SKILL3;
				if (m_pAnimater->SetCurAnimationIndex(m_nAnimNum)) ResetCollisionValue(XMFLOAT3(0, 1, 5), 3.4, 4.5, 5);
				
				m_fSk2Speed = xmf3Distance.x;
				XMStoreFloat3(&m_xmf3Sk2Dir, XMLoadFloat3(&m_f3Diraction));
				break;

			case 2:
				m_nAnimNum = BOSS1_ANI_SKILL4;

				m_fSk2Speed = xmf3Distance.x;
				//XMStoreFloat3(&m_xmf3Sk2Dir, XMLoadFloat3(&m_f3Diraction));
				if (m_pAnimater->SetCurAnimationIndex(m_nAnimNum)) ResetCollisionValue(XMFLOAT3(0, 0, 0), 2, 7, 7);
				break;
			}			
			++m_nPatternNum;
			if (m_nPatternNum == 3) m_nPatternNum = 0;
		}
		
		// 거리가 10 이하면 스킬1 시전
		if (xmf3Distance.x < 7.f){
			if (true == m_pAnimater->GetCurAnimationInfo()->GetLoopDone()){		// 스킬1 할때마다 위치 찾기.
				SetRotation(DirectX::XMMatrixRotationY(fDirAngle));
				ResetCollisionValue(XMFLOAT3(0, 1, 5), 1, 1.7, 5);
			}
			m_f3Diraction = XMFLOAT3(0.f, 0.f, 0.f);
			m_nAnimNum = BOSS1_ANI_SKILL1;
			if(m_pAnimater->SetCurAnimationIndex(m_nAnimNum))ResetCollisionValue(XMFLOAT3(0,1,5), 1, 1.7, 5);
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

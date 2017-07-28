#include "stdafx.h"
#include "ElfSkillArrow.h"
#include "EffectMgr.h"

#include "ArrowTrail.h"

CElfSkillArrow::CElfSkillArrow(string name, tag t)
	:CGameObject(name, t)
{
	m_pArrowTrail = new CArrowTrail("Trail", tag::TAG_DYNAMIC_OBJECT);
	m_pArrowTrail->Begin();

}

CElfSkillArrow::~CElfSkillArrow()
{
}

void CElfSkillArrow::InitData()
{
	m_xmf3Position = XMFLOAT3(0.f, 0.f, 0.f);
	m_xmf3Rotate = XMFLOAT3(0.f, 0.f, 0.f);
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
	m_fAccTime = 0.f;
}
void CElfSkillArrow::DisappearSkill()
{
	CEffectMgr::GetInstance()->Play_Effect(L"SparkTest", XMVectorSet(m_xmf3Position.x, m_xmf3Position.y , m_xmf3Position.z, 1.f),
		XMVectorSet(0.f, 0.f, 0.f, 0.f), XMVectorSet(2.f, 2.f, 2.f, 1.f));

	m_bActive = false;
	InitData();
}

void CElfSkillArrow::SetActive(bool b)
{
	/*m_bActive = b;
	if (false == m_bActive)
	{
		DisappearSkill();
	}*/
}

bool CElfSkillArrow::Begin()
{
	
	CGameObject::Begin();
	return false;
}

void CElfSkillArrow::Initialize()
{
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
	// 크기 조정
	BoundingBox::CreateFromPoints(m_OriBoundingBox, XMVectorSet(+10.f, +10.f, +10.f, 0.f), XMVectorSet(-10.f, -10.f, -10.f, 0.f));
	
	XMStoreFloat4(&m_xmf4Quaternion, XMQuaternionIdentity());
}

void CElfSkillArrow::Animate(float fTimeElapsed)
{
	if (false == m_bActive) return;
	m_fAccTime += fTimeElapsed;
	if (m_fAccTime > 3.f){
		m_bActive = false;
		InitData();
	}
	//if (m_bActive != m_bActive) InitData();

	CGameObject::Animate(fTimeElapsed);

	XMStoreFloat3(&m_xmf3Position, XMLoadFloat3(&m_xmf3Position) + ((XMVector3Normalize(GetLook()) * 40.f) * fTimeElapsed));
	SetPosition(XMLoadFloat3(&m_xmf3Position));

	m_bAlive = m_bActive;
}

void CElfSkillArrow::RegistToContainer()
{
	m_pArrowTrail->RegistToContainer();
	CGameObject::RegistToContainer();
}

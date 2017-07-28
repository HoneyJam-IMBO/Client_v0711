#include "stdafx.h"
#include "ArrowTrail.h"



CArrowTrail::CArrowTrail(string name, tag t)
	:CGameObject(name, t)
{
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
	XMStoreFloat4(&m_xmf4Quaternion, XMQuaternionIdentity());
}

CArrowTrail::~CArrowTrail()
{
}

bool CArrowTrail::Begin()
{
	CGameObject::Begin();
	return false;
}

void CArrowTrail::Initialize()
{
}

void CArrowTrail::Animate(float fTimeElapsed)
{
	CGameObject::Animate(fTimeElapsed);
}

void CArrowTrail::RegistToContainer()
{
	CGameObject::RegistToContainer();
}

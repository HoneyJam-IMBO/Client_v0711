#pragma once
#include "GameObject.h"
class CRoisa :
	public CGameObject
{

private:
	float		m_fSpeed{ 0.f };
	UINT		m_nAnimNum{ 0 };
	XMFLOAT3	m_f3Diraction;

	float		m_fAccSkillTime{ 0.f };
	float		m_fSk2Time{ 0.f };
	float		m_fSk2Speed{ 0.f };
	XMFLOAT3	m_xmf3Sk2Dir;

	bool		m_bAttack{ false };
	bool		m_bSkill{ false };
	WORD		m_nPatternNum{ 1 };
public:
	virtual void Animate(float fTimeElapsed);
	virtual void RegistToContainer();

public:
	virtual void PhisicsLogic(map<utag, list<CGameObject*>>& mlpObject, float fDeltaTime);

private:
	void	UpdatePattern(float fTimeElapsed);

public:
	CRoisa(string name, tag t = tag::TAG_DEFAULT, CGameObject* pTarget = nullptr);
	virtual ~CRoisa();
};


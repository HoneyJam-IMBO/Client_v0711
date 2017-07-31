#pragma once
#include "GameObject.h"
#include "Trail.h"

class CElfSkillArrow :
	public CGameObject
{
public:
	CElfSkillArrow(string name, tag t, bool bStrong = false);
	~CElfSkillArrow();

private:
	bool	m_bAlive{ false };
	float	m_fAccTime{ 0.f };
	
	float	m_fTraceTime{ 0.f };
public:
	void InitData();
	virtual void DisappearSkill();

	virtual void SetActive(bool b);
public:
	bool Begin();
	void Initialize();
	virtual void Animate(float fTimeElapsed);


	void RegistToContainer();

private:
	//CGameObject* m_pArrowTrail{ nullptr };

	CTrail*		m_pArrowTrail{ nullptr };
	bool		m_bStrong{ false };
public:
	CTrail*		GetTrail() { return m_pArrowTrail; }
};


#pragma once
#include "GameObject.h"
class CElfSkillArrow :
	public CGameObject
{
public:
	CElfSkillArrow(string name, tag t);
	~CElfSkillArrow();

private:
	bool m_bAlive{ false };
	float m_fAccTime{ 0.f };
	
public:
	void InitData();
	virtual void DisappearSkill();

	virtual void SetActive(bool b);
public:
	bool Begin();
	void Initialize();
	virtual void Animate(float fTimeElapsed);


	void RegistToContainer();
};


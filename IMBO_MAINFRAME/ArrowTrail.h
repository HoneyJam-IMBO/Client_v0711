#pragma once
#include "GameObject.h"
class CArrowTrail :
	public CGameObject
{
public:
	CArrowTrail(string name, tag t);
	virtual ~CArrowTrail();

public:
	bool Begin();
	void Initialize();
	virtual void Animate(float fTimeElapsed);


	void RegistToContainer();
};


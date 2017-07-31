#pragma once
#include "GameObject.h"

enum SKILLMOTION{
	SKM_DEFAULT,
	SKM_1,
	SKM_2,
	SKM_3,
	SKM_4,
	SKM_END,
};

class CRanger :
	public CGameObject
{
public:
	bool Begin();
	virtual void Animate(float fTimeElapsed);
	virtual bool End();

private:
	void	KeyInput(float fDeltaTime);
	void	PushServerData(float x, float y, float z, float fAngleY, DWORD dwDirection, bool bJump);
	void	GetServerData(float fTimeElapsed);
	void	SetupAnimation(DWORD dwDirection);
	void	Jumping(float fDeltaTime);
	void	SetWeapon();

	void	UpdateSkill();
	void	ShootArrow();
private:
	bool	m_bSelRangeMode{ false };
private:
	float	m_fTranslateTime{ 0.f };
	int		m_iAnimNum{ 0 };
	bool	m_bSprit{ false };
	float	m_fJumpTime{ 0.f };

	bool	m_bDamaged{ false };
private:

	UINT	m_nAnimNum{ 0 };
	float	m_fAngleY{ 0.f };
	float	m_fAngleX{ 0.f };
	int		m_iPawnNum{ -1 };

	CGameObject*	m_pWeapon{ nullptr };

private:	//½ºÅ³
	map<string, vector<CGameObject*>>	m_mapSkill;

	//bool	m_bSkill[SKM_END];
	bool	m_bSkill{ false };

private:
	XMMATRIX	m_xmatrixRotate;
	XMVECTOR	m_xmvShift;

private:	//player data
	float m_fSpeed{ 0.f };
	INT m_SLOT_ID{ 0 };
public:
	void	SetPawNum(int iPawnNum) { m_iPawnNum = iPawnNum; }
	virtual void RegistToContainer();

public:
	virtual void PhisicsLogic(map<utag, list<CGameObject*>>& mlpObject, float fDeltaTime);

public:
	CRanger(string name, tag t = tag::TAG_DEFAULT, bool bSprit = false, CGameObject* pWeapon = nullptr, INT slot_id = 0);
	~CRanger();
};


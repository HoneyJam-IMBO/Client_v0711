#pragma once
#include "GameObject.h"
class CPawn :
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

private:
	float m_fTranslateTime{ 0.f };
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
	bool	m_bSkill{ false };

	float	m_fChargingTime{ 0.f };
private:
	map<string, vector<CGameObject*>>	m_mapSkill;

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
	virtual void PhisicsLogic(CAtlMap<utag, CAtlArray<CGameObject*>*>* pUtagObjectAtlMap, float fDeltaTime);

public:
	CPawn(string name, tag t = tag::TAG_DEFAULT, bool bSprit = false, CGameObject* pWeapon = nullptr, INT slot_id = 0);
	~CPawn();
};


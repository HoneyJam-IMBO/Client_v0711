#pragma once
#include "GameObject.h"

class CLesserGiant :
	public CGameObject
{

public:
	CGameObject*	m_pTempPlayer{ nullptr };

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

	bool SkillCollision(CGameObject* pPlayer);
	//�浹 ó���� �� 
	float m_fAnimTime{ 0.f };//���� �������� Animation time
	XMFLOAT3 m_xmf3CollisionOffset;//�浹ü�� ���� offset ��ġ
	float m_fMinCollisionOffsetTime{ 0.f };//�浹ü�� ������ �ð�
	float m_fMaxCollisionOffsetTime{ 0.f };//�浹ü�� ������ �ð�
	bool m_bCollision{ false };//�浹�� �ѹ��� �Ҳ��ϱ�. .
	float m_fRadius{ 0.f };
	void ResetCollisionValue(XMFLOAT3 xmf3CollisionOffset, float fMin, float fMax, float fRadius) {
		m_xmf3CollisionOffset = xmf3CollisionOffset;
		m_fMinCollisionOffsetTime = fMin;
		m_fMaxCollisionOffsetTime = fMax;
		m_fRadius = fRadius;
		m_fAnimTime = 0.f;
		m_bCollision = false;
	}
public:
	CLesserGiant(string name, tag t = tag::TAG_DEFAULT, CGameObject* pTarget = nullptr);
	~CLesserGiant();
};


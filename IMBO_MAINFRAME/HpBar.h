#pragma once
#include "UIObject.h"
class CHpBar :
	public CUIObject
{
public:
	CHpBar();
	~CHpBar();


public:
	static CHpBar* Create(XMVECTOR xyPos, XMVECTOR xySize);
	void	SetInfo(XMVECTOR xyPos, XMVECTOR xySize);

private:
	 CTexture*	m_pBarTexture;

private:
	int		m_nID{ 0 };
public:
	void	SetID(int nID) { m_nID = nID; }
	int		GetID() { return m_nID; }

public:
	virtual HRESULT Initialize();
	virtual int		Update(float fTimeElapsed);
	virtual void	Render();
	virtual void	Release();

private:
	void	SetParameter();
};


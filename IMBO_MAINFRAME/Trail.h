#pragma once
#include "GameObject.h"

struct TrailInfo {
	XMFLOAT4	m_xmf4Vtx[80];
	XMFLOAT4	m_xmf4Color;
};
class CTrail
{
public:
	CTrail(XMVECTOR xmf4Color, int mode, float followT);
	virtual ~CTrail();

private:
	CEffectRenderCont*			m_pEffectRenderCont;
	TrailInfo	m_tTrailInfo;
	CBuffer*	m_pCBuffer;
	TCHAR		m_szTexture[64];		//텍스처 이름

private:
	XMFLOAT4	m_xmf4Pos1;
	XMFLOAT4	m_xmf4Pos2;

	float		m_fTime{ 0.f };
	float		m_fAccTime{ 0.f };

	int			m_iMode{ 0 };		// 0- 따라가는, 1-검
	float		m_fFollowTime{ 0.f };

	bool		m_bRender{ true };

public:
	void	SetStartPos(XMVECTOR xmPos1, XMVECTOR xmPos2) { XMStoreFloat4(&m_xmf4Pos1, xmPos1);	XMStoreFloat4(&m_xmf4Pos2, xmPos2);};
	void	SetInitPos(XMVECTOR xmPos1, XMVECTOR xmPos2);
	void	SetTexName(CString name);
	void	SetRenderSwitch(bool bRender) { m_bRender = bRender; }

//	void	SetWorld(XMMATRIX xmworld) { XMStoreFloat4x4(&m_tTrailInfo.m_xmWorld, xmworld); }

private:
	void	SetParameter();
	void	SetLerpPos();

public:
	HRESULT Initialize();
	int		Update(float fTimeElapsed);
	void	Render();
	void	Release();
};


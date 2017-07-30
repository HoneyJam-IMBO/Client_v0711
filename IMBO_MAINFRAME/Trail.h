#pragma once
#include "GameObject.h"

struct TrailInfo {
	XMFLOAT4	m_xmf4Vtx[80];
	XMFLOAT4X4	m_xmWorld;
};
class CTrail
{
public:
	CTrail();
	virtual ~CTrail();

private:
	CEffectRenderCont*			m_pEffectRenderCont;
	TrailInfo	m_tTrailInfo;
	CBuffer*	m_pCBuffer;
	TCHAR		m_szTexture[64];		//텍스처 이름

private:
	XMFLOAT4	m_xmf4Pos1;
	XMFLOAT4	m_xmf4Pos2;

public:
	void	SetStartPos(XMVECTOR xmPos1, XMVECTOR xmPos2) { XMStoreFloat4(&m_xmf4Pos1, xmPos1);	XMStoreFloat4(&m_xmf4Pos2, xmPos2);};
	void	SetTexName(CString name);

	void	SetWorld(XMMATRIX xmworld) { XMStoreFloat4x4(&m_tTrailInfo.m_xmWorld, xmworld); }

private:
	void	SetParameter();

public:
	HRESULT Initialize();
	int		Update(float fTimeElapsed);
	void	Render();
	void	Release();
};


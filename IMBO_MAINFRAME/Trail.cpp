#include "stdafx.h"
#include "Trail.h"

CTrail::CTrail()
{
}

CTrail::~CTrail()
{
	Release();
}
void CTrail::SetTexName(CString name)
{
	_tcscpy_s(m_szTexture, _countof(m_szTexture), name);
}

HRESULT CTrail::Initialize()
{
	m_pEffectRenderCont = RENDERER->GetEffectRenderer();

	m_pCBuffer = CBuffer::CreateConstantBuffer(1, sizeof(TrailInfo), 5, BIND_VS | BIND_GS | BIND_PS, NULL);
	ZeroMemory(&m_tTrailInfo, sizeof(TrailInfo));
	//XMStoreFloat4x4(&m_tTrailInfo.m_matWorld, XMMatrixIdentity());

	return S_OK;
}

int CTrail::Update(float fTimeElapsed)
{
	if (m_pEffectRenderCont) {

		XMFLOAT3 xmf3NearPos;
		XMMATRIX matView, matProj;
		matView = CAMMGR->GetCamera(CAM_FREE)->GetViewMtx();
		matProj = CAMMGR->GetCamera(CAM_FREE)->GetProjectionMtx();

		XMStoreFloat3(&xmf3NearPos, XMVector3TransformCoord(XMLoadFloat3(&xmf3NearPos), matView * matProj));
		
		m_pEffectRenderCont->SetTrailRenderContainer(xmf3NearPos.z, this);
	}
	return 0;
}

void CTrail::Render()
{
	//CTexture* pTexture = RESOURCEMGR->GetTexture(TCHARToString(m_szTexture));
	CTexture* pTexture = RESOURCEMGR->GetTexture(TCHARToString(CString("Trail01")));
	pTexture->SetTextureSlot(5);
	//CResourceManager::GetInstance();

	pTexture->UpdateShaderState();
	pTexture->SetShaderState();
	SetParameter();

	GLOBALVALUEMGR->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	GLOBALVALUEMGR->GetDeviceContext()->Draw(1, 0);

	//ÇØÁ¦
	pTexture->CleanShaderState();
	m_pCBuffer->CleanShaderState();
}

void CTrail::Release()
{
}

void CTrail::SetParameter()
{
	for (int i = 29; i > -1; i -= 10)
	{
		m_tTrailInfo.m_xmf4Vtx[i + 10] = m_tTrailInfo.m_xmf4Vtx[i];
		m_tTrailInfo.m_xmf4Vtx[i + 50] = m_tTrailInfo.m_xmf4Vtx[i + 40];
	}

	m_tTrailInfo.m_xmf4Vtx[9]	= m_tTrailInfo.m_xmf4Vtx[0];
	m_tTrailInfo.m_xmf4Vtx[49]	= m_tTrailInfo.m_xmf4Vtx[40];

	m_tTrailInfo.m_xmf4Vtx[0]	= m_xmf4Pos1;
	m_tTrailInfo.m_xmf4Vtx[40]	= m_xmf4Pos2;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (0 == i)
			{
				if (0 == j)		continue;
				XMStoreFloat4(&m_tTrailInfo.m_xmf4Vtx[i * 10 + j],
					XMVectorCatmullRom(XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[0]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[0]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[9]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[19]),
						(float)(j) * 0.125f));

				XMStoreFloat4(&m_tTrailInfo.m_xmf4Vtx[i * 10 + j + 40],
					XMVectorCatmullRom(XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[9 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[19 + 40]),
						(float)(j) * 0.125f));
			}
			else if (1 == i)
			{
				XMStoreFloat4(&m_tTrailInfo.m_xmf4Vtx[i * 10 + j],
					XMVectorCatmullRom(XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[0]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[9]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[19]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[29]),
						(float)(j) * 0.125f));

				XMStoreFloat4(&m_tTrailInfo.m_xmf4Vtx[i * 10 + j + 40],
					XMVectorCatmullRom(XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[0 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[9 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[19 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[29 + 40]),
						(float)(j) * 0.125f));
			}
			else if (2 == i)
			{
				XMStoreFloat4(&m_tTrailInfo.m_xmf4Vtx[i * 10 + j ],
					XMVectorCatmullRom(XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[9]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[19]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[29]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[39]),
						(float)(j) * 0.125f));

				XMStoreFloat4(&m_tTrailInfo.m_xmf4Vtx[i * 10 + j + 40],
					XMVectorCatmullRom(XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[9 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[19 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[29 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[39 + 40]),
						(float)(j) * 0.125f));
			}
			else if (3 == i)
			{
				XMStoreFloat4(&m_tTrailInfo.m_xmf4Vtx[i * 10 + j ],
					XMVectorCatmullRom(XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[19]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[29]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[39]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[39]),
						(float)(j) * 0.125f));

				XMStoreFloat4(&m_tTrailInfo.m_xmf4Vtx[i * 10 + j + 40],
					XMVectorCatmullRom(XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[19 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[29 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[39 + 40]),
						XMLoadFloat4(&m_tTrailInfo.m_xmf4Vtx[39 + 40]),
						(float)(j) * 0.125f));
			}
		}
	}

	TrailInfo* pdata = (TrailInfo*)m_pCBuffer->Map();

	for (int i = 0; i < 80; ++i)
	{
		pdata->m_xmf4Vtx[i] = m_tTrailInfo.m_xmf4Vtx[i];
	}
	pdata->m_xmWorld = m_tTrailInfo.m_xmWorld;

	m_pCBuffer->Unmap();
	m_pCBuffer->SetShaderState();
}

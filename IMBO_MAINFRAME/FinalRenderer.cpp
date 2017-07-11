#include "stdafx.h"
#include "FinalRenderer.h"


CFinalRenderer::CFinalRenderer()
{
}


CFinalRenderer::~CFinalRenderer()
{
}

HRESULT CFinalRenderer::Initialize()
{
	ResizeBuffer();
	m_pRenderShader = RESOURCEMGR->GetRenderShader("FinalPass");
	m_pMesh = RESOURCEMGR->GetMesh("DirectionalLight");
	return S_OK;
}

void CFinalRenderer::ResizeBuffer()
{
}

void CFinalRenderer::RenderFinalPass(ID3D11ShaderResourceView * pPostProcessSRV, ID3D11ShaderResourceView * pAlphaSRV,
	ID3D11ShaderResourceView * pSkyBoxSRV, ID3D11ShaderResourceView * pDistortion)
{
	m_pRenderShader->UpdateShaderState();
	m_pRenderShader->SetShaderState();


	GLOBALVALUEMGR->GetDeviceContext()->PSSetShaderResources(1, 1, &pPostProcessSRV);
	GLOBALVALUEMGR->GetDeviceContext()->PSSetShaderResources(2, 1, &pAlphaSRV);
	GLOBALVALUEMGR->GetDeviceContext()->PSSetShaderResources(3, 1, &pSkyBoxSRV);
	GLOBALVALUEMGR->GetDeviceContext()->PSSetShaderResources(4, 1, &pDistortion);


	// screen mesh render
	m_pMesh->Render(1);
	m_pRenderShader->CleanShaderState();


	ID3D11ShaderResourceView* pSRVnull[1] = { nullptr };
	GLOBALVALUEMGR->GetDeviceContext()->PSSetShaderResources(1, 1, pSRVnull);
	GLOBALVALUEMGR->GetDeviceContext()->PSSetShaderResources(2, 1, pSRVnull);
	GLOBALVALUEMGR->GetDeviceContext()->PSSetShaderResources(3, 1, pSRVnull);
	GLOBALVALUEMGR->GetDeviceContext()->PSSetShaderResources(4, 1, pSRVnull);

}

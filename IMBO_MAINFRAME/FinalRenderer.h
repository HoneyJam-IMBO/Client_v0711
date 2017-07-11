#pragma once
class CFinalRenderer
{
public:
	CFinalRenderer();
	~CFinalRenderer();

public:
	HRESULT Initialize();

private:
	CRenderShader*	m_pRenderShader{ nullptr };
	CMesh*			m_pMesh{ nullptr };
	CBuffer*		m_pBuffer{ nullptr };

public:
	void	ResizeBuffer();
	void	RenderFinalPass(ID3D11ShaderResourceView* pPostProcessSRV, ID3D11ShaderResourceView* pAlphaSRV, ID3D11ShaderResourceView* pSkyBoxSRV, ID3D11ShaderResourceView * pDistortion);

};


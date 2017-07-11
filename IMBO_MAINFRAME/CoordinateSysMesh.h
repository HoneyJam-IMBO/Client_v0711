#pragma once
#include "Mesh.h"


class CCoordinateSysMesh : public CMesh {

public:
	//----------------------------dxobject-----------------------------
	//----------------------------dxobject-----------------------------

	//---------------------------mesh----------------------------------
	//begin func
	virtual bool CreateVertexBuffer();
	virtual bool CreateIndexBuffer();
	//begin func
	//---------------------------mesh----------------------------------
private:
	//----------------------vertex buffers---------------------------
	ID3D11Buffer* m_pd3dPositionBuffer{ nullptr };
	ID3D11Buffer* m_pd3dNormalBuffer{ nullptr };
	ID3D11Buffer* m_pd3dUVBuffer{ nullptr };
	ID3D11Buffer* m_pd3dColorBuffer{ nullptr };
	//----------------------vertex buffers---------------------------

public:
	CCoordinateSysMesh();
	virtual ~CCoordinateSysMesh();
};
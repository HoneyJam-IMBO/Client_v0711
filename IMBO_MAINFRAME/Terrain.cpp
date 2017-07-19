#include "stdafx.h"
#include "Terrain.h"
#include "TerrainContainer.h"

bool CTerrain::Begin() {
	//object_id set
//	m_objectID = object_id::OBJECT_TERRAIN;

	if (m_pTerrainContainer->GetIsTool()) {
		CGameObject::Begin();
		return true;
	}
	else {
		XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
		XMStoreFloat4(&m_xmf4Quaternion, XMQuaternionIdentity());
		m_pRenderContainer = RCSELLER->GetRenderContainer("terrain");

		float fx = static_cast<float>(m_pTerrainContainer->GetSpaceContainer()->GetOneSpaceSize());
		float fy = static_cast<float>(m_pTerrainContainer->GetSpaceContainer()->GetSpaceSize());
		float fz = static_cast<float>(m_pTerrainContainer->GetSpaceContainer()->GetOneSpaceSize());
		BoundingBox::CreateFromPoints(m_OriBoundingBox, XMVectorSet(0.f, 0.f, 0.f, 0.f), XMVectorSet(fx, fy, fz, 0.f));

		return true;
	}
}
bool CTerrain::End() {

	return CGameObject::End();
}

void CTerrain::SetTerrainContainer(CTerrainContainer * pTerrainContainer){
	m_pTerrainContainer = pTerrainContainer;
}


#define OFFSET 5
bool CTerrain::CheckPickObject(XMVECTOR xmvWorldCameraStartPos, XMVECTOR xmvRayDir, float & distance) {
	float fHitDistance = FLT_MAX;
	float fNearHitDistance = FLT_MAX;
	bool bIntersection = false;

	XMMATRIX xmMtxViewInverse = UPDATER->GetCamera()->GetWorldMtx();
	XMVECTOR xmvWorldRayDir = xmvRayDir;
	float start_x = m_xmf3Position.x;
	float start_z = m_xmf3Position.z;
	auto pSpaceContainer = m_pTerrainContainer->GetSpaceContainer();
	int one_space_size = pSpaceContainer->GetOneSpaceSize();
	int loop_num = one_space_size / OFFSET;
	for (int i = 0; i < loop_num; ++i) {
		for (int j = 0; j < loop_num; ++j) {
			float pivot_x = start_x + i * OFFSET;
			float pivot_z = start_z + j * OFFSET;
			//0 0 
			XMVECTOR v0 = XMVectorSet(pivot_x, m_pTerrainContainer->GetHeight(XMFLOAT2(pivot_x, pivot_z)), pivot_z, 1.0f);
			//1 0
			XMVECTOR v1 = XMVectorSet(pivot_x + OFFSET, m_pTerrainContainer->GetHeight(XMFLOAT2(pivot_x + OFFSET, pivot_z)), pivot_z, 1.0f);
			//0 1
			XMVECTOR v2 = XMVectorSet(pivot_x, m_pTerrainContainer->GetHeight(XMFLOAT2(pivot_x, pivot_z + OFFSET)), pivot_z + OFFSET, 1.0f);
			//1 1
			XMVECTOR v3 = XMVectorSet(pivot_x + OFFSET, m_pTerrainContainer->GetHeight(XMFLOAT2(pivot_x + OFFSET, pivot_z + OFFSET)), pivot_z + OFFSET, 1.0f);

			if (TriangleTests::Intersects(xmvWorldCameraStartPos, xmvWorldRayDir, v0, v1, v2, fHitDistance)) {//ray�� �浹�ߴٸ�
				if (fNearHitDistance > fHitDistance) {//������ ���� ����� �༮�� ��
					fNearHitDistance = fHitDistance;
					distance = fHitDistance;//�� ������ ���� ����� ��ü ����
					bIntersection = true;
				}
			}
			if (TriangleTests::Intersects(xmvWorldCameraStartPos, xmvWorldRayDir, v1, v2, v3, fHitDistance)) {//ray�� �浹�ߴٸ�
				if (fNearHitDistance > fHitDistance) {//������ ���� ����� �༮�� ��
					fNearHitDistance = fHitDistance;
					distance = fHitDistance;//�� ������ ���� ����� ��ü ����
					bIntersection = true;
				}
			}
		}
	}
	return bIntersection;
}

CTerrain* CTerrain::CreateTerrain(CTerrainContainer * pTerrainContainer, int x, int y){
	CTerrain* pTerrain = new CTerrain;
	pTerrain->SetTerrainContainer(pTerrainContainer);
	pTerrain->Begin();
	pTerrain->SetPosition(XMVectorSet(x*pTerrainContainer->GetSpaceContainer()->GetOneSpaceSize(), 
		0.f, y*pTerrainContainer->GetSpaceContainer()->GetOneSpaceSize(), 0.f));
	pTerrainContainer->GetSpaceContainer()->AddObject(pTerrain);

	return pTerrain;
}

void CTerrain::LoadInfo()
{
}

CTerrain::CTerrain() : CGameObject("terrain", tag::TAG_TERRAIN) {

}
CTerrain::~CTerrain() {

}
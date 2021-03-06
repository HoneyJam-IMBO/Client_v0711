#pragma once

#include "GameObject.h"
#include "Camera.h"

class CSpaceContainer;


class CSpace : public CGameObject {
public:
	void Begin(CSpaceContainer* m_pSpaceContainer, UINT size, int lv, XMVECTOR pos);
	virtual bool End();

	virtual void Animate(float fTimeElapsed);
	virtual void PhisicsUpdate(float fTimeElapsed);
	virtual void PrepareRender( CCamera* pCamera, UINT renderFlag);
	void SetObejcts(int n, CGameObject** ppObjects);
	void AddObject(CGameObject* pObject);
	void RemoveObject(CGameObject* pObject);
	void RemoveObject(string name);

	void SetbRender(bool b) { m_bRender = b; }
	bool GetbRender() { return m_bRender; }
	//virtual void SetGlobalBufferInfo(void** ppMappedResources);

	//해당 space안의 lay 충돌 검사된 객체 중 가장 가장 가까운 객체
	CGameObject* PickObject(XMVECTOR xmvWorldCameraStartPos, XMVECTOR xmvRayDir, float& distance, UINT tag);
	map<tag, list<CGameObject*>>& GetmlpObject() { return m_mlpObject; }
	map<utag, list<CGameObject*>>& GetmlpCollisionObject() { return m_mlpCollisionObject; }
private:
	//자식 space 4개
	CSpace** m_ppChildSpace{ nullptr };
	UINT m_size{ 0 };//size
	int m_index{ -1 };//index -1은 오류이거나. brunch space들이다.
	bool m_bRender{ false };//해당 frame에 render를 했으면 true다.
	//AABB aabb;

	//객체들
	//map<tag, list<CGameObject*>> m_mlpObject;
	map<tag, list<CGameObject*>> m_mlpObject;
	map<utag, list<CGameObject*>> m_mlpCollisionObject;

	//space container
	CSpaceContainer* m_pSpaceContainer{ nullptr };

private:
	void OptimizePrepare(UINT renderFlag,  CCamera* pCamera);
public:
	CSpace();
	~CSpace();

};
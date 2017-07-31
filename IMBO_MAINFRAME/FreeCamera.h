#pragma once
#include "Camera.h"


class CFreeCamera :public CCamera{
public:
	//----------------------------dxobject-----------------------------
	virtual bool Begin();
	virtual bool End();

	virtual void UpdateShaderState();//CCamera::UpdateShaderState호출 꼭 해야한다. 
	//----------------------------dxobject-----------------------------


	//---------------------------------------카메라 조정---------------------------------
	//회전
	virtual void Rotate(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	//Ani 카메라 액션

	//----------------------------------------자주 불릴 함수들------------------------
	//player따라다니기
	virtual void Update(float fTimeElapsed);
	virtual void ProcessInput(float fTimeElapsed);
	//----------------------------------------자주 불릴 함수들------------------------
	//debug모드시 카메라 그리기 
	virtual void Render() {};
	//---------------------------------------카메라 조정---------------------------------

private:
	void CameraInputProcess(float fTimeDelta);
	void FixCamera();
	void CalcultateMouseMoveValue();

	virtual void CameraStartVibration(float fVibeYvalue, float fVibeSpeed) ;
	virtual void CameraVibration(float fTime);
	virtual void AttackZoomInOut(float fTime);


	POINT m_ptOldMousePos;

public:
	CFreeCamera();
	virtual ~CFreeCamera();

};
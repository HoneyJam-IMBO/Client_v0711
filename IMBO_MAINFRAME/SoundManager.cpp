#include "stdafx.h"
#include "SoundManager.h"

#pragma comment(lib, "../../Assets/import/FMOD/lib/fmod64_vc.lib")

System* CSoundManager::m_pSystem = nullptr;
map<string, stSoundInfo*> CSoundManager::m_mpSoundInfo;
map<string, stSoundInfo*> CSoundManager::m_mp3DSoundInfo;

void CSoundManager::Begin()
{
	m_pSystem->set3DNumListeners(1);//3d listener num

	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(
		FMOD_MAX_CHANNEL_WIDTH
		, FMOD_INIT_NORMAL
		, nullptr
	);

	Add_sound("../../Assets/Sound/game/bgm/bgm_aldenard.mp3", "bgm_aldenard", FMOD_LOOP_NORMAL | FMOD_2D);
	Add_sound("../../Assets/Sound/game/bgm/bgm_boss1_appear.wav", "bgm_boss1_appear", FMOD_LOOP_NORMAL | FMOD_2D);
	Add_sound("../../Assets/Sound/game/bgm/bgm_boss2_balcony.wav", "bgm_boss2_balcony", FMOD_LOOP_NORMAL | FMOD_2D);
	Add_sound("../../Assets/Sound/game/bgm/bgm_boss2_battle.mp3", "bgm_boss2_battle", FMOD_LOOP_NORMAL | FMOD_2D);
	Add_sound("../../Assets/Sound/game/bgm/bgm_boss2_cam.mp3", "bgm_boss2_cam", FMOD_LOOP_NORMAL | FMOD_2D);
	Add_sound("../../Assets/Sound/game/bgm/bgm_firsttown_battle.wav", "bgm_firsttown_battle", FMOD_LOOP_NORMAL | FMOD_2D);
	Add_sound("../../Assets/Sound/game/bgm/bgm_fly_loop1.mp3", "bgm_fly_loop1", FMOD_LOOP_NORMAL | FMOD_2D);
	Add_sound("../../Assets/Sound/game/bgm/bgm_fly_loop2.wav", "bgm_fly_loop2", FMOD_LOOP_NORMAL | FMOD_2D);
	Add_sound("../../Assets/Sound/game/bgm/bgm_gate_loop.wav", "bgm_gate_loop", FMOD_LOOP_NORMAL | FMOD_2D);
	Add_sound("../../Assets/Sound/game/bgm/bgm_victory.wav", "bgm_victory", FMOD_LOOP_NORMAL | FMOD_2D);

	//Add_3Dsound("../../Assets/Sound/bgm/bird_03", "bird_03", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	//Add_3Dsound("../../Assets/Sound/bgm/bird_04", "bird_04", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	//Add_3Dsound("../../Assets/Sound/bgm/cat_01", "cat_01", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	//Add_3Dsound("../../Assets/Sound/bgm/cat_02", "cat_02", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	//Add_3Dsound("../../Assets/Sound/bgm/env_bird_one", "env_bird_one", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	//Add_3Dsound("../../Assets/Sound/bgm/env_bird_two", "env_bird_two", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	//Add_3Dsound("../../Assets/Sound/bgm/env_bird_three", "env_bird_three", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	//Add_3Dsound("../../Assets/Sound/bgm/regina_camera_1", "regina_camera_1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	//Add_3Dsound("../../Assets/Sound/bgm/regina_camera_2", "regina_camera_2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	//Add_3Dsound("../../Assets/Sound/bgm/regina_camera_3", "regina_camera_3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);

	//boss1
	Add_3Dsound("../../Assets/Sound/game/boss1/boss1_die", "boss1_die", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss1/boss1_hurt", "boss1_hurt", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss1/boss1_skill1", "boss1_skill1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss1/boss1_skill2", "boss1_skill2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss1/boss1_skill3", "boss1_skill3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss1/boss1_skill4", "boss1_skill4", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	
	//boss2
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_die", "boss2_die", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_hurt", "boss2_hurt", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_skill1", "boss2_skill1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_skill2", "boss2_skill2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_skill3", "boss2_skill3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_skill4", "boss2_skill4", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_skill_sound1", "boss2_skill_sound1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_skill_sound2", "boss2_skill_sound2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_skill_sound3", "boss2_skill_sound3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/boss2/boss2_skill_sound4", "boss2_skill_sound4", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);

	//ranger
	Add_3Dsound("../../Assets/Sound/game/c0_ranger/ranger_attack", "ranger_attack", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c0_ranger/ranger_die", "ranger_die", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c0_ranger/ranger_hurt", "ranger_hurt", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c0_ranger/ranger_skill1", "ranger_skill1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c0_ranger/ranger_skill2", "ranger_skill2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c0_ranger/ranger_skill3", "ranger_skill3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c0_ranger/ranger_skill4", "ranger_skill4", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);

	//knight
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_attack", "knight_attack", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_die", "knight_die", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_hurt", "knight_hurt", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_skill1", "knight_skill1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_skill2", "knight_skill2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_skill3", "knight_skill3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_skill4", "knight_skill4", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_attack1", "knight_attack1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_attack2", "knight_attack2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c1_knight/knight_attack3", "knight_attack3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);

	//dementor
	Add_3Dsound("../../Assets/Sound/game/c2_dementor/dementor_attack", "dementor_attack", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c2_dementor/dementor_die", "dementor_die", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c2_dementor/dementor_hurt", "dementor_hurt", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c2_dementor/dementor_skill1", "dementor_skill1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c2_dementor/dementor_skill2", "dementor_skill2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c2_dementor/dementor_skill3", "dementor_skill3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c2_dementor/dementor_skill4", "dementor_skill4", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);

	//sister
	Add_3Dsound("../../Assets/Sound/game/c3_sister/sister_attack", "sister_attack", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c3_sister/sister_die", "sister_die", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c3_sister/sister_hurt", "sister_hurt", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c3_sister/sister_skill1", "sister_skill1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c3_sister/sister_skill2", "sister_skill2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c3_sister/sister_skill3", "sister_skill3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c3_sister/sister_skill4", "sister_skill4", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);

	//wizard
	Add_3Dsound("../../Assets/Sound/game/c4_wizard/wizard_attack", "wizard_attack", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_wizard/wizard_die", "wizard_die", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_wizard/wizard_hurt", "wizard_hurt", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_wizard/wizard_skill1", "wizard_skill1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_wizard/wizard_skill2", "wizard_skill2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_wizard/wizard_skill3", "wizard_skill3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_wizard/wizard_skill4", "wizard_skill4", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);

	//bard
	Add_3Dsound("../../Assets/Sound/game/c4_bard/bard_attack", "bard_attack", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_bard/bard_die", "bard_die", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_bard/bard_hurt", "bard_hurt", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_bard/bard_skill1", "bard_skill1", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_bard/bard_skill2", "bard_skill2", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_bard/bard_skill3", "bard_skill3", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);
	Add_3Dsound("../../Assets/Sound/game/c4_bard/bard_skill4", "bard_skill4", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);

	//other masic eff
	Add_3Dsound("../../Assets/Sound/game/other_eff/magic_healing_accept", "magic_healing_accept", FMOD_LOOP_OFF | FMOD_3D_LINEARROLLOFF);

}

void CSoundManager::End()
{
	for (auto& p : m_mpSoundInfo) {
		p.second->m_pSound->release();
	}

	m_pSystem->release();
	m_pSystem->close();
}

void CSoundManager::Add_sound(string sPath, string sName, UINT flag)
{
	if (m_mpSoundInfo.end() != m_mpSoundInfo.find(sName)) {//�ִٸ� �����
		m_mpSoundInfo.erase(sName);//�����
	}
	m_mpSoundInfo[sName] = new stSoundInfo;
	m_pSystem->createSound(
		sPath.c_str()
		, flag
		, nullptr
		, &m_mpSoundInfo[sName]->m_pSound
	);
}

void CSoundManager::Play_bgm(string sName)
{
	m_pSystem->playSound(m_mpSoundInfo[sName]->m_pSound
		, nullptr, false, &m_mpSoundInfo[sName]->m_pChannel);
}

void CSoundManager::Play_effect(string sName)
{
	m_pSystem->update();
	m_pSystem->playSound(m_mpSoundInfo[sName]->m_pSound
		, nullptr, false, nullptr);
}

void CSoundManager::Stop_bgm(string sName)
{
	bool bPlaying;
	m_mpSoundInfo[sName]->m_pChannel->isPlaying(&bPlaying);
	if (bPlaying)
		m_mpSoundInfo[sName]->m_pChannel->stop();
}

void CSoundManager::Add_3Dsound(string sPath, string sName, UINT flag)
{
	if (m_mp3DSoundInfo.end() != m_mp3DSoundInfo.find(sName)) {//�ִٸ� �����
		m_mp3DSoundInfo.erase(sName);//�����
	}
	flag = flag | FMOD_3D;//flag�� ������ 3D flag�߰�
	m_mp3DSoundInfo[sName] = new stSoundInfo;
	m_pSystem->createSound(
		sPath.c_str()
		, flag
		, nullptr
		, &m_mp3DSoundInfo[sName]->m_pSound
	);
}

void CSoundManager::Play_3Dsound(string sName, int nPoints, XMFLOAT3* pPoints, float fVolume, float fMin, float fMax)
{
	FMOD_VECTOR pFmodVecPoints[20];//�ѹ��� 20���� �������
	for (int i = 0; i < nPoints; ++i) {
		pFmodVecPoints[i].x = pPoints[i].x;
		pFmodVecPoints[i].y = pPoints[i].y;
		pFmodVecPoints[i].z = pPoints[i].z;
	}
	//m_mp3DSoundInfo[sName]->m_pSound->set3DCustomRolloff(pFmodVecPoints, nPoints);
	m_mp3DSoundInfo[sName]->m_pSound->set3DMinMaxDistance(fMin, fMax);

	for (int i = 0; i < nPoints; ++i) {
		m_pSystem->update();
		m_pSystem->playSound(m_mp3DSoundInfo[sName]->m_pSound
			, nullptr, false, &m_mp3DSoundInfo[sName]->m_pChannel);
		m_mp3DSoundInfo[sName]->m_pChannel->setVolume(fVolume);
		m_mp3DSoundInfo[sName]->m_pChannel->set3DMinMaxDistance(fMin, fMax);
		m_mp3DSoundInfo[sName]->m_pChannel->set3DAttributes(&pFmodVecPoints[i], nullptr);
	}

}

void CSoundManager::Update() {
	FMOD_VECTOR poss[1];
	FMOD_VECTOR forwards[1];
	FMOD_VECTOR ups[1];

	auto pCamera = UPDATER->GetCamera();
	XMFLOAT3 xmf3Pos;
	XMStoreFloat3(&xmf3Pos, pCamera->GetPosition());
	poss[0].x = xmf3Pos.x;
	poss[0].y = xmf3Pos.y;
	poss[0].z = xmf3Pos.z;

	XMFLOAT3 xmf3Look;
	XMStoreFloat3(&xmf3Look, pCamera->GetLook());
	forwards[0].x = xmf3Look.x;
	forwards[0].y = xmf3Look.y;
	forwards[0].z = xmf3Look.z;

	XMFLOAT3 xmf3Up;
	XMStoreFloat3(&xmf3Up, pCamera->GetUp());
	ups[0].x = xmf3Up.x;
	ups[0].y = xmf3Up.y;
	ups[0].z = xmf3Up.z;

	m_pSystem->set3DListenerAttributes(0, poss, nullptr, forwards, ups);
	m_pSystem->update();
}


CSoundManager::CSoundManager()
{

	//	for (auto& p : m_mpSoundInfo) {
	//		p.second->m_pSound = nullptr;
	//	}
}


CSoundManager::~CSoundManager()
{

}
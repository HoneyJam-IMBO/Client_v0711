#pragma once

enum tag {
	TAG_DEFAULT,
	TAG_TERRAIN = 0b000001,
	TAG_STATIC_OBJECT = 0b000010,
	TAG_DYNAMIC_OBJECT = 0b000100,
	TAG_LIGHT = 0b001000,
	TAG_REFLECTION = 0b010000,
	TAG_SPACE,
	TAG_SSRF,
	TAG_SSLR,
	TAG_POSTPROCESSING,
	TAG_DEBUG,
	TAG_END
};

enum utag {
	UTAG_DEFAULT,//충돌검사 x 0
	UTAG_COLLISION,//충돌 검사 o 1
	UTAG_COLLISION_MULTIOBB,//2
	UTAG_PLAYER,//3
	UTAG_BOSS1,//4
	UTAG_BOSS2,//5
	UTAG_ARROW,
	UTAG_END
};

enum shader_value_num {
	SVN_DEFAULT,
	SVN_DEBUG,
	SVN_END
};

enum SCENE_ID
{
	SCN_TITLE,
	SCN_LOBBY,
	SCN_HEROSEL,
	SCN_ORITOWN,	
	SCN_REPAIRTOWN,
	SCN_ALDENAD,
	SCN_BOSS,
	SCN_FINAL,
	SCN_END
};


enum ANIMSTATE
{
	ANIM_IDLE,
	ANIM_WPREADY,
	ANIM_DIE,
	ANIM_DEADBODY,
	ANIM_JUMP_START,
	ANIM_JUMP_LOOP,
	ANIM_JUMP_END,
	ANIM_RUN_F,
	ANIM_RUN_B,
	ANIM_RUN_L,
	ANIM_RUN_R,
	ANIM_RUN_FL,
	ANIM_RUN_FR,
	ANIM_RUN_BL,
	ANIM_RUN_BR,
	ANIM_RUN_FSTOP,
	ANIM_JUMP_F_START,
	ANIM_JUMP_F_LOOP,
	ANIM_JUMP_F_END,
	ANIM_JUMP_B_START,
	ANIM_JUMP_B_LOOP,
	ANIM_JUMP_B_END,
	ANIM_HIT_F,
	ANIM_HIT_B,
	ANIM_HITDOWN_START,
	ANIM_HITDOWN_LOOP,
	ANIM_HITDOWN_END,
	ANIM_HITDOWN_BOUNCE,
	ANIM_HITDOWN_GETUP,
	ANIM_ATTACK,
	ANIM_SKILL1_CHARGING,
	ANIM_SKILL1_FIRE,
	ANIM_END
};

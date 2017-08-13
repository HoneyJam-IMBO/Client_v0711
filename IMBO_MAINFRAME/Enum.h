#pragma once

enum tag {
	TAG_DEFAULT,
	TAG_TERRAIN			= 0b0000001,
	TAG_STATIC_OBJECT	= 0b0000010,
	TAG_DYNAMIC_OBJECT	= 0b0000100,
	TAG_LIGHT			= 0b0001000,
	TAG_REFLECTION		= 0b0010000,
	TAG_BIGWATER		= 0b0100000,
	TAG_DYNAMIC_SKILL	= 0b1000000,
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
	UTAG_NPC,//2
	UTAG_PLAYER,//3
	UTAG_BOSS1,//4
	UTAG_BOSS2,//5
	UTAG_ARROW,
	UTAG_OTHERPLAYER_ARROW,
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

enum BOSS1_ANIM
{
	BOSS1_ANI_IDLE,
	BOSS1_ANI_WALK,
	BOSS1_ANI_SKILL1,
	BOSS1_ANI_SKILL2,
	BOSS1_ANI_SKILL3,
	BOSS1_ANI_DOWN,
	BOSS1_ANI_UP,
	BOSS1_ANI_SKILL4,
	BOSS1_ANI_DYING,
	BOSS1_ANI_DIE,
	BOSS1_ANI_END
};
//Elf
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
	ANIM_SKILL1_FIRE,
	ANIM_SKILL2_START,
	ANIM_SKILL2_CHARGING,
	ANIM_SKILL2_FIRE,
	ANIM_SKILL3_FIRE,
	ANIM_SKILL4_FIRE,
	/*ANIM_SKILL1_CHARGING,
	ANIM_SKILL1_FIRE,
	ANIM_SKILL2_FIRE,
	ANIM_SKILL3_FIRE,
	ANIM_SKILL4_START,
	ANIM_SKILL4_CHARGING,
	ANIM_SKILL4_FIRE,*/
	ANIM_END
};
//Knight
enum KNIGHTSTATE
{
	KNIGHT_ANIM_IDLE,
	KNIGHT_ANIM_WPREADY,
	KNIGHT_ANIM_DIE,
	KNIGHT_ANIM_DEADBODY,
	KNIGHT_ANIM_JUMP_START,
	KNIGHT_ANIM_JUMP_LOOP,
	KNIGHT_ANIM_JUMP_END,
	KNIGHT_ANIM_RUN_F,
	KNIGHT_ANIM_RUN_B,
	KNIGHT_ANIM_RUN_L,
	KNIGHT_ANIM_RUN_R,
	KNIGHT_ANIM_RUN_FL,
	KNIGHT_ANIM_RUN_FR,
	KNIGHT_ANIM_RUN_BL,
	KNIGHT_ANIM_RUN_BR,
	KNIGHT_ANIM_RUN_FSTOP,
	KNIGHT_ANIM_JUMP_F_START,
	KNIGHT_ANIM_JUMP_F_LOOP,
	KNIGHT_ANIM_JUMP_F_END,
	KNIGHT_ANIM_JUMP_B_START,
	KNIGHT_ANIM_JUMP_B_LOOP,
	KNIGHT_ANIM_JUMP_B_END,
	KNIGHT_ANIM_HIT_F,
	KNIGHT_ANIM_HIT_B,
	KNIGHT_ANIM_HITDOWN_START,
	KNIGHT_ANIM_HITDOWN_LOOP,
	KNIGHT_ANIM_HITDOWN_END,
	KNIGHT_ANIM_HITDOWN_BOUNCE,
	KNIGHT_ANIM_HITDOWN_GETUP,
	KNIGHT_ANIM_ATTACK,
	KNIGHT_ANIM_SKILL1_FIRE,
	KNIGHT_ANIM_SKILL2_FIRE,
	KNIGHT_ANIM_SKILL3_FIRE,
	KNIGHT_ANIM_SKILL4_FIRE,
	KNIGHT_ANIM_ATTACK2,
	KNIGHT_ANIM_ATTACK3,
	KNIGHT_ANIM_END
};
//Dementor
enum DEMENTORSTATE
{
	DEMENTOR_ANIM_IDLE,
	DEMENTOR_ANIM_WPREADY,
	DEMENTOR_ANIM_DIE,
	DEMENTOR_ANIM_DEADBODY,
	DEMENTOR_ANIM_JUMP_START,
	DEMENTOR_ANIM_JUMP_LOOP,
	DEMENTOR_ANIM_JUMP_END,
	DEMENTOR_ANIM_RUN_F,
	DEMENTOR_ANIM_RUN_B,
	DEMENTOR_ANIM_RUN_L,
	DEMENTOR_ANIM_RUN_R,
	DEMENTOR_ANIM_RUN_FL,
	DEMENTOR_ANIM_RUN_FR,
	DEMENTOR_ANIM_RUN_BL,
	DEMENTOR_ANIM_RUN_BR,
	DEMENTOR_ANIM_RUN_FSTOP,
	DEMENTOR_ANIM_JUMP_F_START,
	DEMENTOR_ANIM_JUMP_F_LOOP,
	DEMENTOR_ANIM_JUMP_F_END,
	DEMENTOR_ANIM_JUMP_B_START,
	DEMENTOR_ANIM_JUMP_B_LOOP,
	DEMENTOR_ANIM_JUMP_B_END,
	DEMENTOR_ANIM_HIT_F,
	DEMENTOR_ANIM_HIT_B,
	DEMENTOR_ANIM_HITDOWN_START,
	DEMENTOR_ANIM_HITDOWN_LOOP,
	DEMENTOR_ANIM_HITDOWN_END,
	DEMENTOR_ANIM_HITDOWN_BOUNCE,
	DEMENTOR_ANIM_HITDOWN_GETUP,
	DEMENTOR_ANIM_ATTACK,
	DEMENTOR_ANIM_SKILL1_START,
	DEMENTOR_ANIM_SKILL1_CHARGING,
	DEMENTOR_ANIM_SKILL1_FIRE,
	DEMENTOR_ANIM_SKILL2_START,
	DEMENTOR_ANIM_SKILL2_CHARGING,
	DEMENTOR_ANIM_SKILL2_FIRE,
	DEMENTOR_ANIM_SKILL3_FIRE,
	DEMENTOR_ANIM_SKILL4_START,
	DEMENTOR_ANIM_SKILL4_CHARGING,
	DEMENTOR_ANIM_SKILL4_FIRE,
	DEMENTOR_ANIM_END
};
//Wizard
enum WIZARDSTATE
{
	WIZARD_ANIM_IDLE,
	WIZARD_ANIM_WPREADY,
	WIZARD_ANIM_DIE,
	WIZARD_ANIM_DEADBODY,
	WIZARD_ANIM_JUMP_START,
	WIZARD_ANIM_JUMP_LOOP,
	WIZARD_ANIM_JUMP_END,
	WIZARD_ANIM_RUN_F,
	WIZARD_ANIM_RUN_B,
	WIZARD_ANIM_RUN_L,
	WIZARD_ANIM_RUN_R,
	WIZARD_ANIM_RUN_FL,
	WIZARD_ANIM_RUN_FR,
	WIZARD_ANIM_RUN_BL,
	WIZARD_ANIM_RUN_BR,
	WIZARD_ANIM_RUN_FSTOP,
	WIZARD_ANIM_JUMP_F_START,
	WIZARD_ANIM_JUMP_F_LOOP,
	WIZARD_ANIM_JUMP_F_END,
	WIZARD_ANIM_JUMP_B_START,
	WIZARD_ANIM_JUMP_B_LOOP,
	WIZARD_ANIM_JUMP_B_END,
	WIZARD_ANIM_HIT_F,
	WIZARD_ANIM_HIT_B,
	WIZARD_ANIM_HITDOWN_START,
	WIZARD_ANIM_HITDOWN_LOOP,
	WIZARD_ANIM_HITDOWN_END,
	WIZARD_ANIM_HITDOWN_BOUNCE,
	WIZARD_ANIM_HITDOWN_GETUP,
	WIZARD_ANIM_ATTACK,
	WIZARD_ANIM_SKILL1_FIRE,
	WIZARD_ANIM_SKILL2_FIRE,
	WIZARD_ANIM_SKILL3_START,
	WIZARD_ANIM_SKILL3_FIRE,
	WIZARD_ANIM_SKILL4_START,
	WIZARD_ANIM_SKILL4_CHARGING,
	WIZARD_ANIM_SKILL4_FIRE,
	WIZARD_ANIM_END
};
//sister
enum SISTERSTATE
{
	SISTER_ANIM_IDLE,
	SISTER_ANIM_WPREADY,
	SISTER_ANIM_DIE,
	SISTER_ANIM_DEADBODY,
	SISTER_ANIM_JUMP_START,
	SISTER_ANIM_JUMP_LOOP,
	SISTER_ANIM_JUMP_END,
	SISTER_ANIM_RUN_F,
	SISTER_ANIM_RUN_B,
	SISTER_ANIM_RUN_L,
	SISTER_ANIM_RUN_R,
	SISTER_ANIM_RUN_FL,
	SISTER_ANIM_RUN_FR,
	SISTER_ANIM_RUN_BL,
	SISTER_ANIM_RUN_BR,
	SISTER_ANIM_RUN_FSTOP,
	SISTER_ANIM_JUMP_F_START,
	SISTER_ANIM_JUMP_F_LOOP,
	SISTER_ANIM_JUMP_F_END,
	SISTER_ANIM_JUMP_B_START,
	SISTER_ANIM_JUMP_B_LOOP,
	SISTER_ANIM_JUMP_B_END,
	SISTER_ANIM_HIT_F,
	SISTER_ANIM_HIT_B,
	SISTER_ANIM_HITDOWN_START,
	SISTER_ANIM_HITDOWN_LOOP,
	SISTER_ANIM_HITDOWN_END,
	SISTER_ANIM_HITDOWN_BOUNCE,
	SISTER_ANIM_HITDOWN_GETUP,
	SISTER_ANIM_ATTACK,
	SISTER_ANIM_SKILL1_FIRE,
	SISTER_ANIM_SKILL2_FIRE,
	SISTER_ANIM_SKILL3_CHARGING,
	SISTER_ANIM_SKILL3_FIRE,
	SISTER_ANIM_SKILL4_FIRE,
	SISTER_ANIM_END
};
//Bard
enum BARDSTATE
{
	BARD_ANIM_IDLE,
	BARD_ANIM_WPREADY,
	BARD_ANIM_DIE,
	BARD_ANIM_DEADBODY,
	BARD_ANIM_JUMP_START,
	BARD_ANIM_JUMP_LOOP,
	BARD_ANIM_JUMP_END,
	BARD_ANIM_RUN_F,
	BARD_ANIM_RUN_B,
	BARD_ANIM_RUN_L,
	BARD_ANIM_RUN_R,
	BARD_ANIM_RUN_FL,
	BARD_ANIM_RUN_FR,
	BARD_ANIM_RUN_BL,
	BARD_ANIM_RUN_BR,
	BARD_ANIM_RUN_FSTOP,
	BARD_ANIM_JUMP_F_START,
	BARD_ANIM_JUMP_F_LOOP,
	BARD_ANIM_JUMP_F_END,
	BARD_ANIM_JUMP_B_START,
	BARD_ANIM_JUMP_B_LOOP,
	BARD_ANIM_JUMP_B_END,
	BARD_ANIM_HIT_F,
	BARD_ANIM_HIT_B,
	BARD_ANIM_HITDOWN_START,
	BARD_ANIM_HITDOWN_LOOP,
	BARD_ANIM_HITDOWN_END,
	BARD_ANIM_HITDOWN_BOUNCE,
	BARD_ANIM_HITDOWN_GETUP,
	BARD_ANIM_ATTACK,
	BARD_ANIM_SKILL1_FIRE,
	BARD_ANIM_SKILL2_FIRE,
	BARD_ANIM_SKILL3_FIRE,
	BARD_ANIM_SKILL4_FIRE,
	BARD_ANIM_END
};
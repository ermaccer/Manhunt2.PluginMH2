#pragma once
#include "calling.h"

struct CVector {
	float x, y, z;
};

struct CVector4 {
	float x, y, z, w;
};

struct CEntity{
	//todo: pretty much everything
	char field[124];
	float health;
};



enum EFontType {
	FONT_TYPE_DEBUG,
	FONT_TYPE_DEFAULT,
	FONT_FRONTEND,
	FONT_TYPE_LOADING
};



CEntity* GetEntity(const char* name);
CEntity* FindPlayer();
CEntity* FindEntity(const char* name);


CVector  GetEntityPosition(CEntity* ent);

void     CreateInventoryItem(CEntity* ent, int item, bool b1);
void     AddAmmoToInventoryWeapon(int item, int amount);
void     SetHunterHideHealth(CEntity* ent, float health);
void     SetDrawRGBA(int r, int g, int b, int a);
void     PrintText(const char* text, float x, float y, float sizex, float sizey, float unk, EFontType font);
void     SetEntityFlag(CEntity* ent, int flag, bool state);

wchar_t* GetCollectableName(int id);
char*    GetRecordName(int id);

bool     IsAlive(CEntity* ent);

int      GetTimer();

template<typename ...Args>
void WriteDebug(int line, const char * msg, Args ...args)
{
	Call<0x53D8D0, int, const char*, Args...>(line, msg, args...);
}

// todo: fill up

enum eItems {
	CT_TRIPWIRE = 1,
	CT_GASOLINE,
	CT_WATER,
	CT_LIGHTER,
	CT_CASH,
	CT_TORCH,
	CT_N_VISION,
	CT_PAINKILLERS,
	CT_G_FIRST_AID,
	CT_Y_FIRST_AID,
	CT_SPEED_BOOST,
	CT_STRENGTH_BOOST,
	CT_SHOOTING_BOOST,
	CT_REFLEXES_BOOST,
	CT_HEALTH_BOOST,
	CT_FISTS,
	CT_K_DUST,
	CT_KNIFE,
	CT_SHARD,
	CT_BROKEN_BOTTLE,
	CT_JURYBLADES,
	CT_BOTTLE,
	CT_PIPE,
	CT_CLEAVER,
	CT_WOODEN_BAR,
	CT_CROWBAR,
	CT_SICKLE,
	CT_NIGHTSTICK,
	CT_CANE,
	CT_AXE,
	CT_ICEPICK,
	CT_MACHETE,
	CT_SMALL_BAT,
	CT_PLIERS,
	CT_BASEBALL_BAT,
	CT_W_BASEBALL_BAT,
	CT_FIRE_AXE,
	CT_HOCKEY_STICK,
	CT_BASEBALL_BAT_BLADES,
	CT_6SHOOTER,
	CT_GLOCK,
	CT_GLOCK_SILENCED,
	CT_GLOCK_TORCH,
	CT_UZI,
	CT_UZI_TORCH,
	CT_SHOTGUN,
	CT_SHOTGUN_TORCH,
	CT_DESERT_EAGLE,
	CT_COLT_COMMANDO,
	CT_SNIPER_RIFLE,
	CT_TRANQ_RIFLE,
	CT_SAWNOFF,
	CT_GRENADE,
	CT_MOLOTOV,
	CT_EXPMOLOTOV,
	CT_TEAR_GAS,
	CT_F_GRENADE,
	CT_BRICK_HALF,
	CT_FIREWORK,
	CT_BAG,
	CT_RAG,
	CT_CHLORINE,
	CT_METHS,
	CT_HCC,
	CT_D_BEER_GUY,
	CT_D_MERC_LEADER,
	CT_D_SMILEY,
	CT_D_HUNTLORD,
	CT_E_L_SIGHT,
	CT_S_SILENCER,
	CT_RADIO,
	CT_BAR_KEY,
	CT_SYARD_COMB,
	CT_CAMERA,
	CT_BODY_P1,
	CT_BODY_P2,
	CT_PREC_KEY,
	CT_PREC_CARD,
	CT_PREC_DOCS,
	CT_PHARM_HAND,
	CT_EST_G_KEY,
	CT_EST_A_KEY,
	CT_DOLL,
	CT_ANTIDOTE,
	CT_KEY,
	CT_SWIPE_CARD, // did not have ct_ entry
	dummy = 89,
	CT_CHAINSAW,
	CT_NAILGUN,
	CT_WIRE,
	CT_CAN,
	CT_WOODEN_SPIKE,
	CT_SNIPER_RIFLE_SILENCED,
	CT_PIGSY_SHARD,
	CT_PIGSY_WIRE,
	CT_PIGSY_SPIKE,
	CT_HAMMER,
	CT_DOLL_1,
	CT_DOLL_2,
	CT_DOLL_3,
	CT_HEAD,
	CT_AMMO_NAILS,
	CT_AMMO_SHOTGUN,
	CT_AMMO_PISTOL,
	CT_AMMO_MGUN,
	CT_AMMO_TRANQ,
	CT_AMMO_SNIPER,
	CT_CHAINSAW_PLAYER,
	CT_DVTAPE,
	CT_HANDYCAM,
	CT_SYRINGE,
	CT_SHOVEL,
	CT_SLEDGEHAMMER,
	CT_STUNPROD,
	CT_PEN,
	CT_ACID_BOTTLE,
	CT_1H_FIREARM,
	CT_2H_FIREARM,
	CT_CUT_THROAT_RAZOR,
	CT_BLOWTORCH,
	CT_MACE,
	CT_HEDGETRIMMER,
	CT_METAL_HOOK,
	CT_CIRCULAR_SAW,
	CT_FLAREGUN,
	CT_AMMO_FLARES,
	CT_NOOSE,
	CT_CAMERA_WEAPON,
	CT_CROSSBOW,
	CT_AMMO_CROSSBOW,
	CT_AMMO_ARROW,
	CT_NEWSPAPER,
	CT_MILKBOTTLE,
	CT_DILDO,
	CT_KATANA,
	CT_HACKSAW,
	CT_GOLFBALL, // 143 too?
	CT_CASH_BUNDLE,
	CT_PORN,
	CT_MATCHBOOK,
};

enum eWeatherTypes {
	CLOUDY,
	WINDY,
	RAINY,
	THUNDER,
	FOGGY,
	CLEAR,
	FREE = -1
};

enum eMenuTypes {
	MENU_EPISODE_FAILED  = 1,
	MENU_LEVEL_COMPLETED,
	MENU_DUALSHOCK_WARNING,
	MENU_DUALSHOCK_WARNING2,
	MENU_DISC_TRAY_OPEN,
	MENU_DISC_WARNING,
	MENU_DISC_WARNING2,
	MENU_DISC_READ_ERROR,
	MENU_NO_MEM_CARD,
	MENU_SAVE_CONFIRM = 11,
	MENU_CAN_FOR,
	MENU_CAN_FOR2,
	MENU_DEL_PROGRESS,
	// todo

};


class Game {
public:
	// debug ones
	static int &FreezeWorld;
	static int &FreeCamera;
	
	// other
	static int &iBodyCounterKills;
	static int &iHuntersKilled;
	static int &iHuntersExecuted;
    
	static int &iTimePassed;
	static int &iTimerMinutes;
	static int &iTimerSeconds;
};


// thanks to MAJEST1C_R3
class CString
{
public:
	char* c_str;
	short length;
	short capacity;
};

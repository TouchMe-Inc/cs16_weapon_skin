#pragma semicolon 1

#include <amxmodx>
#include <engine>
#include <fakemeta>
#include <hamsandwich>


#include "ws/sugar.sma"


#define SKIN_CONFIG                 "addons/amxmodx/configs/weapon_skin.cfg"
#define SKIN_TRANSLATION            "weapon_skin.txt"

// get_weaponname not work before plugin_init().
new WEAPON_NAME[][] = {
    "", "weapon_p228", "weapon_shield", "weapon_scout", "weapon_hegrenade", "weapon_xm1014", "weapon_c4",
    "weapon_mac10", "weapon_aug", "weapon_smokegrenade", "weapon_elite", "weapon_fiveseven", "weapon_ump45",
    "weapon_sg550", "weapon_galil", "weapon_famas", "weapon_usp", "weapon_glock18", "weapon_awp", "weapon_mp5navy",
    "weapon_m249", "weapon_m3", "weapon_m4a1", "weapon_tmp", "weapon_g3sg1", "weapon_flashbang", "weapon_deagle",
    "weapon_sg552", "weapon_ak47", "weapon_knife", "weapon_p90"
};


#include "ws/config.h"
#include "ws/events.h"
#include "ws/forwards.h"
#include "ws/skins.h"
#include "ws/weapon_skin.h"
#include "ws/client_skin.h"
#include "ws/commands.h"
#include "ws/menus.h"

#include "ws/config.inc"
#include "ws/forwards.inc"
#include "ws/events.inc"
#include "ws/skins.inc"
#include "ws/weapon_skin.inc"
#include "ws/client_skin.inc"
#include "ws/commands.inc"
#include "ws/menus.inc"

#include "ws/natives.sma"


public RegPluginNatives() {
	SetupPluginNatives();
}

public OnPluginPrecache()
{
	InitSkinData();

	LoadConfig(SKIN_CONFIG);

	LoadTranslations(SKIN_TRANSLATION);	

	// Precache skins.
	for (new iIndex = 0, sModelPath[64], eSkinInfo[SkinInfo]; iIndex < ArraySize(g_aSkinList); iIndex++)
	{
		ArrayGetArray(g_aSkinList, iIndex, eSkinInfo);

		engfunc(EngFunc_SzFromIndex, eSkinInfo[model_v], sModelPath, charsmax(sModelPath));
		precache_model(sModelPath);

		if (eSkinInfo[model_p])
		{
			engfunc(EngFunc_SzFromIndex, eSkinInfo[model_p], sModelPath, charsmax(sModelPath));
			precache_model(sModelPath);
		}

		if (eSkinInfo[model_w]) {
			precache_model(eSkinInfo[model_w]);
		}
	}
}

public OnPluginStart()
{
	RegPluginInfo("WeaponSkin", "v0001", "TouchMe");

	SetupPluginEvents();
	SetupPluginCommands();
	SetupPluginMenus();

	InitGlobalForwards();
}

public OnPluginEnd()
{
	DestroySkinData();

	DestroyGlobalForwards();
}

public client_connect(iClient) {
	ResetClientSkinAll(iClient);
}

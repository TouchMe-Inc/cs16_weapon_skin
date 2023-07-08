#define XO_CBASEPLAYER                 5
#define XO_CBASEPLAYERWEAPON           4
#define m_pPlayer                      41
#define m_pNext                        42
#define m_iId                          43
#define m_iTeam                        114
#define m_pActiveItem                  373
#define m_rgpPlayerItems_CWeaponBox    34
#define m_rgpPlayerItems_CBasePlayer   367

#define GetClientByWeaponEnt(%0)       get_pdata_cbase(%0, m_pPlayer, XO_CBASEPLAYERWEAPON)
#define GetWeaponEntByClient(%0)       get_pdata_cbase(%0, m_pActiveItem, XO_CBASEPLAYER)
#define GetWeaponIdByWeaponEnt(%0)     get_pdata_int(%0, m_iId, XO_CBASEPLAYERWEAPON)

// General
#define OnPluginStart                  plugin_init
#define OnPluginEnd                    plugin_end
#define OnPluginPrecache               plugin_precache
#define RegPluginInfo                  register_plugin
#define SetFailState                   set_fail_state
#define LoadTranslations               register_dictionary
#define GetGameTime                    get_gametime
#define GetWeaponId                    get_weaponid
#define GetWeaponName                  get_weaponname

// Natives
#define RegPluginNatives               plugin_natives
#define CreateNative                   register_native
#define GetNativeString                get_string
#define SetNativeString                set_string
#define GetNativeCell                  get_param
#define SetNativeCellRef               set_param_byref

// String
#define Format                         format
#define FormatEx                       formatex
#define StrEqual                       equal

// Types
#define StringToInt                    str_to_num
#define RoundToFloor(%0)               floatround(%0, floatround_floor)

// Players
#define IsClientInGame                 is_user_connected
#define IsClientAlive                  is_user_alive

// Old Menu
#define ShowMenu                       show_menu
#define RegMenuId                      register_menuid
#define RegMenu                        register_menucmd

// Task
#define CreateTimer                    set_task

// Other
#define IsValidPev(%0)                 (pev_valid(%0) == 2)
#define HasOwner(%0)                   (pev(%0, pev_owner) > 0)
#define GetOwner(%0)                   pev(%0, pev_owner)
#define GetClassName(%0,%1,%2)         pev(%0, pev_classname, %1, %2)


stock GetOldMenu(iClient)
{
	new iOldMenu, iNewMenu;

	player_menu_info(iClient, iOldMenu, iNewMenu);

	return iOldMenu;
}

stock GetNewMenu(iClient)
{
	new iOldMenu, iNewMenu;

	player_menu_info(iClient, iOldMenu, iNewMenu);

	return iNewMenu;
}

stock RegCmd(const sCmd[], const sFunction[], iFlags = -1, const sInfo[] = "", iFlagManager = -1, bool:bIsInfoMl = false)
{
	new const cmdsay[][] = { "say", "say_team" };
	new const marks[] = { '!', '/' };
	new sCmdFormated[64], i, j;

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			FormatEx(sCmdFormated, charsmax(sCmdFormated), "%s %c%s", cmdsay[i], marks[j], sCmd);
			register_clcmd(sCmdFormated, sFunction, iFlags, sInfo, iFlagManager, bIsInfoMl);
		}
	}
}
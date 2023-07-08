
public SetupPluginCommands() {
	RegCmd(CMD_SHOW_SKIN_MENU, "Cmd_ShowSkinMenu");
}

public Cmd_ShowSkinMenu(iClient)
{
	new iWeaponId = get_user_weapon(iClient);
	ShowSkinMenu(iClient, g_iClientWeaponId[iClient] = iWeaponId, g_iClientPage[iClient] = 0);

	return PLUGIN_HANDLED;
}
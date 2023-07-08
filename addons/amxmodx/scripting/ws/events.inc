public SetupPluginEvents()
{
	for(new iWeaponId = CSW_P228, sWeaponName[32]; iWeaponId <= CSW_P90; iWeaponId++)
	{
		if(GetWeaponName(iWeaponId, sWeaponName, charsmax(sWeaponName)))
		{
			RegisterHam(Ham_Item_Deploy, sWeaponName, "Ham_WeaponDeploy_Post", .Post = true);
			RegisterHam(Ham_Item_AddToPlayer, sWeaponName, "Ham_WeaponAddToPlayer_Post", .Post = true);
		}
	}

	RegisterHam(Ham_Spawn, "weaponbox", "Ham_WeaponSpawn_Post", .Post = true);
	RegisterHam(Ham_Spawn, "grenade", "Ham_WeaponSpawn_Post", .Post = true);

	register_forward(FM_SetModel, "FM_SetModel_Pre", ._post = false);

	register_touch("weaponbox", "player", "Touch_WeaponBox");
}

public Ham_WeaponDeploy_Post(const iWeaponEnt)
{
	new iClient = GetClientByWeaponEnt(iWeaponEnt);
	new iWeaponId = GetWeaponIdByWeaponEnt(iWeaponEnt);

	new iSkinIndex = HasWeaponSkin(iWeaponEnt) ? GetWeaponSkin(iWeaponEnt) : GetClientSkin(iClient, iWeaponId);

	if (iSkinIndex >= 0)
	{
		new eSkinInfo[SkinInfo]; ArrayGetArray(g_aSkinList, iSkinIndex, eSkinInfo);

		set_pev(iClient, pev_viewmodel, eSkinInfo[model_v]);

		if (eSkinInfo[model_p]) {
			set_pev(iClient, pev_weaponmodel, eSkinInfo[model_p]);
		}

		Call_OnClientWeaponDeploy(iClient, iSkinIndex);
	}

	if (SeeSkinMenu(iClient) && g_iClientWeaponId[iClient] != iWeaponId) {
		ShowSkinMenu(iClient, g_iClientWeaponId[iClient] = iWeaponId, g_iClientPage[iClient] = 0);
	}

	return HAM_IGNORED;
}

public Ham_WeaponAddToPlayer_Post(const iWeaponEnt, const iClient)
{
	new iWeaponId = GetWeaponIdByWeaponEnt(iWeaponEnt);

	if (HasOwner(iWeaponEnt)) {
		return HAM_IGNORED;
	}

	if (HasWeaponSkin(iWeaponEnt)) {
		return HAM_IGNORED;
	}

	new iSkinIndex = GetClientSkin(iClient, iWeaponId);

	if (iSkinIndex >= 0) {
		SetWeaponSkin(iWeaponEnt, iSkinIndex);
	}

	return HAM_IGNORED;
}

public Ham_WeaponSpawn_Post(const iWeaponEnt)
{
	if (IsValidPev(iWeaponEnt)) {
		g_bIgnoreSetModel = false;
	}

	return HAM_IGNORED;
}

public FM_SetModel_Pre(const iEnt)
{
	if (g_bIgnoreSetModel || !IsValidPev(iEnt)) {
		return FMRES_IGNORED;
	}

	g_bIgnoreSetModel = true;

	new iClient = GetOwner(iEnt);
	new sClassName[32]; GetClassName(iEnt, sClassName, charsmax(sClassName));
	new iWeaponId, iSkinIndex;

	if (StrEqual(sClassName, CLASSNAME_GRENADE))
	{
		new iWeaponId = CSW_FLASHBANG;
		new iGrenadeType = get_pdata_int(iEnt, m_iTeam);

		if (iGrenadeType & TYPE_HEGRENADE) {
			iWeaponId = CSW_HEGRENADE;
		} else if (iGrenadeType & TYPE_SMOKEGRENADE) {
			iWeaponId = CSW_SMOKEGRENADE;
		}

		iSkinIndex = GetClientSkin(iClient, iWeaponId);

		if (iSkinIndex >= 0)
		{
			new eSkinInfo[SkinInfo]; ArrayGetArray(g_aSkinList, iSkinIndex, eSkinInfo);

			engfunc(EngFunc_SetModel, iEnt, eSkinInfo[model_w]);

			Call_OnClientWeaponDrop(iClient, iSkinIndex);

			return FMRES_SUPERCEDE;
		}

		return FMRES_IGNORED;
	}

	for(new iSlot = 1, iWeaponEnt; iSlot < MAX_ITEM_SLOT; iSlot++)
	{
		iWeaponEnt = get_pdata_cbase(iEnt, m_rgpPlayerItems_CWeaponBox + iSlot, XO_CBASEPLAYERWEAPON);

		if(!IsValidPev(iWeaponEnt)) {
			continue;
		}

		iWeaponId = GetWeaponIdByWeaponEnt(iWeaponEnt);
		iSkinIndex = HasWeaponSkin(iWeaponEnt) ? GetWeaponSkin(iWeaponEnt) : GetClientSkin(iClient, iWeaponId);

		if (iSkinIndex >= 0)
		{
			new eSkinInfo[SkinInfo]; ArrayGetArray(g_aSkinList, iSkinIndex, eSkinInfo);

			engfunc(EngFunc_SetModel, iEnt, eSkinInfo[model_w]);

			Call_OnClientWeaponDrop(iClient, iSkinIndex);

			return FMRES_SUPERCEDE;
		}
	}

	return FMRES_IGNORED;
}

public Touch_WeaponBox(iEnt, iClient)
{
	new iSkinIndex;

	for(new iSlot = 1, iWeaponEnt; iSlot < MAX_ITEM_SLOT; iSlot++)
	{
		iWeaponEnt = get_pdata_cbase(iEnt, m_rgpPlayerItems_CWeaponBox + iSlot, XO_CBASEPLAYERWEAPON);

		if (!IsValidPev(iWeaponEnt)) {
			continue;
		}

		iSkinIndex = GetWeaponSkin(iWeaponEnt);

		if (iSkinIndex >= 0 && Call_OnClientWeaponPickUp(iClient, iSkinIndex)) {
			return PLUGIN_HANDLED;
		}
	}

	return PLUGIN_CONTINUE;
}
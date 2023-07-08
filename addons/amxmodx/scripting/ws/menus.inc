public SetupPluginMenus() {
	RegMenu((g_idSkinMenu = RegMenuId(MENU_SKINS)), MENU_KEY_ALL, HANDLER_MENU_SKINS);
}

public bool:SeeSkinMenu(iClient) {
	return g_idSkinMenu == GetOldMenu(iClient);
}

public ShowSkinMenu(iClient, iWeaponId, iPage)
{
	new sWeaponName[32]; GetWeaponName(iWeaponId, sWeaponName, charsmax(sWeaponName));

	new Array:aSkinList; TrieGetCell(g_tSkinCache, sWeaponName, aSkinList);

	new iKeys = MENU_KEY_0;
	new sMenuBody[512];

	new iStart = iPage * MENU_PER_PAGE;
	new iEnd = iStart + MENU_PER_PAGE;

	new iSkinListSize = ArraySize(aSkinList);

	if (iEnd > iSkinListSize) {
		iEnd = iSkinListSize;
	}

	new iLen = FormatEx(sMenuBody, charsmax(sMenuBody), "\y%L^n\w^n", iClient, "MENU_SKIN_TITLE");

	new iClientSkin = GetClientSkin(iClient, iWeaponId);
	new eSkinInfo[SkinInfo];

	new iWeaponEnt = GetWeaponEntByClient(iClient);
	new iWeaponSkin = GetWeaponSkin(iWeaponEnt);

	new bool:bIsAnotherSkin = HasWeaponSkin(iWeaponEnt) && iWeaponSkin != iClientSkin;

	if (bIsAnotherSkin)
	{
		ArrayGetArray(g_aSkinList, iWeaponSkin, eSkinInfo);

		iKeys |= MENU_KEY_1;
		iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\y1. \w%L^n", iClient, "MENU_SKIN_ITEM_RESET", eSkinInfo[name]);
	}

	else if (iClientSkin >= 0)
	{
		iKeys |= MENU_KEY_1;
		iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\y1. \w%L^n", iClient, "MENU_SKIN_ITEM_DEFAULT");
	} else {
		iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\r#\d. %L^n", iClient, "MENU_SKIN_ITEM_DEFAULT");
	}

	new iNum = 1;

	for (new iIndex = iStart, iSkinIndex; iIndex < iEnd; iIndex++)
	{
		iSkinIndex = ArrayGetCell(aSkinList, iIndex);

		ArrayGetArray(g_aSkinList, iSkinIndex, eSkinInfo);

		if (iClientSkin == iSkinIndex) {
			iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\r#\d. %s^n", eSkinInfo[name]);
		}

		else if (bIsAnotherSkin) {
			iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\d%d. %s^n", (iNum + 1), eSkinInfo[name]);
		}

		else
		{
			iKeys |= (1 << iNum);
			iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\y%d. \w%s^n", (iNum + 1), eSkinInfo[name]);
		}

		iNum++;
	}

	for (;iNum <= (MENU_PER_PAGE + 1); iNum++)
	{
		iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "^n");
	}

	if (iEnd < iSkinListSize)
	{
		iKeys |= MENU_KEY_8;
		iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\y8. \w%L^n", iClient, "MENU_SKIN_ITEM_NEXT");
	} else {
		iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\d8. %L^n", iClient, "MENU_SKIN_ITEM_NEXT");
	}

	if (iPage > 0)
	{
		iKeys |= MENU_KEY_9;
		iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\y9. \w%L^n", iClient, "MENU_SKIN_ITEM_BACK");
	} else {
		iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\d9. %L^n", iClient, "MENU_SKIN_ITEM_BACK");
	}

	iLen += FormatEx(sMenuBody[iLen], charsmax(sMenuBody) - iLen, "\y0. \w%L", iClient, "MENU_SKIN_ITEM_EXIT");

	ShowMenu(iClient, iKeys, sMenuBody, MENU_TIME_FOREVER, MENU_SKINS);
}

public HandlerSkinMenu(iClient, iKey)
{
	new iWeaponId = g_iClientWeaponId[iClient];

	switch(iKey)
	{
		case KEY_1:
		{
			new iClientSkin = GetClientSkin(iClient, iWeaponId);

			new iWeaponEnt = GetWeaponEntByClient(iClient);
			new iWeaponSkin = GetWeaponSkin(iWeaponEnt);

			if (HasWeaponSkin(iWeaponEnt) && iWeaponSkin != iClientSkin) {
				SetWeaponSkin(iWeaponEnt, iClientSkin);
			}

			else if (iClientSkin >= 0)
			{
				ResetClientSkin(iClient, iWeaponId);
				ResetWeaponSkin(iWeaponEnt);
			}

			ExecuteHam_ItemDeploy(iWeaponEnt);

			ShowSkinMenu(iClient, iWeaponId, g_iClientPage[iClient]);
		}

		case KEY_2..MENU_PER_PAGE:
		{
			new iWeaponEnt = GetWeaponEntByClient(iClient);
			new sWeaponName[32]; GetWeaponName(iWeaponId, sWeaponName, charsmax(sWeaponName));
			new Array:aSkinList; TrieGetCell(g_tSkinCache, sWeaponName, aSkinList);
			new iSkinIndex = ArrayGetCell(aSkinList, (g_iClientPage[iClient] * MENU_PER_PAGE + iKey - 1));

			SetClientSkin(iClient, iWeaponId, iSkinIndex);
			SetWeaponSkin(iWeaponEnt, iSkinIndex);

			ExecuteHam_ItemDeploy(iWeaponEnt);

			ShowSkinMenu(iClient, iWeaponId, g_iClientPage[iClient]);
		}

		case KEY_8: ShowSkinMenu(iClient, iWeaponId, ++g_iClientPage[iClient]);
		case KEY_9: ShowSkinMenu(iClient, iWeaponId, --g_iClientPage[iClient]);
	}

	return PLUGIN_HANDLED;
}

stock ExecuteHam_ItemDeploy(iEnt)
{
	if (IsValidPev(iEnt)) {
		ExecuteHamB(Ham_Item_Deploy, iEnt);
	}
}
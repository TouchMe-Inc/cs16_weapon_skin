public InitSkinData()
{
	g_aSkinList = ArrayCreate(SkinInfo);

	g_tSkinCache = TrieCreate();

	for(new iWeaponId = CSW_P228, sWeaponName[32]; iWeaponId <= CSW_P90; iWeaponId++)
	{
		// GetWeaponName return zero in precache.
		if (GetWeaponNameEx(iWeaponId, sWeaponName, charsmax(sWeaponName))) {
			TrieSetCell(g_tSkinCache, sWeaponName, ArrayCreate()); 
		}
	}
}

public DestroySkinData()
{
	ArrayDestroy(g_aSkinList);

	new Array:aSkinCache;
	for(new iWeaponId = CSW_P228, sWeaponName[32]; iWeaponId <= CSW_P90; iWeaponId++)
	{
		if (GetWeaponNameEx(iWeaponId, sWeaponName, charsmax(sWeaponName)))
		{
			TrieGetCell(g_tSkinCache, sWeaponName, aSkinCache);
			ArrayDestroy(aSkinCache);
		}
	}

	TrieDestroy(g_tSkinCache);
}

public PushSkin(eSkinInfo[SkinInfo])
{
	if (IsValidSkinInfo(eSkinInfo))
	{
		new iSkinIndex = ArrayPushArray(g_aSkinList, eSkinInfo);

		new Array:aSkinCache;
		new sWeaponName[32]; GetWeaponNameEx(eSkinInfo[weapon_id], sWeaponName, charsmax(sWeaponName));

		TrieGetCell(g_tSkinCache, sWeaponName, aSkinCache);

		// No need to override array via TrieSetCell.
		ArrayPushCell(aSkinCache, iSkinIndex);

		return iSkinIndex;
	}

	return -1;
}

public bool:IsValidSkinInfo(eSkinInfo[SkinInfo]) {
	return eSkinInfo[weapon_id] && eSkinInfo[name][0] && eSkinInfo[model_v];
}

public GetWeaponNameEx(iWeaponId, sWeaponName[], iLength) {
	return copy(sWeaponName, iLength, WEAPON_NAME[iWeaponId]);
}
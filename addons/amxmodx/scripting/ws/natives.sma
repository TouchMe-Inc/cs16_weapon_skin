public SetupPluginNatives()
{
	CreateNative("WS_GetSkinList", "Native_GetSkinList");
	CreateNative("WS_GetSkinWeaponId", "Native_GetSkinWeaponId");
	CreateNative("WS_GetSkinName", "Native_GetSkinName");
}

public Native_GetSkinList(hPluginId, iParams)
{
	new sWeaponName[32];

	if (!GetNativeString(1, sWeaponName, charsmax(sWeaponName))) {
		abort(AMX_ERR_NATIVE, "Incorrect weapon name");
	}

	if (!TrieKeyExists(g_tSkinCache, sWeaponName)) {
		abort(AMX_ERR_NATIVE, "Weapon %s invalid", sWeaponName);
	}

	new Array:aSkinCache = Array:GetNativeCell(2);

	TrieGetCell(g_tSkinCache, sWeaponName, aSkinCache);

	SetNativeCellRef(2, _:aSkinCache);

	return 1;
}

public Native_GetSkinWeaponId(hPluginId, iParams)
{
	new iSkinIndex = GetNativeCell(1);

	new eSkinInfo[SkinInfo];
	ArrayGetArray(g_aSkinList, iSkinIndex, eSkinInfo);

	return eSkinInfo[weapon_id];
}

public Native_GetSkinName(hPluginId, iParams)
{
	new iSkinIndex = GetNativeCell(1);

	new eSkinInfo[SkinInfo];
	ArrayGetArray(g_aSkinList, iSkinIndex, eSkinInfo);

	SetNativeString(2, eSkinInfo[name], GetNativeCell(3));

	return 1;
}
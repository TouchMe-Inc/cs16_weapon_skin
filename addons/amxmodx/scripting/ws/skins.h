enum _:SkinInfo
{
	weapon_id,
	name[64],
	model_w[128],
	model_v,
	model_p,
}

new g_eTempSkinInfo[SkinInfo];

new Array:g_aSkinList = Invalid_Array;
new Trie:g_tSkinCache = Invalid_Trie;
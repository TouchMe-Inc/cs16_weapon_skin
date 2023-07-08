public bool:HasWeaponSkin(iEnt) {
	return pev(iEnt, pev_iuser4) > WEAPON_SKIN_NONE;
}

public GetWeaponSkin(iEnt) {
	return pev(iEnt, pev_iuser4) - WEAPON_SKIN_OFFSET;
}

public SetWeaponSkin(iEnt, iSkinIndex) {
	set_pev(iEnt, pev_iuser4, iSkinIndex + WEAPON_SKIN_OFFSET);
}

public ResetWeaponSkin(iEnt) {
	set_pev(iEnt, pev_iuser4, WEAPON_SKIN_NONE);
}
public InitGlobalForwards()
{
	g_fwdOnClientWeaponPickUp = CreateMultiForward(FWD_ON_CLIENT_WEAPON_PICK_UP, ET_CONTINUE, FP_CELL, FP_CELL);
	g_fwdOnClientWeaponDeploy = CreateMultiForward(FWD_ON_CLIENT_WEAPON_DEPLOY, ET_IGNORE, FP_CELL, FP_CELL);
	g_fwdOnClientWeaponDrop = CreateMultiForward(FWD_ON_CLIENT_WEAPON_DROP, ET_IGNORE, FP_CELL, FP_CELL);
}

public DestroyGlobalForwards()
{
	DestroyForward(g_fwdOnClientWeaponPickUp);
	DestroyForward(g_fwdOnClientWeaponDeploy);
	DestroyForward(g_fwdOnClientWeaponDrop);
}

/**
 * @param iClient       Player index.
 * @param iSkinIndex    Skin Index.
 * @return              Returns 1 if disabled, otherwise 0.
 * @error               Invalid callback function.
 */
public Call_OnClientWeaponPickUp(iClient, iSkinIndex)
{
	new iReturn;

	ExecuteForward(g_fwdOnClientWeaponPickUp, iReturn, iClient, iSkinIndex);

	return iReturn;
}

/**
 * @param iClient       Player index.
 * @param iSkinIndex    Skin Index.
 * @error               Invalid callback function.
 */
public Call_OnClientWeaponDeploy(iClient, iSkinIndex) {
	ExecuteForward(g_fwdOnClientWeaponDeploy, _, iClient, iSkinIndex);
}

/**
 * @param iClient       Player index.
 * @param iSkinIndex    Skin Index.
 * @error               Invalid callback function.
 */
public Call_OnClientWeaponDrop(iClient, iSkinIndex) {
	ExecuteForward(g_fwdOnClientWeaponDrop, _, iClient, iSkinIndex);
}
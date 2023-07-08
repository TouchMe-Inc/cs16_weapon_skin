#if defined _ws_core_included
  #endinput
#endif
#define _ws_core_included

native WS_GetSkinList(const sWeaponName[], &Array:aSkinList);
native WS_GetSkinWeaponId(iSkinIndex);
native WS_GetSkinName(iSkinIndex, sSkinName[], iLength);

forward WS_OnClientWeaponPickUp(iClient, iSkinIndex);
forward WS_OnClientWeaponDeploy(iClient, iSkinIndex);
forward WS_OnClientWeaponDrop(iClient, iSkinIndex);
public GetClientSkin(iClient, iWeponId) {
	return g_iClientSkin[iClient][iWeponId];
}

public SetClientSkin(iClient, iWeponId, iSkinIndex) {
	g_iClientSkin[iClient][iWeponId] = iSkinIndex;
}

public ResetClientSkin(iClient, iWeponId) {
	g_iClientSkin[iClient][iWeponId] = INVALID_SKIN;
}

public ResetClientSkinAll(iClient) {
	arrayset(g_iClientSkin[iClient], INVALID_SKIN, sizeof(g_iClientSkin[]));
}
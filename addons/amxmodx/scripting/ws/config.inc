public LoadConfig(const sPath[])
{
	new SMCParser:hParser = SMC_CreateParser();

	SMC_SetReaders(hParser, "Parser_KeyValue", "Parser_EnterSection", "Parser_LeaveSection");

	new SMCError:hSmcError = SMC_ParseFile(hParser, sPath);

	if (hSmcError != SMCError_Okay)
	{
		new sBuffer[64];
		SetFailState("%s", SMC_GetErrorString(hSmcError, sBuffer, charsmax(sBuffer)) ? sBuffer : "Fatal parse error");
	}

	SMC_DestroyParser(hParser);
}

public Parser_KeyValue(SMCParser:hParser, const sKey[], const sValue[])
{
	if (!sValue[0]) {
		return;
	}

	switch(g_eConfigSection)
	{
		case ConfigSection_Skin:
		{
			if (StrEqual(sKey, KEY_SKIN_NAME)) {
				copy(g_eTempSkinInfo[name], charsmax(g_eTempSkinInfo[name]), sValue);
			}

			if (StrEqual(sKey, KEY_SKIN_MODEL_W) && file_exists(sValue)) {
				copy(g_eTempSkinInfo[model_w], charsmax(g_eTempSkinInfo[model_w]), sValue);
			}

			if (StrEqual(sKey, KEY_SKIN_MODEL_V) && file_exists(sValue)) {
				g_eTempSkinInfo[model_v] = engfunc(EngFunc_AllocString, sValue);
			}

			if (StrEqual(sKey, KEY_SKIN_MODEL_P) && file_exists(sValue)) {
				g_eTempSkinInfo[model_p] = engfunc(EngFunc_AllocString, sValue);
			}
		}
	}
}

public Parser_EnterSection(SMCParser:hParser, const sName[])
{
	switch(g_eConfigSection)
	{
		case ConfigSection_None: g_eConfigSection = ConfigSection_Root;

		case ConfigSection_Root:
		{
			g_eConfigSection = ConfigSection_Skin;

			g_eTempSkinInfo[weapon_id] = 0;
			g_eTempSkinInfo[name] = 0;
			g_eTempSkinInfo[model_w] = 0;
			g_eTempSkinInfo[model_v] = 0;
			g_eTempSkinInfo[model_p] = 0;

			for(new iWeaponId = 1; iWeaponId < sizeof(WEAPON_NAME); iWeaponId++)
			{
				if (!StrEqual(sName, WEAPON_NAME[iWeaponId])) {
					continue;
				}

				g_eTempSkinInfo[weapon_id] = iWeaponId;
				break;
			}
		}
	}
}

public Parser_LeaveSection(SMCParser:hParser)
{
	switch(g_eConfigSection)
	{
		case ConfigSection_Root: g_eConfigSection = ConfigSection_None;

		case ConfigSection_Skin:
		{
			PushSkin(g_eTempSkinInfo);

			g_eTempSkinInfo[weapon_id] = 0;
			g_eTempSkinInfo[name] = 0;
			g_eTempSkinInfo[model_w] = 0;
			g_eTempSkinInfo[model_v] = 0;
			g_eTempSkinInfo[model_p] = 0;

			g_eConfigSection = ConfigSection_Root;
		}

		default: g_eConfigSection = ConfigSection_Root;
	}
}
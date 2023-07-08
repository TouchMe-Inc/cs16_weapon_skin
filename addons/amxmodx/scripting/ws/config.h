#define KEY_SKIN_NAME                  "name"
#define KEY_SKIN_MODEL_W               "model_w"
#define KEY_SKIN_MODEL_V               "model_v"
#define KEY_SKIN_MODEL_P               "model_p"

enum ConfigSection
{
	ConfigSection_None,
	ConfigSection_Root,
	ConfigSection_Skin,
}

new ConfigSection:g_eConfigSection = ConfigSection_None;
# About weapon_skin
Adds the ability to select a weapon model.

## Commands
* `!ws`, `/ws` - Show available models of active weapons.

# Menu features
Changing weapons while the menu is active will automatically update the menu to display the available models for the new weapon.

# Drop features
A player who has not chosen their own model, when picking up a weapon with a modified model, will see it.

# Adding a weapon model 
1. Open file `addons/amxmodx/configs/weapon_skin.cfg`.
2. Fill in the fields inside the Root block according to the template.
Example:
```
"Root"
{
	//"weapon_*"
	//{
	//	"name" "MENU NAME"                        <-- required
  	//  	"model_v" "models/PATH_TO_MODEL/v_*.mdl"  <-- required
	//	"model_w" "models/PATH_TO_MODEL/w_*.mdl"  <-- optional
	//	"model_p" "models/PATH_TO_MODEL/p_*.mdl"  <-- optional
	//}

	"weapon_deagle"
	{
		"name" "Night Shine"
		"model_w" "models/night_shine/w_deagle.mdl"
		"model_v" "models/night_shine/v_deagle.mdl"
		"model_p" "models/night_shine/p_deagle.mdl"
	}
}
```

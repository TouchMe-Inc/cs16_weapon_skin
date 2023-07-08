#define MENU_KEY_ALL                   1023
#define MENU_TIME_FOREVER              -1

#define KEY_1                          0
#define KEY_2                          1
#define KEY_8                          7
#define KEY_9                          8
#define KEY_0                          9

#define MENU_PER_PAGE                  5

#define MENU_SKINS                     "SkinMenu"
#define HANDLER_MENU_SKINS             "HandlerSkinMenu"

new g_iClientPage[MAX_PLAYERS + 1];
new g_iClientWeaponId[MAX_PLAYERS + 1];

new g_idSkinMenu = 0;
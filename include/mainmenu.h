#ifndef __MAINMENU_H__
#define __MAINMENU_H__

/* Includes Begin*/
#include "cot_menu.h"
#include "language.h"

//#include "temperaturemenu.h"
//#include "humiditymenu.h"

/* Includes End */
void LoadMainMenu(const cotMenuItemInfo_t *pItemInfo);
void MainMenuTask(const cotMenuItemInfo_t *pItemInfo);
#endif // __MAINMENU_H__

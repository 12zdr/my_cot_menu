#ifndef __WEIGHTMENU_H__
#define __WEIGHTMENU_H__

/* Includes Begin */
#include <stdio.h>
#include "cot_menu.h"
#include "language.h"
#include "common.h"
/* Includes End */
extern void EnterWeightMenu(const cotMenuItemInfo_t *pItemInfo);
extern void ExitWeightMenu(const cotMenuItemInfo_t *pItemInfo);
extern void LoadWeightMenu(const cotMenuItemInfo_t *pItemInfo);
extern void WeightMenuTask(const cotMenuItemInfo_t *pItemInfo);

#endif // __WEIGHTMENU_H__

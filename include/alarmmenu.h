#ifndef __ALARM_MENU_H__
#define __ALARM_MENU_H__

/* Includes Begin */
#include <stdio.h>
#include "cot_menu.h"
#include "language.h"
#include "common.h"
/* Inlcudes End */
/* Defines Begin */
extern void EnterAlarmMenu(const cotMenuItemInfo_t *pItemInfo);
extern void ExitAlarmMenu(const cotMenuItemInfo_t *pItemInfo);
extern void LoadAlarmMenu(const cotMenuItemInfo_t *pItemInfo);
extern void AlarmMenuTask(const cotMenuItemInfo_t *pItemInfo);
/* Defines End */
#endif // __ALARM_MENU_H__

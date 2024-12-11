#include <stdio.h>
#include <stdlib.h>
#include "cot_menu.h"
#include "language.h"
#include "mainmenu.h"
#include "common.h"

int isEnter = 0;

void EnterMainMenu(const cotMenuItemInfo_t *pItemInfo)
{
    isEnter = 1;
}

void ExitMainMenu(const cotMenuItemInfo_t *pItemInfo)
{
    isEnter = 0;
}

int main(int argc, char const *argv[])
{
    static cotMainMenuCfg_t sg_tMainMenu = COT_MENU_ITEM_BIND(TEXT_MAIN_MENU, EnterMainMenu, ExitMainMenu, LoadMainMenu, MainMenuTask, NULL);

    set_language(SYSTEM_LANGUAGE_ENGLISH);

    cotMenu_Init(&sg_tMainMenu);
    int cmd;
    while (1)
    {
        CLEAR();
        MOVETO(0, 0);

        if (!isEnter)
        {
            printf("%s(0-%s%s; 1-%s): ", get_text(TEXT_SELECT_OPTION), 
                    get_text(TEXT_ENTER), get_text(TEXT_MAIN_MENU), get_text(TEXT_EXIT));
            scanf(" %d", &cmd); // 空格作用是忽略上次的回车

            if (cmd == 0)
            {
                cotMenu_MainEnter();

                CLEAR();
                MOVETO(0, 0);
            }
            else if (cmd == 1)
            {
                break;
            }
        }

        cotMenu_Task();
    }

    cotMenu_DeInit();
    return 0;
}

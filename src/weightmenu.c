#include "weightmenu.h"

cotMenuList_t sg_tWeightMenuTable[] = {
    COT_MENU_ITEM_BIND(TEXT_SET_WEIGHT,NULL, NULL, NULL, OnCommonFunction, NULL),
    COT_MENU_ITEM_BIND(TEXT_SET_WEIGHT_THRESHOLD,NULL, NULL, NULL, OnCommonFunction, NULL)
};

static void ShowWeightMenu(cotMenuShow_t *ptShowInfo)
{
    uint8_t showNum = 1;
    menusize_t  tmpselect;

    cotMenu_LimitShowListNum(ptShowInfo, &showNum);

    printf("\e[0;30;46m ------------- %s ------------- \e[0m\n", get_text(ptShowInfo->uMenuDesc.textId));

    for (int i = 0; i < showNum; i++)
    {
        tmpselect = i + ptShowInfo->showBaseItem;

        if (tmpselect == ptShowInfo->selectItem)
        {
            printf("\e[0;30;47m %d. %-34s\e[0m\n", tmpselect + 1, get_text(ptShowInfo->uItemsListDesc[tmpselect].textId));
        }
        else
        {
            printf("\e[7;30;47m %d. %-34s\e[0m\n", tmpselect + 1, get_text(ptShowInfo->uItemsListDesc[tmpselect].textId));
        }
    }
}

void EnterWeightMenu(const cotMenuItemInfo_t *pItemInfo)
{

}

void ExitWeightMenu(const cotMenuItemInfo_t *pItemInfo)
{

}

void LoadWeightMenu(const cotMenuItemInfo_t *pItemInfo)
{
    cotMenu_Bind(sg_tWeightMenuTable, COT_GET_MENU_NUM(sg_tWeightMenuTable), ShowWeightMenu);
}

void WeightMenuTask(const cotMenuItemInfo_t *pItemInfo)
{
    int cmd;

    printf("%s(0-%s; 1-%s%s; 2-%s; 3-%s; 4-%s): ", 
            get_text(TEXT_SELECT_OPTION), get_text(TEXT_RETURN), get_text(TEXT_RETURN), get_text(TEXT_MAIN_MENU),
            get_text(TEXT_ENTER), get_text(TEXT_NEXT), get_text(TEXT_PREVIOUS));
    scanf(" %d", &cmd); 
 
    switch (cmd)
    {
    case 0:
        cotMenu_Exit(true);
        break;
    case 1:
        cotMenu_Reset();
        break;
    case 2:
        cotMenu_Enter();
        break;
    case 3:
        cotMenu_SelectNext(true);
        break;
    case 4:
        cotMenu_SelectPrevious(true);
        break;

    default:
        break;    
    }
}
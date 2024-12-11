#include "common.h"
#include "language.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void OnCommonFunction(const cotMenuItemInfo_t *pItemInfo)
{
    int cmd;

    printf("--------------------------\n");
    printf("     %s%s\n", get_text(pItemInfo->uMenuDesc.textId), "function test");
    printf("--------------------------\n");

    printf("%s(0-%s): ", 
            get_text(TEXT_SELECT_OPTION), get_text(TEXT_EXIT));
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车

    if (cmd == 0)
    {
        cotMenu_Exit(false);
    }
}
# 前言

这是我第一次编写Blog😜

在毕业设计的准备过程中，根据自己的构想，需要实现一个多级菜单，在经过一顿**“大搜特搜“**过后发现了一个多级菜单框架

> [轻量级多级菜单控制框架程序（C语言）](https://blog.csdn.net/qq_24130227/article/details/121167276?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22121167276%22%2C%22source%22%3A%22qq_24130227%22%7D&ctrtid=VbyfV)

以下是我的一些学习的过程记录

# 一、编译环境及移植准备

1. 编译环境

   - VSCODE 
   - GCC 8.1.0 x86_64-w64-mingw32
   - Cmake

2. 移植准备

   - 在gitee仓库下载源码[cotMenu: 嵌入式设备常用的菜单框架模块组件代码（轻量级）](https://gitee.com/cot_package/cot_menu)

   - ```shell
     可以使用 git clone https://gitee.com/const-zpc/menu.git 命令下载
     ```

   - 也可以下载 ZIP 压缩文件

# 二、移植过程

1. 构思多级菜单

<img src="E:\2425-毕业设计-智能猫粮喂食控制系统的设计与实现（张东锐）\设计图\菜单设计.png" style="zoom:50%;" />

2. 编辑菜单文本

以下分别是 ***language.h*** 和 ***language.c*** 文件的修改

```c
#ifndef LANGUAGE_H
#define LANGUAGE_H

typedef enum
{
    SYSTEM_LANGUAGE_CHINESE = 0,
    SYSTEM_LANGUAGE_ENGLISH,

    SYSTEM_LANGUAGE_ALL,
} SystemLanguage_e;


typedef enum
{
    TEXT_MAIN_MENU = 0,         // 主菜单
    TEXT_SELECT_OPTION,         // 选择操作
    TEXT_ENTER,                 // 进入
    TEXT_EXIT,                  // 退出
    TEXT_RETURN,                // 返回

    TEXT_ALARM,                 // 闹钟
    TEXT_WEIGHT,                // 重量
    TEXT_TEMPERATURE,           // 温度
    TEXT_HUMIDITY,              // 湿度

    TEXT_SET_ALARM,             // 设置闹钟
    TEXT_DELETE_ALARM,          // 删除闹钟
    TEXT_SET_WEIGHT,            // 设置重量
    TEXT_SET_WEIGHT_THRESHOLD,  // 设置重量阈值

    TEXT_NEXT,                  // 下一个
    TEXT_PREVIOUS,              // 上一个
    TEXT_EXIT_MAIN_MENU,        // 退出主菜单
    TEXT_RETURN_MAIN_MENU,      // 返回主菜单

    TEXT_ALL,
} TextId_e;

void set_language(SystemLanguage_e lang);
const char *get_text(TextId_e id);
const char *get_text_by_language(SystemLanguage_e lang, TextId_e id);

#endif

```

```c
#include "language.h"

static SystemLanguage_e sg_eSystemLanguage = SYSTEM_LANGUAGE_CHINESE;

const char *(sg_kSystemLanguage[TEXT_ALL])[SYSTEM_LANGUAGE_ALL] =
{
    [TEXT_MAIN_MENU] = {"主菜单", "main menu"},
    [TEXT_SELECT_OPTION] = {"选项", "select option"},
    [TEXT_ENTER] = {"进入", "enter"},
    [TEXT_EXIT] = {"退出", "exit"},
    [TEXT_RETURN] = {"返回", "return"},

    [TEXT_ALARM] = {"闹钟","alarm"},
    [TEXT_WEIGHT] = {"重量","weight"},
    [TEXT_TEMPERATURE] = {"温度","temperature"},
    [TEXT_HUMIDITY] = {"湿度","humidity"},

    [TEXT_SET_ALARM] = {"设置闹钟", "set alarm"},
    [TEXT_DELETE_ALARM] = {"删除闹钟", "delete alarm"},
    [TEXT_SET_WEIGHT] = {"设置重量", "set weight"},
    [TEXT_SET_WEIGHT_THRESHOLD] = {"设置重量阈值", "set weight threshold"},

    [TEXT_NEXT] = {"下一个", "next"},
    [TEXT_PREVIOUS] = {"上一个", "previous"},
    [TEXT_EXIT_MAIN_MENU] = {"退出主菜单", "exit main menu"},
    [TEXT_RETURN_MAIN_MENU] = {"返回主菜单", "return main menu"},


};

void set_language(SystemLanguage_e lang)
{
    if (lang >= 0 && lang < SYSTEM_LANGUAGE_ALL)
    {
        sg_eSystemLanguage = lang;
    }
}


const char *get_text(TextId_e id)
{
    static const char *pszNullString = "N/A";

    if (id >= 0 && id < TEXT_ALL)
    {
        return sg_kSystemLanguage[id][sg_eSystemLanguage];
    }

    return pszNullString; // 未找到对应文本
}

const char *get_text_by_language(SystemLanguage_e lang, TextId_e id)
{
    static const char *pszNullString = "N/A";

    if (id >= 0 && id < TEXT_ALL)
    {
        return sg_kSystemLanguage[id][lang];
    }

    return pszNullString; // 未找到对应文本
}

```

3. 移植相关菜单函数

首先设置主菜单并初始化 代码位置 ***main.c***

```C
    static cotMainMenuCfg_t sg_tMainMenu = COT_MENU_ITEM_BIND(TEXT_MAIN_MENU, EnterMainMenu, ExitMainMenu, LoadMainMenu, MainMenuTask, NULL);

    set_language(SYSTEM_LANGUAGE_ENGLISH); // 设置为英文显示

    cotMenu_Init(&sg_tMainMenu);
```

然后设置子菜单并且进行绑定到主菜单 代码位置 ***mainmenu.c***

```C
cotMenuList_t sg_tMainMenuTable[] = {
    COT_MENU_ITEM_BIND(TEXT_ALARM, EnterAlarmMenu,ExitAlarmMenu, LoadAlarmMenu,AlarmMenuTask,NULL),
    COT_MENU_ITEM_BIND(TEXT_WEIGHT, EnterWeightMenu,ExitWeightMenu, LoadWeightMenu,WeightMenuTask,NULL),
    COT_MENU_ITEM_BIND(TEXT_TEMPERATURE, NULL, NULL, NULL,OnCommonFunction, NULL),
    COT_MENU_ITEM_BIND(TEXT_HUMIDITY, NULL, NULL, NULL,OnCommonFunction, NULL),
};
```

再然后分别是 ***Alarm*** 和 ***Weight*** 的子菜单 也要进行绑定 代码位置 ***alarmmenu.c*** ***weightmenu.c***

```c
cotMenuList_t sg_tAlarmMenuTable[] = {
    COT_MENU_ITEM_BIND(TEXT_SET_ALARM,NULL,NULL,NULL,OnCommonFunction,NULL),
    COT_MENU_ITEM_BIND(TEXT_DELETE_ALARM,NULL,NULL,NULL,OnCommonFunction,NULL),
};
```

```C
cotMenuList_t sg_tWeightMenuTable[] = {
    COT_MENU_ITEM_BIND(TEXT_SET_WEIGHT,NULL, NULL, NULL, OnCommonFunction, NULL),
    COT_MENU_ITEM_BIND(TEXT_SET_WEIGHT_THRESHOLD,NULL, NULL, NULL, OnCommonFunction, NULL)
};
```

绑定到上一级菜单的函数 对应位置在 注释位置标出

```
cotMenu_Bind(sg_tMainMenuTable, COT_GET_MENU_NUM(sg_tMainMenuTable), ShowMainMenu); 
// mainmenu.c LoadMainMenu()

cotMenu_Bind(sg_tAlarmMenuTable,COT_GET_MENU_NUM(sg_tAlarmMenuTable),ShowAlarmMenu);
// alarmmenu.c LoadAlarmMenu()

cotMenu_Bind(sg_tWeightMenuTable, COT_GET_MENU_NUM(sg_tWeightMenuTable), ShowWeightMenu);
// weightmenu.c LoadWeightMenu()
```

最后是各种那个 ***EnterxxxxxMenu*** ***ExitxxxxMenu*** ***LoadxxxxMenu*** 和 ***运行时需要执行的函数***

以 mainmenu.c 为例

```C
   // 根据 主菜单的定义 需要传入的参数 
   // EnterMainMenu 有子菜单时 这个位置不能为NULL
   // ExitMainMenu
   // LoadMainMenu
   // MainMenuTask
   // NULL 的位置为想要显示的图标数据 自己决定
   // 前两个函数代码位置 main.c
   // 后两个在mainmenu.c
   static cotMainMenuCfg_t sg_tMainMenu = COT_MENU_ITEM_BIND(TEXT_MAIN_MENU, EnterMainMenu, ExitMainMenu, LoadMainMenu, MainMenuTask, NULL);
```

```c

int isEnter = 0;

void EnterMainMenu(const cotMenuItemInfo_t *pItemInfo)
{
    isEnter = 1;
}

void ExitMainMenu(const cotMenuItemInfo_t *pItemInfo)
{
    isEnter = 0;
}
```

```
static void ShowMainMenu(cotMenuShow_t *ptShowInfo) // 作为参数传入 cotMenu_Bind();
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
            printf("\e[0;30;47m %d. %-16s\e[0m |\n", tmpselect + 1, get_text(ptShowInfo->uItemsListDesc[tmpselect].textId));
        }
        else
        {
            printf("\e[7;30;47m %d. %-16s\e[0m |\n", tmpselect + 1, get_text(ptShowInfo->uItemsListDesc[tmpselect].textId));
        }
    }
}

void LoadMainMenu(const cotMenuItemInfo_t *pItemInfo)
{
    cotMenu_Bind(sg_tMainMenuTable, COT_GET_MENU_NUM(sg_tMainMenuTable), ShowMainMenu);
}

void MainMenuTask(const cotMenuItemInfo_t *pItemInfo)
{
    int cmd;

    printf("%s(0-%s; 1-%s; 2-%s; 3-%s; 4-%s): ", 
            get_text(TEXT_SELECT_OPTION), get_text(TEXT_EXIT_MAIN_MENU),get_text(TEXT_RETURN_MAIN_MENU),
            get_text(TEXT_ENTER), get_text(TEXT_NEXT), get_text(TEXT_PREVIOUS));
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车
 
    switch (cmd)
    {
    case 0:
        cotMenu_MainExit();
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
```

以上代码片段 最重要的是 ***cotMenu_Bind();*** 函数 函数原型代码位置 ***cot_menu.c***

它可以被放在 ***EnterxxxxxMenu*** 函数中 或 ***LoadxxxxxMenu*** 函数中 执行一次即可

```
/**
  * @brief      子菜单绑定当前菜单选项
  * 
  * @param      pMenuList       新的菜单列表
  * @param      menuNum         新的菜单列表数目
  * @param      pfnShowMenuFun  新的菜单列表显示效果回调函数, 为NULL则延续上级菜单显示效果
  * @return     0,成功; -1,失败 
  */
int cotMenu_Bind(cotMenuList_t *pMenuList, menusize_t menuNum, cotShowMenuCallFun_f pfnShowMenuFun)
{
    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    if (sg_tMenuManage.pMenuCtrl->pMenuList != NULL)
    {
        return 0;
    }

    sg_tMenuManage.pMenuCtrl->pMenuList = pMenuList;
    sg_tMenuManage.pMenuCtrl->itemsNum = menuNum;

    if (pfnShowMenuFun != NULL)
    {
        sg_tMenuManage.pMenuCtrl->pfnShowMenuFun = pfnShowMenuFun;
    }

    return 0;
}
```

# 三、实现效果

附上视频
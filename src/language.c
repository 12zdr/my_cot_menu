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

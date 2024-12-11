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

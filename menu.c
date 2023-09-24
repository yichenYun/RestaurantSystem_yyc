#include "menu.h"
/*******************************
 *功能：根据菜品id进行比较
 *参数：
 *      data1:数据1
 *      data2:数据2
 *返回值：相同返回true   不同返回false
 ********************************/
inline bool Cmp_id(void *data1, void *data2)
{
    Menu_t *value1 = data1;
    Menu_t *value2 = data2;
    return value1->id == value2->id;
}
/*******************************
 *功能：根据菜品name进行比较（模糊查找）
 *参数：
 *      data1:数据1
 *      data2:数据2
 *返回值：相同返回true   不同返回false
 ********************************/
inline bool Cmp_name(void *data1, void *data2)
{
    Menu_t *value1 = data1;
    Menu_t *value2 = data2;
    return strstr(value1->name, value2->name) != NULL; // 模糊查找
}
/*******************************
*功能：根据菜品price进行比较
*参数：
*      data1:数据1
*      data2:数据2
*返回值：相同返回true   不同返回false
********************************/
inline bool Cmp_price(void *data1, void *data2)
{
    Menu_t *value1 = data1;
    Menu_t *value2 = data2;
    return value1->price == value2->price;
}
/*******************************
*功能：根据菜品number进行比较
*参数：
*      data1:数据1
*      data2:数据2
*返回值：相同返回true   不同返回false
********************************/
inline bool Cmp_number(void *data1, void *data2)
{
    Menu_t *value1 = data1;
    Menu_t *value2 = data2;
    return value1->number == value2->number;
}
/*******************************
*功能：根据菜品flavor进行比较(模糊查找)
*参数：
*      data1:数据1
*      data2:数据2
*返回值：相同返回true   不同返回false
********************************/
inline bool Cmp_flavor(void *data1, void *data2)
{
    Menu_t *value1 = data1;
    Menu_t *value2 = data2;
    return strstr(value1->flavor, value2->flavor) != NULL;
}
/*******************************
*功能：更改菜品属性
*参数：
*      data1:旧数据
*      data2:新数据
*      mode:模式选择 1(id) 2(name) 3(price) 4(number) 5(flavor)
*返回值：无
********************************/
inline void Menu_Updata(void *data1, void *data2, int mode)
{
    Menu_t *value1 = data1;
    Menu_t *value2 = data2;
    switch (mode)
    {
    case 1:
        value1->id = value2->id;
        break;
    case 2:
        strcpy(value1->name, value2->name);
        break;
    case 3:
        value1->price = value2->price;
        break;
    case 4:
        value1->number = value2->number;
        break;
    case 5:
        strcpy(value1->flavor, value2->flavor);
        break;
    }
}
/*******************************
 *功能：刷新菜品剩余数量
 *参数：
 *      data:菜谱数据
 *      mode:为0数量减1，为1数量=1,为2数量加1
 *返回值：
 ********************************/
inline void Menu_Updata_number(void *data, int mode)
{
    Menu_t *value = data;
    switch (mode)
    {
    case 0:
        value->number--;
        break;
    case 1:
        value->number = 1;
        break;
    case 2:
        value->number++;
        break;
    }
}
/*******************************
*功能：比较密码
*参数：
*      data1:数据1
*      data2:数据2
*返回值：相同返回true 不同返回false
********************************/
bool Cmp_name_passwd(void *data1, void *data2)
{
    User_t *value1 = data1;
    User_t *value2 = data2;
    return strcmp(value1->id, value2->id) == 0 && strcmp(value1->passwd, value2->passwd) == 0;
}
/*******************************
*功能：根据id升序
*参数：
*      data1:数据1
*      data2:数据2
*返回值：成功返回true,失败返回false
********************************/
bool Cmp_SortId(void *data1,void *data2)
{
    Menu_t *value1 = data1;
    Menu_t *value2 = data2;
    return value1->id > value2->id;
}
/*******************************
*功能：根据Price升序
*参数：
*      data1:数据1
*      data2:数据2
*返回值：成功返回true,失败返回false
********************************/
bool Cmp_SortPrice(void *data1,void *data2)
{
    Menu_t *value1 = data1;
    Menu_t *value2 = data2;
    return value1->price > value2->price;
}
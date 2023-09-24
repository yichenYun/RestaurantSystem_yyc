#ifndef __MENU_H__
#define __MENU_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MENUNAME "menu.txt" // 菜谱文件名
#define USERNAME "user.txt" // 用户信息文件名
// 从文件中读取菜谱格式
#define READ_FORMAT "%d%s%f%d%s"
#define READ_DATA(value) &value.id, value.name, &value.price, &value.number, value.flavor
// 输出菜品的格式
#define PRINT_FORMAT "%10s\t%-20s\t%-10s\t%-10s\t%s\n"
#define PRINT_DATA "菜品编号", "菜名", "单价", "剩余数量", "口味"
// 写入内容到菜谱的的格式
#define WRITE_FORMAT "%-10d\t%-20s\t%-10.2f\t%-10d\t%s\n"
#define WRITE_DATA(value) value->id, value->name, value->price, value->number, value->flavor
// 菜品结构体
typedef struct menu
{
    int id;
    char name[20];
    float price;
    int number;
    char flavor[20];
} Menu_t;
// 用户信息结构体
typedef struct user
{
    char id[20];
    char passwd[20];
    char phone[12];

} User_t;

extern bool Cmp_id(void *data1, void *data2); 
extern bool Cmp_name(void *data1, void *data2);
extern bool Cmp_price(void *data1, void *data2);
extern bool Cmp_number(void *data1, void *data2);
extern bool Cmp_flavor(void *data1, void *data2);

extern bool Cmp_name_passwd(void *data1, void *data2);

extern void Menu_Updata(void *data1, void *data2, int mode);
extern void Menu_Updata_number(void *data, int mode);

extern bool Cmp_SortId(void *data1,void *data2);
extern bool Cmp_SortPrice(void *data1,void *data2);

#endif
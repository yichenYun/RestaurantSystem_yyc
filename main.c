#include "menu.h"
#include "list.h"

#define adminPasswd "1" // 设置管理员密码
char LISTNAME[20];      //"用户订单.txt"

void Print_MENU(void *data);
void Print_Write(void *data);
void Print_Write_userlist(void *data);
void Print_Write_userName(void *data);

const char *DATA[] = {PRINT_DATA};
int main(int argc, const char *argv[])
{
    List_t l = List_Init();        // 管理员菜单链表
    List_t userlist = List_Init(); // 用户订单链表
    List_t userName = List_Init(); // 用户信息表

    FILE *fp = NULL;
    Node_t *node = NULL;
    Menu_t m, *menu;
    User_t user;

    // 读取菜谱信息
    fp = fopen(MENUNAME, "r");
    if (fp != NULL)
    {
        while (fscanf(fp, READ_FORMAT, READ_DATA(m)) > 0) // 读取数据保存到m
        {
            List_PushBack(&l, &m, sizeof(m)); // 将数据写入链表
        }
        fclose(fp);
    }
    // 读取用户信息
    fp = fopen(USERNAME, "r");
    if (NULL != fp)
    {
        while (fscanf(fp, "%20s%20s%12s\n", user.id, user.passwd, user.phone) > 0)
        {
            List_PushBack(&userName, &user, sizeof(user));
        }
        fclose(fp);
    }

    int select;
    char ch;
    bool (*Cmp)(void *, void *); // 比较用的函数指针

    while (1)
    {
    first:
        system("clear");
        printf("···········点餐系统···········\n");
        printf("1.用户登录\n");
        printf("2.用户注册\n");
        printf("3.管理员登录\n");
        printf("4.退出\n");
        printf("-----------------------------\n");
        printf("请输入你的选项：\n");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            system("clear");
            char uName[20], uPasswd[20];
            printf("---------------登录界面---------------\n");
            printf("用户ID：");
            scanf("%s", uName);
            printf("  密码：");
            scanf("%s", uPasswd);
            memset(&user, 0, sizeof(user));
            strcpy(user.id, uName);
            strcpy(user.passwd, uPasswd);

            if (List_FindNode(&userName, &user, Cmp_name_passwd) != NULL)
                while (1)
                {
                quit:
                    system("clear");
                    printf("···········用户点餐界面···········\n");
                    printf("1.查看菜单\n");
                    printf("2.菜品添加\n");
                    printf("3.菜品删除\n");
                    printf("4.菜品搜索\n");
                    printf("5.查看订单\n");
                    printf("6.提交订单\n");
                    printf("7.退出\n");

                    printf("请输入你的选项：\n");
                    scanf("%d", &select);
                    switch (select)
                    {
                    case 1:
                        system("clear");
                        printf(PRINT_FORMAT, PRINT_DATA);
                        List_Foreach(&l, Print_MENU);
                        break;
                    case 2:
                        system("clear");
                        printf("-------------添菜---------------\n");
                        memset(&m, 0, sizeof(m));
                        printf("请输入菜品编号：");
                        scanf("%d", &m.id);

                        node = List_FindNode(&l, &m, Cmp_id); // 进行节点查找判断
                        if (node == NULL)
                        {
                            printf("菜品不存在！\n");
                            break;
                        }

                        menu = node->data;

                        printf("查找到：\n");
                        printf(PRINT_FORMAT, PRINT_DATA);
                        printf(WRITE_FORMAT, WRITE_DATA(menu));

                        printf("请输入Y/N选择是否添加到订单:");
                        getchar();
                        scanf("%c", &ch);
                        if (ch == 'Y' || ch == 'y')
                        {
                            m = *menu;
                            Menu_Updata_number(&m, 1);               // 订单里面的数量置为1
                            List_PushBack(&userlist, &m, sizeof(m)); // 写入到订单文档中
                            Menu_Updata_number(menu, 0);             // 菜谱里面的数量减1
                            printf("添加完成!\n");
                        }
                        break;
                    case 3:
                        system("clear");
                        printf("-------------减菜---------------\n");
                        printf("您的订单:\n");
                        printf(PRINT_FORMAT, PRINT_DATA);
                        List_Foreach(&userlist, Print_MENU); // 打印订单信息
                        printf("\n");

                        memset(&m, 0, sizeof(m));
                        printf("请输入菜品编号：");
                        scanf("%d", &m.id);
                        node = List_FindNode(&userlist, &m, Cmp_id);
                        if (node == NULL)
                        {
                            printf("菜品不存在！\n");
                            break;
                        }
                        menu = node->data;
                        printf("查找到：\n");
                        printf(PRINT_FORMAT, PRINT_DATA);
                        printf(WRITE_FORMAT, WRITE_DATA(menu));

                        printf("请输入Y/N选择是否删除:");
                        getchar();
                        scanf("%c", &ch);
                        if (ch == 'Y' || ch == 'y')
                        {
                            List_Erase(&userlist, node);
                            node = List_FindNode(&l, &m, Cmp_id);
                            Menu_Updata_number(node->data, 2); // 从订单中删除后菜谱中加1

                            printf("删除完成!\n");
                        }
                        break;
                    case 4:
                        system("clear");
                        printf("-------------查找菜谱---------------\n");
                        for (int i = 1; i <= 5; i++)
                        {
                            printf("%d.%s\n", i, DATA[i - 1]);
                        }
                        printf("请输入要查找的选项：\n");
                        scanf("%d", &select);

                        if (select < 1 || select > 5)
                        {
                            printf("不存在此选项！\n");
                            break;
                        }

                        memset(&m, 0, sizeof(m));
                        switch (select)
                        {
                        case 1:
                            printf("请输入菜品编号：");
                            scanf("%d", &m.id);
                            Cmp = Cmp_id;

                            break;
                        case 2:
                            printf("请输入菜名：");
                            scanf("%s", m.name);
                            Cmp = Cmp_name;

                            break;
                        case 3:
                            printf("请输入价格：");
                            scanf("%f", &m.price);
                            Cmp = Cmp_price;
                            break;
                        case 4:

                            printf("请输入数量：");
                            scanf("%d", &m.number);
                            Cmp = Cmp_number;
                            break;
                        case 5:
                            printf("请输入口味：");
                            scanf("%s", m.flavor);
                            Cmp = Cmp_flavor;
                            break;
                        }
                        node = List_FindNode(&l, &m, Cmp);
                        if (node == NULL)
                        {
                            printf("查找失败！\n");
                            break;
                        }

                        printf("查找成功：\n");
                        printf(PRINT_FORMAT, PRINT_DATA);
                        while (node != NULL)
                        {
                            menu = node->data;
                            printf(WRITE_FORMAT, WRITE_DATA(menu));
                            node = List_FindNode(NULL, &m, Cmp);
                        }
                        printf("\n");
                        break;
                    case 5:
                        system("clear");
                        printf(PRINT_FORMAT, PRINT_DATA);
                        List_Foreach(&userlist, Print_MENU);
                        break;

                    case 6:
                        strcat(LISTNAME, uName); // 订单文件用ID命名
                        strcat(LISTNAME, "用户订单.txt");
                        goto submit;

                    case 7:
                        List_Clear(&userlist); // 清空订单
                        goto first;
                    }

                    printf("按任意健继续......\n");
                    getchar();
                    getchar();
                }
            else
            {
                system("clear");
                printf("用户名或密码错误！！\n");
                printf("按任意健继续......\n");
                getchar();
                getchar();
            }
            break;
        case 2:
            system("clear");
            printf("···········用户注册界面···········\n");
            memset(&user, 0, sizeof(user));
            printf("请输入用户ID:\n");
            scanf("%s", user.id);
            printf("请输入用户密码:\n");
            scanf("%s", user.passwd);
            printf("请输入手机号:\n");
            scanf("%s", user.phone);
            List_PushBack(&userName, &user, sizeof(user));
            fp = fopen(USERNAME, "w"); // 文件不存在则新建
            fclose(fp);
            List_Foreach(&userName, Print_Write_userName); // 写入用户信息
            printf("注册成功！！！");
            getchar();
            getchar();
            break;
        case 3:
            system("clear");
            char passwd[20];
            printf("请输入管理员密码：");
            scanf("%s", passwd);
            if (strcmp(passwd, adminPasswd))
            {
                printf("密码错误！！！\n");
                printf("按任意健继续......\n");
                getchar();
                getchar();
                break;
            }
            while (1)
            {

                system("clear");
                printf("···········管理员界面···········\n");
                printf("1.查看菜单\n");
                printf("2.增加菜单菜品\n");
                printf("3.删除菜单菜品\n");
                printf("4.更改菜单菜品\n");
                printf("5.保存并退出\n");
                printf("0.菜品排序\n");
                printf("请输入你的选项：\n");
                scanf("%d", &select);

                switch (select)
                {
                case 0:
                    system("clear");
                    printf("···········排序界面···········\n");
                    printf("1.按菜品id排序\n");
                    printf("2.按菜品price排序\n");
                    printf("请输入你的选项：\n");
                    scanf("%d", &select);
                    if (select == 1)
                    {
                        List_Sort(&l, Cmp_SortId);
                    }
                    else if (select == 2)
                    {
                        List_Sort(&l, Cmp_SortPrice);
                    }
                    else
                    {
                        printf("没有此选项！\n");
                        printf("按任意键继续!\n");
                        getchar();
                        getchar();
                        break;
                    }
                    printf("排序完成！\n");

                    break;
                case 1:
                    system("clear");
                    printf(PRINT_FORMAT, PRINT_DATA);
                    List_Foreach(&l, Print_MENU);
                    break;
                case 2:
                    system("clear");
                    printf("-------------添加菜谱---------------\n");
                    memset(&m, 0, sizeof(m));
                    m.id = 1000 + l.size + 1; // 菜品id根据菜品数量递增变化
                    printf("新菜ID：%d\n", m.id);
                    printf("请输入菜名：");
                    scanf("%s", m.name);
                    printf("请输入价格：");
                    scanf("%f", &m.price);
                    printf("请输入数量：");
                    scanf("%d", &m.number);
                    printf("请输入口味：");
                    scanf("%s", m.flavor);
                    List_PushBack(&l, &m, sizeof(m));
                    printf("添加完成!\n");
                    break;
                case 3:
                    system("clear");
                    printf("-------------删除菜谱---------------\n");
                    memset(&m, 0, sizeof(m));
                    printf("请输入菜品编号：");
                    scanf("%d", &m.id);
                    node = List_FindNode(&l, &m, Cmp_id);
                    if (node == NULL)
                    {
                        printf("菜品不存在！\n");
                        break;
                    }
                    menu = node->data;
                    printf("查找到：\n");
                    printf(PRINT_FORMAT, PRINT_DATA);
                    printf(WRITE_FORMAT, WRITE_DATA(menu));

                    printf("请输入Y/N选择是否删除:");
                    getchar();
                    scanf("%c", &ch);
                    if (ch == 'Y' || ch == 'y')
                    {
                        List_Erase(&l, node);
                        printf("删除完成!\n");
                    }

                    break;
                case 4:
                    system("clear");
                    printf("-------------修改菜谱---------------\n");
                    memset(&m, 0, sizeof(m));
                    printf("请输入菜品编号：");
                    scanf("%d", &m.id);
                    node = List_FindNode(&l, &m, Cmp_id);
                    if (node == NULL)
                    {
                        printf("菜品不存在！\n");
                        break;
                    }
                    menu = node->data;
                    printf("查找成功：\n");
                    printf(PRINT_FORMAT, PRINT_DATA);
                    printf(WRITE_FORMAT, WRITE_DATA(menu));
                    printf("\n");
                    for (int i = 1; i <= 5; i++)
                    {
                        printf("%d.%s\n", i, DATA[i - 1]);
                    }
                    printf("请输入要修改的选项：\n");
                    scanf("%d", &select);

                    if (select < 1 || select > 5)
                    {
                        printf("不存在此选项！\n");
                        break;
                    }

                    switch (select)
                    {
                    case 1:
                        printf("请输入新的[菜品编号]:");
                        scanf("%d", &m.id);
                        Menu_Updata(menu, &m, select);
                        break;
                    case 2:
                        printf("请输入新的[菜名]:");
                        scanf("%s", m.name);
                        Menu_Updata(menu, &m, select);
                        break;
                    case 3:
                        printf("请输入新的[单价]:");
                        scanf("%f", &m.price);
                        Menu_Updata(menu, &m, select);
                        break;
                    case 4:
                        printf("请输入新的[剩余数量]:");
                        scanf("%d", &m.number);
                        Menu_Updata(menu, &m, select);
                        break;
                    case 5:
                        printf("请输入新的[口味]:");
                        scanf("%s", m.flavor);
                        Menu_Updata(menu, &m, select);
                        break;
                    }
                    printf("修改成功!\n");
                    break;
                case 5:
                    fp = fopen(MENUNAME, "w");
                    fclose(fp);
                    List_Foreach(&l, Print_Write);
                    goto first;
                }
                printf("按任意键继续！");
                getchar();
                getchar();
            }
            break;
        case 4:
            goto out;
            break;
        default:
            system("clear");
            printf("请输入正确的选项！！！\n");
            printf("按Enter键继续...");
            getchar();
            getchar();
        }
    }
submit:
    // 保存订单信息
    fp = fopen(LISTNAME, "w");
    fclose(fp);
    List_Foreach(&userlist, Print_Write_userlist);
    //刷新菜谱信息(剩余数量)
    fp = fopen(MENUNAME, "w");
    fclose(fp);
    List_Foreach(&l, Print_Write);

out:
    // 销毁链表
    List_Free(&l);
    List_Free(&userlist);
    List_Free(&userName);

    return 0;
}
/*******************************
 *功能：打印菜品函数
 *参数：
 *      data:菜品节点指针
 *返回值：无
 ********************************/
void Print_MENU(void *data)
{
    Menu_t *value = data;
    printf(WRITE_FORMAT, WRITE_DATA(value));
}
/*******************************
 *功能：写入数据到菜谱文件的函数格式
 *参数：
 *      data:菜品节点指针
 *返回值：无
 ********************************/
void Print_Write(void *data)
{
    Menu_t *value = data;
    FILE *fp = fopen(MENUNAME, "a+");
    fprintf(fp, WRITE_FORMAT, WRITE_DATA(value));
    fclose(fp);
}
/*******************************
 *功能：写入数据到订单中的函数格式
 *参数：
 *      data:菜品节点指针
 *返回值：无
 ********************************/
void Print_Write_userlist(void *data)
{
    Menu_t *value = data;
    FILE *fp = fopen(LISTNAME, "a+");
    fprintf(fp, WRITE_FORMAT, WRITE_DATA(value));
    fclose(fp);
}
/*******************************
 *功能：写入数据到用户文件的函数格式
 *参数：
 *      data:用户信息节点指针
 *返回值：无
 ********************************/
void Print_Write_userName(void *data)
{
    User_t *user = data;
    FILE *fp = fopen(USERNAME, "a+");
    fprintf(fp, "%-20s%-20s%-12s\n", user->id, user->passwd, user->phone);
    fclose(fp);
}
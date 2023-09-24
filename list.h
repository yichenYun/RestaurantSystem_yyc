#ifndef __LIST_H__
#define __LIST_H__
/****** 可能需要的头文件 ******/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/****** 判错的宏函数 *********/
#define IS_ERR(v1, op, v2, err, ret)                                                            \
    if (v1 op v2)                                                                               \
    {                                                                                           \
        printf("文件名:%s,函数名:%s,行号:%d,错误信息:%s\n", __FILE__, __func__, __LINE__, err); \
        return ret;                                                                             \
    }
/****** 节点结构体　**********/
typedef struct Node
{
    void *data;        /***** 数据域:万能类型 ******/
    struct Node *prev; // 上一个节点地址
    struct Node *next; // 下一个节点地址
} Node_t;

/******　链表结构体 ***********/
typedef struct
{
    Node_t *head; // 链表表头
    int size;     // 元素个素
} List_t;

/******　链表相关API函数 *******/
extern List_t List_Init(void);    // 初始化
extern void List_Foreach(List_t *v,void (*Print)(void *)); //遍历

extern bool List_PushBack(List_t *v, void *data, int size); //尾部插入
extern bool List_PushFront(List_t *v, void *data, int size);//
extern bool List_Insert(List_t *v, void *data, int size);

extern bool List_PopFront(List_t *v);             //头部删除
extern bool List_PopBack(List_t *v);              //尾部删除
extern bool List_Erase(List_t *v, Node_t *index); //指定位置删除

extern bool List_IsEmpty(List_t *v);                //判空

extern Node_t *List_FindNode(List_t *v, void *data, bool (*Cmp)(void *data1, void *data2)); //查找
extern void List_Sort(List_t *v,bool (*Cmp)(void *data1,void *data2));  //排序

extern void List_Clear(List_t *v);  //清空
extern void List_Free(List_t *v);   //销毁

extern void List_Reserve(List_t *v);    //反转

#endif
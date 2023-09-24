#include "list.h"

/*******************************
*功能：创建一个node类型的新节点
*参数：
*      data:节点数据
*       size:节点大小
*返回值：数据节点指针
********************************/
static Node_t *NewNode(void *data, int size)
{
    Node_t *node = malloc(sizeof(Node_t));
    node->data = malloc(size);
    memcpy(node->data, data, size);
    node->next = NULL;
    node->prev = NULL;

    return node;
}
/*******************************
*功能：初始化链表
*参数：无
*返回值：链表节点
********************************/
List_t List_Init(void)
{
    List_t v;
    Node_t *node = malloc(sizeof(Node_t));

    node->data = NULL;
    node->prev = node;
    node->next = node;

    v.head = node;
    v.size = 0;

    return v;
}
/*******************************
*功能：尾部插入数据节点
*参数：
*      v:链表头指针
*      data:数据
*      size:大小
*返回值：成功返回true  失败返回false
********************************/
bool List_PushBack(List_t *v, void *data, int size)
{
    IS_ERR(v, ==, NULL, "容器为空", false);
    IS_ERR(data, ==, NULL, "数据为空", false);

    Node_t *head = v->head;
    Node_t *end = head->prev;

    Node_t *node = NewNode(data, size);

    end->next = node;
    head->prev = node;

    node->prev = end;
    node->next = head;

    v->size += 1;

    return true;
}
/*******************************
*功能：遍历链表
*参数：
*     v:链表头指针
*     Print:打印格式函数指针
*返回值：无
********************************/
void List_Foreach(List_t *v, void (*Print)(void *))
{
    IS_ERR(v, ==, NULL, "容器为空", );
    IS_ERR(Print, ==, NULL, "函数为空", );
    Node_t *node = v->head->next;

    while (node != v->head)
    {
        Print(node->data);
        node = node->next;
    }
}
/*******************************
*功能：尾部删除
*参数：
*     v:链表头指针
*返回值：成功返回true  失败返回false
********************************/
bool List_PopBack(List_t *v)
{
    IS_ERR(v, ==, NULL, "容器为空", false);
    if (v->size <= 0)
        return false;

    Node_t *head = v->head;
    Node_t *end = head->prev->prev;
    free(head->prev->data);
    free(head->prev);

    head->prev = end;
    end->next = head;

    v->size -= 1;

    return true;
}
/*******************************
*功能：头部删除
*参数：
*     v:链表头指针
*返回值：成功返回true  失败返回false
********************************/
bool List_PopFront(List_t *v)
{
#if 0
    IS_ERR(v, ==, NULL, "容器为空", false);
    if (v->size <= 0)
        return false;
    Node_t *head = v->head;
    Node_t *end = head->next->next;
    free(head->next->data);
    free(head->next);

    head->next = end;
    end->prev = head;
    v->size -= 1;

    return true;
#else
    return List_Erase(v, v->head->next);
#endif
}
/*******************************
*功能：指定位置删除
*参数：
*     v:链表头指针
*     index:要删除的节点
*返回值：成功返回true  失败返回false
********************************/
bool List_Erase(List_t *v, Node_t *index)
{
    IS_ERR(v, ==, NULL, "容器为空", false);
    if (v->size <= 0)
        return false;

    Node_t *prev = index->prev;
    Node_t *next = index->next;

    free(index->data);
    free(index);

    prev->next = next;
    next->prev = prev;

    v->size -= 1;

    return true;
}
/*******************************
*功能：查找节点（存在多个也可查找）
*参数：
*     v:链表头指针
*     data:被查数据
*     Cmp:比较方式函数指针
*返回值：成功返回节点指针  失败返回NULL
********************************/
Node_t *List_FindNode(List_t *v, void *data, bool (*Cmp)(void *data1, void *data2))
{
    IS_ERR(Cmp, ==, NULL, "函数为空", NULL);

    static Node_t *s_head = NULL;
    static Node_t *s_node = NULL;
    Node_t *node;

    if (v != NULL)
    {
        s_head = v->head;
        node = s_head->next;
    }
    else
    {
        node = s_node->next;
    }

    while (node != s_head)
    {
        if (Cmp(node->data, data) == true)
        {
            s_node = node;
            return node;
        }
        node = node->next;
    }

    return NULL;
}
/*******************************
*功能：清空链表（表头还在）
*参数：
*     v:链表头指针
*返回值：无
********************************/
void List_Clear(List_t *v)
{
    IS_ERR(v, ==, NULL, "容器为空", );
    if (v->size <= 0)
        return;
    Node_t *node = v->head->next;
    while (node != v->head)
    {
        Node_t *temp = node;
        node = node->next;
        free(temp->data);
        free(temp);
    }
    v->head->next = v->head;
    v->head->prev = v->head;
    v->size = 0;
}
/*******************************
*功能：销毁链表（无表头）
*参数：
*     v:链表头指针
*返回值：无
********************************/
void List_Free(List_t *v)
{
    List_Clear(v);
    free(v->head);
    v->head = NULL;
    v->size = 0;
}
/*******************************
*功能：链表排序
*参数：
*     v:链表头指针
*     Cmp:排序比较方式的函数指针
*返回值：无
********************************/
void List_Sort(List_t *v, bool (*Cmp)(void *data1, void *data2))
{
    IS_ERR(v, ==, NULL, "容器为空", );
    IS_ERR(Cmp, ==, NULL, "函数为空", );

    Node_t *q, *p;
    void *temp;
    for (q = v->head->next; q != v->head->prev; q = q->next)
        for (p = v->head->next; p != v->head->prev; p = p->next)
        {
            if (Cmp(p->data, p->next->data))
            {
                temp = p->data;
                p->data = p->next->data;
                p->next->data = temp;
            }
        }
}
/*******************************
*功能：链表反序
*参数：
*     v:链表头指针
*返回值：无
********************************/
void List_Reserve(List_t *v)
{
    IS_ERR(v, ==, NULL, "容器为空", );
    if (v->size <= 0)
        return;

    Node_t *node = v->head->next, *p=NULL;
    while (node != v->head)
    {
        p = node->prev;
        node->prev = node->next;
        node->next = p;
        node = node->prev;
    }
    p = node->prev;
    node->prev = node->next;
    node->next = p;
}
/*******************************
*功能：判断链表是否为空
*参数：
*      v:链表指针
*返回值：空返回true   非空返回false
********************************/
bool List_IsEmpty(List_t *v)
{
    IS_ERR(v, ==, NULL, "容器为空",true);

    return v->size <= 0;
}
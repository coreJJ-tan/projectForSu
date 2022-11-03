要求：
    时间复杂度O(n)
    空间复杂度O(1)
思路：
    将链表成员拷贝并入栈，然后再出栈与原链表节点一一对比，节点值不等则失败。
#include <stdio.h>
#include <stdlib.h>

#ifndef NULL
#define NULL ((*)0)
#endif

struct list_head {
    int value;
    struct list_head *next;
};

int list_init(struct list_head *head)
{
    if(!head)
        return -1;
    head->next = NULL;
    head->value = 0;
    return 0;
}

int list_add_tail(struct list_head *head, int value)
{
    struct list_head *node = NULL;
    if(!head)
        return -1;

    node = (struct list_head *)malloc(sizeof(struct list_head));
    if(!node)
        return -1;
    
    node->value = value;
    node->next = head->next;
    head->next = node;
    return 0;
}

int del_list(struct list_head *head)
{
    struct list_head *tmp;
    if(!head)
        return -1;
    tmp = head->next;
    head->next = NULL;
    free(head);
    
    while(tmp)
    {
        tmp = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return 0;
}

int print_list_value(struct list_head *head)
{
    struct list_head *tmp;
    if(!head)
        return -1;
    tmp = head->next;
    while(tmp)
    {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
    return 0;
}

struct list_head *reversal_list(struct list_head *head)
{   //翻转链表
    struct list_head *tmp1, *tmp2;
    struct list_head *head_new = (struct list_head *)malloc(sizeof(struct list_head));
    if(!head_new)
        return NULL;
    if(!head)
    {
        free(head_new);
        return NULL;
    }
    list_init(head_new);
    tmp1 = head->next;

    while(tmp1)
    {
        list_add_tail(head_new, tmp1->value);
        tmp1 = tmp1->next;
    }
    return head_new;
}



int main(int argc, char* argv[])
{
    struct list_head *list, *list_new;
    struct list_head *tmp1, *tmp2;
    int flag = 1;

    list = (struct list_head *)malloc(sizeof(struct list_head));
    if(!list)
        return -1;
    list_init(list);
    list_add_tail(list, 1);
    list_add_tail(list, 2);
    list_add_tail(list, 5);
    list_add_tail(list, 6);
    list_add_tail(list, 7);
    list_add_tail(list, 7);
    list_add_tail(list, 6);
    list_add_tail(list, 5);
    list_add_tail(list, 2);
    list_add_tail(list, 1);

    list_new = reversal_list(list);
    if(!list_new)
        return -1;

    tmp1 = list->next;
    tmp2 = list_new->next;
    while(tmp1 != NULL && tmp2 != NULL)
    {
        /*  这一步不需要了，因为肯定会同时为NULL
        if(tmp1 == NULL || tmp2 == NULL)
        {
            flag = 0;
            printf("不是回文结构\n");
            break;
        }
        */
        if(tmp1->value == tmp2->value)
        {
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
            continue;
        }
        else
        {
            flag = 0;
            printf("不是回文结构\n");
            break;
        }
    }
    if(flag)
        printf("是回文结构\n");

    del_list(list);
    del_list(list_new);
    return 0;
}
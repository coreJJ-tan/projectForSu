要求：
    时间复杂度O(n)
    空间复杂度O(1)
思路：
    按照单向链表节点添加的规则，此时最后一个时靠近链表头的，因此，只需要创建一个临时链表头，从靠近旧链表头的元素开始添加，得到新的链表即为原链表的翻转。

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

int reversal_list(struct list_head *head)
{   //翻转链表
    struct list_head *tmp1, *tmp2;
    struct list_head *head_new = (struct list_head *)malloc(sizeof(struct list_head));
    if(!head_new)
        return -1;
    if(!head)
    {
        free(head_new);
        return -1;
    }
    list_init(head_new);
    tmp1 = head->next;

    while(tmp1)
    {
        tmp2 = tmp1->next;
        tmp1->next = head_new->next;
        head_new->next = tmp1;
        tmp1 = tmp2;
    }
    head->next = head_new->next;
    free(head_new);
    return 0;
}


int main(int argc, char* argv[])
{
    int i;
    struct list_head *head = (struct list_head *)malloc(sizeof(struct list_head));
    list_init(head);

    if(!head)
        return -1;
    for(i = 0; i < 10; i++)
        list_add_tail(head, i);

    printf("原链表：\n");
    print_list_value(head);

    reversal_list(head);
    printf("翻转链表：\n");
    print_list_value(head);
    del_list(head);
    return 0;
}
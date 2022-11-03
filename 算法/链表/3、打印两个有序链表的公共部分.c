要求：
    时间复杂度O(n)
    空间复杂度O(1)
思路：
    分别用两个变量遍历两个链表，若节点值相等，那么获得公共部分，若节点值不相等，则小的那个变量指向下一个节点，另一个不变，进行下一轮对比，指导其中一个为NULL

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
    struct list_head *list1, *list2;
    struct list_head *tmp1, *tmp2;

    list1 = (struct list_head *)malloc(sizeof(struct list_head));
    if(!list1)
        return -1;
    list_init(list1);
    list2 = (struct list_head *)malloc(sizeof(struct list_head));
    if(!list2)
        return -1;
    list_init(list2);

    list_add_tail(list1, 1);
    list_add_tail(list1, 2);
    list_add_tail(list1, 5);
    list_add_tail(list1, 6);
    list_add_tail(list1, 7);
    list_add_tail(list1, 8);
    list_add_tail(list1, 10);
    list_add_tail(list1, 12);
    list_add_tail(list1, 13);
    list_add_tail(list1, 15);
    list_add_tail(list1, 18);
    list_add_tail(list1, 20);
    
    list_add_tail(list2, 1);
    list_add_tail(list2, 3);
    list_add_tail(list2, 4);
    list_add_tail(list2, 5);
    list_add_tail(list2, 7);
    list_add_tail(list2, 9);
    list_add_tail(list2, 12);
    list_add_tail(list2, 15);
    list_add_tail(list2, 18);

    reversal_list(list1);
    reversal_list(list2);
    print_list_value(list1);
    print_list_value(list2);

    tmp1 = list1->next;
    tmp2 = list2->next;

    while(tmp1 != NULL && tmp2 != NULL)
    {
        if(tmp1->value == tmp2->value)
        {
            printf("公共部分，value = %d\n", tmp1->value);
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        } else if (tmp1->value > tmp2->value)
        {
            tmp2 = tmp2->next;
        } else if (tmp1->value < tmp2->value)
        {
            tmp1 = tmp1->next;
        }
    }

    del_list(list1);
    del_list(list2);
    
    return 0;
}
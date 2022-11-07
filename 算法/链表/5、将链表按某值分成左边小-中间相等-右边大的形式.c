
/*
要求：
    小于该值的节点、等于该值的节点、大于该值的节点原顺序不变
    时间复杂度O(n)
    空间复杂度O(1)
思路：
    定义三个新的链表头，遍历原链表，按情况将节点加到三个链表中，然后再遍历三个链表，将节点重新加到原链表头之后 
*/    
#include <stdio.h>
#include <stdlib.h>

#ifndef NULL
#define NULL ((*)0)
#endif

#define CHECK_NULL_POINTER(pointer) \
do{ \
    if(!pointer){ \
        printf("got NULL pointer\n"); \
        return -1; \
    } \
} while(0)

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

int math_list(struct list_head *head, int value)
{
    struct list_head *left_list = NULL, *eq_list = NULL, *right_list = NULL;
    struct list_head *tmp1 = NULL, *tmp2 = NULL;

    left_list = (struct list_head *)malloc(sizeof(struct list_head));
    CHECK_NULL_POINTER(left_list);
    list_init(left_list);

    eq_list = (struct list_head *)malloc(sizeof(struct list_head));
    CHECK_NULL_POINTER(eq_list);
    list_init(eq_list);

    right_list = (struct list_head *)malloc(sizeof(struct list_head));
    CHECK_NULL_POINTER(right_list);
    list_init(right_list);

    tmp1 = head->next;
    while(tmp1){
        tmp2 = tmp1->next;
        if(tmp1->value < value){
            tmp1->next = left_list->next;
            left_list->next = tmp1;
        }
        else if(tmp1->value == value){
            tmp1->next = eq_list->next;
            eq_list->next = tmp1;
        }
        else {
            tmp1->next = right_list->next;
            right_list->next = tmp1;
        }
        tmp1 = tmp2;
    }

    head->next = NULL;
    tmp1 = right_list->next;
    while(tmp1){
        tmp2 = tmp1->next;
        tmp1->next = head->next;
        head->next = tmp1;
        tmp1= tmp2;
    }
    tmp1 = eq_list->next;
    while(tmp1){
        tmp2 = tmp1->next;
        tmp1->next = head->next;
        head->next = tmp1;
        tmp1= tmp2;
    }
    tmp1 = left_list->next;
    while(tmp1){
        tmp2 = tmp1->next;
        tmp1->next = head->next;
        head->next = tmp1;
        tmp1= tmp2;
    }
    free(left_list);
    free(eq_list);
    free(right_list);
    return 0;
}


int main(int argc, char* argv[])
{
    struct list_head *list = NULL;

    list = (struct list_head *)malloc(sizeof(struct list_head));
    CHECK_NULL_POINTER(list);
    list_init(list);

    list_add_tail(list, 5);
    list_add_tail(list, 5);
    list_add_tail(list, 8);
    list_add_tail(list, 9);
    list_add_tail(list, 2);
    list_add_tail(list, 4);
    list_add_tail(list, 5);
    list_add_tail(list, 4);
    list_add_tail(list, 41);
    list_add_tail(list, 14);
    list_add_tail(list, 12);
    list_add_tail(list, 2);
    list_add_tail(list, 4);
    list_add_tail(list, 5);
    list_add_tail(list, 8);
    list_add_tail(list, 0);
    list_add_tail(list, 6);
    list_add_tail(list, 1);
    list_add_tail(list, 15);

    print_list_value(list);
    math_list(list, 5);
    print_list_value(list);

    free(list);
    return 0;
}



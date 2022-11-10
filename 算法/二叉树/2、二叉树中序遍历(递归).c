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

struct BiTNode{
    int value;//数据域
    struct BiTNode *left,*right;//左右孩子指针
    struct BiTNode *parent;
};

int initBiTNode(struct BiTNode *node, int value)
{
    CHECK_NULL_POINTER(node);

    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->value = value;
    return 0;
}

int add_lchild(struct BiTNode *node, struct BiTNode *left)
{
    CHECK_NULL_POINTER(node);
    CHECK_NULL_POINTER(left);

    node->left = left;
    left->parent = node;
    return 0;
}
int add_rchild(struct BiTNode *node, struct BiTNode *right)
{
    CHECK_NULL_POINTER(node);
    CHECK_NULL_POINTER(right);

    node->right = right;
    right->parent = node;

    return 0;
}

int delBitTree(struct BiTNode *node)
{
    CHECK_NULL_POINTER(node);

    return 0;
}


void Middle_order_traversal(struct BiTNode *node)
{
    if(!node)
        return;

    Middle_order_traversal(node->left);
    printf("%d ", node->value);
    Middle_order_traversal(node->right);
}

int main(int argc, char* argv[])
{
    struct BiTNode *node1 = (struct BiTNode*)malloc(sizeof(struct BiTNode));
    struct BiTNode *node2 = (struct BiTNode*)malloc(sizeof(struct BiTNode));
    struct BiTNode *node3 = (struct BiTNode*)malloc(sizeof(struct BiTNode));
    struct BiTNode *node4 = (struct BiTNode*)malloc(sizeof(struct BiTNode));
    struct BiTNode *node5 = (struct BiTNode*)malloc(sizeof(struct BiTNode));
    struct BiTNode *node6 = (struct BiTNode*)malloc(sizeof(struct BiTNode));
    struct BiTNode *node7 = (struct BiTNode*)malloc(sizeof(struct BiTNode));
    
    CHECK_NULL_POINTER(node1);
    CHECK_NULL_POINTER(node2);
    CHECK_NULL_POINTER(node3);
    CHECK_NULL_POINTER(node4);
    CHECK_NULL_POINTER(node5);
    CHECK_NULL_POINTER(node6);
    CHECK_NULL_POINTER(node7);

    initBiTNode(node1, 1);
    initBiTNode(node2, 2);
    initBiTNode(node3, 3);
    initBiTNode(node4, 4);
    initBiTNode(node5, 5);
    initBiTNode(node6, 6);
    initBiTNode(node7, 7);

    add_lchild(node1, node2);
    add_rchild(node1, node3);

    add_lchild(node2, node4);
    add_rchild(node2, node5);

    add_lchild(node3, node6);
    add_rchild(node3, node7);
    
    
    Middle_order_traversal(node1);
    printf("\n");

    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
    free(node6);
    free(node7);

    return 0;
}
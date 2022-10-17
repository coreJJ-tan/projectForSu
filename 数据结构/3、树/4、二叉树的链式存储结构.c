1、普通二叉树的存储
    一棵普通的二叉树，若将其采用链式存储，则只需从树的根节点开始，将各个节点及其左右孩子使用链表存储即可。

2、节点描述
    采用链式存储二叉树时，其节点结构最少由 3 部分构成：
    （1）指向左孩子节点的指针（*Lchild）；
    （2）节点存储的数据（data）；
    （3） 指向右孩子节点的指针（*Rchild）；
    （4）若想获取父节点，则可以再定义一个父节点指针（*parent）;
C语言表示：
typedef struct BiTNode{
    TElemType data;//数据域
    struct BiTNode *lchild,*rchild;//左右孩子指针
    struct BiTNode *parent;
}BiTNode,*BiTree;

3、
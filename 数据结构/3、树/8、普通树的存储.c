    存储具有普通树结构数据的方法有 3 种：
    采用如下树作为示例
            |-----------R-----------|
    |---A---|       B           C
    D       E               |---F---|
                            G   H   K
一、双亲表示法
    双亲表示法采用顺序表（也就是数组）存储普通树，其实现的核心思想是：顺序存储各个节点的同时，给各节点附加一个记录其父节点位置的变量。
    注意，根节点没有父节点（父节点又称为双亲节点），因此根节点记录父节点位置的变量通常置为 -1。

    如上实例的存储结构为：
    数组下标: 0  1  2  3  4  5  6  7  8  9
    data:    R  A  B  C  D  E  F  G  H  K
    parent:  -1 0  0  0  1  1  3  6  6  6

 C 语言代码为：
#define MAX_SIZE 100//宏定义树中结点的最大数量
typedef char TElemType;//宏定义树结构中数据类型
typedef struct Snode{
    TElemType data;//树中结点的数据类型
    int parent;//结点的父结点在数组中的位置下标
}PTNode;
typedef struct {
    PTNode tnode[MAX_SIZE];//存放树中所有结点
    int n;//根的位置下标和结点数
}PTree;

    当算法中需要在树结构中频繁地查找某结点的父结点时，使用双亲表示法最合适。当频繁地访问结点的孩子结点时，双亲表示法就很麻烦，采用孩子表示法就很简单。

二、孩子表示法
    孩子表示法存储普通树采用的是 "顺序表+链表" 的组合结构，其存储过程是：从树的根节点开始，使用顺序表依次存储树中各个节点，需要注意的是，与双亲表示法
不同，孩子表示法会给各个节点配备一个链表，用于存储各节点的孩子节点位于顺序表中的位置。
    如果节点没有孩子节点（叶子节点），则该节点的链表为空链表。

    C语言代码为：
typedef struct CTNode {
    int child;//链表中每个结点存储的不是数据本身，而是数据在数组中存储的位置下标
    struct CTNode * next;
}ChildPtr;
typedef struct {
    TElemType data;//结点的数据类型
    ChildPtr* firstchild;//孩子链表的头指针
}CTBox;
typedef struct {
    CTBox nodes[MAX_SIZE];//存储结点的数组
    int n, r;//结点数量和树根的位置
}CTree;

    如上实例的存储结构为：
    数组下标:    0  1  2  3  4  5  6  7  8  9
    data:       R  A  B  C  D  E  F  G  H  K
    children:   1  4     6        7
                2  5              8
                3                 9

    还可以将双亲表示法和孩子表示法合二为一:
    数组下标:    0  1  2  3  4  5  6  7  8  9
    parent:     -1 0  0  0  1  1  3  6  6  6
    data:       R  A  B  C  D  E  F  G  H  K
    children:   1  4     6        7
                2  5              8
                3                 9


三、孩子兄弟表示法
    孩子兄弟表示法，采用的是链式存储结构，其存储树的实现思想是：从树的根节点开始，依次用链表存储各个节点的孩子节点和兄弟节点。
    因此，该链表中的节点应包含以下 3 部分内容：
    （1）节点的值；
    （2）指向孩子节点的指针；
    （3）指向兄弟节点的指针；

    C语言代码为：
#define ElemType char
typedef struct CSNode{
    ElemType data;
    struct CSNode * firstchild,*nextsibling;
}CSNode,*CSTree;
    可以得出这样一个结论，即通过孩子兄弟表示法，任意一棵普通树都可以相应转化为一棵二叉树，换句话说，任意一棵普通树都有唯一的一棵二叉树与其对应。
    因此，孩子兄弟表示法可以作为将普通树转化为二叉树的最有效方法，通常又被称为"二叉树表示法"或"二叉链表表示法"。
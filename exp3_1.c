#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2     //表示上溢
#define Underflow 3    //表示下溢
#define NotPresent 4   //表示元素不存在
#define Duplicate 5    //表示有重复元素
typedef int ElemType;
typedef int Status;


//邻接表的结构体定义
typedef struct ENode {
    int adjVex;             //任意顶点u相邻的顶点
    ElemType w;             //边的权值
    struct ENode* nextArc;  //指向下一个边结点
}ENode;

typedef struct {
    int n;             //图的当前顶点数
    int e;             //图的当前边数
    ENode** a;         //指向一维指针数组
}LGraph;


//邻接表的初始化
Status Init(LGraph* lg, int nSize) {
    int  i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));  //动态生成长度为n的一维指针数组
    if (!lg->a) return ERROR;
    else {
        for (i = 0; i < lg->n; i++) {
            lg->a[i] = NULL;                        //将指针数组a置空
        }
        return OK;
    }
}


//邻接表的撤销(改成了int型，有返回值)
int Destory(LGraph* lg) {
    int i;
    ENode* p, * q;
    for (i = 0; i < lg->n; i++) {
        p = lg->a[i];                 //指针p指向顶点i的单链表的第一个边结点
        q = p;
        while (p) {                     //释放顶点i的单链表中所有边结点
            p = p->nextArc;
            free(q);
            q = p;
        }
    }
    free(lg->a);                     //释放一维指针数组a的存储空间
    return 1;                        //改为int型函数,有返回值
}


//邻接表的搜索边
Status Exist(LGraph* lg, int u, int v) {
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR;
    p = lg->a[u];                   //指针p指向顶点u的单链表的第一个边结点
    while (p != NULL && p->adjVex != v) {
        p = p->nextArc;
    }
    if (!p) return ERROR;            //若未找到此边,则返回ERROR
    else return OK;
}


//邻接表的插入边
Status Insert(LGraph* lg, int u, int v, ElemType w) {
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR;
    if (Exist(lg, u, v)) return Duplicate;  //此边已存在,返回错误
    p = (ENode*)malloc(sizeof(ENode));   //为新的边结点分配存储空间
    p->adjVex = v;
    p->w = w;
    p->nextArc = lg->a[u];             //将新的边结点插入单链表的最前面
    lg->a[u] = p;
    lg->e++;                            //边加1
    return OK;
}


//邻接表的删除边
Status Remove(LGraph* lg, int u, int v) {
    ENode* p, * q;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR;
    p = lg->a[u];
    q = NULL;
    while (p && p->adjVex != v) {         //查找待删除边是否存在
        q = p;
        p = p->nextArc;
    }
    if (!p) return NotPresent;          //p为空,待删除边不存在
    if (q) q->nextArc = p->nextArc;     //从单链表删除此边
    else lg->a[u] = p->nextArc;
    free(p);
    lg->e--;
    return OK;
}



int main() {
    LGraph g;
    int nSize, edge, u, v, i;
    ElemType w;

    printf("Please enter the number of nodes in the graph: ");
    scanf_s("%d", &nSize);                // 输入图的节点数
    Init(&g, nSize);                      // 初始化图

    printf("Please enter the number of edges: ");
    scanf_s("%d", &edge);                 // 输入图的边数

    printf("Enter edges with the order of u, v, w: \n");
    for (i = 0; i < edge; i++) {
        scanf_s("%d%d%d", &u, &v, &w);    // 输入边的两个端点和权重
        Insert(&g, u, v, w);              // 插入边
    }

    printf("Please enter the edge to delete:\n");
    printf("Enter the u of the edge: ");
    scanf_s("%d", &u);                    // 输入待删除边的u

    printf("Enter the v of the edge: ");
    scanf_s("%d", &v);                    // 输入待删除边的v
    Remove(&g, u, v);                     // 删除指定的边

    printf("Now searching for the edge just deleted: ");
    if (Exist(&g, u, v))                  // 检查删除的边是否存在
        printf("OK\n");
    else
        printf("ERROR\n");

    printf("Now destroying the graph: ");
    if (Destory(&g))                      // 销毁图并释放内存
        printf("OK\n");
    else
        printf("ERROR\n");

    return 0;                             // 程序结束
}

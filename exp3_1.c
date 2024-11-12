#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2     //��ʾ����
#define Underflow 3    //��ʾ����
#define NotPresent 4   //��ʾԪ�ز�����
#define Duplicate 5    //��ʾ���ظ�Ԫ��
typedef int ElemType;
typedef int Status;


//�ڽӱ�Ľṹ�嶨��
typedef struct ENode {
    int adjVex;             //���ⶥ��u���ڵĶ���
    ElemType w;             //�ߵ�Ȩֵ
    struct ENode* nextArc;  //ָ����һ���߽��
}ENode;

typedef struct {
    int n;             //ͼ�ĵ�ǰ������
    int e;             //ͼ�ĵ�ǰ����
    ENode** a;         //ָ��һάָ������
}LGraph;


//�ڽӱ�ĳ�ʼ��
Status Init(LGraph* lg, int nSize) {
    int  i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));  //��̬���ɳ���Ϊn��һάָ������
    if (!lg->a) return ERROR;
    else {
        for (i = 0; i < lg->n; i++) {
            lg->a[i] = NULL;                        //��ָ������a�ÿ�
        }
        return OK;
    }
}


//�ڽӱ�ĳ���(�ĳ���int�ͣ��з���ֵ)
int Destory(LGraph* lg) {
    int i;
    ENode* p, * q;
    for (i = 0; i < lg->n; i++) {
        p = lg->a[i];                 //ָ��pָ�򶥵�i�ĵ�����ĵ�һ���߽��
        q = p;
        while (p) {                     //�ͷŶ���i�ĵ����������б߽��
            p = p->nextArc;
            free(q);
            q = p;
        }
    }
    free(lg->a);                     //�ͷ�һάָ������a�Ĵ洢�ռ�
    return 1;                        //��Ϊint�ͺ���,�з���ֵ
}


//�ڽӱ��������
Status Exist(LGraph* lg, int u, int v) {
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR;
    p = lg->a[u];                   //ָ��pָ�򶥵�u�ĵ�����ĵ�һ���߽��
    while (p != NULL && p->adjVex != v) {
        p = p->nextArc;
    }
    if (!p) return ERROR;            //��δ�ҵ��˱�,�򷵻�ERROR
    else return OK;
}


//�ڽӱ�Ĳ����
Status Insert(LGraph* lg, int u, int v, ElemType w) {
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR;
    if (Exist(lg, u, v)) return Duplicate;  //�˱��Ѵ���,���ش���
    p = (ENode*)malloc(sizeof(ENode));   //Ϊ�µı߽�����洢�ռ�
    p->adjVex = v;
    p->w = w;
    p->nextArc = lg->a[u];             //���µı߽����뵥�������ǰ��
    lg->a[u] = p;
    lg->e++;                            //�߼�1
    return OK;
}


//�ڽӱ��ɾ����
Status Remove(LGraph* lg, int u, int v) {
    ENode* p, * q;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR;
    p = lg->a[u];
    q = NULL;
    while (p && p->adjVex != v) {         //���Ҵ�ɾ�����Ƿ����
        q = p;
        p = p->nextArc;
    }
    if (!p) return NotPresent;          //pΪ��,��ɾ���߲�����
    if (q) q->nextArc = p->nextArc;     //�ӵ�����ɾ���˱�
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
    scanf_s("%d", &nSize);                // ����ͼ�Ľڵ���
    Init(&g, nSize);                      // ��ʼ��ͼ

    printf("Please enter the number of edges: ");
    scanf_s("%d", &edge);                 // ����ͼ�ı���

    printf("Enter edges with the order of u, v, w: \n");
    for (i = 0; i < edge; i++) {
        scanf_s("%d%d%d", &u, &v, &w);    // ����ߵ������˵��Ȩ��
        Insert(&g, u, v, w);              // �����
    }

    printf("Please enter the edge to delete:\n");
    printf("Enter the u of the edge: ");
    scanf_s("%d", &u);                    // �����ɾ���ߵ�u

    printf("Enter the v of the edge: ");
    scanf_s("%d", &v);                    // �����ɾ���ߵ�v
    Remove(&g, u, v);                     // ɾ��ָ���ı�

    printf("Now searching for the edge just deleted: ");
    if (Exist(&g, u, v))                  // ���ɾ���ı��Ƿ����
        printf("OK\n");
    else
        printf("ERROR\n");

    printf("Now destroying the graph: ");
    if (Destory(&g))                      // ����ͼ���ͷ��ڴ�
        printf("OK\n");
    else
        printf("ERROR\n");

    return 0;                             // �������
}

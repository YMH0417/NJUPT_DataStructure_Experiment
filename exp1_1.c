#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef int Status;

typedef struct {
	int n;
	int maxLength;
	ElemType* element;
} SeqList;

Status Init(SeqList* L, int mSize) {
	L->maxLength = mSize;
	L->n = 0;
	L->element = (ElemType*)malloc(sizeof(ElemType) * mSize);
	if (L->element)
		return 1;
	exit(0);
}

Status Find(SeqList seqList, int i, ElemType* x) {
	if (i < 0 || i > seqList.n - 1) {
		return 0;
	}
	*x = seqList.element[i];
	return 1;
}

Status Insert(SeqList* seqList, int i, ElemType x) {
	int j;
	if (i < -1 || i > seqList->n - 1)
		return 0;
	if (seqList->n == seqList->maxLength)
		return 0;
	for (j = seqList->n - 1; j > i; j--) {
		seqList->element[j + 1] = seqList->element[j];
	}
	seqList->element[i + 1] = x;
	seqList->n++;
	return 1;
}

Status Delete(SeqList* seqList, int i) {
	int j;
	if (i < 0 || i > seqList->n - 1) {
		return 0;
	}
	if (!seqList->n) {
		return 0;
	}
	for (j = i + 1; j < seqList->n; j++) {
		seqList->element[j - 1] = seqList->element[j];
	}
	seqList->n--;
	return 1;
}

int Output(SeqList seqList) {
	int i;
	if (!seqList.n)
		return 0;
	for (i = 0; i <= seqList.n - 1; i++)
		printf("%d ", seqList.element[i]);
	return 1;
}

void Destroy(SeqList* L) {
	(*L).n = 0;
	(*L).maxLength = 0;
	free((*L).element);
}

int main(){
	int i, j, delPos, findPos, n, findResult;
	SeqList list;

	printf("Number of elements:\n");
	scanf_s("%d", &n);
	Init(&list, n);
	printf("Elements: \n");
	for (i = 0; i < n; i++) {
		scanf_s("%d", &j);
		Insert(&list, i - 1, j);
	}
	printf("Sequence list: ");
	Output(list);
	printf("\n");

	printf("Delete element at this position: \n");
	scanf_s("%d", &delPos);
	Delete(&list, delPos);
	printf("Sequence list after deleting this element: \n");
	Output(list);
	printf("\n");
	printf("Find element at this position: \n");
	scanf_s("%d", &findPos);
	Find(list, findPos, &findResult);
	printf("This element: %d", findResult);
	printf("\n");
	Destroy(&list);
	return 0;
}

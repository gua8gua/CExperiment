#include <stdio.h>

typedef enum { TYPE_INT, TYPE_CHAR } ElemType;

typedef struct {
    ElemType type;
    union {
        int i;
        char c;
    } data;
} Element;

static Element makeInt(int v) {
    Element e;
    e.type = TYPE_INT;
    e.data.i = v;
    return e;
}

static Element makeChar(char ch) {
    Element e;
    e.type = TYPE_CHAR;
    e.data.c = ch;
    return e;
}

int compare(Element a, Element b) {
    if (a.type == TYPE_INT && b.type == TYPE_INT) {
        return (a.data.i < b.data.i) ? -1 : (a.data.i > b.data.i ? 1 : 0);
    }
    if (a.type == TYPE_CHAR && b.type == TYPE_CHAR) {
        return (a.data.c < b.data.c) ? -1 : (a.data.c > b.data.c ? 1 : 0);
    }
    //整数 < 字符
    return (a.type == TYPE_INT) ? -1 : 1;
}

// 打印数组
void printArray(Element arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        if (arr[i].type == TYPE_INT)
            printf("%d", arr[i].data.i);
        else
            printf("%c", arr[i].data.c);
        if (i != n - 1) printf(",");
    }
    printf("]\n");
}

// 合并有序数组
void merge(Element A[], int n, Element B[], int m, Element C[], int* len) {
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (compare(A[i], B[j]) <= 0)
            C[k++] = A[i++];
        else
            C[k++] = B[j++];
    }
    while (i < n) C[k++] = A[i++];
    while (j < m) C[k++] = B[j++];
    *len = k;
}



//int main() {
//    Element A2[] = { makeInt(1), makeInt(4), makeInt(7), makeChar('A'), makeChar('B'), makeChar('c') };
//    Element B2[] = { makeInt(2), makeInt(11), makeChar('a') };
//    Element C[200];
//    int len;
//    merge(A2, 6, B2, 2, C, &len);
//    printArray(C, len); 
//
//    return 0;
//    return 0;
//}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int step = 0;

// ��ӡ��ǰ¥��
void printHeights(int* a, int n) {
    printf("Step %d: ", ++step);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// �ݹ������� [l, r]
void removeBuildings(int* a, int l, int r, int n) {
    if (l > r) return;

    // �ҵ���С�߶�
    int minH = a[l];
    for (int i = l; i <= r; i++) {
        if (a[i] < minH) minH = a[i];
    }

    // �������ȥ minH
    for (int i = l; i <= r; i++) {
        a[i] -= minH;
    }

    // ��ӡ��ǰ¥��
    printHeights(a,n);

    // �ݹ鴦�����������
    int start = l;
    while (start <= r) {
        while (start <= r && a[start] == 0) start++;
        if (start > r) break;
        int end = start;
        while (end <= r && a[end] > 0) end++;
        removeBuildings(a, start, end - 1, n);
        start = end;
    }
}

void demolateBuildingMenu() {
    int n;
    scanf("%d", &n);
    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    removeBuildings(a, 0, n - 1, n);

    free(a);
}

//void main() {
//    demolateBuildingMenu();
//}
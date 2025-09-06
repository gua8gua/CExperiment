#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int step = 0;

// 打印当前楼高
void printHeights(int* a, int n) {
    printf("Step %d: ", ++step);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// 递归拆除区间 [l, r]
void removeBuildings(int* a, int l, int r, int n) {
    if (l > r) return;

    // 找到最小高度
    int minH = a[l];
    for (int i = l; i <= r; i++) {
        if (a[i] < minH) minH = a[i];
    }

    // 对区间减去 minH
    for (int i = l; i <= r; i++) {
        a[i] -= minH;
    }

    // 打印当前楼高
    printHeights(a,n);

    // 递归处理非零子区间
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
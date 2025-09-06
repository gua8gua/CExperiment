#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;       
    int cost;     // 存储成本
    int sold;     // 是否已售出
} Plane;

// 按成本降序排序
int cmp(const void* a, const void* b) {
    Plane* p1 = (Plane*)a;
    Plane* p2 = (Plane*)b;
    return p2->cost - p1->cost;
}

void planeBuildMenu() {
    int n, m;

    // 数据读取
    FILE* fp = fopen("D://CProject//CExperiment//CExperiment//day11//input.txt", "r");
    if (!fp) {
        printf("无法打开文件\n");
        return;
    }

    if (fscanf(fp, "%d %d", &n, &m) != 2) {
        printf("读取 n 和 m 失败\n");
        fclose(fp);
        return;
    }

    Plane* planes = (Plane*)malloc(n * sizeof(Plane));
    if (!planes) {
        printf("内存分配失败\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &planes[i].cost) != 1) {
            printf("读取飞机成本失败\n");
            free(planes);
            fclose(fp);
            return;
        }
        planes[i].id = i + 1; // 生产日
        planes[i].sold = 0;   // 未售
    }

    fclose(fp);


    // 按成本降序排序
    qsort(planes, n, sizeof(Plane), cmp);

    long long total = 0;
    int soldCount = 0;


    for (int day = m + 1; soldCount < n; day++) {
        // 找到当天可以卖的成本最高的飞机
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!planes[i].sold && planes[i].id <= day) {
                int stayDays = day - planes[i].id;
                total += (long long)stayDays * planes[i].cost;
                planes[i].sold = 1;
                soldCount++;
                found = 1;
                break; // 每天卖一架
            }
        }
    }

    printf("%d\n", total);

    free(planes);

}

//int main() {
//    planeBuildMenu();
//}
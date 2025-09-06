#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;       
    int cost;     // �洢�ɱ�
    int sold;     // �Ƿ����۳�
} Plane;

// ���ɱ���������
int cmp(const void* a, const void* b) {
    Plane* p1 = (Plane*)a;
    Plane* p2 = (Plane*)b;
    return p2->cost - p1->cost;
}

void planeBuildMenu() {
    int n, m;

    // ���ݶ�ȡ
    FILE* fp = fopen("D://CProject//CExperiment//CExperiment//day11//input.txt", "r");
    if (!fp) {
        printf("�޷����ļ�\n");
        return;
    }

    if (fscanf(fp, "%d %d", &n, &m) != 2) {
        printf("��ȡ n �� m ʧ��\n");
        fclose(fp);
        return;
    }

    Plane* planes = (Plane*)malloc(n * sizeof(Plane));
    if (!planes) {
        printf("�ڴ����ʧ��\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &planes[i].cost) != 1) {
            printf("��ȡ�ɻ��ɱ�ʧ��\n");
            free(planes);
            fclose(fp);
            return;
        }
        planes[i].id = i + 1; // ������
        planes[i].sold = 0;   // δ��
    }

    fclose(fp);


    // ���ɱ���������
    qsort(planes, n, sizeof(Plane), cmp);

    long long total = 0;
    int soldCount = 0;


    for (int day = m + 1; soldCount < n; day++) {
        // �ҵ�����������ĳɱ���ߵķɻ�
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!planes[i].sold && planes[i].id <= day) {
                int stayDays = day - planes[i].id;
                total += (long long)stayDays * planes[i].cost;
                planes[i].sold = 1;
                soldCount++;
                found = 1;
                break; // ÿ����һ��
            }
        }
    }

    printf("%d\n", total);

    free(planes);

}

//int main() {
//    planeBuildMenu();
//}
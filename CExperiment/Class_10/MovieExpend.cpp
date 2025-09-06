#define _CRT_SECURE_NO_WARNINGS

#define INF 1000000000
#define MAX_CITY 20
#include <stdio.h>
void computeMinCost(int start, int n, int matrix[MAX_CITY][MAX_CITY], int tickets[MAX_CITY]) {
    int distArr[MAX_CITY];
    int visited[MAX_CITY];

    // ��ʼ��
    for (int i = 0; i < n; i++) {
        if (matrix[start][i] > 0)
            distArr[i] = matrix[start][i];
        else
            distArr[i] = INF;
        visited[i] = 0;
    }
    distArr[start] = 0;
    visited[start] = 1;

    // Dijkstra
    for (int k = 1; k < n; k++) {
        int minDist = INF, u = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && distArr[i] < minDist) {
                minDist = distArr[i];
                u = i;
            }
        }
        if (u == -1) break; // �޷��ҵ�����ɴ��
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && matrix[u][v] > 0 && distArr[u] + matrix[u][v] < distArr[v]) {
                distArr[v] = distArr[u] + matrix[u][v];
            }
        }
    }

    // ����������С���� = ·�� + ��Ʊ
    int minCost = INF;
    //printf("�ӳ���%d�����������е���С����:\n", start);
    for (int i = 0; i < n; i++) {
        if (distArr[i] >= INF) {
            //printf("����%d : �޷�����\n", i);
        }
        else {
            //printf("����%d : %d\n", i, distArr[i] + tickets[i]);
            if (distArr[i] + tickets[i] < minCost) {
                minCost = distArr[i] + tickets[i];
            }
        }
    }
    //printf("��С����Ϊ: %d\n", minCost);
    if (minCost == INF) {
        printf("-1 ");
    }
    else {
        printf("%d ", minCost);
    }
}

void movieExpendMenu() {
    int n, edge_num, node1, node2, dist;
    int tickes[MAX_CITY];
    //printf("�����������: ");
    scanf("%d", &n);
    //printf("������·����: ");
    scanf("%d", &edge_num);

    //printf("�������������Ʊ: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tickes[i]);
    }

    int matrix[MAX_CITY][MAX_CITY];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    //printf("�������·������: ");
    for (int i = 0; i < edge_num; i++) {
        scanf("%d %d %d", &node1, &node2, &dist);
        node1--, node2--;
        if (node1 < 0 || node1 >= n || node2 < 0 || node2 >= n || dist <= 0 || matrix[node1][node2] != 0) {
            printf("���������������������룡\n");
            i--;
        }
        else {
            matrix[node1][node2] = dist;
        }
    }

    for (int i = 0; i < n; i++) {
        computeMinCost(i, n, matrix, tickes);
    }
}

//void main() {
//    movieExpendMenu();
//}
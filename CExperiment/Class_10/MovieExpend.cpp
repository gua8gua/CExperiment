#define _CRT_SECURE_NO_WARNINGS

#define INF 1000000000
#define MAX_CITY 20
#include <stdio.h>
void computeMinCost(int start, int n, int matrix[MAX_CITY][MAX_CITY], int tickets[MAX_CITY]) {
    int distArr[MAX_CITY];
    int visited[MAX_CITY];

    // 初始化
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
        if (u == -1) break; // 无法找到更多可达点
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && matrix[u][v] > 0 && distArr[u] + matrix[u][v] < distArr[v]) {
                distArr[v] = distArr[u] + matrix[u][v];
            }
        }
    }

    // 输出结果：最小花费 = 路费 + 门票
    int minCost = INF;
    //printf("从城市%d出发到各城市的最小花费:\n", start);
    for (int i = 0; i < n; i++) {
        if (distArr[i] >= INF) {
            //printf("城市%d : 无法到达\n", i);
        }
        else {
            //printf("城市%d : %d\n", i, distArr[i] + tickets[i]);
            if (distArr[i] + tickets[i] < minCost) {
                minCost = distArr[i] + tickets[i];
            }
        }
    }
    //printf("最小花费为: %d\n", minCost);
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
    //printf("请输入城市数: ");
    scanf("%d", &n);
    //printf("请输入路径数: ");
    scanf("%d", &edge_num);

    //printf("请输入各城市门票: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tickes[i]);
    }

    int matrix[MAX_CITY][MAX_CITY];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    //printf("请输入各路径数据: ");
    for (int i = 0; i < edge_num; i++) {
        scanf("%d %d %d", &node1, &node2, &dist);
        node1--, node2--;
        if (node1 < 0 || node1 >= n || node2 < 0 || node2 >= n || dist <= 0 || matrix[node1][node2] != 0) {
            printf("输入数据有误，请重新输入！\n");
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
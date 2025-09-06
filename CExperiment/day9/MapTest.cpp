#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20   // 最大节点数

// 邻接表的边节点
typedef struct EdgeNode {
    int adjvex;                // 顶点下标
    struct EdgeNode* next;     // 下一个边节点
} EdgeNode;

// 邻接表的顶点节点
typedef struct VertexNode {
    char name[20];             // 节点名
    EdgeNode* firstEdge;       // 边表头指针
} VertexNode;

// 图结构
typedef struct {
    VertexNode adjList[MAX];
    int numVertexes;
} Graph;

// 队列
typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

// 初始化队列
void InitQueue(Queue* q) {
    q->front = q->rear = 0;
}

int QueueEmpty(Queue* q) {
    return q->front == q->rear;
}

void EnQueue(Queue* q, int e) {
    if ((q->rear + 1) % MAX == q->front) return;
    q->data[q->rear] = e;
    q->rear = (q->rear + 1) % MAX;
}

int DeQueue(Queue* q) {
    if (QueueEmpty(q)) return -1;
    int e = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    return e;
}

// 创建图
void CreateGraph(Graph* G, int matrix[MAX][MAX], int n) {
    G->numVertexes = n;
    for (int i = 0; i < n; i++) {
        sprintf(G->adjList[i].name, "Node%d", i); 
        G->adjList[i].firstEdge = NULL;
    }

    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) { // 从后往前插，保持顺序
            if (matrix[i][j] != 0) {
                EdgeNode* e = (EdgeNode*)malloc(sizeof(EdgeNode));
                e->adjvex = j;
                e->next = G->adjList[i].firstEdge;
                G->adjList[i].firstEdge = e;
            }
        }
    }
}

int visited[MAX];

// 深度优先搜索
void DFS(Graph* G, int i) {
    visited[i] = 1;
    printf("%s ", G->adjList[i].name);

    EdgeNode* p = G->adjList[i].firstEdge;
    while (p) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex);
        }
        p = p->next;
    }
}

// 广度优先搜索
void BFS(Graph* G, int start) {
    Queue q;
    InitQueue(&q);

    visited[start] = 1;
    printf("%s ", G->adjList[start].name);
    EnQueue(&q, start);

    while (!QueueEmpty(&q)) {
        int v = DeQueue(&q);
        EdgeNode* p = G->adjList[v].firstEdge;
        while (p) {
            if (!visited[p->adjvex]) {
                visited[p->adjvex] = 1;
                printf("%s ", G->adjList[p->adjvex].name);
                EnQueue(&q, p->adjvex);
            }
            p = p->next;
        }
    }
}

void mapTestMenu() {
    int n;
    printf("请输入节点数: ");
    scanf("%d", &n);

    int matrix[MAX][MAX];
    printf("请输入邻接矩阵 (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    Graph G;
    CreateGraph(&G, matrix, n);

    printf("\n深度优先搜索(DFS)遍历结果: ");
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++) {
        if (!visited[i]) DFS(&G, i);
    }

    printf("\n广度优先搜索(BFS)遍历结果: ");
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++) {
        if (!visited[i]) BFS(&G, i);
    }

    printf("\n");
    return ;
}

void main() {
    mapTestMenu();
}

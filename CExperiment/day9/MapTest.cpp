#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20   // ���ڵ���

// �ڽӱ�ı߽ڵ�
typedef struct EdgeNode {
    int adjvex;                // �����±�
    struct EdgeNode* next;     // ��һ���߽ڵ�
} EdgeNode;

// �ڽӱ�Ķ���ڵ�
typedef struct VertexNode {
    char name[20];             // �ڵ���
    EdgeNode* firstEdge;       // �߱�ͷָ��
} VertexNode;

// ͼ�ṹ
typedef struct {
    VertexNode adjList[MAX];
    int numVertexes;
} Graph;

// ����
typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

// ��ʼ������
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

// ����ͼ
void CreateGraph(Graph* G, int matrix[MAX][MAX], int n) {
    G->numVertexes = n;
    for (int i = 0; i < n; i++) {
        sprintf(G->adjList[i].name, "Node%d", i); 
        G->adjList[i].firstEdge = NULL;
    }

    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) { // �Ӻ���ǰ�壬����˳��
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

// �����������
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

// �����������
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
    printf("������ڵ���: ");
    scanf("%d", &n);

    int matrix[MAX][MAX];
    printf("�������ڽӾ��� (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    Graph G;
    CreateGraph(&G, matrix, n);

    printf("\n�����������(DFS)�������: ");
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++) {
        if (!visited[i]) DFS(&G, i);
    }

    printf("\n�����������(BFS)�������: ");
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

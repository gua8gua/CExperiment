#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAX 100

// ѭ�����нṹ
typedef struct {
    char names[MAX][20];
    int front, rear, size;
} Queue;

// ��ʼ������
void initQueue(Queue* q) {
    q->front = q->rear = 0;
    q->size = 0;
}

// ���
void enqueue(Queue* q, const char* name) {
    if (q->size >= MAX) return;
    strcpy(q->names[q->rear], name);
    q->rear = (q->rear + 1) % MAX;
    q->size++;
}

// ���ӣ���������ָ�룩
char* dequeue(Queue* q, char* buf) {
    if (q->size == 0) return NULL;
    strcpy(buf, q->names[q->front]);
    q->front = (q->front + 1) % MAX;
    q->size--;
    return buf;
}

// ��ͷԪ��
char* peek(Queue* q, char* buf) {
    if (q->size == 0) return NULL;
    strcpy(buf, q->names[q->front]);
    return buf;
}

void dancerMatchMenu() {
    Queue men, women;
    initQueue(&men);
    initQueue(&women);

    int nMen, nWomen, rounds;
    char buf[20];

    printf("�жӣ�\n��������������");
    scanf("%d", &nMen);
    printf("���������ߵ�������");
    for (int i = 0; i < nMen; i++) {
        scanf("%s", buf);
        enqueue(&men, buf);
    }

    printf("Ů�ӣ�\n��������������");
    scanf("%d", &nWomen);
    printf("���������ߵ�������");
    for (int i = 0; i < nWomen; i++) {
        scanf("%s", buf);
        enqueue(&women, buf);
    }

    printf("����������������");
    scanf("%d", &rounds);

    for (int r = 1; r <= rounds; r++) {
        printf("��%d��:\n", r);
        int pairs = (men.size < women.size) ? men.size : women.size;

        for (int i = 0; i < pairs; i++) {
            char man[20], woman[20];
            dequeue(&men, man);
            dequeue(&women, woman);
            printf("��Ե����ߣ�%s %s\n", man, woman);
            // ��Ժ�Żض�β
            enqueue(&men, man);
            enqueue(&women, woman);
        }

        // ���δ�����
        if (men.size > women.size) {
            char firstUnpaired[20];
            peek(&men, firstUnpaired);
            printf("��һ��������δ������ߵ�������%s\n", firstUnpaired);
        }
        else if (women.size > men.size) {
            char firstUnpaired[20];
            peek(&women, firstUnpaired);
            printf("��һ��������δ������ߵ�������%s\n", firstUnpaired);
        }
    }

}

//int main() {
//    dancerMatchMenu();
//}

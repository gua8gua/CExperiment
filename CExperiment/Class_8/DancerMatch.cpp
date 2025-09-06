#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAX 100

// 循环队列结构
typedef struct {
    char names[MAX][20];
    int front, rear, size;
} Queue;

// 初始化队列
void initQueue(Queue* q) {
    q->front = q->rear = 0;
    q->size = 0;
}

// 入队
void enqueue(Queue* q, const char* name) {
    if (q->size >= MAX) return;
    strcpy(q->names[q->rear], name);
    q->rear = (q->rear + 1) % MAX;
    q->size++;
}

// 出队（返回姓名指针）
char* dequeue(Queue* q, char* buf) {
    if (q->size == 0) return NULL;
    strcpy(buf, q->names[q->front]);
    q->front = (q->front + 1) % MAX;
    q->size--;
    return buf;
}

// 队头元素
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

    printf("男队：\n输入跳舞人数：");
    scanf("%d", &nMen);
    printf("输入跳舞者的姓名：");
    for (int i = 0; i < nMen; i++) {
        scanf("%s", buf);
        enqueue(&men, buf);
    }

    printf("女队：\n输入跳舞人数：");
    scanf("%d", &nWomen);
    printf("输入跳舞者的姓名：");
    for (int i = 0; i < nWomen; i++) {
        scanf("%s", buf);
        enqueue(&women, buf);
    }

    printf("请输入舞会的轮数：");
    scanf("%d", &rounds);

    for (int r = 1; r <= rounds; r++) {
        printf("第%d轮:\n", r);
        int pairs = (men.size < women.size) ? men.size : women.size;

        for (int i = 0; i < pairs; i++) {
            char man[20], woman[20];
            dequeue(&men, man);
            dequeue(&women, woman);
            printf("配对的舞者：%s %s\n", man, woman);
            // 配对后放回队尾
            enqueue(&men, man);
            enqueue(&women, woman);
        }

        // 输出未配对者
        if (men.size > women.size) {
            char firstUnpaired[20];
            peek(&men, firstUnpaired);
            printf("第一个出场的未配对舞者的姓名：%s\n", firstUnpaired);
        }
        else if (women.size > men.size) {
            char firstUnpaired[20];
            peek(&women, firstUnpaired);
            printf("第一个出场的未配对舞者的姓名：%s\n", firstUnpaired);
        }
    }

}

//int main() {
//    dancerMatchMenu();
//}

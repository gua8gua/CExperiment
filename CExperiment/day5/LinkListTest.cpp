#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev; // ˫��������
} Node;

Node* createNode(int data) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = data;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

// ��������
Node* insertSingly(Node* head, int data) {
    Node* newNode = createNode(data);
    if (!head || data < head->data) { // ���뵽ͷ��
        newNode->next = head;
        return newNode;
    }
    Node* cur = head;
    while (cur->next && cur->next->data < data) {
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    return head;
}

Node* deleteSingly(Node* head, int data) {
    if (!head) return NULL;
    if (head->data == data) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
        return head;
    }
    Node* cur = head;
    while (cur->next && cur->next->data != data) {
        cur = cur->next;
    }
    if (cur->next) {
        Node* tmp = cur->next;
        cur->next = tmp->next;
        free(tmp);
    }
    return head;
}

void displaySingly(Node* head) {
    Node* cur = head;
    while (cur) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// ˫������
Node* insertDoubly(Node* head, int data) {
    Node* newNode = createNode(data);
    if (!head || data < head->data) {
        newNode->next = head;
        if (head) head->prev = newNode;
        return newNode;
    }
    Node* cur = head;
    while (cur->next && cur->next->data < data) cur = cur->next;
    newNode->next = cur->next;
    if (cur->next) cur->next->prev = newNode;
    newNode->prev = cur;
    cur->next = newNode;
    return head;
}

Node* deleteDoubly(Node* head, int data) {
    Node* cur = head;
    while (cur && cur->data != data) cur = cur->next;
    if (!cur) return head;
    if (cur->prev) cur->prev->next = cur->next;
    else head = cur->next;
    if (cur->next) cur->next->prev = cur->prev;
    free(cur);
    return head;
}

void displayDoubly(Node* head) {
    Node* cur = head;
    while (cur) {
        printf("%d <-> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// ����ѭ������
Node* insertCircular(Node* head, int data) {
    Node* newNode = createNode(data);
    if (!head) {
        newNode->next = newNode;
        return newNode;
    }
    Node* cur = head;
    Node* prev = NULL;
    do {
        if (data < cur->data) break;
        prev = cur;
        cur = cur->next;
    } while (cur != head);

    if (!prev) { // ���뵽ͷ
        Node* last = head;
        while (last->next != head) last = last->next;
        newNode->next = head;
        last->next = newNode;
        return newNode; // �µ�ͷ
    }
    else {
        newNode->next = cur;
        prev->next = newNode;
        return head;
    }
}

Node* deleteCircular(Node* head, int data) {
    if (!head) return NULL;
    Node* cur = head, * prev = NULL;
    do {
        if (cur->data == data) break;
        prev = cur;
        cur = cur->next;
    } while (cur != head);

    if (cur->data != data) return head; // û�ҵ�

    if (cur == head) {
        if (head->next == head) {
            free(head);
            return NULL;
        }
        Node* last = head;
        while (last->next != head) last = last->next;
        head = head->next;
        last->next = head;
        free(cur);
    }
    else {
        prev->next = cur->next;
        free(cur);
    }
    return head;
}

void displayCircular(Node* head) {
    if (!head) {
        printf("������\n");
        return;
    }
    Node* cur = head;
    do {
        printf("%d -> ", cur->data);
        cur = cur->next;
    } while (cur != head);
    printf("NULL\n");
}

void menu() {
    int choice, type, val;
    Node* head = NULL;

    printf("ѡ����������:\n1. ��������\n2. ˫������\n3. ����ѭ������\n");
    scanf("%d", &type);

    int n;
    printf("�������ʼ�ڵ����: ");
    scanf("%d", &n);
    printf("������ %d ������:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        if (type == 1) head = insertSingly(head, val);
        else if (type == 2) head = insertDoubly(head, val);
        else head = insertCircular(head, val);
    }

    printf("��ʼ����Ϊ:\n");
    if (type == 1) displaySingly(head);
    else if (type == 2) displayDoubly(head);
    else displayCircular(head);

    while (1) {
        printf("\n�˵�:\n1. ����\n2. ɾ��\n3. ��ʾ\n4. �˳�\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("����Ҫ�����ֵ: ");
            scanf("%d", &val);
            if (type == 1) head = insertSingly(head, val);
            else if (type == 2) head = insertDoubly(head, val);
            else head = insertCircular(head, val);
            break;
        case 2:
            printf("����Ҫɾ����ֵ: ");
            scanf("%d", &val);
            if (type == 1) head = deleteSingly(head, val);
            else if (type == 2) head = deleteDoubly(head, val);
            else head = deleteCircular(head, val);
            break;
        case 3:
            if (type == 1) displaySingly(head);
            else if (type == 2) displayDoubly(head);
            else displayCircular(head);
            break;
        case 4:
            exit(0);
        }
    }
}

//int main() {
//    menu();
//}

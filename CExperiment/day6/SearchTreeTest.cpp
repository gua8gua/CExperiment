#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
    p->data = data;
    p->left = p->right = NULL;
    return p;
}

// ����ڵ�
TreeNode* insert(TreeNode* root, int data) {
    if (!root) return createNode(data);
    if (data < root->data) root->left = insert(root->left, data);
    else if (data > root->data) root->right = insert(root->right, data);
    // ������� root->data��������
    return root;
}

// ������Сֵ�ڵ�
TreeNode* findMin(TreeNode* root) {
    while (root && root->left) root = root->left;
    return root;
}

// ɾ���ڵ�,���ش���ڵ�
TreeNode* deleteNode(TreeNode* root, int data) {
    if (!root) return NULL;
    if (data < root->data) root->left = deleteNode(root->left, data);
    else if (data > root->data) root->right = deleteNode(root->right, data);
    else {
        // �ҵ�Ҫɾ���Ľڵ�
        if (!root->left && !root->right) { // Ҷ�ӽڵ�
            free(root);
            return NULL;
        }
        else if (!root->left) { // ֻ��������
            TreeNode* tmp = root->right;
            free(root);
            return tmp;
        }
        else if (!root->right) { // ֻ��������
            TreeNode* tmp = root->left;
            free(root);
            return tmp;
        }
        else {
            // ������������ȡ��������Сֵ�滻
            TreeNode* tmp = findMin(root->right);
            root->data = tmp->data;
            root->right = deleteNode(root->right, tmp->data);
        }
    }
    return root;
}

// ǰ�����
void preorder(TreeNode* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// ������������������
void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// �������
void postorder(TreeNode* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void freeTree(TreeNode* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void treeTestMenu() {
    TreeNode* root = NULL;
    int choice, val, n;

    while (1) {
        printf("\n�˵�:\n");
        printf("1. ��ʼ������\n");
        printf("2. ����\n");
        printf("3. ɾ��\n");
        printf("4. ǰ�����\n");
        printf("5. �������\n");
        printf("6. �������\n");
        printf("7. �˳�\n");
        printf("���������: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            freeTree(root);
            root = NULL;
            printf("����ڵ����: ");
            scanf("%d", &n);
            printf("������ %d ������: ", n);
            for (int i = 0; i < n; i++) {
                scanf("%d", &val);
                root = insert(root, val);
            }
            break;
        case 2:
            printf("����Ҫ�����ֵ: ");
            scanf("%d", &val);
            root = insert(root, val);
            break;
        case 3:
            printf("����Ҫɾ����ֵ: ");
            scanf("%d", &val);
            root = deleteNode(root, val);
            break;
        case 4:
            printf("ǰ�����: ");
            preorder(root);
            printf("\n");
            break;
        case 5:
            printf("�������: ");
            inorder(root);
            printf("\n");
            break;
        case 6:
            printf("�������: ");
            postorder(root);
            printf("\n");
            break;
        case 7:
            freeTree(root);
            exit(0);
        default:
            printf("��Ч����\n");
        }
    }

}

// ������
//void main() {
//    treeTestMenu();
//}

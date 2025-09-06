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

// 插入节点
TreeNode* insert(TreeNode* root, int data) {
    if (!root) return createNode(data);
    if (data < root->data) root->left = insert(root->left, data);
    else if (data > root->data) root->right = insert(root->right, data);
    // 如果等于 root->data，不插入
    return root;
}

// 查找最小值节点
TreeNode* findMin(TreeNode* root) {
    while (root && root->left) root = root->left;
    return root;
}

// 删除节点,返回代替节点
TreeNode* deleteNode(TreeNode* root, int data) {
    if (!root) return NULL;
    if (data < root->data) root->left = deleteNode(root->left, data);
    else if (data > root->data) root->right = deleteNode(root->right, data);
    else {
        // 找到要删除的节点
        if (!root->left && !root->right) { // 叶子节点
            free(root);
            return NULL;
        }
        else if (!root->left) { // 只有右子树
            TreeNode* tmp = root->right;
            free(root);
            return tmp;
        }
        else if (!root->right) { // 只有左子树
            TreeNode* tmp = root->left;
            free(root);
            return tmp;
        }
        else {
            // 有两个子树，取右子树最小值替换
            TreeNode* tmp = findMin(root->right);
            root->data = tmp->data;
            root->right = deleteNode(root->right, tmp->data);
        }
    }
    return root;
}

// 前序遍历
void preorder(TreeNode* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// 中序遍历（升序输出）
void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// 后序遍历
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
        printf("\n菜单:\n");
        printf("1. 初始化新树\n");
        printf("2. 插入\n");
        printf("3. 删除\n");
        printf("4. 前序遍历\n");
        printf("5. 中序遍历\n");
        printf("6. 后序遍历\n");
        printf("7. 退出\n");
        printf("请输入操作: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            freeTree(root);
            root = NULL;
            printf("输入节点个数: ");
            scanf("%d", &n);
            printf("请输入 %d 个整数: ", n);
            for (int i = 0; i < n; i++) {
                scanf("%d", &val);
                root = insert(root, val);
            }
            break;
        case 2:
            printf("输入要插入的值: ");
            scanf("%d", &val);
            root = insert(root, val);
            break;
        case 3:
            printf("输入要删除的值: ");
            scanf("%d", &val);
            root = deleteNode(root, val);
            break;
        case 4:
            printf("前序遍历: ");
            preorder(root);
            printf("\n");
            break;
        case 5:
            printf("中序遍历: ");
            inorder(root);
            printf("\n");
            break;
        case 6:
            printf("后序遍历: ");
            postorder(root);
            printf("\n");
            break;
        case 7:
            freeTree(root);
            exit(0);
        default:
            printf("无效输入\n");
        }
    }

}

// 主程序
//void main() {
//    treeTestMenu();
//}

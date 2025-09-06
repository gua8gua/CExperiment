#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void printYangHui() {
    int n;
    printf("请输入杨辉三角的高度: ");
    scanf("%d", &n);

    if (n > 50)
        printf("数量过多");
    else if (n < 1) {
        printf("请输入正数");
    }
    int arr[50][50];


    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i)
                arr[i][j] = 1;
            else
                arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }

    // 打印杨辉三角
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++)
            printf("%d  ", arr[i][j]); 
        printf("\n");
    }
}

//void main() {
//    printYangHui();
//}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void printYangHui() {
    int n;
    printf("������������ǵĸ߶�: ");
    scanf("%d", &n);

    if (n > 50)
        printf("��������");
    else if (n < 1) {
        printf("����������");
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

    // ��ӡ�������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++)
            printf("%d  ", arr[i][j]); 
        printf("\n");
    }
}

//void main() {
//    printYangHui();
//}
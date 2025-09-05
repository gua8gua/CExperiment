#include <stdio.h>
#include <string.h>

#define MAX 200 

// ��ӡ���
void printBigInt(int num[], int len) {
    for (int i = len - 1; i >= 0; i--)
        printf("%d", num[i]);
    printf("\n");
}

// �������˷�
int multiply(int num[], int len, int x) {
    int carry = 0;
    for (int i = 0; i < len; i++) {
        int prod = num[i] * x + carry;
        num[i] = prod % 10;
        carry = prod / 10;
    }
    //�������λ
    while (carry) {
        num[len] = carry % 10;
        carry /= 10;
        len++;
    }
    return len;
}

void printFactorial() {
    int num[MAX];  // ����洢������
    int len = 1;   // ��ǰ���ֵĳ���
    num[0] = 1;    // ��ʼֵ = 1

    for (int i = 1; i <= 40; i++) {
        len = multiply(num, len, i);
        printf("%2d! = ", i);
        printBigInt(num, len);
    }
}

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// �ж��ַ����Ƿ�Ϊ����
int isNumber(const char* s) {
    while (*s) {
        if (!isdigit(*s)) return 0;
        s++;
    }
    return 1;
}

// ��֤ IPv4 ��ַ
int validateIPv4(const char* ip) {
    char buf[100];
    strcpy(buf, ip);
    char* token = strtok(buf, ".");
    int count = 0;

    while (token) {
        count++;
        if (!isNumber(token)) {
            printf("IPv4 ����: �� %d �ΰ���������\n", count);
            return 0;
        }
        if (strlen(token) > 1 && token[0] == '0') {
            printf("IPv4 ����: �� %d �β�����ǰ��0\n", count);
            return 0;
        }
        int num = atoi(token);
        if (num < 0 || num > 255) {
            printf("IPv4 ����: �� %d ����ֵ������Χ (0-255)\n", count);
            return 0;
        }
        token = strtok(NULL, ".");
    }
    if (count != 4) {
        printf("IPv4 ����: ��������4\n");
        return 0;
    }
    return 1;
}

// ��֤ IPv6 ��ַ
int validateIPv6(const char* ip) {
    char buf[200];
    strcpy(buf, ip);
    char* token = strtok(buf, ":");
    int count = 0;

    while (token) {
        count++;
        int len = strlen(token);
        if (len == 0) {
            printf("IPv6 ����: �� %d ��Ϊ��\n", count);
            return 0;
        }
        if (len > 4) {
            printf("IPv6 ����: �� %d �γ���4λ\n", count);
            return 0;
        }
        for (int i = 0; i < len; i++) {
            if (!isxdigit(token[i])) {
                printf("IPv6 ����: �� %d �ΰ�����16�����ַ�\n", count);
                return 0;
            }
        }
        token = strtok(NULL, ":");
    }
    if (count != 8) {
        printf("IPv6 ����: ��������8\n");
        return 0;
    }
    return 1;
}

// ��֤ MAC ��ַ
int validateMAC(const char* mac) {
    char buf[200];
    strcpy(buf, mac);
    char* token;
    int count = 0;

    // ֧�� ":" �� "-"
    const char* delim = strchr(mac, '-') ? "-" : ":";

    token = strtok(buf, delim);
    while (token) {
        count++;
        if (strlen(token) != 2) {
            printf("MAC ����: �� %d �γ��Ȳ���2\n", count);
            return 0;
        }
        for (int i = 0; i < 2; i++) {
            if (!isxdigit(token[i])) {
                printf("MAC ����: �� %d �ΰ�����16�����ַ�\n", count);
                return 0;
            }
        }
        token = strtok(NULL, delim);
    }
    if (count != 6) {
        printf("MAC ����: ��������6\n");
        return 0;
    }
    return 1;
}

void checkAddress(const char* addr) {
    if (strchr(addr, '.')) {
        if (validateIPv4(addr))
            printf("IPv4 ��ַ\n");
    }
    else if (strchr(addr, ':')) {
        // �ȳ��� IPv6���ٳ��� MAC
        if (validateIPv6(addr)) {
            printf("IPv6 ��ַ\n");
        }
        else if (validateMAC(addr)) {
            printf("MAC ��ַ\n");
        }
    }
    else if (strchr(addr, '-')) {
        if (validateMAC(addr))
            printf("MAC ��ַ\n");
    }
    else {
        printf("δ֪���͵�ַ\n");
    }
}

//int main() {
//    char input[200];
//
//    printf("�������ַ: ");
//    scanf("%199s", input);
//
//    checkAddress(input);
//
//    return 0;
//}

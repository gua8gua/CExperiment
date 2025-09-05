#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// 判断字符串是否为数字
int isNumber(const char* s) {
    while (*s) {
        if (!isdigit(*s)) return 0;
        s++;
    }
    return 1;
}

// 验证 IPv4 地址
int validateIPv4(const char* ip) {
    char buf[100];
    strcpy(buf, ip);
    char* token = strtok(buf, ".");
    int count = 0;

    while (token) {
        count++;
        if (!isNumber(token)) {
            printf("IPv4 错误: 第 %d 段包含非数字\n", count);
            return 0;
        }
        if (strlen(token) > 1 && token[0] == '0') {
            printf("IPv4 错误: 第 %d 段不能有前导0\n", count);
            return 0;
        }
        int num = atoi(token);
        if (num < 0 || num > 255) {
            printf("IPv4 错误: 第 %d 段数值超出范围 (0-255)\n", count);
            return 0;
        }
        token = strtok(NULL, ".");
    }
    if (count != 4) {
        printf("IPv4 错误: 段数不是4\n");
        return 0;
    }
    return 1;
}

// 验证 IPv6 地址
int validateIPv6(const char* ip) {
    char buf[200];
    strcpy(buf, ip);
    char* token = strtok(buf, ":");
    int count = 0;

    while (token) {
        count++;
        int len = strlen(token);
        if (len == 0) {
            printf("IPv6 错误: 第 %d 段为空\n", count);
            return 0;
        }
        if (len > 4) {
            printf("IPv6 错误: 第 %d 段超过4位\n", count);
            return 0;
        }
        for (int i = 0; i < len; i++) {
            if (!isxdigit(token[i])) {
                printf("IPv6 错误: 第 %d 段包含非16进制字符\n", count);
                return 0;
            }
        }
        token = strtok(NULL, ":");
    }
    if (count != 8) {
        printf("IPv6 错误: 段数不是8\n");
        return 0;
    }
    return 1;
}

// 验证 MAC 地址
int validateMAC(const char* mac) {
    char buf[200];
    strcpy(buf, mac);
    char* token;
    int count = 0;

    // 支持 ":" 或 "-"
    const char* delim = strchr(mac, '-') ? "-" : ":";

    token = strtok(buf, delim);
    while (token) {
        count++;
        if (strlen(token) != 2) {
            printf("MAC 错误: 第 %d 段长度不是2\n", count);
            return 0;
        }
        for (int i = 0; i < 2; i++) {
            if (!isxdigit(token[i])) {
                printf("MAC 错误: 第 %d 段包含非16进制字符\n", count);
                return 0;
            }
        }
        token = strtok(NULL, delim);
    }
    if (count != 6) {
        printf("MAC 错误: 段数不是6\n");
        return 0;
    }
    return 1;
}

void checkAddress(const char* addr) {
    if (strchr(addr, '.')) {
        if (validateIPv4(addr))
            printf("IPv4 地址\n");
    }
    else if (strchr(addr, ':')) {
        // 先尝试 IPv6，再尝试 MAC
        if (validateIPv6(addr)) {
            printf("IPv6 地址\n");
        }
        else if (validateMAC(addr)) {
            printf("MAC 地址\n");
        }
    }
    else if (strchr(addr, '-')) {
        if (validateMAC(addr))
            printf("MAC 地址\n");
    }
    else {
        printf("未知类型地址\n");
    }
}

//int main() {
//    char input[200];
//
//    printf("请输入地址: ");
//    scanf("%199s", input);
//
//    checkAddress(input);
//
//    return 0;
//}

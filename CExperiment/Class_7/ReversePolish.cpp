#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 1024
#define OUTBUF 4096

// 判断运算符
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 运算符优先级
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// 转换中缀为后缀
int infix_to_postfix(const char* infix, char* out, size_t outsize) {
    char stack[MAXLEN];
    int top = -1;
    size_t outpos = 0;

    int n = strlen(infix);
    for (int i = 0; i < n;) {
        char c = infix[i];

        if (isspace((unsigned char)c)) { i++; continue; }

        // 数字
        if (isdigit((unsigned char)c)) {
            char num[128];
            int p = 0;
            while (i < n && (isdigit((unsigned char)infix[i]) || infix[i] == '.')) {
                num[p++] = infix[i++];
            }
            num[p] = '\0';
            int written = snprintf(out + outpos, outsize - outpos, "%s ", num);
            if (written < 0 || (size_t)written >= outsize - outpos) return -1;
            outpos += written;
            continue;
        }

        // 左括号
        if (c == '(') {
            stack[++top] = c;
            i++;
            continue;
        }

        // 右括号
        if (c == ')') {
            int found = 0;
            while (top >= 0) {
                char op = stack[top--];
                if (op == '(') { found = 1; break; }
                out[outpos++] = op; out[outpos++] = ' ';
            }
            if (!found) return -2; // 括号不匹配
            i++;
            continue;
        }

        // 运算符
        if (isOperator(c)) {
            while (top >= 0 && isOperator(stack[top]) &&
                precedence(stack[top]) >= precedence(c)) {
                out[outpos++] = stack[top--];
                out[outpos++] = ' ';
            }
            stack[++top] = c;
            i++;
            continue;
        }

        return -3; // 非法字符
    }

    // 剩余运算符出栈
    while (top >= 0) {
        if (stack[top] == '(') return -2; // 括号不匹配
        out[outpos++] = stack[top--];
        out[outpos++] = ' ';
    }
    if (outpos > 0) out[outpos - 1] = '\0'; else out[outpos] = '\0';
    return 0;
}

// 计算后缀表达式
int eval_postfix(const char* postfix, double* res) {
    double stack[MAXLEN];
    int top = -1;
    char buf[MAXLEN];
    strncpy(buf, postfix, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    char* tok = strtok(buf, " ");
    while (tok) {
        if (strlen(tok) == 1 && isOperator(tok[0])) {
            if (top < 1) return -1;
            double b = stack[top--];
            double a = stack[top--];
            switch (tok[0]) {
            case '+': stack[++top] = a + b; break;
            case '-': stack[++top] = a - b; break;
            case '*': stack[++top] = a * b; break;
            case '/':
                if (b == 0) return -2;
                stack[++top] = a / b;
                break;
            }
        }
        else {
            char* endptr;
            double v = strtod(tok, &endptr);
            if (*endptr != '\0') return -3;
            stack[++top] = v;
        }
        tok = strtok(NULL, " ");
    }
    if (top != 0) return -4;
    *res = stack[top];
    return 0;
}

void reversePolishMenu() {
    char infix[MAXLEN], postfix[OUTBUF];
    printf("请输入中缀表达式(支持 + - * / 和括号):\n");
    if (!fgets(infix, sizeof(infix), stdin)) return;
    infix[strcspn(infix, "\r\n")] = '\0';

    int rc = infix_to_postfix(infix, postfix, sizeof(postfix));
    if (rc != 0) {
        printf("转换失败，错误码 %d\n", rc);
    }
    printf("后缀表达式: %s\n", postfix);

    double res;
    rc = eval_postfix(postfix, &res);
    if (rc == 0) printf("计算结果: %.10g\n", res);
    else printf("计算失败，错误码 %d\n", rc);

}

//void main() {
//    reversePolishMenu();
//}

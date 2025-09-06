#include <stdio.h>

int calculateRabbitsNum(int months = 12) {   
    long long prev2 = 1;       
    long long prev1 = 1;      

    if (months < 0)
        return 0;

    printf("1月: %lld\n", prev2);
    if(months > 1)
        printf("2月: %lld\n", prev1);

    long long cur = prev1;
    //上个月兔子 + 成年兔子
    for (int m = 3; m <= months; ++m) {
        cur = prev1 + prev2;   
        printf("%d月: %lld\n", m, cur);
        prev2 = prev1;
        prev1 = cur;
    }

    printf("共有兔子%lld对\n",  cur);
    return cur;
}

//int main() {
//    int months = 12;
//    calculateRabbitsNum(months);
//    return 0;
//}
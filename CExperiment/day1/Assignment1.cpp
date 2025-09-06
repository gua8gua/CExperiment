#include <stdio.h>

int calculateRabbitsNum(int months = 12) {   
    long long prev2 = 1;       
    long long prev1 = 1;      

    if (months < 0)
        return 0;

    printf("1��: %lld\n", prev2);
    if(months > 1)
        printf("2��: %lld\n", prev1);

    long long cur = prev1;
    //�ϸ������� + ��������
    for (int m = 3; m <= months; ++m) {
        cur = prev1 + prev2;   
        printf("%d��: %lld\n", m, cur);
        prev2 = prev1;
        prev1 = cur;
    }

    printf("��������%lld��\n",  cur);
    return cur;
}

//int main() {
//    int months = 12;
//    calculateRabbitsNum(months);
//    return 0;
//}
#include <stdio.h>

int main(void) {
    int months = 12;              // Ò»Äê
    long long prev2 = 1;          // F(1)
    long long prev1 = 1;          // F(2)
    if (months == 1) {
        printf("Month 1: 1\nTotal: 1\n");
        return 0;
    }

    printf("Month 1: %lld\n", prev2);
    printf("Month 2: %lld\n", prev1);

    long long cur = prev1;
    for (int m = 3; m <= months; ++m) {
        cur = prev1 + prev2;      // F(n) = F(n-1) + F(n-2)
        printf("Month %d: %lld\n", m, cur);
        prev2 = prev1;
        prev1 = cur;
    }

    printf("After %d months: %lld pairs of rabbits\n", months, cur);
    return 0;
}
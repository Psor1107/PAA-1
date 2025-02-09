// Gabriel Lucchetta Garcia Sanchez - BCC - 828513 //
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 100
#define W 500
#define MAX N * W

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    while (scanf("%d", &n) && n != 0) {
        int weights[N];
        int total_sum = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d", &weights[i]);
            total_sum += weights[i];
        }

        bool dp[MAX + 1] = {false};
        dp[0] = true;

        for (int i = 0; i < n; i++) {
            for (int j = total_sum; j >= weights[i]; j--) {
                if (dp[j - weights[i]]) {
                    dp[j] = true;
                }
            }
        }

        int min_diff = total_sum;
        for (int j = total_sum / 2; j >= 0; j--) {
            if (dp[j]) {
                min_diff = total_sum - 2 * j;
                break;
            }
        }

        printf("%d\n", min_diff);
    }

    return 0;
}
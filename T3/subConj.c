// Gabriel Lucchetta Garcia Sanchez - BCC - 828513 //
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_D 100

int main() {
    int N, D;

    while (1) {
        scanf("%d", &N);
        if (N == 0) 
            break;
        scanf("%d", &D);
        int dp[MAX_N + 1][MAX_D] = {0};
        dp[0][0] = 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < D; j++) {
                dp[i][j] += dp[i - 1][j];
                dp[i][(j + i) % D] += dp[i - 1][j];
            }
        }
        printf("%d\n", dp[N][0]);
    }
    return 0;
}
// Gabriel Lucchetta Garcia Sanchez - BCC - 828513 //
#include <stdio.h>
#include <stdlib.h>

#define MAX_D 100000

int main()
{
    long long N, D;

    while (1)
    {
        scanf("%lld", &N);
        if (N == 0)
            break;
        scanf("%lld", &D);
        long long *dp_prev = (long long *)malloc(D * sizeof(long long));
        long long *dp_curr = (long long *)malloc(D * sizeof(long long));
        for (long long j = 0; j < D; j++)
        {
            dp_prev[j] = 0;
            dp_curr[j] = 0;
        }
        dp_prev[0] = 1;
        for (long long i = 1; i <= N; i++)
        {
            for (long long j = 0; j < D; j++)
            {
                dp_curr[j] = 0;
            }
            for (long long j = 0; j < D; j++)
            {
                dp_curr[j] += dp_prev[j];
                dp_curr[(j + i) % D] += dp_prev[j];
            }
            long long *temp = dp_prev;
            dp_prev = dp_curr;
            dp_curr = temp;
        }
        printf("%lld\n", dp_prev[0]);
        free(dp_prev);
        free(dp_curr);
    }
    return 0;
}
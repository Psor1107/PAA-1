#include <stdio.h>
#include <stdlib.h>

double exponencial(double B, unsigned int N)
{
    // Calcule o valor da exponencial B^N
    if (N == 0)
    {
        return 1;
    }
    else if (N % 2 == 0)
    {
        return exponencial(B, N / 2) * exponencial(B, N / 2);
    }
    else
    {
        return B * exponencial(B, N - 1);
    }
}

void imprimeDigitoOrdem(double num)
{
    int i = 0;
    while (num >= 10)
    {
        num = num / 10;
        i++;
    }
    printf("%d %d\n", (int)num, i);
}

int main()
{
    double B, resp;
    unsigned int N;
    scanf("%lf %u", &B, &N);
    resp = exponencial(B, N);
    // printf("%.2lf\n", resp);
    // printf("%.5e\n", resp);
    imprimeDigitoOrdem(resp);
    return 0;
}
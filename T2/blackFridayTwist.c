// Gabriel Lucchetta Garcia Sanchez - BCC - 828513 //
#include <stdio.h>
#include <stdlib.h>

void imprime(int v[], int n)
{
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", v[i]);
    }
    printf("\n");
}

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

long long calculaDesconto(int *precos, int n) {
    long long desconto = 0;
    
    qsort(precos, n, sizeof(int), compare);
    for (int i = 0; i < n; i++) {
        if ((i + 1) % 2 == 0 && i + 1 != n) { 
            desconto += precos[i];
            n--;
        }
    }
    return desconto;
}

int main(int argc, char *argv[])
{

    int i, n;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }

    scanf("%d", &n);
    int *v = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);

    // crie uma funcao que resolva o problema

    //printf("%d\n", n);
    //imprime(v, n);

    long long desconto = calculaDesconto(v, n);
    printf("%lld\n", desconto);

    free(v);

    return 0;
}
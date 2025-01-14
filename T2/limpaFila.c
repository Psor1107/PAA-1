#include <stdio.h>
#include <stdlib.h>

void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int compare(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

int *limpaFila(int v[], int n)
{
    int i = 0, a = 0;
    int *out = (int *)malloc(n * sizeof(int));
    qsort(v, n, sizeof(int), compare);
    out[a] = v[i];
    for(i = 1; i < n; i++)
    {
        if(v[i] != v[i-1])
        {
            a++;
            out[a] = v[i];
        }
    }
    imprime(out, a);
    return out;
} 

int main(int argc, char *argv[])
{
    int i, n;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }

    // lendo o tamanho de um vetor e os elementos do mesmo
    scanf("%d", &n);
    int *v = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);

    // crie uma funcao que resolva o problema
    int *out = limpaFila(v, n);

    //imprime(out, n);

    free(v);

    return 0;
}
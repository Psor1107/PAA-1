#include <stdio.h>
#include <stdlib.h>

void imprime(long v[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%ld ", v[i]);
    printf("\n");
}

long countInversionsAux(long v[], long aux[], int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    long inversions = 0;

    while (i <= mid && j <= right)
    {
        if (v[i] <= v[j])
            aux[k++] = v[i++];
        else
        {
            aux[k++] = v[j++];
            inversions += (mid - i + 1); // Evita overflow
        }
    }

    while (i <= mid)
        aux[k++] = v[i++];
    while (j <= right)
        aux[k++] = v[j++];

    for (i = left; i <= right; i++)
        v[i] = aux[i];

    return inversions;
}

long countInversions(long v[], long aux[], int left, int right)
{
    int mid;
    long inversions = 0;
    if (left < right)
    {
        mid = (left + right) / 2;

        inversions += countInversions(v, aux, left, mid);
        inversions += countInversions(v, aux, mid + 1, right);
        inversions += countInversionsAux(v, aux, left, mid, right);
    }
    return inversions;
}

long distanciaGenomica(int v1[], int v2[], int n)
{
    long *index_map = (long *)malloc(n * sizeof(long));
    for (int i = 0; i < n; i++)
        index_map[v1[i]] = i;

    long *matched = (long *)malloc(n * sizeof(long));
    for (int i = 0; i < n; i++)
        matched[i] = index_map[v2[i]];

    long *aux = (long *)malloc(n * sizeof(long));
    long result = countInversions(matched, aux, 0, n - 1); // Trabalha com `long`

    free(index_map);
    free(matched);
    free(aux);

    return result;
}

int main(int argc, char *argv[])
{
    int n;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: ./nome_arquivo_executavel\n");
        return 0;
    }

    // Lendo o tamanho dos vetores e seus elementos
    scanf("%d", &n);
    int *v1 = (int *)malloc(n * sizeof(int));
    int *v2 = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &v1[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &v2[i]);

    // Calcula e imprime o resultado
    printf("%ld\n", distanciaGenomica(v1, v2, n)); // Usa `%ld` para long

    free(v1);
    free(v2);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int countInversionsAux(int v[], int aux[], int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left, inversions = 0;

    while (i <= mid && j <= right)
    {
        if (v[i] <= v[j])
            aux[k++] = v[i++];
        else
        {
            aux[k++] = v[j++];
            inversions += (mid - i + 1);
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

int countInversions(int v[], int aux[], int left, int right)
{
    int mid, inversions  = 0;
    if (left < right)
    {
        mid = (left + right) / 2;

        inversions  += countInversions(v, aux, left, mid);
        inversions  += countInversions(v, aux, mid + 1, right);
        inversions  += countInversionsAux(v, aux, left, mid, right);
    }
    return inversions;
}

int distanciaGenomica(int v1[], int v2[], int n)
{
    int *index_map = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        index_map[v1[i]] = i;

    int *matched = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        matched[i] = index_map[v2[i]];

    int *aux = (int *)malloc(n * sizeof(int));
    int result = countInversions(matched, aux, 0, n - 1);

    free(index_map);
    free(matched);
    free(aux);

    return result;
}

int main(int argc, char *argv[])
{
    char file_name[MAX];
    FILE *entrada;
    int i, n;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }
    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNao encontrei o arquivo! Informe o nome da instancia\n");
        exit(EXIT_FAILURE);
    }

    // lendo do arquivo da instância
    fscanf(entrada, "%d", &n);
    int *v1 = (int *)malloc(n * sizeof(int));
    int *v2 = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        fscanf(entrada, "%d", &v1[i]);
    for (i = 0; i < n; i++)
        fscanf(entrada, "%d", &v2[i]);

    // lendo o tamanho de um vetor e os elementos do mesmo
    /*scanf("%d", &n);
    int *v = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    */

    // crie uma funcao que resolva o problema

    printf("%d\n", distanciaGenomica(v1, v2, n));

    // printf("%d\n", n);
    // imprime(v1, n);
    // imprime(v2, n);

    free(v1);
    free(v2);

    // fclose(entrada);
    return 0;
}
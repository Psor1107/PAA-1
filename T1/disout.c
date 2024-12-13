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
    float diff = *(float *)a - *(float *)b;
    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else
        return 0;
}

int detectaOutliers(int N, int S, int k, float L, float **D)
{
    int outliers = 0;
    for (int i = 0; i < S; i++)
    {
        float *distances = (float *)malloc((N - 1) * sizeof(float));
        int aux = 0;
        for (int j = 0; j < N; j++)
        {
            if (j != i)
                distances[aux++] = D[i][j];
        }

        qsort(distances, N - 1, sizeof(float), compare);

        if (distances[k] > L)
            outliers++;

        free(distances);
    }

    return outliers;
}

int main(int argc, char *argv[])
{
    // char file_name[MAX];
    // FILE *entrada;

    int N, S, k;
    float L;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }

    // scanf("%s", file_name);
    // entrada = fopen(file_name, "r");
    // if (entrada == NULL)
    // {
    //     printf("\nNao encontrei o arquivo! Informe o nome da instancia\n");
    //     exit(EXIT_FAILURE);
    // }

    // lendo do arquivo da instância
    // fscanf(entrada, "%d", &n);
    // int *v = (int *)malloc(n * sizeof(int));
    // for (i = 0; i < n; i++)
    //     fscanf(entrada, "%d", &v[i]);

    // lendo o tamanho de um vetor e os elementos do mesmo
    scanf("%d %d %d %f", &N, &S, &k, &L);
    float **D = (float **)malloc(S * sizeof(float *));
    for (int i = 0; i < S; i++)
        D[i] = (float *)malloc(N * sizeof(float));

    for (int i = 0; i < S; i++)
        for (int j = 0; j < N; j++)
            scanf("%f", &D[i][j]);

    // crie uma funcao que resolva o problema
    int result = detectaOutliers(N, S, k, L, D);
    printf("%d\n", result);

    for (int i = 0; i < S; i++)
        free(D[i]);
    free(D);

    // fclose(entrada);
    return 0;
}
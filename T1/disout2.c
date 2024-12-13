#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int compare(const void *a, const void *b)
{
    double diff = (*(double *)a) - (*(double *)b);
    return (diff > 0) - (diff < 0); 
}

double calculaMedia(int N, int S, int k, double **D)
{
    double totalDistance = 0.0;
    for (int i = 0; i < S; i++)
    {
        double *distances = (double *)malloc((N - 1) * sizeof(double));
        int idx = 0;
        for (int j = 0; j < N; j++)
        {
            if (j != i)
                distances[idx++] = D[i][j];
        }

        qsort(distances, N - 1, sizeof(double), compare);

        totalDistance += distances[k];

        free(distances);
    }
    return totalDistance / S;
}

int main(int argc, char *argv[])
{
    // char file_name[MAX];
    // FILE *entrada;

    int N, S, k;

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
    scanf("%d %d %d", &N, &S, &k);
    double **D = (double **)malloc(S * sizeof(double *));
    for (int i = 0; i < S; i++)
        D[i] = (double *)malloc(N * sizeof(double));

    for (int i = 0; i < S; i++)
        for (int j = 0; j < N; j++)
            scanf("%lf", &D[i][j]);

    // crie uma funcao que resolva o problema
    double result = calculaMedia(N, S, k, D);
    printf("%.2lf\n", round(result * 100) / 100);

    for (int i = 0; i < S; i++)
        free(D[i]);
    free(D);

    // fclose(entrada);
    return 0;
}
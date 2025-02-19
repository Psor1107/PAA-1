// Gabriel Lucchetta Garcia Sanchez - BCC - 828513 //
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VALUE 100000000

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

int *limpaFila(int v[], int n, int *size) {
    bool *visited = (bool *)calloc(MAX_VALUE + 1, sizeof(bool));
    int *out = (int *)malloc(n * sizeof(int));
    int a = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[v[i]]) {
            visited[v[i]] = true;
            out[a++] = v[i];
        }
    }

    *size = a;
    free(visited);
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
    int size;
    int *out = limpaFila(v, n, &size);


    imprime(out, size);
    
    free(v);
    free(out);

    return 0;
}

// Gabriel Lucchetta Garcia Sanchez - BCC - 828513 //
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct {
    int vertice;
    int peso;
} Aresta;

typedef struct {
    Aresta *arestas;
    int tamanho;
    int capacidade;
} ListaAdjacencia;

typedef struct {
    ListaAdjacencia *listasAdjacencia;
    int numVertices;
} Grafo;

Grafo* criarGrafo(int vertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = vertices;
    grafo->listasAdjacencia = (ListaAdjacencia*)malloc(vertices * sizeof(ListaAdjacencia));

    for (int i = 0; i < vertices; i++) {
        grafo->listasAdjacencia[i].arestas = (Aresta*)malloc(10 * sizeof(Aresta));
        grafo->listasAdjacencia[i].tamanho = 0;
        grafo->listasAdjacencia[i].capacidade = 10;
    }

    return grafo;
}

void adicionarAresta(Grafo* grafo, int origem, int destino, int peso) {
    if (grafo->listasAdjacencia[origem].tamanho == grafo->listasAdjacencia[origem].capacidade) {
        grafo->listasAdjacencia[origem].capacidade *= 2;
        grafo->listasAdjacencia[origem].arestas = (Aresta*)realloc(grafo->listasAdjacencia[origem].arestas, grafo->listasAdjacencia[origem].capacidade * sizeof(Aresta));
    }

    grafo->listasAdjacencia[origem].arestas[grafo->listasAdjacencia[origem].tamanho].vertice = destino;
    grafo->listasAdjacencia[origem].arestas[grafo->listasAdjacencia[origem].tamanho].peso = peso;
    grafo->listasAdjacencia[origem].tamanho++;
}

int dijkstra(Grafo* grafo, int verticeInicial, int verticeFinal) {
    int V = grafo->numVertices;
    int dist[V];
    int visitado[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visitado[i] = 0;
    }

    dist[verticeInicial] = 0;

    for (int i = 0; i < V - 1; i++) {
        int minDist = INF, minIndice = -1;

        for (int v = 0; v < V; v++) {
            if (!visitado[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndice = v;
            }
        }

        if (minIndice == -1) {
            break;
        }

        int u = minIndice;
        visitado[u] = 1;

        for (int j = 0; j < grafo->listasAdjacencia[u].tamanho; j++) {
            int v = grafo->listasAdjacencia[u].arestas[j].vertice;
            int peso = grafo->listasAdjacencia[u].arestas[j].peso;

            if (!visitado[v] && dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
            }
        }
    }

    return dist[verticeFinal];
}

int main(int argc, char *argv[]) {
    
    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }

    int V, E;
    scanf("%d %d", &V, &E);

    Grafo* grafo = criarGrafo(V);

    for (int i = 0; i < E; i++) {
        int A, B, W;
        scanf("%d %d %d", &A, &B, &W);
        adicionarAresta(grafo, A, B, W);
    }

    int distancia = dijkstra(grafo, 0, V - 1);
    printf("%d\n", distancia);

    for (int i = 0; i < V; i++) {
        free(grafo->listasAdjacencia[i].arestas);
    }
    free(grafo->listasAdjacencia);
    free(grafo);

    return 0;
}
// Gabriel Lucchetta Garcia Sanchez - BCC - 828513 //
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX LLONG_MAX

typedef struct {
    int destino;
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

typedef struct {
    int vertice;
    long long distancia;
} Nodo;

typedef struct {
    int tamanho;
    int capacidade;
    int *pos;
    Nodo **array;
} MinHeap;

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

    grafo->listasAdjacencia[origem].arestas[grafo->listasAdjacencia[origem].tamanho].destino = destino;
    grafo->listasAdjacencia[origem].arestas[grafo->listasAdjacencia[origem].tamanho].peso = peso;
    grafo->listasAdjacencia[origem].tamanho++;
}

Nodo* novoNodo(int vertice, long long distancia) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->vertice = vertice;
    nodo->distancia = distancia;
    return nodo;
}

MinHeap* criarMinHeap(int capacidade) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacidade * sizeof(int));
    minHeap->tamanho = 0;
    minHeap->capacidade = capacidade;
    minHeap->array = (Nodo**)malloc(capacidade * sizeof(Nodo*));
    return minHeap;
}

void trocarNodos(Nodo** a, Nodo** b) {
    Nodo* t = *a;
    *a = *b;
    *b = t;
}

void heapify(MinHeap* minHeap, int idx) {
    int menor = idx;
    int esquerda = 2 * idx + 1;
    int direita = 2 * idx + 2;

    if (esquerda < minHeap->tamanho && minHeap->array[esquerda]->distancia < minHeap->array[menor]->distancia)
        menor = esquerda;

    if (direita < minHeap->tamanho && minHeap->array[direita]->distancia < minHeap->array[menor]->distancia)
        menor = direita;

    if (menor != idx) {
        Nodo* menorNodo = minHeap->array[menor];
        Nodo* idxNodo = minHeap->array[idx];

        minHeap->pos[menorNodo->vertice] = idx;
        minHeap->pos[idxNodo->vertice] = menor;

        trocarNodos(&minHeap->array[menor], &minHeap->array[idx]);

        heapify(minHeap, menor);
    }
}

int heapVazia(MinHeap* minHeap) {
    return minHeap->tamanho == 0;
}

Nodo* extrairMin(MinHeap* minHeap) {
    if (heapVazia(minHeap))
        return NULL;

    Nodo* raiz = minHeap->array[0];

    Nodo* ultimoNodo = minHeap->array[minHeap->tamanho - 1];
    minHeap->array[0] = ultimoNodo;

    minHeap->pos[raiz->vertice] = minHeap->tamanho - 1;
    minHeap->pos[ultimoNodo->vertice] = 0;

    --minHeap->tamanho;
    heapify(minHeap, 0);

    return raiz;
}

void diminuirChave(MinHeap* minHeap, int vertice, long long distancia) {
    int i = minHeap->pos[vertice];
    minHeap->array[i]->distancia = distancia;

    while (i && minHeap->array[i]->distancia < minHeap->array[(i - 1) / 2]->distancia) {
        minHeap->pos[minHeap->array[i]->vertice] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertice] = i;
        trocarNodos(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

bool estaNaHeap(MinHeap* minHeap, int vertice) {
    return minHeap->pos[vertice] < minHeap->tamanho;
}

long long dijkstra(Grafo* grafo, int verticeInicial, int verticeFinal) {
    int V = grafo->numVertices;
    long long* dist = (long long*)malloc(V * sizeof(long long));

    MinHeap* minHeap = criarMinHeap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = MAX;
        minHeap->array[v] = novoNodo(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[verticeInicial] = novoNodo(verticeInicial, dist[verticeInicial]);
    minHeap->pos[verticeInicial] = verticeInicial;
    dist[verticeInicial] = 0;
    diminuirChave(minHeap, verticeInicial, dist[verticeInicial]);

    minHeap->tamanho = V;

    while (!heapVazia(minHeap)) {
        Nodo* minHeapNode = extrairMin(minHeap);
        int u = minHeapNode->vertice;

        for (int i = 0; i < grafo->listasAdjacencia[u].tamanho; ++i) {
            int v = grafo->listasAdjacencia[u].arestas[i].destino;

            if (estaNaHeap(minHeap, v) && dist[u] != MAX && grafo->listasAdjacencia[u].arestas[i].peso + dist[u] < dist[v]) {
                dist[v] = dist[u] + grafo->listasAdjacencia[u].arestas[i].peso;
                diminuirChave(minHeap, v, dist[v]);
            }
        }
    }

    long long resultado = dist[verticeFinal];
    free(dist);
    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);
    return resultado;
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

    long long distancia = dijkstra(grafo, 0, V - 1);
    printf("%lld\n", distancia);

    for (int i = 0; i < V; i++) {
        free(grafo->listasAdjacencia[i].arestas);
    }
    free(grafo->listasAdjacencia);
    free(grafo);

    return 0;
}

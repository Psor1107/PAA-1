#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX LLONG_MAX
#define MAX_VERTICES 1000000
#define MAX_EDGES 1000000

typedef struct {
    int destino;
    int peso;
} Aresta;

// Lista de adjacência
Aresta **grafo;
int *tamanhoArestas;

// Heap para Dijkstra
typedef struct {
    int vertice;
    long long distancia;
} Nodo;

Nodo *heap;
int heapSize;

void inicializaHeap(int maxSize) {
    heap = (Nodo *)malloc(maxSize * sizeof(Nodo));
    heapSize = 0;
}

void heapify(int idx) {
    int menor = idx;
    int esquerda = 2 * idx + 1;
    int direita = 2 * idx + 2;

    if (esquerda < heapSize && heap[esquerda].distancia < heap[menor].distancia) {
        menor = esquerda;
    }

    if (direita < heapSize && heap[direita].distancia < heap[menor].distancia) {
        menor = direita;
    }

    if (menor != idx) {
        Nodo temp = heap[idx];
        heap[idx] = heap[menor];
        heap[menor] = temp;
        heapify(menor);
    }
}

void push(Nodo nodo) {
    heap[heapSize] = nodo;
    int i = heapSize++;

    while (i != 0 && heap[(i - 1) / 2].distancia > heap[i].distancia) {
        Nodo temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Nodo pop() {
    Nodo raiz = heap[0];
    heap[0] = heap[--heapSize];
    heapify(0);
    return raiz;
}

void adicionaAresta(int origem, int destino, int peso) {
    grafo[origem][tamanhoArestas[origem]].destino = destino;
    grafo[origem][tamanhoArestas[origem]].peso = peso;
    tamanhoArestas[origem]++;
}

long long dijkstra(int vertices, int origem, int destino) {
    long long *distancia = (long long *)malloc(vertices * sizeof(long long));
    bool *visitado = (bool *)calloc(vertices, sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        distancia[i] = MAX;
    }
    distancia[origem] = 0;

    inicializaHeap(vertices);
    push((Nodo){origem, 0});

    while (heapSize > 0) {
        Nodo atual = pop();
        int u = atual.vertice;

        if (visitado[u]) continue;
        visitado[u] = true;

        for (int i = 0; i < tamanhoArestas[u]; i++) {
            Aresta v = grafo[u][i];
            if (distancia[u] + v.peso < distancia[v.destino]) {
                distancia[v.destino] = distancia[u] + v.peso;
                push((Nodo){v.destino, distancia[v.destino]});
            }
        }
    }

    long long resultado = distancia[destino];
    free(distancia);
    free(visitado);
    free(heap);
    return resultado;
}

int main(int argc, char *argv[]) {
    int V, E;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }
    
    scanf("%d %d", &V, &E);

    grafo = (Aresta **)malloc(V * sizeof(Aresta *));
    tamanhoArestas = (int *)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++) {
        grafo[i] = (Aresta *)malloc(MAX_EDGES * sizeof(Aresta));
    }

    for (int i = 0; i < E; i++) {
        int A, B, W;
        scanf("%d %d %d", &A, &B, &W);
        adicionaAresta(A, B, W);
    }

    long long distanciaMin = dijkstra(V, 0, V - 1);
    printf("%lld\n", distanciaMin);

    for (int i = 0; i < V; i++) {
        free(grafo[i]);
    }
    free(grafo);
    free(tamanhoArestas);

    return 0;
}

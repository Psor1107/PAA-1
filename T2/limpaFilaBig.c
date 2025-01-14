#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_SIZE 100003

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int hash(int value) {
    return abs(value) % HASH_SIZE;
}

bool insert(Node *hashTable[], int value) {
    int index = hash(value);
    Node *current = hashTable[index];
    while (current != NULL) {
        if (current->value == value) {
            return false;
        }
        current = current->next;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    return true;
}

void freeHashTable(Node *hashTable[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *current = hashTable[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

void imprime(int v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int *limpaFila(int v[], int n, int *newSize) {
    Node *hashTable[HASH_SIZE] = {NULL};
    int *out = (int *)malloc(n * sizeof(int));
    int a = 0;

    for (int i = 0; i < n; i++) {
        if (insert(hashTable, v[i])) {
            out[a++] = v[i];
        }
    }

    *newSize = a;
    freeHashTable(hashTable);
    return out;
}

int main(int argc, char *argv[]) {
    int i, n;

    if (argc != 1) {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }

    // lendo o tamanho de um vetor e os elementos do mesmo
    scanf("%d", &n);
    int *v = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);

    // crie uma funcao que resolva o problema
    int newSize;
    int *out = limpaFila(v, n, &newSize);

    imprime(out, newSize);

    free(v);
    free(out);

    return 0;
}
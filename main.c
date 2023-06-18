#include <stdio.h>
#include <stdlib.h>

#define MAX_ARESTAS 100

typedef struct {
    int origem;
    int destino;
    int peso;
} Aresta;

void lerGrafo(FILE *arquivo, int *numVertices, int *numArestas, int **vertices, Aresta arestas[]) {
    fscanf(arquivo, "%d %d", numVertices, numArestas);

    *vertices = (int *)malloc((*numVertices) * sizeof(int));

    for (int i = 0; i < *numVertices; i++) {
        (*vertices)[i] = i + 1;
    }

    for (int i = 0; i < *numArestas; i++) {
        int origem, destino, peso;
        fscanf(arquivo, "%d %d %d", &origem, &destino, &peso);
        arestas[i].origem = origem;
        arestas[i].destino = destino;
        arestas[i].peso = peso;
    }
}

void escreverGrafo(FILE *arquivo, int numVertices, int numArestas, int vertices[], Aresta arestas[]) {
    fprintf(arquivo, "Grafo\n");
    fprintf(arquivo, "V: ");
    for (int i = 0; i < numVertices; i++) {
        fprintf(arquivo, "%d ", vertices[i]);
    }
    fprintf(arquivo, "\nE: ");
    
    int *visited = (int *)calloc(numVertices, sizeof(int));  // Array to track visited vertices
    
    for (int i = 0; i < numArestas; i++) {
        int origem = arestas[i].origem;
        int destino = arestas[i].destino;
        
        if (!visited[origem - 1]) {
            fprintf(arquivo, "(%d,%d) ", origem, destino);
            visited[origem - 1] = 1;
        } else if (!visited[destino - 1]) {
            fprintf(arquivo, "(%d,%d) ", origem, destino);
            visited[destino - 1] = 1;
        }
    }
    
    fprintf(arquivo, "\n");
    free(visited);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    FILE *entrada = fopen(argv[1], "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    int numVertices = 0, numArestas = 0;
    int *vertices = NULL;
    Aresta arestas[MAX_ARESTAS];

    lerGrafo(entrada, &numVertices, &numArestas, &vertices, arestas);
    fclose(entrada);

    FILE *saida = fopen(argv[2], "w");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        free(vertices);
        return 1;
    }

    escreverGrafo(saida, numVertices, numArestas, vertices, arestas);
    fclose(saida);

    free(vertices);

    return 0;
}

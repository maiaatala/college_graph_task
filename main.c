#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int verificarRegularidade(int numVertices, Aresta arestas[], int numArestas) {
    int grauPrimeiroVertice = 0;
    int grauAtual;

    // Contagem do grau do primeiro vértice
    for (int i = 0; i < numArestas; i++) {
        if (arestas[i].origem == 1) {
            grauPrimeiroVertice++;
        }
    }

    // Verificação do grau dos demais vértices
    for (int i = 2; i <= numVertices; i++) {
        grauAtual = 0;

        for (int j = 0; j < numArestas; j++) {
            if (arestas[j].origem == i || arestas[j].destino == i) {
                grauAtual++;
            }
        }

        if (grauAtual != grauPrimeiroVertice) {
            return 0; // Grafo é irregular
        }
    }

    return 1; // Grafo é regular
}

int verificarCicloRecursivo(int vertice, int visitados[], int pai, Aresta arestas[], int numArestas) {
    visitados[vertice] = 1;

    for (int i = 0; i < numArestas; i++) {
        if (arestas[i].origem == vertice) {
            int vizinho = arestas[i].destino;
            if (!visitados[vizinho]) {
                if (verificarCicloRecursivo(vizinho, visitados, vertice, arestas, numArestas)) {
                    return 1; // Ciclo encontrado
                }
            } else if (vizinho != pai) {
                return 1; // Ciclo encontrado
            }
        }
    }

    return 0; // Nenhum ciclo encontrado
}

int verificarCiclicidade(int numVertices, Aresta arestas[], int numArestas) {
    int *visitados = (int *)malloc(numVertices * sizeof(int));
    memset(visitados, 0, numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        if (!visitados[i]) {
            if (verificarCicloRecursivo(i, visitados, -1, arestas, numArestas)) {
                free(visitados);
                return 1; // Grafo é cíclico
            }
        }
    }

    free(visitados);
    return 0; // Grafo é acíclico
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
    if (verificarRegularidade(numVertices, arestas, numArestas)) {
        fprintf(saida, "Regular\n");
    } else {
        fprintf(saida, "Não Regular\n");
    }

    if (verificarCiclicidade(numVertices, arestas, numArestas)) {
        fprintf(saida, "Cíclico\n");
    } else {
        fprintf(saida, "Acíclico\n");
    }
    
    fclose(saida);

    free(vertices);

    return 0;
}

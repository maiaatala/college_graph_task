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

void lerGrafo(FILE *arquivo, int *numVertices, int *numArestas, int **vertices, Aresta **arestas) {
    fscanf(arquivo, "%d %d", numVertices, numArestas);

    *vertices = (int *)malloc((*numVertices) * sizeof(int));
    *arestas = (Aresta *)malloc((*numArestas) * sizeof(Aresta));

    for (int i = 0; i < *numVertices; i++) {
        (*vertices)[i] = i + 1;
    }

    for (int i = 0; i < *numArestas; i++) {
        int origem, destino, peso;
        fscanf(arquivo, "%d %d %d", &origem, &destino, &peso);
        (*arestas)[i].origem = origem;
        (*arestas)[i].destino = destino;
        (*arestas)[i].peso = peso;
    }
}

void printGraph(FILE *arquivo, int numVertices, int numArestas, int vertices[], Aresta arestas[]) {
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
        
        fprintf(arquivo, "(%d,%d) ", origem, destino);
        visited[origem - 1] = 1;
        visited[destino - 1] = 1;
    }
    
    // Check if there are any unvisited vertices
    // for (int i = 0; i < numVertices; i++) {
    //     if (!visited[i]) {
    //         fprintf(arquivo, "(%d) ", vertices[i]);
    //     }
    // }
    
    fprintf(arquivo, "\n");
    free(visited);
}

int verificarRegularidade(int numVertices, Aresta arestas[], int numArestas) {
    int *graus = (int *)calloc(numVertices, sizeof(int));

    // Contagem dos graus dos vértices
    for (int i = 0; i < numArestas; i++) {
        int origem = arestas[i].origem - 1;
        int destino = arestas[i].destino - 1;
        graus[origem]++;
        graus[destino]++;
    }

    // Verificação se todos os vértices têm o mesmo grau
    int grauPrimeiroVertice = graus[0];
    for (int i = 1; i < numVertices; i++) {
        if (graus[i] != grauPrimeiroVertice) {
            free(graus);
            return 0; // Grafo é irregular
        }
    }

    free(graus);
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

int encontrarVerticeMinimo(int *distancias, int *visitados, int numVertices) {
    int minDistancia = INT_MAX;
    int verticeMinimo = -1;

    for (int i = 0; i < numVertices; i++) {
        if (visitados[i] == 0 && distancias[i] <= minDistancia) {
            minDistancia = distancias[i];
            verticeMinimo = i;
        }
    }

    return verticeMinimo;
}

int encontrarMenorVertice(int numVertices, int *vertices) {
    int menor = INT_MAX;
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] < menor) {
            menor = vertices[i];
        }
    }
    return menor;
}

int encontrarMaiorVertice(int numVertices, int *vertices) {
    int maior = INT_MIN;
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] > maior) {
            maior = vertices[i];
        }
    }
    return maior;
}

void imprimirCaminhoMinimoRecursivo(FILE *saida, int *predecessores, int origem, int destino) {
    if (origem == destino) {
        fprintf(saida, "%d", origem);
    } else if (predecessores[destino - 1] == -1) {
        fprintf(saida, "Não existe caminho entre a origem e o destino.\n");
    } else {
        imprimirCaminhoMinimoRecursivo(saida, predecessores, origem, predecessores[destino - 1] + 1);
        fprintf(saida, "-%d", destino);
    }
}

void imprimirCaminhoMinimo(FILE *saida, int numVertices, Aresta *arestas, int numArestas, int origem, int destino) {
    // Vetor de distâncias e vetor de predecessores
    int *distancias = (int *)malloc(numVertices * sizeof(int));
    int *predecessores = (int *)malloc(numVertices * sizeof(int));

    // Inicializar as distâncias e predecessores
    for (int i = 0; i < numVertices; i++) {
        distancias[i] = INT_MAX;
        predecessores[i] = -1;
    }

    // A distância para a origem é 0
    distancias[origem - 1] = 0;

    // Vetor para armazenar os vértices visitados
    int *visitados = (int *)malloc(numVertices * sizeof(int));

    // Loop principal do algoritmo de Dijkstra
    for (int i = 0; i < numVertices - 1; i++) {
        // Encontrar o vértice não visitado com a menor distância
        int u = -1;
        int minDistancia = INT_MAX;
        for (int j = 0; j < numVertices; j++) {
            if (!visitados[j] && distancias[j] < minDistancia) {
                u = j;
                minDistancia = distancias[j];
            }
        }

        if (u == -1) {
            break;  // Não há mais vértices alcançáveis
        }

        // Marcar o vértice como visitado
        visitados[u] = 1;

        // Atualizar as distâncias dos vértices adjacentes a u
        for (int j = 0; j < numArestas; j++) {
            if (arestas[j].origem == u + 1) {
                int v = arestas[j].destino - 1;
                int peso = arestas[j].peso;

                if (!visitados[v] && distancias[u] != INT_MAX && distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                    predecessores[v] = u;
                }
            }
        }
    }
    fprintf(saida, "Caminho mínimo: ");
    // Imprimir o caminho mínimo
    imprimirCaminhoMinimoRecursivo(saida, predecessores, origem, destino);

    fprintf(saida, "\n");

    free(distancias);
    free(predecessores);
    free(visitados);
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
    Aresta *arestas = NULL;

    lerGrafo(entrada, &numVertices, &numArestas, &vertices, &arestas);
    fclose(entrada);

    FILE *saida = fopen(argv[2], "w");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        free(vertices);
        return 1;
    }

    printGraph(saida, numVertices, numArestas, vertices, arestas);

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
    int origem = encontrarMenorVertice(numVertices, vertices);
    int destino = encontrarMaiorVertice(numVertices, vertices);
    imprimirCaminhoMinimo(saida, numVertices, arestas, numArestas, origem, destino);

    fclose(saida);

    free(vertices);

    return 0;
}

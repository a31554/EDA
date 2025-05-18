/*****************************************************************//**
 * \file   main2.c
 * \brief  Programa principal para gestão de vertices, arestas e grafos
 *
 * \author Afonso Macedo
 * \number 31554
 * \local  Intituto politecnico do cavado e do ave
 * \date   May 2025
 *********************************************************************/
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "Representacao2.h"
#include "Funcoes2.h"

Grafo grafo;  // Grafo global
int res;
char opcao;

int main() {
    do {
        /// Menu de opções
        printf("\n------------ MENU PRINCIPAL ------------\n");
        printf("1. Carregar grafo de antenas do ficheiro\n");
        printf("2. Percorrer grafo em profundidade (DFS)\n");
        printf("3. Percorrer grafo em largura (BFS)\n");
        printf("4. Encontrar todos os caminhos entre duas antenas\n");
        printf("5. Listar interseções entre duas frequencias\n");
        printf("s. Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        switch (opcao) {
        case '1': {
            grafo.numVertices = 0;  // Limpa grafo antes de carregar
            grafo = *carregarGrafo(&grafo, &res, "estrutura.txt");
            if (!res) printf("Erro ao carregar o grafo.\n");
            else printf("Grafo carregado com sucesso com %d antenas.\n", grafo.numVertices);
            break;
        }
        case '2': {
            int origem;
            printf("Indice da antena de origem (0 a %d): ", grafo.numVertices - 1);
            scanf("%d", &origem);
            depthFirstSearch(&grafo, origem, &res);
            if (res) printf("DFS executada com sucesso.\n");
            else printf("Erro: indice invalido.\n");
            break;
        }
        case '3': {
            int origem;
            printf("Indice da antena de origem (0 a %d): ", grafo.numVertices - 1);
            scanf("%d", &origem);
            breadthFirstSearch(&grafo, origem, &res);
            if (res) printf("BFS executada com sucesso.\n");
            else printf("Erro: indice invalido.\n");
            break;
        }
        case '4': {
            int origem, destino;
            printf("Indice da antena origem: ");
            scanf("%d", &origem);
            printf("Indice da antena destino: ");
            scanf("%d", &destino);

            int caminhos[100][MAX_VERTICES], comprimentos[100], totalCaminhos = 0;

            todosCaminhos(&grafo, origem, destino, caminhos, &totalCaminhos, comprimentos);

            if (totalCaminhos == 0)
                printf("Nenhum caminho encontrado.\n");
            else {
                printf("Caminhos entre %d e %d:\n", origem, destino);
                for (int i = 0; i < totalCaminhos; i++) {
                    printf("Caminho %d: ", i + 1);
                    for (int j = 0; j < comprimentos[i]; j++) {
                        int idx = caminhos[i][j];
                        printf("%c(%d,%d) ", grafo.vertices[idx].frequencia, grafo.vertices[idx].linha, grafo.vertices[idx].coluna);
                    }
                    printf("\n");
                }
            }
            break;
        }
        case '5': {
            char f1, f2;
            printf("Frequencia 1: ");
            scanf(" %c", &f1);
            printf("Frequencia 2: ");
            scanf(" %c", &f2);

            int linhas[100], colunas[100], total = 0;
            intersecoesFrequencias(&grafo, f1, f2, linhas, colunas, &total);

            if (total == 0)
                printf("Nenhuma intersecao encontrada.\n");
            else {
                printf("Intersecoes entre '%c' e '%c':\n", f1, f2);
                for (int i = 0; i < total; i++) {
                    printf("(%d, %d)\n", linhas[i], colunas[i]);
                }
            }
            break;
        }
        case 's':
            printf("A sair...\n");
            break;
        default:
            printf("Opcao invalida. Escolha novamente.\n");
        }

    } while (opcao != 's');

    return 0;
}
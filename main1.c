/*****************************************************************//**
 * \file   main1.c
 * \brief  Programa principal para gestão de antenas e efeitos nefastos
 * 
 * \author Afonso Macedo
 * \number 31554
 * \local  Intituto politecnico do cavado e do ave
 * \date   March 2025
 *********************************************************************/
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "funcoes1.h"

Antena* matriz =NULL;
Antena* nefasto = NULL;
char frequencia;
int linha, coluna;
char opcao;
int res;


int main() {
    do {
        /// Menu de opções
        printf("\n---------- MENU PRINCIPAL ----------\n");
        printf("1. Carregar antenas de um ficheiro\n");
        printf("2. Inserir nova antena\n");
        printf("3. Remover antena\n");
        printf("4. Calcular localizacoes com efeito nefasto\n");
        printf("5. Listar antenas e localizacoes\n");
        printf("s. Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);
        
        switch (opcao) {
        case '1':
            printf("\nCarregar ficheiros:\n");
            matriz = carregarFicheiro(matriz, &res, "estrutura.txt");
            if (res == 0) printf("\nErro ao carregar ficheiro\n");
            else printf("\nO ficheiro foi carregado com sucesso!\n");
            break;
        case '2':
            printf("Qual a frequencia:");
            scanf(" %c", &frequencia);
            printf("Qual a linha:");
            scanf(" %d", &linha);
            printf("Qual a coluna:");
            scanf(" %d", &coluna);
            matriz = inserirAntena(matriz, frequencia, coluna, linha, &res);
            if (res == 0) printf("\nErro ao inserir\n");
            else  printf("\nAntena inserida com sucesso!\n");
            break;
        case '3':
            printf("Qual a frequencia:");
            scanf(" %c", &frequencia);
            printf("Qual a linha:");
            scanf(" %d", &linha);
            printf("Qual a coluna:");
            scanf(" %d", &coluna);
            matriz= removerAntena( matriz, frequencia, linha, coluna, &res);
            if (res == 0) printf("Erro ao remover");
            else  printf("\nAntena removida com sucesso!\n");
            break;
        case '4':
            nefasto= calcularEfeitoNefasto(matriz, frequencia, linha, coluna, res);
            ///Listar o Nefasto
            printf("\n=== Lista de Antenas Interferentes (Nefasto) ===\n");
            /// Verificar se a lista de interferentes está vazia
            if (nefasto == NULL) {
                printf("\nNenhuma antena interfere (lista nefasto vazia).\n");
                return;
            }
            Antena* novo = nefasto; /// Apontador para percorrer a lista nefasto
            while (novo != NULL) {
                printf("Frequência: %c | Linha: %d | Coluna: %d\n", novo->frequencia, novo->linha, novo->coluna);
                novo = novo->prox; /// Avança para a próxima antena interferente
                }
            break;
        case '5':
            printf("\n=== Lista de Antenas ===\n");
            listarAntena(matriz);
            break;
        case 's':
            libertarmemoria(matriz);
            printf("\nA sair...\n");
            break;
        default:
            printf("Escolha uma das opções acima.\n");
            break;

        }
    } while (opcao != 's');
            return 0;
    }





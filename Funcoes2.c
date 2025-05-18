/*****************************************************************//**
 * \file   Funcoes2.c
 * \brief  Implementação das funções de manipulação de grafos de antenas
 *
 * \author Afonso Macedo
 * \number 31554
 * \local  Intituto politecnico do cavado e do ave
 * \date   May 2025
 *********************************************************************/

#pragma once
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <malloc.h>
#include "funcoes2.h"

/// Função para carregar os vertices do ficheiro texto
Grafo* carregarGrafo(Grafo* ponteiro, int* res, char localizar[180]) {

    FILE* file = fopen(localizar, "r");
    if (!file) {
        *res = 0; ///não conseguiu abrir o ficheiro
        return ponteiro;
    }

    ponteiro->numVertices = 0; ///Começamos com 0 vertices
    char linha[50]; /// A linha máxima tem 50 caracteres
    int y = 0; /// Coordenada Y (linha da matriz)

    ///Lê o ficheiro linha a linha
    while (fgets(linha, sizeof(linha), file) != NULL) ///Lê uma linha do ficheiro e armazena no char linha.
    {
        for (int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++) { /// Coordenada X (coluna da matriz)
            ///Se estiver entre as seguintes letras:
            if ((linha[x] >= 'A' && linha[x] <= 'Z') || (linha[x] >= 'a' && linha[x] <= 'z'))
            {
                char frequencia = linha[x];
                ///criamos vertices com frequencia, linha e coluna
                Vertice v1;
                v1.frequencia = frequencia;
                v1.linha = y;
                v1.coluna = x;
                
                ///guarda frequencia e posição da antena
                int quantidade = ponteiro->numVertices; ///guarda quantas antenas existem no grafo
                ponteiro->vertices[quantidade] = v1;   ///guarda a nova antena no array vertice
                ponteiro->listaAdj[quantidade] = NULL; ///nova antena ainda não tem ligações
                ponteiro->numVertices++; ///Atualiza o total de antenas no grafo.

                /// procurar antenas com mesma frequência para ligar em arestas
                for (int i = 0; i < quantidade; i++)
                {
                    if (ponteiro->vertices[i].frequencia == frequencia)
                    {
                        ligarAresta(ponteiro, i, quantidade);
                    }
                }
            }
        }
        y++;
    }
    fclose(file); /// Fechar o ficheiro 
    *res = 1; ///conseguiu abrir o ficheiro
    return ponteiro;
}

///Função para criar Arestas entre vertices com a mesma frequancia
Aresta* novaAresta(int destino) {
	
	Aresta* nova = (Aresta*)malloc(sizeof(Aresta));		///Alocar memória para as arestas
	nova->destino = destino;	/// Guarda o índice do vértice de destino
	nova->prox = 0;		/// A próxima ligação começa como NULL
	return nova;
}

///Função para ligar vértices e criar arestas
void ligarAresta(Grafo* ponteiro, int origem, int destino) {
     
    /// Ligar o vertice de origem ao vertice destino
    Aresta* nova = novaAresta(destino);  
    nova->prox = ponteiro->listaAdj[origem]; /// aponta para a nova cabeça da lista (origem)
    ponteiro->listaAdj[origem] = nova; /// nova aresta fica no início da lista

    /// Ligar o vertice destino ao vertice origem (inverso)
    Aresta* novainv = novaAresta(origem);
    novainv->prox = ponteiro->listaAdj[destino]; /// aponta para a nova cabeça da lista (origem)
    ponteiro->listaAdj[destino] = novainv;  /// coloca a nova ligação no início da lista do destino

}

///DFS: Percorre o grafo em profundidade
void depthFirstSearch(Grafo* ponteiro, int origem, int *res) {

    ///Se as caracteristicas da antena forem invalidas
    if (origem <0 || origem >= ponteiro->numVertices)
    {
        *res = 0; ///Erro
        return; ///porque tamos a usar void
    }

    int stack[MAX_VERTICES];  ///guardar os visitantes, controlar o caminho DFS
    int top = -1;  ///numerar os visitantes 

    ///Marca todos os vertices como nao visitados
    for (int i = 0; i < ponteiro->numVertices; i++)
    {
        ponteiro->vertices[i].visitado = 0;
    }

    ///Marcar a antena inicial como visitada e guardar na strack
    ponteiro->vertices[origem].visitado = 1;
    stack[++top] = origem; 

    ///Enquato houver elementos na stack
    while (top>=0) {
        int atual = stack[top]; ///obtemos o indice do vertice atual

        Aresta* arestas = ponteiro->listaAdj[atual]; /// Obter vizinhos

        int novo = 0; ///int para saber se encontramos um visinho nao visitado

        /// Percorremos os vizinhos do vértice atual
        while (arestas != NULL) {
            int destino = arestas->destino;  /// Vértice vizinho

            /// Se esse vizinho ainda não foi visitado
            if (!ponteiro->vertices[destino].visitado) {
                /// Marcamos como visitado
                ponteiro->vertices[destino].visitado = 1;

                /// Adicionamos à stack para continuar a partir dele
                stack[top++] = destino;

                novo = 1;   ///Se este vértice tiver algum vizinho novo dentro do while ()
                break;  /// Paramos para explorar esse novo vértice primeiro (profundidade)
            }

            /// Avançamos para o próximo vizinho
            arestas = arestas->prox;
        }

        /// Se não encontrou nenhum vizinho novo
        if (!novo) {
            top--;  /// Retira o vértice do topo da stack (recuo na DFS)
        }
    }
    *res = 1; ///Sucesso
}

///BFS: Percorre o grafo em largura
void breadthFirstSearch(Grafo* ponteiro, int origem, int* res) {

    ///Se as caracteristicas da antena forem invalidas
    if (origem < 0 || origem >= ponteiro->numVertices)
    {
        *res = 0; ///Erro
        return; ///porque tamos a usar void
    }

    int queue[MAX_VERTICES];    ///Guarda os índices dos vértices a visitar
    int front = 0;  ///	Diz onde está o próximo a sair da fila
    int rear = 0;   /// Diz onde é inserido o próximo elemento

    ///Marca todos os vertices como nao visitados
    for (int i = 0; i < ponteiro->numVertices; i++)
    {
        ponteiro->vertices[i].visitado = 0;
    }

    ///Marcar a antena inicial como visitada e guardar na strack
    ponteiro->vertices[origem].visitado = 1;
    queue[rear++] = origem; ///coloca na fila

    ///Enquato houver elementos na queue(fila)
    while (front < rear) {
        int atual = queue[front++]; ///Retira da fila

        Aresta* arestas = ponteiro->listaAdj[atual]; /// Obter vizinhos

        while (arestas !=NULL) {
            
            int destino = arestas->destino;

            /// Se esse vizinho ainda não foi visitado
            if (!ponteiro->vertices[destino].visitado) {
                /// Marcamos como visitado
                ponteiro->vertices[destino].visitado = 1;

                /// Adicionamos à stack para continuar a partir dele
                queue[rear++] = destino;
            }
            /// Avançamos para o próximo vizinho
            arestas = arestas->prox;
            }
        }

    *res = 1; ///Sucesso
}

///Função para encontrar todos os caminhos possíveis
void todosCaminhos(Grafo* ponteiro, int origem, int destino, int caminhos[][MAX_VERTICES], int* totalCaminhos, int* comprimentos) {

    int path[MAX_VERTICES];      /// Caminho atual a ser explorado
    int pathComp = 0;           /// Comprimento atual do caminho
    *totalCaminhos = 0;          /// Inicializa o contador de caminhos

    ///Marca todos os vertices como nao visitados
    for (int i = 0; i < ponteiro->numVertices; i++)
    {
        ponteiro->vertices[i].visitado = 0;
    }

    // Chamada inicial da DFS
    dfs(ponteiro, origem, destino, caminhos, totalCaminhos, comprimentos, path, pathComp);

}

///Função para procurar caminhos
void dfs(Grafo * ponteiro, int atual, int destino, int caminhos[][MAX_VERTICES], int* totalCaminhos, int* comprimentos, int path[], int pathComp)
    {

    ///Marca vertice como visitado
    ponteiro->vertices[atual].visitado = 1;

    ///Adiciona este vertice ao caminho, inicio
    path[pathComp++] = atual;

    ///Se ja chegamos ao destinho
    if (atual == destino)
    {
        ///copiamos o caminho para o array
        for (int i = 0; i < pathComp; i++)
        { 
            caminhos[*totalCaminhos][i] = path[i];
        }

        /// Guardamos o tamanho do caminho
        comprimentos[*totalCaminhos] = pathComp;

        /// Contamos este caminho como mais um encontrado
        (*totalCaminhos)++;
    }
     else
     {
        ///Percorre todas as ligações (arestas) do vertice atual 
        Aresta* arestas = ponteiro->listaAdj[atual];
        while (arestas != NULL) {
            int prox = arestas->destino;

            /// Se o vizinho ainda não foi visitado, continua o caminho
            if (!ponteiro->vertices[prox].visitado) {
                    dfs(ponteiro, prox, destino, caminhos, totalCaminhos, comprimentos, path, pathComp);  /// chamada recursiva para o próximo vértice
            }

            arestas = arestas->prox;  /// passa à próxima aresta
        }
     }
        /// Se nao chegar ao destino
        ponteiro->vertices[atual].visitado = 0;  /// Desmarca como visitado
    }

///Função para listar na consola todas as interseções de pares de antenas
void intersecoesFrequencias(Grafo * ponteiro, char f1, char f2, int linhas[], int colunas[], int* total) {
    *total = 0;  /// Começamos com zero interseções encontradas

    /// Percorremos todas as antenas do grafo
    for (int i = 0; i < ponteiro->numVertices; i++) {
            Vertice v1 = ponteiro->vertices[i];

        /// Se esta antena não tiver a frequência f1, ignoramos
        if (v1.frequencia != f1) continue;

        /// Procuramos antenas com a segunda frequência f2
        for (int j = 0; j < ponteiro->numVertices; j++) {
            /// Evitar comparar a mesma antena consigo própria
            if (i == j) continue;

            Vertice v2 = ponteiro->vertices[j];

            /// Se esta antena não tiver a frequência f2, ignoramos
            if (v2.frequencia != f2) continue;

            /// Se ambas estiverem na mesma posição (linha e coluna), é uma interseção
            if (v1.linha == v2.linha && v1.coluna == v2.coluna) {
                linhas[*total] = v1.linha;     /// Guarda a linha da interseção
                colunas[*total] = v1.coluna;   /// Guarda a coluna da interseção
                (*total)++;                    /// Conta esta interseção
            }
        }
    }
}

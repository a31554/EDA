/*****************************************************************//**
 * \file   Funcoes2.h
 * \brief  Declarações das funções para manipulação de grafos de antenas
 * 
 * \author Afonso Macedo
 * \number 31554
 * \local  Intituto politecnico do cavado e do ave
 * \date   May 2025
 *********************************************************************/

#pragma once

#include "Representacao2.h"

#ifndef FUNCOES2_H
#define FUNCOES2_H

/// Função para carregar os vertices do ficheiro texto
Grafo* carregarGrafo(Grafo* lista, int* res, char localizar[180]);

///Função para criar Arestas entre vertices com a mesma frequencia
Aresta* novaAresta(int destino);

///Função para ligar os vértices, criando arestas
void ligarAresta(Grafo* ponteiro, int origem, int destino);

///Função que procura em profundidade a partir de uma determinada antena
void depthFirstSearch(Grafo* ponteiro, int origem, int* res);

///Função que procura em largura a partir de uma determinada aresta
void breadthFirstSearch(Grafo* ponteiro, int origem, int* res);

///Função para encontrar todos os caminhos possíveis entre duas antenas
void todosCaminhos(Grafo* ponteiro, int origem, int destino, int caminhos[][MAX_VERTICES], int* totalCaminhos, int* comprimentos);

///Função para procurar caminhos, utilizada em void todosCaminhos
void dfs(Grafo* ponteiro, int atual, int destino, int caminhos[][MAX_VERTICES], int* totalCaminhos, int* comprimentos, int path[], int pathComp);

///Função para listar na consola todas as interseções de pares de antenas
void intersecoesFrequencias(Grafo* ponteiro, char f1, char f2, int linhas[], int colunas[], int* total);

#endif
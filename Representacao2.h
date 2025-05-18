/*****************************************************************//**
 * \file   Representação.h
 * \brief  Estruturas de dados para representação de vertices e arestas em grafos
 *
 * \author Afonso Macedo
 * \number 31554
 * \local  Intituto politecnico do cavado e do ave
 * \date   May 2025
 *********************************************************************/

#pragma once

#ifndef REPRESENTACAO2_H
#define REPRESENTACAO2_H

#define MAX_VERTICES 200

/// Define uma estrutura para representar um vértice
typedef struct Vertice {
    char frequencia;
    int linha;
    int coluna;
    int visitado;
} Vertice;

///Define uma estrutura para as arestas que ligam os vértices
typedef struct Aresta {
    int destino; /// indice de outro vértice (antena), dizendo com quem o vértice está conectado
    struct Aresta* prox; ///próximo elemento da lista
}Aresta;

typedef struct Grafo{
    int numVertices; /// Quantos vértices existem
    Vertice vertices[MAX_VERTICES];    /// Lista de vértices (as antenas)
    Aresta* listaAdj[MAX_VERTICES];    /// Para cada vértice, a sua lista de conexões
}Grafo;

#endif
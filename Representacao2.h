/*****************************************************************//**
 * \file   Representa��o.h
 * \brief  Estruturas de dados para representa��o de vertices e arestas em grafos
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

/// Define uma estrutura para representar um v�rtice
typedef struct Vertice {
    char frequencia;
    int linha;
    int coluna;
    int visitado;
} Vertice;

///Define uma estrutura para as arestas que ligam os v�rtices
typedef struct Aresta {
    int destino; /// indice de outro v�rtice (antena), dizendo com quem o v�rtice est� conectado
    struct Aresta* prox; ///pr�ximo elemento da lista
}Aresta;

typedef struct Grafo{
    int numVertices; /// Quantos v�rtices existem
    Vertice vertices[MAX_VERTICES];    /// Lista de v�rtices (as antenas)
    Aresta* listaAdj[MAX_VERTICES];    /// Para cada v�rtice, a sua lista de conex�es
}Grafo;

#endif
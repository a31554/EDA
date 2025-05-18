/*****************************************************************//**
 * \file   Funcoes1.h
 * \brief  Declarações das funções para manipulação de antenas e efeitos nefastos
 * 
 * \author Afonso Macedo
 * \number 31554
 * \local  Intituto politecnico do cavado e do ave
 * \date   March 2025
 *********************************************************************/

#pragma once
#include "Representacao1.h"

#ifndef FUNCOES1_H
#define FUNCOES1_H

 /// Função para carregar antenas do ficheiro estrutura.txt
 Antena* carregarFicheiro(Antena* lista, int* res, char localizar[180]);

 ///Função para procurar
 Antena* procuraElemento(Antena* lista, char frequencia, int linha, int coluna);

 /// Função para inserir uma antena na lista
 Antena* inserirAntena(Antena* lista, char frequencia, int coluna, int linha, int*res);

 ///Função para remover uma antena que esteja na lista
 Antena* removerAntena(Antena* lista, char frequencia, int linha, int coluna, int* res);

 ///Função para listar as antenas
 void listarAntena(Antena* lista);

 /// Função para calcular locais com efeito nefasto
 Antena* calcularEfeitoNefasto(Antena* lista, char frequencia, int linha, int coluna,int* res);

 /*/// Função para listar as antenas interferentes(nefasto)
 void listarNefasto(Antena* nefasto);*/

 ///Função para libertar a memória
 void libertarmemoria(Antena* lista);

#endif
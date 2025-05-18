/*****************************************************************//**
 * \file   Funcoes1.h
 * \brief  Declara��es das fun��es para manipula��o de antenas e efeitos nefastos
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

 /// Fun��o para carregar antenas do ficheiro estrutura.txt
 Antena* carregarFicheiro(Antena* lista, int* res, char localizar[180]);

 ///Fun��o para procurar
 Antena* procuraElemento(Antena* lista, char frequencia, int linha, int coluna);

 /// Fun��o para inserir uma antena na lista
 Antena* inserirAntena(Antena* lista, char frequencia, int coluna, int linha, int*res);

 ///Fun��o para remover uma antena que esteja na lista
 Antena* removerAntena(Antena* lista, char frequencia, int linha, int coluna, int* res);

 ///Fun��o para listar as antenas
 void listarAntena(Antena* lista);

 /// Fun��o para calcular locais com efeito nefasto
 Antena* calcularEfeitoNefasto(Antena* lista, char frequencia, int linha, int coluna,int* res);

 /*/// Fun��o para listar as antenas interferentes(nefasto)
 void listarNefasto(Antena* nefasto);*/

 ///Fun��o para libertar a mem�ria
 void libertarmemoria(Antena* lista);

#endif
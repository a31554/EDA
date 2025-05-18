/*****************************************************************//**
 * \file   Representação1.h
 * \brief  Define estrutura de dados para antenas e suas características.
 * 
 * \author Afonso Macedo
 * \number 31554
 * \local  Intituto politecnico do cavado e do ave
 * \date   March 2025
 *********************************************************************/
#pragma once

#ifndef REPRESENTACAO1_H
#define REPRESENTACAO1_H

typedef struct Antena {
	char frequencia;	///frequencia da onda sonora
	int linha;	///coordenada linha (Y)
	int coluna; ///coordenada coluna (X)
	struct Antena* prox;
}Antena;

#endif
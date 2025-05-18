/*****************************************************************//**
 * \file   Funcoes1.c
 * \brief  Defenir as funções para manipular a lista ligada que representa as antenas
 * 
 * \author Afonso Macedo
 * \number 31554
 * \local  Intituto politecnico do cavado e do ave
 * \date   March 2025
 *********************************************************************/

#pragma once
#include <stdio.h>
#include <stdlib.h> 
#include <malloc.h>
#include "funcoes1.h"


///Função para carregar ficheiro
Antena* carregarFicheiro(Antena* lista, int* res, char localizar[180]) {
	
    FILE* file = fopen(localizar, "r");
    if (!file) {
        *res =0; ///não conseguiu abrir o ficheiro
        return lista;
    }

    char linha[50]; /// A linha máxima tem 50 caracteres
    int y = 0; /// Coordenada Y (linha da matriz)

    while (fgets(linha, sizeof(linha), file) != NULL) ///Lê uma linha do ficheiro e armazena no char linha.
    {   
        for (int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++) { /// Coordenada X (coluna da matriz)
            ///Se estiver entre as seguintes letras:
            if ((linha[x]>= 'A' && linha[x]<='Z') || (linha[x]>='a' && linha[x]<='z'))
            { 
                 lista= inserirAntena(lista, linha[x], x, y, res); ///insere na funcao inserirAntena com a frequencia, linha e coluna respetiva
            }
        }
        y++;
    }
    fclose(file); /// Fechar o ficheiro 
    *res = 1; ///conseguiu abrir o ficheiro
    return lista;
}

///função para procurar
Antena* procuraElemento(Antena* lista, char frequencia, int linha, int coluna) {
    Antena* aux = lista;
    while (aux != NULL) {
        if (aux->linha == linha && aux->coluna == coluna && aux->frequencia == frequencia) 
            return aux;	///valor encontrado
        aux = aux->prox;
    }
    return NULL;/// Se não encontrou o elemento
}

///função para inserir
Antena* inserirAntena(Antena* lista, char frequencia, int coluna, int linha, int* res) {

///criar uma nova antena

Antena* nova = (Antena*)malloc(sizeof(Antena)); ///Alocar memória para a nova antena

if (nova == NULL) return lista; /// Falha na alocação de memória

nova->frequencia = frequencia;
nova->coluna = coluna;
nova->linha = linha;
nova->prox = NULL;  /// IMPORTANTE!

///Se já existe, não insere
if (procuraElemento(lista,frequencia,linha,coluna)) {
    *res = 0; return lista;
}

///procurar a posição
///1ª posição
if (lista == NULL) {
    lista = nova; 
    *res=1;
    return lista;
}
if (lista->linha > nova->linha && lista->coluna > nova->coluna) {
    nova->prox = lista;
    lista = nova;
}
///procura posição
Antena* aux = lista;
Antena* aux2 = aux;
while (aux->linha < nova->linha && aux->coluna < nova->coluna && aux->prox != NULL)
{
    aux2 = aux;
    aux = aux->prox;
}
///se for na última posição
if (aux->linha < nova->linha && aux->coluna < nova->coluna)
    aux->prox = nova;
///se for no meio
else
{
    nova->prox = aux;
    aux2->prox = nova;
}
*res = 1;
return lista;
}

///função para remover
Antena* removerAntena(Antena* lista, char frequencia, int linha, int coluna, int* res) {
    if (lista == NULL) {
        *res = 0;  /// Lista vazia, nada para remover
        return NULL;
    }

    /// Se o elemento a remover estiver no início da lista
    if (lista->linha == linha && lista->coluna == coluna && lista->frequencia == frequencia) {
        Antena* nova = lista;
        lista = lista->prox;
        free(nova);
        *res = 1;  /// Remoção bem-sucedida
        return lista;
    }

    Antena* nova = lista;
    Antena* pass = NULL;

    /// Procurar o elemento na lista
    while (nova != NULL) {
        if (nova->linha == linha && nova->coluna == coluna && nova->frequencia == frequencia) {
            pass->prox = nova->prox;
            free(nova);
            *res = 1; ///remoção bem sucessida
            return lista;
        }
        pass = nova;
        nova = nova->prox;
    }

    *res = 0; ///não conseguir encontrar e nao removeu
    return lista;
}

///função para listar
void listarAntena(Antena* lista) {

    ///Verificar se a lista está vazia
    if (lista == NULL) {
        printf("\nA lista encontra-se vazia.\n");
        return;
    }
    ///Se nao tiver, percorre e coloca os detalhes de cada antena
    Antena* novo = lista; /// o apontador novo aponta para o início da lista
    while (novo != NULL) {
        printf("\nFrequencia: %c | Linha: %d | Coluna: %d\n", novo->frequencia, novo->linha, novo->coluna);
        novo = novo->prox; ///Avança para o proximo ate ser nulo
    }
}

///função para o efeito nefasto
Antena* calcularEfeitoNefasto(Antena* lista, char frequencia, int linha,int coluna, int* res) {
    Antena* novo = lista;
    Antena* nefasto = NULL; /// Lista de antenas que causam interferência

while (novo != NULL) {
    /// Verifica se a antena tem a mesma frequência (só interferem antenas com igual frequência)
    if (novo->frequencia == frequencia) {
        /// Verifica se está na mesma linha, coluna ou diagonal (interferência direta)
        if (
            (novo->linha == linha || novo->coluna == coluna ||
                abs(novo->linha - linha) == abs(novo->coluna - coluna)) &&
            !(novo->linha == linha && novo->coluna == coluna) /// Ignora a própria antena
            ) {
            /// Insere na lista nefasto, marcando como '#' para indicar interferência
            nefasto = inserirAntena(nefasto, '#', novo->coluna, novo->linha, res);
        }
    }
    novo = novo->prox; /// Avança para a próxima antena na lista original
}
return nefasto; /// Devolve a lista de antenas que causam interferência
}

/*/// Função para listar nefasto
void listarNefasto(Antena* nefasto) {
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
}*/
  
///função para libertar memória
void libertarmemoria(Antena* lista) {
    Antena* novo=lista;
    while(novo){
        Antena* pass = novo;
        novo = novo->prox;
        free(pass);
    }
}


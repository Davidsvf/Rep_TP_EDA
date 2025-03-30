/**
 * @file funcoes.h
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief Define as funções e estruturas
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <stdbool.h>

#define TAM_MAX_LINHA 200 // Tamanho maximo da linha do ficheiro

// Tamanho da matriz
#define TAM_X 12 
#define TAM_Y 12


typedef struct Antena{
    char freq; // Como no enunciado os valores de frequencia serão letras, logo é do tipo 'char', este também armazena o '.'
    int x; // Posição da antena na matriz (eixo X) (int)
    int y; // Posição da antena na matriz (eixo Y) (int)
    struct Antena* prox;// Ponteiro para a próxima antena na lista ligada
}Antena;

typedef struct EfeitoNefasto{
    int x; // Localização com efeito nefasto na lista (eixo X) 
    int y; // Localização com efeito nefasto na lista (eixo Y)
    struct EfeitoNefasto *prox; // Ponteiro para o próximo elemento na lista
}EfeitoNefasto;

typedef struct AntenaF{ // Estrutura para guardar os dados das antenas no ficheiro
    char freq;
    int x;
    int y;
}AntenaF;

Antena* CriarAntena(char freq, int x, int y);

Antena* InserirAntena(Antena* inicio, char freq, int x, int y);

Antena* RemoverAntena(Antena* inicio, int x, int y);

EfeitoNefasto* CriarEfeitoNefasto(int x, int y);

EfeitoNefasto* InserirEfeitoNefasto(EfeitoNefasto* inicio, int x, int y);

EfeitoNefasto* CalcularEfeito(Antena* inicio);

Antena* RemoverAntenasComConflito(EfeitoNefasto* Lista_Efeitos, Antena* inicio);

Antena* CarregarFicheiro(char* nomeficheiro);

bool GravarFicheiroBin(char* nomeficheiro, Antena* inicio);

Antena* DestroiLista(Antena* inicio);

Antena* LerFicheiroBin(char* nomeficheiro);

void MostrarAntenas(Antena* inicio);

void MostrarAntenasEEfeitos(Antena* inicio, EfeitoNefasto* Lista_Efeitos);

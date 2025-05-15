/**
 * @file grafos.h
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <stdbool.h>

#define TAM_MAX_LINHA 200

typedef struct Antena{
    char freq;
    int x;
    int y;
    struct Adj* adj;
    struct Antena* prox;
}Antena;

typedef struct Adj{
    Antena* destino;
    struct Adj* prox;
}Adj;

Antena* CriarAntena( char freq, int x, int y, bool* validar);

Antena* InserirAntena(Antena* inicio, Antena* nova, bool* validar);

Antena* RemoverAntena(Antena* inicio, int x, int y, bool* validar);

bool EncontrarAntena(Antena* inicio, int x, int y);

Adj* CriarAresta(Antena* destino, bool* validar);

Adj* InserirAresta(Antena* inicio, Adj* aresta, bool* validar);

Adj* CalcularArestas(Antena* inicio, bool* validar);

Antena* CarregarFicheiro(char* nomeficheiro, bool* validar);

bool GravarFicheiroBin(char* nomeficheiro, Antena* inicio);

Antena* LerFicheiroBin(char* nomeficheiro, bool* validar);


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

#define TAM_MAX_LINHA 200 /// Tamanho maximo da linha do ficheiro

#pragma region Estruturas

/**
 * @brief Esta estrutura é usada numa lista ligada para armazenar informações sobre antenas
 * Como, a frequência, as coordenadas na matriz e um ponteiro para a próxima antena na lista
 */
typedef struct Antena{
    char freq; // Como os valores de frequencia serão letras, logo é do tipo 'char'
    int x; // Posição da antena na matriz (eixo X) (int)
    int y; // Posição da antena na matriz (eixo Y) (int)
    struct Antena* prox;// Ponteiro para a próxima antena na lista ligada
}Antena;

/**
 * @brief Esta estrutura é utilizada numa lista ligada para armazenar as coordenadas de pontos da matriz onde há efeitos nefastos assim como a ligação para o próximo elemento da lista
 * Assim, representa um efeito nefasto na matriz
 */
typedef struct EfeitoNefasto{
    int x; // Localização com efeito nefasto na lista (eixo X) 
    int y; // Localização com efeito nefasto na lista (eixo Y)
    struct EfeitoNefasto *prox; // Ponteiro para o próximo elemento na lista
}EfeitoNefasto;

/**
 * @brief Estrutura usada para armazenar uma antena, com a frequência
 * (representada por uma letra) e as suas coordenadas na matriz num ficheiro
 */
typedef struct AntenaF{ 
    char freq;
    int x;
    int y;
}AntenaF;

#pragma endregion 

#pragma region Funções

/**
 * @brief Função para criar antena e alocar a mesma na memória
 * 
 * @param freq Letra que representa a frequência da antena
 * @param x Coordenada X da antena na matriz
 * @param y Coordenada Y da antena na matriz
 * @param validar Ponteiro para uma variável booleana que será definida como verdadeiro se a criação for bem-sucedida, ou falso caso contrário
 * @return Antena* Ponteiro para a antena criada ou NULL em caso de falha
 */
Antena* CriarAntena(char freq, int x, int y, bool* validar);

/**
 * @brief Insere uma nova antena no início da lista ligada de antenas
 * 
 * @param inicio Ponteiro para o início atual da lista de antenas
 * @param nova Ponteiro para a nova antena a ser inserida
 * @param validar Ponteiro para uma variável booleana que será definida como verdadeiro se a inserção for bem-sucedida, ou falso caso contrário
 * @return Antena* Ponteiro para o novo início da lista
 */
Antena* InserirAntena(Antena* inicio, Antena* nova, bool* validar);

/**
 * @brief Remove uma antena da lista ligada com base nas suas coordenadas
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param x Coordenada X da antena a remover
 * @param y Coordenada Y da antena a remover
 * @param validar Ponteiro para uma variável booleana que indicará se a remoção foi bem-sucedida ou não
 * @return Antena* Ponteiro para o novo início da lista após a remoção
 */
Antena* RemoverAntena(Antena* inicio, int x, int y, bool* validar);

/**
 * @brief Cria um novo efeito nefasto e devolve um ponteiro para ele
 * 
 * @param x Coordenada X do efeito nefasto na matriz
 * @param y Coordenada Y do efeito nefasto na matriz
 * @param validar Ponteiro para uma variável booleana que será definida como verdadeiro se a criação for bem-sucedida, ou falso caso contrário
 * @return EfeitoNefasto* Ponteiro para o efeito nefasto criado ou NULL em caso de falha
 */
EfeitoNefasto* CriarEfeitoNefasto(int x, int y, bool* validar);

/**
 * @brief Insere um novo efeito nefasto na lista ligada
 * 
 * @param inicio Ponteiro para o início atual da lista de efeitos nefastos
 * @param n Ponteiro para o novo efeito nefasto a ser inserido
 * @param validar Ponteiro para uma variável booleana que indicará se a inserção foi bem-sucedida
 * @return EfeitoNefasto* Ponteiro para o novo início da lista
 */
EfeitoNefasto* InserirEfeitoNefasto(EfeitoNefasto* inicio, EfeitoNefasto* n, bool* validar);

/**
 * @brief Calcula os efeitos nefastos gerados pelas antenas e devolve uma lista com esses efeitos
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param validar Ponteiro para uma variável booleana que indicará se o cálculo foi bem-sucedido
 * @return EfeitoNefasto* Ponteiro para o início da lista de efeitos nefastos
 */
EfeitoNefasto* CalcularEfeito(Antena* inicio, bool* validar);

/**
 * @brief Remove as antenas da lista que estão em locais de conflito com efeitos nefastos
 * 
 * @param Lista_Efeitos Ponteiro para o início da lista de efeitos nefastos
 * @param inicio Ponteiro para o início da lista de antenas
 * @param validar Ponteiro para uma variável booleana que indicará se a remoção foi bem-sucedida
 * @return Antena* Ponteiro para o novo início da lista de antenas após a remoção
 */
Antena* RemoverAntenasComConflito(EfeitoNefasto* Lista_Efeitos, Antena* inicio, bool* validar);

/**
 * @brief Carrega as antenas a partir de um ficheiro e as insere numa lista ligada
 * 
 * @param nomeficheiro Nome do ficheiro a ser lido
 * @param validar Ponteiro para uma variável booleana que indicará se o carregamento foi bem-sucedido
 * @return Antena* Ponteiro para o início da lista de antenas carregadas
 */
Antena* CarregarFicheiro(char* nomeficheiro, bool* validar);

/**
 * @brief Grava as antenas numa lista ligada para um ficheiro binário
 * 
 * @param nomeficheiro Nome do ficheiro onde os dados das antenas serão gravados
 * @param inicio Ponteiro para o início da lista de antenas a ser gravada
 * @return true Se a gravação for bem-sucedida
 * @return false Se a gravação não for bem-sucedida
 */
bool GravarFicheiroBin(char* nomeficheiro, Antena* inicio);

/**
 * @brief Liberta a memória de todas as antenas na lista ligada
 * 
 * @param inicio Ponteiro para o início da lista de antenas a ser destruída
 * @param validar Ponteiro para uma variável booleana que indicará se a destruição foi bem-sucedida
 * @return Antena* Ponteiro nulo após a libertação da memória de todas as antenas
 */
Antena* DestroiLista(Antena* inicio, bool* validar);

/**
 * @brief Lê um ficheiro binário e carrega as antenas para uma lista ligada
 * 
 * @param nomeficheiro Nome do ficheiro binário a ser lido
 * @param validar Ponteiro para uma variável booleana que indicará se a leitura foi bem-sucedida
 * @return Antena* Ponteiro para o início da lista de antenas carregadas
 */
Antena* LerFicheiroBin(char* nomeficheiro, bool* validar);

#pragma endregion
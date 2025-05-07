/**
 * @file matriz.h
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief Define as funções para apresentar as matrizes no ecrã
 * @version 0.1
 * @date 2025-05-01
 * 
 * @copyright Copyright (c) 2025
 * 
*/

#include "funcoes.h"

/**
 * @brief Calcula as dimensões da matriz necessária para mostrar as antenas
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param linhas Ponteiro para a variável que irá armazenar o número de linhas da matriz
 * @param colunas Ponteiro para a variável que irá armazenar o número de colunas da matriz
 */
void CalcularDimensaoAntenas(Antena* inicio, int* linhas, int* colunas);

/**
 * @brief Mostra as antenas presentes na lista ligada numa matriz
 * 
 * @param inicio Ponteiro para o início da lista de antenas a ser exibida
 */
void MostrarAntenas(Antena* inicio);

/**
 * @brief Calcula as dimensões da matriz necessária para mostrar as antenas e os efeitos nefastos
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param efeitos Ponteiro para o início da lista de efeitos nefastos
 * @param linhas Ponteiro para a variável que irá armazenar o número de linhas da matriz
 * @param colunas Ponteiro para a variável que irá armazenar o número de colunas da matriz
 */
void CalcularDimensaoAntenasEEfeitos(Antena* inicio, EfeitoNefasto* efeitos, int* linhas, int* colunas);

/**
 * @brief Mostra as antenas e os efeitos nefastos presentes nas listas ligadas
 * 
 * @param antenas Ponteiro para o início da lista de antenas a ser exibida
 * @param efeitos Ponteiro para o início da lista de efeitos nefastos a ser exibida
 */
void MostrarAntenasEEfeitos(Antena* antenas, EfeitoNefasto* efeitos);
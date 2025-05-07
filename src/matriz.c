/**
 * @file matriz.c
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief Implementação das funções para mostrar as matrizes no ecrã
 * @version 0.1
 * @date 2025-05-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "matriz.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Calcula as dimensões máximas (linhas e colunas) de uma matriz baseada nas coordenadas das antenas
 * 
 * Esta função percorre a lista de antenas e encontra as coordenadas máximas (x, y), de modo a determinar a dimensão necessária para representar todas as antenas
 * 
 * @param inicio Ponteiro para o início da lista ligada de antenas
 * @param linhas Ponteiro para armazenar o número máximo de linhas
 * @param colunas Ponteiro para armazenar o número máximo de colunas
 */
void CalcularDimensaoAntenas(Antena* inicio, int* linhas, int* colunas) {
    *linhas = 0;
    *colunas = 0;

    Antena* aux = inicio;
    
    // Percorre todas as antenas para calcular as dimensões máximas
    while (aux != NULL) {
        if (aux->x > *colunas) {
            *colunas = aux->x;  // Calcula o máximo de colunas
        }
        if (aux->y > *linhas) {
            *linhas = aux->y;  // Calcula o máximo de linhas
        }
        aux = aux->prox;
    }

    (*linhas)++;
    (*colunas)++;
}

/**
 * @brief Mostra as antenas na matriz e imprime no terminal
 * 
 * Esta função calcula as dimensões da cidade (matriz) com base nas antenas, aloca dinamicamente uma matriz para armazenar a cidade, e exibe-a no terminal.
 * 
 * @param inicio Ponteiro para o início da lista ligada de antenas
 */
void MostrarAntenas(Antena* inicio) {
    int linhas, colunas;
    
    // Calcula as dimensões da matriz
    CalcularDimensaoAntenas(inicio, &linhas, &colunas);

    // Aloca a matriz dinamicamente
    char** matriz = (char**)malloc(linhas * sizeof(char*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (char*)malloc(colunas * sizeof(char));
    }

    // Preenche a matriz com '.' inicialmente
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = '.';
        }
    }

    // Preenche a matriz com as antenas
    Antena* aux = inicio;
    while (aux != NULL) {
        if (aux->x >= 0 && aux->x < colunas && aux->y >= 0 && aux->y < linhas) {
            matriz[aux->y][aux->x] = aux->freq; 
        }
        aux = aux->prox;
    }

    // Mostra a matriz no terminal
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }

    // Liberta a memória alocada
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

/**
 * @brief Calcula as dimensões (linhas e colunas) da matriz, considerando tanto as antenas como os efeitos nefastos
 * 
 * Esta função percorre a lista de antenas e efeitos nefastos para determinar as dimensões mínimas necessárias para a matriz que pode conter todas as antenas e efeitos, levando em consideração as suas coordenadas
 * As dimensões calculadas correspondem ao número total de linhas e colunas da matriz, ajustadas para cobrir todas as posições das antenas e efeitos.
 * 
 * @param inicio Ponteiro para a lista ligada das antenas
 * @param efeitos Ponteiro para a lista ligada dos efeitos nefastos
 * @param linhas Ponteiro para o número de linhas da matriz (será atualizado pela função)
 * @param colunas Ponteiro para o número de colunas da matriz (será atualizado pela função)
 */
void CalcularDimensaoAntenasEEfeitos(Antena* inicio, EfeitoNefasto* efeitos, int* linhas, int* colunas){
    *linhas = 0;
    *colunas = 0;

    // Considera posições das antenas
    for(Antena* a = inicio; a != NULL; a = a->prox){
        if(a->x >= *colunas) *colunas = a->x + 1;
        if(a->y >= *linhas)  *linhas  = a->y + 1;
    }

    // Considera posições dos efeitos
    for(EfeitoNefasto* e = efeitos; e != NULL; e = e->prox){
        if(e->x >= *colunas) *colunas = e->x + 1;
        if(e->y >= *linhas)  *linhas  = e->y + 1;
    }
}

/**
 * @brief Exibe as antenas e os efeitos nefastos numa matriz, representando as suas localizações.
 * 
 * Esta função calcula as dimensões da matriz necessária para acomodar tanto as antenas quanto os efeitos nefastos.
 * A matriz resultante é preenchida com as posições das antenas (representadas pelo seu identificador de frequência) e os efeitos nefastos (representados pelo símbolo '#').
 * As antenas são colocadas primeiro, seguidas pelos efeitos.
 * 
 * As posições das antenas são inseridas nas coordenadas correspondentes na matriz, enquanto os efeitos são representados nas mesmas posições onde ocorrem, sobrepondo as antenas caso necessário.
 * 
 * @param antenas Ponteiro para a lista ligada de antenas a ser exibida.
 * @param efeitos Ponteiro para a lista ligada de efeitos nefastos a ser exibidos.
 */
void MostrarAntenasEEfeitos(Antena* antenas, EfeitoNefasto* efeitos) {
    int linhas, colunas;
    CalcularDimensaoAntenasEEfeitos(antenas, efeitos, &linhas, &colunas);

    // Alocação dinâmica da matriz
    char** matriz = (char**)malloc(linhas * sizeof(char*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (char*)malloc(colunas * sizeof(char));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = '.'; // Inicializa com '.'
        }
    }

    // Preenche antenas
    for (Antena* a = antenas; a != NULL; a = a->prox) {
        if (a->x >= 0 && a->x < colunas && a->y >= 0 && a->y < linhas)
            matriz[a->y][a->x] = a->freq;
    }

    // Preenche efeitos
    for (EfeitoNefasto* e = efeitos; e != NULL; e = e->prox) {
        if (e->x >= 0 && e->x < colunas && e->y >= 0 && e->y < linhas)
            matriz[e->y][e->x] = '#';  // Usa '#' para representar efeitos
    }

    // Imprime matriz
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }

    // Liberta memória
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}


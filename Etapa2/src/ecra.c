/**
 * @file ecra.c
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief Implementação das funções para mostrar no ecrã
 * @version 0.1
 * @date 2025-05-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecra.h"
#include <stdio.h>

/**
 * @brief Mostra as antenas e as respetivas adjacencias na consola
 *
 * Esta função percorre a lista ligada de antenas e apresenta as coordenadas e frequência
 * Para cada antena, também, lista as antenas adjacentes (arestas) associadas
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 */
void MostraGrafo(Antena* inicio) {
    if (inicio == NULL) {
        printf("Grafo vazio!\n");
        return;
    }

    // Ponteiro para percorrer a lista de antenas no grafo
    Antena* aux = inicio;
    while (aux) {
        printf("Antena (%d, %d) - Frequência: %c\n", aux->x, aux->y, aux->freq);

        // Imprime as adjacências da antena
        Adj* adj = aux->adj;
        printf("Adjacências: ");
        while (adj) {
            printf("(%d, %d) ", adj->destino->x, adj->destino->y);
            adj = adj->prox;
        }
        printf("\n\n");

        aux = aux->prox;
    }
}

/**
 * @brief Lista todos os caminhos armazenados
 * 
 * Esta função percorre a lista ligada de caminhos e apresenta para cada caminho as coordenadas das antenas que o compõem, na ordem em que são percorridas
 * 
 * @param caminhos Ponteiro para o início da lista de caminhos a listar
 */
void ListarCaminhos(Caminho* caminhos){
    Caminho* atual= caminhos;
    while (atual) {
        for (int i = 0; i < atual->nAntenas; i++){
            printf("(%d, %d)", atual->antenas[i]->x, atual->antenas[i]->y);
            if (i<atual->nAntenas - 1) printf(" -> ");
        }
        printf("\n");
        atual = atual->prox;
    }
}

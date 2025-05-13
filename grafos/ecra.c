/**
 * @file ecra.c
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecra.h"
#include <stdio.h>

// Função para imprimir o grafo e as suas adjacências
void MostraGrafoLargura(Antena* inicio) {
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
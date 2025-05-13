/**
 * @file main.c
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"
#include "ecra.h"


int main() {
    bool sucesso;
    bool validar = false;

    // Carregar o grafo a partir do ficheiro
    Antena* ficheiro= CarregarFicheiro("cidade.txt", &sucesso);
    if (!sucesso || ficheiro == NULL) {
        printf("Erro ao carregar o ficheiro ou ficheiro vazio!\n");
        return -1;
    }

    Antena* inicio=ficheiro;

    // Calcular as adjacências entre as antenas
    CalcularArestas(inicio, &validar);
    if (!validar) {
        printf("Erro ao calcular as adjacências!\n");
        return -1;
    }

    // Imprimir o grafo e suas adjacências em largura
    printf("Grafo e suas adjacências em largura:\n\n");
    MostraGrafoLargura(inicio);

    // Libertar a memoria das antenas 
    Antena* aux = inicio;
    while (aux) {
        Antena* temp = aux;
        aux = aux->prox;
        free(temp);  // Liberta cada antena
    }

    return 0;
}

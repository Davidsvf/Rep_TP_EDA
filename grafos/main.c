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
    Antena* inicio= CarregarFicheiro("cidade.txt", &sucesso);
    if (!sucesso || inicio == NULL) {
        printf("Erro ao carregar o ficheiro ou ficheiro vazio!\n");
    }
    
    // Calcular as adjacências entre as antenas
    CalcularArestas(inicio, &validar);
    if (!validar) {
        printf("Erro ao calcular as adjacências!\n");
    }

    // Imprimir o grafo e suas adjacências em largura
    printf("Grafo e suas adjacências em largura:\n\n");
    MostraGrafoLargura(inicio);

    // Gravar as listas ligadas das antenas e adjacências no ficheiro binário
    if (GravarFicheiroBin("Grafo.bin", inicio)) {
        printf("Gravado com sucesso!\n");
    } else {
        printf("Erro ao gravar no ficheiro binário.\n");
    }

    // Ler o ficheiro binário e inserir os dados nas respetivas listas ligadas
    Antena* lerLista = LerFicheiroBin("Grafos.bin", &sucesso);
    if (sucesso) {
        printf("Leitura do ficheiro binário realizada com sucesso!\n");
    }else{
        printf("Erro ao ler ficheiro binário.\n");
    }

    return 0;
}

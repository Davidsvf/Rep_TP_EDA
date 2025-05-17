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
    Antena* grafo= CarregarFicheiro("cidade.txt", &sucesso);
    if (!sucesso || grafo == NULL) {
        printf("Erro ao carregar o ficheiro ou ficheiro vazio!\n\n");
    }
    
    // Calcular as adjacências entre as antenas
    CalcularArestas(grafo, &validar);
    if (!validar) {
        printf("Erro ao calcular as adjacências!\n\n");
    }

    // Imprimir o grafo e suas adjacências em largura
    printf("Antenas e as suas adjacências:\n\n");
    MostraGrafo(grafo);

    // Gravar as listas ligadas das antenas e adjacências no ficheiro binário
    if (GravarFicheiroBin("Grafo.bin", grafo)) {
        printf("Dados gravados com sucesso no ficheiro binário!\n\n");
    } else {
        printf("Erro ao gravar no ficheiro binário!\n\n");
    }

    // Ler o ficheiro binário e inserir os dados nas respetivas listas ligadas
    Antena* lerLista = LerFicheiroBin("Grafo.bin", &sucesso);
    if (sucesso) {
        printf("Leitura do ficheiro binário realizada com sucesso!\n\n");
    }else{
        printf("Erro ao ler ficheiro binário!\n\n");
    }

    // Limpar os visitados antes de fazer a procura
    LimparVisitados(grafo, &sucesso);
    if(sucesso){
        printf("Visitados dos vertices limpos com sucesso antes da procura em profundidade!\n\n"); 
    }else{
        printf("Erro ao limpar visitados dos vertices antes da procura em profundidade!\n\n");
    }

    Antena* visitados[MAX_ANTENAS];
    int nVisitados = 0;

    // Procurar em profundiade
    ProcuraProfundidade(grafo, visitados, &nVisitados, &sucesso);
    if(sucesso){
        printf("Antenas visitadas na procura em profundidade:\n");
        for (int i=0; i<nVisitados; i++){
        printf("Antena em (%d, %d) Frequência: %c\n", visitados[i]->x, visitados[i]->y, visitados[i]->freq);
        }
        printf("\n");
    }else{
        printf("Erro ao procurar em profundidade!\n\n");
    }

    // Mostrar caminhos possiveis 
    Antena* caminho[MAX_ANTENAS];
    Caminho* caminhos = NULL;

    int xOrigem, yOrigem, xDestino, yDestino;

    printf("Escreva as coordenadas da antena de origem (x,y): ");
    scanf("%d %d", &xOrigem, &yOrigem);

    printf("Escreva as coordenadas da antena de destino (x,y): ");
    scanf("%d %d", &xDestino, &yDestino);

    Antena* origem= EncontrarAntena(grafo, xOrigem, yOrigem);
    Antena* destino= EncontrarAntena(grafo, xDestino, yDestino);

    if (!origem || !destino) {
        printf("Origem ou destino não encontrados!\n");
    }

    caminhos= CalcularCaminhosEntreAntenas(origem, destino, caminho, 0, caminhos, &sucesso);
    if(sucesso){
        ListarCaminhos(caminhos);
    }else{
        printf("Erro ao calcular caminhos!\n");
    }
    

    return 0;
}

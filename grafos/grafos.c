/**
 * @file grafos.c
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "grafos.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

Antena* CriarAntena(char freq, int x, int y, bool* validar){
    Antena* aux;
    aux= (Antena*)malloc(sizeof(Antena));
    if(aux){
        aux->freq=freq;
        aux->x=x;
        aux->y=y;
        aux->adj=NULL;
        aux->prox=NULL;
        *validar=true;
    }else{
    *validar=false;
    }
    return(aux);
}   

Antena* InserirAntena(Antena* inicio, Antena* nova, bool* validar){

    // Se a criação da antena falhar, retorna a lista sem modificações
    if (nova==NULL){
        *validar=false;
        return(inicio);
    }

    // Se a lista estiver vazia a nova antena será a primeira
    if(inicio==NULL){
        nova->prox=inicio; 
        *validar=true;
        return(nova); 
    }

    Antena* aux1=inicio; // Ponteiro auxiliar que aponta para a antena 
    Antena* aux2=NULL; // Ponteiro auxiliar que aponta para a antena anterior

    // Percorre a lista para encontrar a posição correta para a nova antena
    // Continua a avançar na lista enquanto a coordenada y da antena atual for menor que y  
    // Se os valores de y forem iguais continua a avançar enquanto o x da antena for menor 
    while(aux1 != NULL && (aux1->y < nova->y || (aux1->y == nova->y && aux1->x < nova->x))){
        aux2=aux1; // Guarda a antena atual como a anterior
        aux1=aux1->prox; // Avança para a próxima antena na lista
    }

    // Se o valor de y da nova antena for menor do que o y da primeira antena da lista, a nova antena deve ser inserida antes 
    // Se a linha (y) for a mesma, a antena é ordenada pelo valor da coluna x, ou seja, se x da nova antena for menor do que o x da primeira antena da lista esta será inserida antes
    if(nova->y < inicio->y || (nova->y == inicio->y && nova->x < inicio->x)){
        nova->prox=inicio; 
        inicio=nova;
        *validar=true;
        return(inicio); 
    }

    // Verifica se já existe uma antena nas coordenadas (x, y)
    if(aux1 != NULL && aux1->x == nova->x && aux1->y == nova->y){
        free(nova); 
        *validar=false;
        return(inicio); 
    } 
    // Inserção no início da lista
    if (aux2 == NULL) {
        nova->prox = inicio;
        *validar=true;
        return nova;
    }
    // Inserção entre aux2 e aux1
    nova->prox = aux1;
    aux2->prox = nova;
    *validar=true;

    // Retorna o ponteiro atualizado para o início da lista
    return(inicio);  
}

Antena* RemoverAntena(Antena* inicio, int x, int y, bool* validar){
    // Verifica se a lista está vazia
    if(inicio == NULL){
        *validar=false;
        return NULL;
    }

    // Ponteiros auxiliares para percorrer a lista
    Antena* aux1=inicio; 
    Antena* aux2=NULL;   

    // Percorre a lista ligada até encontrar a antena a ser removida 
    while(aux1 != NULL){
        // Verifica se encontrou a antena na posição (x, y)
        if(aux1->x == x && aux1->y == y){
            // Caso a antena a remover esteja no inicio da lista
            if(aux2 == NULL){ 
                inicio=aux1->prox; 
            }else{
                aux2->prox=aux1->prox; // Salta a antena a remover e liga a anterior á próxima 
            }

            free(aux1); 
            *validar=true;
            return(inicio); 
        }

        // Avança na lista
        aux2=aux1; 
        aux1=aux1->prox; 
    }

    // Se não encontrou a antena após percorrer a lista toda
    *validar=false;
    return(inicio); // Retorna a lista original sem modificações
}

Adj* CriarAresta(Antena* destino, bool* validar){
    Adj*aux;
    aux=(Adj*)malloc(sizeof(Adj));
    if(aux){
        aux->destino=destino;
        aux->prox=NULL;
        *validar=true;
    }else{
        *validar=false;
    }
    return(aux);
}

Adj* InserirAresta(Antena* inicio, Adj* aresta, bool* validar){
    
    // Se a criação da aresta falhar, ou a lista ligada das antenas estiver vazia, retorna a lista sem modificações
    if (aresta==NULL || inicio==NULL){
        *validar=false;
    }

    // Se a lista estiver vazia a nova aresta será a primeira
    if(inicio->adj==NULL){
        inicio->adj=aresta; 
        *validar=true;
        return(aresta); 
    }else{
        // Caso contrário, adiciona a nova aresta no fim da lista de adjacencias
        Adj* aux = inicio->adj;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = aresta;
    }
    *validar = true;
}   

Adj* CalcularArestas(Antena* inicio, bool* validar){

    *validar=false; // Inicializa com false e só muda se alguma adjacencia for criada
    
    // Ponteiros auxiliares para percorrer a lista ligada das antenas e comparar a frequencia das antenas umas com as outras
    Antena* aux=inicio; 
    Antena* aux2;

    while(aux){
       aux2=aux->prox;
       while(aux2){
            if(aux->freq==aux2->freq){
                bool sucesso;

                // Criar aresta de aux para aux2
                Adj* nova=CriarAresta(aux2, &sucesso);
                if(sucesso){
                    InserirAresta(aux, nova, &sucesso);
                    *validar=true;
                }

                // Criar adjacencia de aux2 para aux
                Adj* nova2=CriarAresta(aux, &sucesso);
                if(sucesso){
                    InserirAresta(aux2, nova2, &sucesso);
                    *validar=true;
                }
            }
            aux2=aux2->prox;
        } 
    aux=aux->prox;
    }
}

Antena* CarregarFicheiro(char* nomeficheiro, bool* validar){
    bool sucesso;
    *validar = false;

    // Abrir o ficheiro em modo leitura
    FILE* ficheiro = fopen(nomeficheiro, "r");
    if (!ficheiro) {
        return NULL; 
    }

    Antena* inicio= NULL;
    char linha[TAM_MAX_LINHA];
    int y = 0;

    // Lê o ficheiro linha a linha
    while (fgets(linha, sizeof(linha), ficheiro)) {
        for (int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++) {
            if (linha[x] != '.') {
                Antena* nova = CriarAntena(linha[x], x, y, &sucesso);
                if (sucesso) {
                    inicio = InserirAntena(inicio, nova, &sucesso);
                    if (sucesso) *validar = true;
                }
            }
        }
        y++;
    }

    fclose(ficheiro);
    return inicio; 
}

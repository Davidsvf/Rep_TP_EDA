/**
 * @file grafos.c
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief Implementação de todas as funções
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

#pragma region Vertices

/**
 * @brief Cria uma nova antena com os parâmetros especificados
 *
 * Esta função aloca dinamicamente memória para uma nova estrutura `Antena`,
 * inicializa os seus campos com os valores fornecidos e define o campo `visitado`
 * como `false`. Caso a alocação de memória falhe, o parâmetro `validar` é
 * atualizado para `false`; caso contrário, é atualizado para `true`.
 * 
 * @param freq Frequência de ressonância da antena  
 * @param x Coordenada X da posição da antena
 * @param y Coordenada Y da posição da antena   
 * @param validar Ponteiro para uma variável booleana que indica se a operação foi bem-sucedida
 * @return Antena* Ponteiro para a nova antena criada, ou `NULL` se ocorrer um erro durante a alocação
 */
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

/**
 * @brief Insere uma nova antena numa lista ligada ordenada por coordenadas (y, x)
 *
 * Esta função insere a antena `nova` na lista ligada de antenas `inicio`,
 * mantendo a ordem crescente primeiro pela coordenada `y` e, em caso de empate,
 * pela coordenada `x`. Caso já exista uma antena com as mesmas coordenadas,
 * a inserção não é realizada e `validar` é definido como falso
 * 
 * @param inicio 
 * @param nova 
 * @param validar 
 * @return Antena* 
 */
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

/**
 * @brief Remove uma antena da lista ligada com coordenadas específicas (x, y)
 *
 * Esta função procura e remove a antena na lista ligada `inicio` que tenha as coordenadas (x, y)
 * Se a antena for encontrada, é removida da lista, a memória é libertada, e o ponteiro para o início da lista é atualizado
 * Caso contrário, a lista permanece inalterada e `validar` é definido como falso.
 * 
 * @param inicio Ponteiro para o início da lista de antenas 
 * @param x Coordenada x da antena a remover
 * @param y Coordenada y da antena a remover
 * @param validar Ponteiro para variável booleana onde será armazenado o resultado da operação
 * @return Antena* Ponteiro para o início atualizado da lista de antenas
 */
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

/**
 * @brief Procura uma antena na lista ligada com coordenadas específicas (x, y)
 *
 * Esta função percorre a lista ligada de antenas `inicio` e retorna o ponteiro para a primeira antena que tenha as coordenadas (x, y)
 * Se não encontrar nenhuma antena com essas coordenadas, a função retorna `NULL`
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param x Coordenada x da antena a procurar
 * @param y Coordenada y da antena a procurar
 * @return Antena* Ponteiro para a antena encontrada, ou `NULL` se não for encontrada
 */
Antena* EncontrarAntena(Antena* inicio, int x, int y){
    while (inicio != NULL) {
        if (inicio->x == x && inicio->y == y) {
            return inicio;
        }
        inicio = inicio->prox;
    }
}


#pragma endregion

#pragma region Adjacencias

/**
 * @brief Cria uma nova aresta que liga uma antena de origem a uma antena de destino
 * 
 * Esta função aloca dinamicamente memória para uma nova estrutura `Adj`, inicializa o
 * campo `destino` com o ponteiro para a antena de destino fornecida e define o campo
 * `prox` como `NULL`. Caso a alocação de memória falhe, o parâmetro `validar` é
 * atualizado para `false`; caso contrário, é atualizado para `true`
 * 
 * @param destino Ponteiro para a antena de destino da aresta   
 * @param validar Ponteiro para uma variável booleana que indica se a operação foi bem-sucedida
 * @return Adj* Ponteiro para a nova aresta criada, ou `NULL` se ocorrer um erro durante a alocação
 */
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

/**
 * @brief Insere uma nova aresta na lista de adjacências de uma antena
 *
 * Esta função adiciona a aresta `aresta` à lista de adjacências da antena `inicio`
 * Se a lista de adjacências estiver vazia, a aresta torna-se o primeiro elemento
 * Caso contrário, a aresta é inserida no final da lista
 * Se ocorrer uma falha na alocação de memória ou se a lista de antenas estiver vazia,
 * a operação é considerada inválida e o parâmetro `validar` é definido como `false`
 * 
 * @param inicio Ponteiro para a antena cuja lista de adjacências será atualizada
 * @param validar Ponteiro para a nova aresta a ser inserida
 * @return Adj* Ponteiro para variável booleana onde será armazenado o resultado da operação
 */
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

#pragma endregion

#pragma region Ficheiros

/**
 * @brief Carrega um ficheiro de texto e cria uma lista encadeada de antenas
 *
 * Esta função lê um ficheiro de texto especificado por `nomeficheiro`, linha por linha,
 * e cria uma lista encadeada de antenas representadas por caracteres não pontuais ('.')
 * Cada linha do ficheiro representa uma linha de antenas, com cada carácter representando
 * uma antena numa posição específica. As antenas são inseridas na lista de acordo com
 * a sua posição (x, y) na matriz representada pelo ficheiro
 * 
 * @param nomeficheiro Nome do ficheiro de texto a ser lido
 * @param validar Ponteiro para variável booleana onde será armazenado o resultado da operação
 * @return Antena* Ponteiro para o início da lista encadeada de antenas, ou `NULL` se ocorrer um erro
 */
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

/**
 * @brief Grava a lista de antenas num ficheiro binário
 *
 * Esta função grava os dados da lista ligada de antenas e respetivas adjacências
 * num ficheiro binário especificado por `nomeficheiro`
 * 
 * O formato do ficheiro é:
 * - Número total de antenas (int)
 * - Para cada antena:
 *   - Frequência (char)
 *   - Coordenada x (int)
 *   - Coordenada y (int)
 *   - Número de adjacências (int)
 *   - Para cada adjacência:
 *     - Coordenada x do destino (int)
 *     - Coordenada y do destino (int)
 * 
 * @param nomeficheiro Nome do ficheiro onde os dados serão gravados
 * @param inicio Ponteiro para o início da lista de antenas
 * @return true se a gravação foi bem sucedida
 * @return false caso contrário
 */
bool GravarFicheiroBin(char* nomeficheiro, Antena* inicio){
    // Abre o ficheiro para escrita binária
    FILE* ficheiro= fopen(nomeficheiro, "wb");
    if(!ficheiro){
        return false;
    }

    // Percorre a lista das antenas para contar quantas são (vertices)
    int totVertices=0;
    Antena* aux=inicio;
    while (aux){
        totVertices++;
        aux=aux->prox;
    }

    // Escreve o numero de vertices
    fwrite(&totVertices, sizeof(int), 1, ficheiro);

    // Percorre a lista ligada de antenas e escreve os dados no ficheiro
    while(aux){
        fwrite(&aux->freq, sizeof(char), 1, ficheiro);
        fwrite(&aux->x, sizeof(int), 1, ficheiro);
        fwrite(&aux->y, sizeof(int), 1, ficheiro);

        // Percorre a lista das adjacencias e conta quantas essa mesma antena contém
        int totAdj=0;
        Adj* adj=aux->adj;
        while(adj){
            totAdj++;
            adj=adj->prox;
        }

        // Escreve o número de adjacencias dessa mesma antena
        fwrite(&totAdj, sizeof(int), 1, ficheiro);

        // Percorre a lista de adjacencias dessa mesma antena
        while(adj){
            // Escreve as adjacencias no ficheiro binário
            fwrite(&adj->destino->x, sizeof(int), 1, ficheiro);
            fwrite(&adj->destino->y, sizeof(int), 1, ficheiro);
        
            adj= adj->prox; 
        }

        aux=aux->prox; 
    }
  
    fclose(ficheiro);
    return true;
}

/**
 * @brief Lê uma lista de antenas e as respetivas adjacências de um ficheiro binário
 *
 * Esta função carrega a informação de antenas e as suas adjacências a partir de um
 * ficheiro binário especificado por `nomeficheiro` e recria a lista ligada de antenas
 * 
 * @param nomeficheiro Nome do ficheiro binário a ler
 * @param validar Apontador para booleano que será setado a true se a leitura for bem sucedida
 * @return Antena* Ponteiro para o início da lista ligada de antenas, ou NULL em caso de erro
 */
Antena* LerFicheiroBin(char* nomeficheiro, bool* validar){
    bool sucesso;
    *validar=false;

    // Abre o ficheiro para leitura binária
    FILE* ficheiro= fopen(nomeficheiro, "rb");
    if(!ficheiro){
        return NULL;
    }
 
    Antena* inicio=NULL;
    int totVertices=0;
    int totAdj=0;

    char freq;
    int x, y, adjX, adjY;

    // Lê o número de vértices previamente anotados
    fread(&totVertices, sizeof(int), 1, ficheiro);

    // Percorre todos os vértices (antenas)
    for(int i=0; i<totVertices; i++){
        // Lê todos os dados de cada antena 
        fread(&freq, sizeof(char), 1, ficheiro);
        fread(&x, sizeof(int), 1, ficheiro);
        fread(&y, sizeof(int), 1, ficheiro);
       

        // Insere os vértices (antenas) na respetiva lista ligada 
        Antena* nova= CriarAntena(freq, x, y, &sucesso);
        if(sucesso){
        inicio=InserirAntena(inicio, nova, &sucesso);
        if(sucesso) *validar=true;
        }

        // Lê o número de adjacencia de cada vertice (antena) previamente anotados
        fread(&totAdj, sizeof(int), 1, ficheiro);
        
        // Verifica se antena existe
        Antena* origem = EncontrarAntena(inicio, x, y);
        if(origem){
            // Percorre todas as adjacências da antena
            for(int j=0; j<totAdj; j++){
                // Lê todos os dados da adjacência
                fread(&adjX, sizeof(int), 1, ficheiro);
                fread(&adjY, sizeof(int), 1, ficheiro);

                // Insere as arestas na respetiva lista ligada para cada antena
                Antena* destino= EncontrarAntena(inicio, adjX, adjY);
                if(destino){
                    Adj* novaAdj= CriarAresta(destino, &sucesso);
                    if(sucesso){
                        Adj* adjs= InserirAresta(origem, novaAdj, &sucesso);
                        if(sucesso) *validar=true;
                    }
                }
            }
        }
    }
    fclose(ficheiro);
    return (inicio);
}

#pragma endregion

#pragma region Grafos

/**
 * @brief Limpa o estado de visita de todas as antenas na lista
 *
 * Esta função percorre a lista ligada de antenas, começando pelo ponteiro `inicio`,
 * e define o campo `visitado` de cada antena como `false`. É útil para reiniciar
 * o estado de visita antes de realizar uma nova busca ou algoritmo que dependa
 * desse campo, como a busca em profundidade e em largura etc...
 * 
 * @param inicio Ponteiro para o início da lista ligada de antenas
 * @param validar Ponteiro para variável booleana onde será armazenado o resultado da operação
 */
void LimparVisitados(Antena* inicio, bool* validar){
    *validar=false;
    while(inicio){
        inicio->visitado=false;
        inicio= inicio->prox;
    }
    *validar=true;
}

/**
 * @brief Realiza uma busca em profundidade a partir de uma antena
 * 
 * Esta função percorre recursivamente as antenas adjacentes à antena fornecida,
 * marcando-as como visitadas e armazenando-as no vetor `visitados`. A busca
 * é limitada às antenas que ainda não foram visitadas e que partilham a mesma
 * frequência da antena de origem.
 * 
 * @param antena Ponteiro para a antena de origem da busca
 * @param visitados Vetor onde serão armazenadas as antenas visitadas durante a busca
 * @param nVisitados Ponteiro para o número de antenas visitadas até o momento
 * @param validar Ponteiro para variável booleana que será setada a `true` se a operação for bem-sucedida
 */
void ProcuraProfundidade(Antena* antena, Antena* visitados[], int* nVisitados, bool* validar){

    if(!antena || antena->visitado) return;

    antena->visitado=true;
    visitados[(*nVisitados)++]=antena;

    Adj* adj=antena->adj;
    while(adj){
        if(!adj->destino->visitado && adj->destino->freq==antena->freq){
            ProcuraProfundidade(adj->destino, visitados, nVisitados, validar); 
        }
        adj= adj->prox;
    }
    *validar=true;
}

/**
 * @brief Armazena um caminho percorrido por um vetor de antenas numa lista ligada de caminhos
 *
 * Esta função cria um novo nó na lista ligada de caminhos, copiando o vetor de antenas
 * até a posição especificada, e insere-o no início da lista
 * 
 * @param caminho Vetor de ponteiros para antenas que representam o caminho percorrido
 * @param posicao Índice da última antena válida no vetor `caminho`
 * @param caminhos Ponteiro para o início da lista ligada de caminhos
 * @return Caminho* Ponteiro para o novo início da lista ligada de caminhos
 */
Caminho* GuardarCaminho(Antena* caminho[], int posicao, Caminho* caminhos){
    Caminho* novo=(Caminho*)malloc(sizeof(Caminho));
    if(novo==NULL){
        return caminhos;
    }
    
    for(int i=0; i<=posicao; i++){
        novo->antenas[i]=caminho[i];
    }

    novo->nAntenas= posicao + 1;
    novo->prox= caminhos;

    return novo;
}

/**
 * @brief Calcula todos os caminhos entre duas antenas com a mesma frequência
 *
 * Esta função calcula todos caminhos possiveis da antena de origem até à antena de destino,
 * armazenando todos os caminhos encontrados num vetor de antenas. Apenas são consideradas antenas com a mesma
 * frequência da antena de origem e que ainda não tenham sido visitadas
 * 
 * @param origem Ponteiro para a antena de origem da busca
 * @param destino Ponteiro para a antena de destino da busca
 * @param caminho Vetor de ponteiros para antenas que representa o caminho percorrido até ao momento
 * @param posicao Índice da próxima posição disponível no vetor `caminho`
 * @param caminhos Ponteiro para a lista ligada de caminhos onde serão armazenados os caminhos encontrados
 * @param validar Ponteiro para variável booleana que será setada a `true` se a operação for bem-sucedida
 * @return Caminho* Ponteiro para a lista ligada de caminhos atualizada com os novos caminhos encontrados
 */
Caminho* CalcularCaminhosEntreAntenas(Antena* origem, Antena* destino, Antena* caminho[], int posicao, Caminho* caminhos, bool* validar){
    if(!origem || origem->visitado) return caminhos;

    origem->visitado=true;
    caminho[posicao]= origem;

    if(origem==destino){
        caminhos= GuardarCaminho(caminho, posicao, caminhos);
        origem->visitado=false; // Marcar como nao visitada para poder ser usada noutros caminhos
        *validar=true;
        return caminhos;
    }

    Adj* adj= origem->adj;
    while(adj){
        if(!adj->destino->visitado && adj->destino->freq == origem->freq){
            caminhos= CalcularCaminhosEntreAntenas(adj->destino, destino, caminho, posicao + 1, caminhos, validar);
        }
        adj=adj->prox;
    }
    origem->visitado=false; // Marcar como nao visitada para poder ser usada noutros caminhos
    return caminhos;
}



#pragma endregion
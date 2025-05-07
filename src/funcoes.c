/**
 * @file funcoes.c
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief Implementação de todas as funções
 * @version 0.1
 * @date 2025-03-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include "funcoes.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#pragma region Antenas

/**
 * @brief Cria uma nova antena e aloca na memória
 *
 * Esta função aloca dinamicamente memória para uma nova antena, inicializa os seus campos com os valores fornecidos e retorna um ponteiro para a antena criada. 
 * Caso a alocação de memória falhe, o ponteiro `validar` é definido como falso
 *
 * @param freq Letra que representa a frequência da antena
 * @param x Coordenada X da antena na matriz
 * @param y Coordenada Y da antena na matriz
 * @param validar Ponteiro para uma variável booleana que será definido como verdadeiro se a criação for bem-sucedida, ou falso caso contrário
 * @return Ponteiro para a antena criada ou NULL em caso de falha na alocação
  */
Antena* CriarAntena(char freq, int x, int y, bool* validar){
    Antena* aux; // Ponteiro auxiliar para armazenar o novo elemento
    // Aloca memória dinamicamente para um novo elemento do tipo 'Antena'
    aux=(Antena*)malloc(sizeof(Antena));
    // Verifica se alocou corretamente
    if(aux!=NULL){
        // Colocar os respetivos valores
        aux->freq=freq; 
        aux->x= x; 
        aux->y= y; 
        aux->prox=NULL; 
        *validar=true;
    } else {
    *validar=false;
    }
    return(aux); 
}

/**
 * @brief Insere uma antena nova na lista ligada, ordenada corretamente pelas coordenadas (x, y)
 *
 * Esta função insere uma antena na posição correta dentro da lista ligada, mantendo a ordem crescente das coordenadas (y, x)
 * A ordenação é feita primeiramente pelo valor de 'y' (linha), e, caso 'y' seja igual, a ordenação é feita pelo valor de 'x' (coluna)
 * Se já existir uma antena nas mesmas coordenadas, a nova antena não será adicionada, e a memória alocada para ela será libertada
 *
 * @param inicio Ponteiro para o início da lista ligada de antenas
 * @param nova Ponteiro para a nova antena a ser inserida
 * @param validar Ponteiro para uma variável booleana que indica se a inserção foi bem-sucedida
 * @return Retorna a lista de antenas atualizada
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
        *validar=false;
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
 * @brief Remove uma antena da lista ligada com base nas coordenadas (x, y)
 * 
 * Esta função percorre a lista ligada de antenas e caso encontre uma antena na posição (x, y) remove-a da lista e liberta a memória
 * 
 * @param inicio Ponteiro para o primeiro elemento da lista ligada de antenas
 * @param x Coordenada x da antena a ser removida
 * @param y Coordenada y da antena a ser removida
 * @param validar Ponteiro para uma variável booleana que será definido como true se a remoção for bem-sucedida, ou false caso contrário
 * @return Antena* Retorna a lista ligada das antenas já atualizada
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
 * @brief Liberta e destroí a memória da lista ligada das antenas
 * 
 * Esta função percorre a lista ligada de antenas toda e liberta a memória de cada antena
 * 
 * @param inicio Ponteiro para o início da lista ligada de antenas
 * @param validar Ponteiro para uma variável booleana que será definida como true se a lista for destruída corretamente, ou false caso contrário
 * @return Antena* Retorna `NULL` após destruir a lista, o que indica que a memória foi libertada e a lista destruída corretamente
 */
Antena* DestroiLista(Antena* inicio, bool* validar){
	if (inicio != NULL) {
		Antena* aux;
        // Percorre toda a lista e liberta todas as antenas
		while (inicio) {
			aux = inicio;
			inicio = inicio->prox;
			free(aux);
		}
        *validar=true;
	}else{
        *validar=false;
    }
}

#pragma endregion

#pragma region Efeito_Nefasto

/**
 * @brief Função para criar efeitos nefastos e alocar na memória com os parâmetros especificados
 * 
 * Esta função aloca dinamicamente memória para um novo efeito da estrutura 'EfeitoNefasto'
 * Coloca os respetivos valores nas coordenadas (x, y)
 * 
 * @param x Coordenada X da localização com efeito nefasto
 * @param y Coordenada Y da localização com efeito nefasto
 * @param validar Ponteiro para uma variável booleana que será definido como true se a alocação for bem-sucedida, ou false caso contrário
 * @return EfeitoNefasto* Retorna o ponteiro para o novo efeito, ou NULL caso a alocação na memória falhe
 */
EfeitoNefasto* CriarEfeitoNefasto(int x, int y, bool* validar){
    // Declara um ponteiro auxiliar para o novo efeito da lista
    EfeitoNefasto* aux;
     // Aloca memória dinamicamente para o novo efeito da lista 
    aux=(EfeitoNefasto*)malloc(sizeof(EfeitoNefasto));
    // Verifica se alocou corretamente
    if(aux!=NULL){
        // Coloca os respetivos valores
        aux->x=x; 
        aux->y=y; 
        aux->prox=NULL; 
        *validar=true;
    } else {  
    *validar=false;
    }
    return(aux);
}

/**
 * @brief Insere um novo efeito nefasto numa lista ligada de efeitos, caso ainda não exista um efeito nessa posição
 * 
 * Esta função cria um novo efeito nefasto e insere o efeito na lista de forma ordenada (pelas coordenadas (x, y)), a menos que já exista um na posição especificada
 * Se o efeito já estiver na posição fornecida (com as mesmas coordenadas 'x' e 'y'), o novo efeito não será inserido e a lista será retornada sem modificações
 * Caso a lista esteja vazia, o novo efeito será o primeiro da lista
 * 
 * @param inicio Ponteiro para o início da lista de efeitos nefastos
 * @param n Ponteiro para o novo efeito a ser inserido
 * @param validar Ponteiro para uma variável booleana que será definida como true se a inserção for bem-sucedida ou false caso contrário
 * @return EfeitoNefasto* Retorna o início da lista de efeitos nefastos após a inserção ou sem modificações caso o efeito já exista
 */
EfeitoNefasto* InserirEfeitoNefasto(EfeitoNefasto* inicio, EfeitoNefasto* n, bool* validar){
    
    // Verifica se a alocação do novo efeito falhou
    if(n==NULL){
        *validar=false;
        return(inicio);
    }

    // Se a lista estiver vazia o novo efeito será o primeiro da lista
    if(inicio==NULL){
        *validar=true;
        inicio=n;
        return(n);
    } 

    // Ponteiros auxiliares para percorrer a lista
    EfeitoNefasto* aux1= inicio;
    EfeitoNefasto* aux2= NULL;


    // Percorrer a lista até encontrar a posição para inserir
    while(aux1!=NULL && (aux1->x < n->x || ( aux1->x == n->x && aux1->y < n->y))){
        aux2= aux1;
        aux1= aux1->prox;
    }

    // Se um efeito já existe na posição o novo efeito não será inserido
    if(aux1!=NULL && aux1->x == n->x && aux1->y == n->y){
    free(n); 
    *validar=false;
    return(inicio); // Retorna a lista sem modificações
    }
    
    // Caso o novo efeito seja inserido no início da lista
    if(aux2==NULL){
        n->prox=inicio;
        inicio=n;
        *validar=true;
        return(inicio);
    }

    // Inserir o novo efeito entre aux2 e aux1
    n->prox=aux1;
    aux2->prox=n;
    *validar=true;

    return(inicio);
}

/**
 * @brief Calcula o efeito nefasto entre o sinal das antenas com a mesma frequência e insere os efeitos nefastos nas devidas posições
 * 
 * Esta função percorre todas as antenas da lista e compara as antenas com a mesma frequência
 * Quando encontra antenas que estão a uma distância até 2 unidades numa direção horizontal, vertical ou diagonal, é gerado um efeito nefasto nas posições ao lado dessas antenas
 * Para cada par de antenas que estão a uma distância de 2 unidades, a função insere efeitos nefastos antes e depois das antenas nas direções horizontal, vertical ou diagonal
 * A função guarda os efeitos nefastos numa lista ligada e os efeitos são inseridos nas posições de interferência de forma ordenada
 * A interferência é apenas entre antenas com a mesma frequência
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param validar Ponteiro para variável booleana que indica se o processo foi bem-sucedido ou não
 * @return EfeitoNefasto* Retorna a lista de efeitos nefastos após inserir os mesmos
 */
EfeitoNefasto* CalcularEfeito(Antena* inicio, bool* validar){
    // Cria a lista vazia
    EfeitoNefasto* Lista_Efeitos= NULL; 

    // Ponteiro para novo efeito criado
    EfeitoNefasto* efeito;

    // Ponteiros para percorrer a lista de antenas
    Antena* aux1;
    Antena* aux2;

    bool sucesso;
    bool sucesso2;

    *validar=false;

    // Percorre todas as antenas
    for (aux1=inicio; aux1 != NULL; aux1 = aux1->prox) {
        for (aux2=aux1->prox; aux2 != NULL; aux2 = aux2->prox) {
    
            // Apenas considera antenas com a mesma frequencia
            if(aux1->freq == aux2->freq){
                // Calcula a diferença nas coordenadas X e Y entre as antenas
                int Dif_X= aux2->x-aux1->x;
                int Dif_Y= aux2->y-aux1->y;

            
                // Verifica horizontalmente o efeito
                if(Dif_Y==0 && (abs(Dif_X)==2 || abs(Dif_X)==1)){
                    // Adicionar efeitos antes e depois das antenas na direção horizontal
                    efeito= CriarEfeitoNefasto(aux1->x - Dif_X, aux1->y, &sucesso);
                    if(sucesso){
                        Lista_Efeitos= InserirEfeitoNefasto(Lista_Efeitos, efeito, &sucesso2);
                        if(sucesso2){
                            *validar=true;
                        }
                    }
                    efeito= CriarEfeitoNefasto(aux2->x + Dif_X, aux2->y, &sucesso);
                    if(sucesso){
                        Lista_Efeitos= InserirEfeitoNefasto(Lista_Efeitos, efeito, &sucesso2);
                        if(sucesso2) *validar= true;
                    }
                }
                // Verifica verticalmente o efeito
                if(Dif_X==0 && (abs(Dif_Y)==2 || abs(Dif_Y)==1)){
                    // Adicionar efeitos acima e abaixo das antenas na direção vertical
                    efeito = CriarEfeitoNefasto(aux1->x, aux1->y - Dif_Y, &sucesso);
                    if(sucesso){
                        Lista_Efeitos = InserirEfeitoNefasto(Lista_Efeitos, efeito, &sucesso2);
                        if(sucesso2) *validar=true;
                    }
                    efeito = CriarEfeitoNefasto(aux2->x, aux2->y + Dif_Y, &sucesso);
                    if(sucesso){
                        Lista_Efeitos = InserirEfeitoNefasto(Lista_Efeitos, efeito, &sucesso2);
                        if(sucesso2) *validar=true;
                    }
                }
                // Verifica diagonalmente o efeito
                if((abs(Dif_X)==2 || abs(Dif_X)==1) && (abs(Dif_Y)==2 || abs(Dif_Y)==1)){
                    // Adicionar efeitos nas diagonais antes e depois das antenas
                    efeito = CriarEfeitoNefasto(aux1->x - Dif_X, aux1->y - Dif_Y, &sucesso);
                    if(sucesso){
                        Lista_Efeitos = InserirEfeitoNefasto(Lista_Efeitos, efeito, &sucesso2);
                        if(sucesso2) *validar=true;
                    }
                    efeito = CriarEfeitoNefasto(aux2->x + Dif_X, aux2->y + Dif_Y, &sucesso);
                    if(sucesso){
                        Lista_Efeitos = InserirEfeitoNefasto(Lista_Efeitos, efeito, &sucesso2);
                        if(sucesso2) *validar= true;
                    }
                }
            }
 
        }
    }
    return(Lista_Efeitos);  
}
      

/**
 * @brief Remove as antenas que estejam nas posições onde correspondem efeitos nefastos
 * 
 * Esta função percorre e compara as posições da lista de efeitos nefastos e da lista de antenas
 * Remove todas as antenas que estejam na mesma posição de um efeito nefasto ao chamar a função 'RemoverAntena' 
 * 
 * @param Lista_Efeitos Ponteiro para a lista ligada de efeitos nefastos
 * @param inicio Ponteiro para a lista ligada de antenas
 * @param validar Ponteiro para a variável booleana que indica se houve alguma remoção
 * @return Antena* Retorna o ponteiro atualizado para a lista de antenas após remover
 */
Antena* RemoverAntenasComConflito(EfeitoNefasto* Lista_Efeitos, Antena* inicio, bool* validar){

    EfeitoNefasto* auxE;
    Antena* auxA;

    bool sucesso;

    *validar=false;

    for (auxE = Lista_Efeitos; auxE != NULL; auxE = auxE->prox) {
        inicio = RemoverAntena(inicio, auxE->x, auxE->y, &sucesso);
        if (sucesso) {
            *validar = true;
        }
    }

    return(inicio);
}
#pragma endregion

#pragma region Ficheiros

/**
 * @brief Carrega apenas as antenas a partir de um ficheiro e cria uma lista ligada com a representação da cidade
 *
 * Esta função lê um ficheiro de texto que contém uma matriz que representa uma cidade com antenas
 * Apenas as antenas (!='.') são copiadas para a lista ligada, enquanto os pontos '.' representam posições vazias
 * A função chama 'InserirAntena()' para adicionar as antenas à lista
 *
 * @param nomeficheiro Nome do ficheiro a ser lido
 * @param validar Ponteiro para a variável booleana que indica se a operação foi bem-sucedida
 * @return Retorna o ponteiro para a primeira antena da lista ligada, ou NULL em caso de falha
 */
Antena* CarregarFicheiro(char* nomeficheiro, bool* validar){
    bool sucesso;
    *validar=false;

    // Abre o ficheiro em modo leitura
    FILE* ficheiro = fopen(nomeficheiro, "r");
    // Verifica se o ficheiro foi aberto corretamente
    if(!ficheiro){
        *validar=false;
        return NULL; 
    }

    Antena* inicio = NULL; // Ponteiro para o início da lista ligada (inicialmente vazia)
    char linha[TAM_MAX_LINHA]; // Array para armazenar cada linha lida do ficheiro
    int y = 0; // Coordenada Y, representa as linhas das matriz

    // Lê o ficheiro linha a linha
    while(fgets(linha, sizeof(linha), ficheiro)){
        // Percorre cada caracter da linha até encontrar espaço vazio ou uma quebra de linha 
        for(int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++){
            // Apenas as antenas são adicionados à lista ligada 
            if (linha[x]!='.'){
                Antena* nova= CriarAntena(linha[x], x, y, &sucesso);
                if(sucesso){
                inicio = InserirAntena(inicio, nova, &sucesso); 
                if(sucesso) *validar=true;
                }
            }
        }
        y++; // Avança para a próxima linha do ficheiro
    }
    fclose(ficheiro); 
    return inicio; 
   
}

/**
 * @brief Grava a lista de antenas num ficheiro binário
 * 
 * Esta função percorre a lista ligada de antenas e grava as antenas num ficheiro binário
 * 
 * @param nomeficheiro Nome do ficheiro onde as antenas serão guardadas
 * @param inicio Ponteiro para a lista ligada de antenas a ser gravada
 * @return true Se a gravação das antenas no ficheiro ocorrer corretamente
 * @return false Caso ocorra erro ao abrir o ficheiro
 */
bool GravarFicheiroBin(char* nomeficheiro, Antena* inicio){
    // Abre o ficheiro para escrita binária
    FILE* ficheiro= fopen(nomeficheiro, "wb");
    if(!ficheiro){
        return false;
    }

    Antena* aux=inicio;
    AntenaF antenas;

    // Percorre a lista ligada de antenas e escreve no ficheiro
    while(aux){
        // Copia os dados da estrutura Antena para AntenaF
        antenas.freq = aux->freq;
        antenas.x = aux->x;
        antenas.y = aux->y;
        // Escreve a estrutura AntenaF no ficheiro binário
        fwrite(&antenas, sizeof(antenas), 1, ficheiro);
        aux=aux->prox; // Avança para a próxima antena na lista
    }

    fclose(ficheiro);
    return true;
}


/**
 * @brief Lê a lista de antenas apartir do ficheiro binário
 *
 * Esta função abre o ficheiro binário e lê os dados das antenas e reconstroí a lista ligada
 * As antenas são inseridas na lista através da função 'InserirAntena'
 *
 * @param nomeficheiro Nome do ficheiro binário de onde as antenas serão lidas
 * @param validar Um ponteiro para variável boleano de sucesso
 * @return Antena* Retorna um ponteiro para a lista ligada reconstruída (antenas) ou 'NULL' caso o ficheiro não exista
 */
Antena* LerFicheiroBin(char* nomeficheiro, bool* validar){
    bool sucesso;
    *validar = false;

    // Abre o ficheiro para leitura binária
    FILE* ficheiro= fopen(nomeficheiro, "rb");
    if(!ficheiro){
        return NULL;
    }
 
    Antena* inicio=NULL;
    AntenaF antenas;

    // Lê os dados do ficheiro e insere na lista
    while(fread(&antenas, sizeof(antenas), 1, ficheiro)){
        Antena* nova= CriarAntena(antenas.freq, antenas.x, antenas.y, &sucesso);
        if(sucesso){
        inicio=InserirAntena(inicio, nova, &sucesso);
        if(sucesso) *validar=true;
        }
    }
    
    fclose(ficheiro);
    return (inicio);

}

#pragma endregion


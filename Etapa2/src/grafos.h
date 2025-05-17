/**
 * @file grafos.h
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief Define as funções e estruturas
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <stdbool.h>

#define TAM_MAX_LINHA 200
#define MAX_ANTENAS 100

#pragma region Estruturas

/**
 * @brief Esta estrutura modela uma antena no grafo e contém informações sobre a sua frequência,
 * posição no espaço (coordenadas x e y), ligações a outras antenas (adjacências), um ponteiro
 * para a próxima antena na lista ligada e uma flag de visita para saber se esta ja foi visitada ou não
 * 
 */
typedef struct Antena{
    char freq;
    int x;
    int y;
    struct Adj* adj;
    struct Antena* prox;
    bool visitado;
}Antena;

/**
 * @brief Representa uma aresta entre antenas no grafo
 * 
 * Esta estrutura modela uma ligação entre duas antenas no grafo, onde cada uma representa uma adjacência (aresta) a partir de uma antena de origem para uma antena de destino
 * 
 */
typedef struct Adj{
    Antena* destino;
    struct Adj* prox;
}Adj;

/**
 * @brief Representa um caminho composto por uma sequência de antenas
 *
 * Esta estrutura modela um caminho no grafo, contendo um array de ponteiros para antenas que constituem o percurso, o número total de antenas no caminho
 * e um ponteiro para o próximo caminho na lista ligada
 *  
 */
typedef struct Caminho{
    Antena* antenas[MAX_ANTENAS];
    int nAntenas;
    struct Caminho* prox;
} Caminho;

#pragma endregion

#pragma region Funções
/**
 * @brief Cria uma nova antena com os parâmetros especificados
 * 
 * @param freq Carácter representando a frequência de ressonância da antena
 * @param x Coordenada horizontal (x) da antena
 * @param y Coordenada vertical (y) da antena
 * @param validar Ponteiro para uma variável booleana que indica se a criação foi bem-sucedida
 * @return Antena* Ponteiro para a nova antena criada, ou NULL se ocorrer um erro durante a alocação
 */
Antena* CriarAntena( char freq, int x, int y, bool* validar);

/**
 * @brief Insere uma nova antena na lista ligada de antenas
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param nova Ponteiro para a nova antena a ser inserida
 * @param validar Ponteiro para uma variável booleana que indica se a inserção foi bem-sucedida
 * @return Antena* Ponteiro para o início atualizado da lista de antenas
 */
Antena* InserirAntena(Antena* inicio, Antena* nova, bool* validar);

/**
 * @brief Remove uma antena da lista ligada com base nas suas coordenadas
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param x Coordenada horizontal (x) da antena a remover
 * @param y Coordenada vertical (y) da antena a remover
 * @param validar Ponteiro para uma variável booleana que indica se a remoção foi bem-sucedida
 * @return Antena* Ponteiro para o início atualizado da lista de antenas
 */
Antena* RemoverAntena(Antena* inicio, int x, int y, bool* validar);

/**
 * @brief Procura uma antena na lista ligada com base nas suas coordenadas
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param x Coordenada horizontal (x) da antena a procurar
 * @param y Coordenada vertical (y) da antena a procurar
 * @return Antena* Ponteiro para a antena encontrada, ou NULL se não encontrar nenhuma
 */
Antena* EncontrarAntena(Antena* inicio, int x, int y);

/**
 * @brief Cria uma nova aresta (ligação) entre antenas
 * 
 * @param destino Ponteiro para a antena de destino da aresta
 * @param validar Ponteiro para uma variável booleana que indica se a criação foi bem-sucedida
 * @return Adj* Ponteiro para a nova aresta criada, ou NULL se ocorrer um erro durante a alocação
 */
Adj* CriarAresta(Antena* destino, bool* validar);

/**
 * @brief Insere uma nova aresta na lista de adjacências de uma antena
 * 
 * @param inicio Ponteiro para a lista de antenas
 * @param aresta Ponteiro para a aresta a ser inserida
 * @param validar Ponteiro para uma variável booleana que indica se a inserção foi bem-sucedida 
 * @return Adj* Ponteiro para a lista de antenas atualizada
 */
Adj* InserirAresta(Antena* inicio, Adj* aresta, bool* validar);

/**
 * @brief Calcula todas as arestas de adjacência no grafo de antenas
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param validar Ponteiro para uma variável booleana que indica se a operação foi bem-sucedida.
 * @return Adj* Ponteiro para a lista de arestas calculadas
 */
Adj* CalcularArestas(Antena* inicio, bool* validar);

/**
 * @brief Carrega uma lista de antenas a partir de um ficheiro de texto
 * 
 * @param nomeficheiro Nome do ficheiro a ser carregado
 * @param validar Ponteiro para uma variável booleana que indica se a operação foi bem-sucedida
 * @return Antena* Ponteiro para a lista de antenas carregada, ou NULL se ocorrer um erro durante a leitura
 */
Antena* CarregarFicheiro(char* nomeficheiro, bool* validar);

/**
 * @brief Grava a lista de antenas num ficheiro binário
 * 
 * @param nomeficheiro Nome do ficheiro binário onde as antenas serão gravadas
 * @param inicio Ponteiro para o início da lista de antenas a ser gravada
 * @return true se todas as antenas forem gravadas com sucesso
 * @return false em caso de erro
 */
bool GravarFicheiroBin(char* nomeficheiro, Antena* inicio);

/**
 * @brief Lê um ficheiro binário e carrega os dados das antenas
 * 
 * @param nomeficheiro Nome do ficheiro binário a ser lido
 * @param validar Ponteiro para uma variável booleana que indica se a operação foi bem-sucedida
 * @return Antena* Ponteiro para o início da lista de antenas carregada, ou NULL se ocorrer um erro durante a leitura
 */
Antena* LerFicheiroBin(char* nomeficheiro, bool* validar);

/**
 * @brief Limpa o estado de visitação de todas as antenas no grafo
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 * @param validar Ponteiro para uma variável booleana que indica se a operação foi bem-sucedida
 */
void LimparVisitados(Antena* inicio, bool* validar);

/**
 * @brief Realiza uma busca em profundidade a partir de uma antena
 * 
 * @param antena Ponteiro para a antena de início da busca
 * @param visitados Vetor de ponteiros para antenas já visitadas
 * @param nVisitados Ponteiro para o número de antenas visitadas    
 * @param validar Ponteiro para uma variável booleana que indica se a operação foi bem-sucedida
 */
void ProcuraProfundidade(Antena* antena, Antena* visitados[], int* nVisitados, bool* validar);

/**
 * @brief Guarda um caminho percorrido pelas antenas na lista de caminhos
 * 
 * @param caminho Vetor de ponteiros para as antenas que compõem o caminho  
 * @param posicao Índice que representa a posição final do caminho no vetor 
 * @param caminhos Ponteiro para a lista de caminhos onde o novo caminho será inserido
 * @return Caminho* Ponteiro para a lista de caminhos atualizada com o novo caminho
 */
Caminho* GuardarCaminho(Antena* caminho[], int posicao, Caminho* caminhos);

/**
 * @brief Calcula todos os caminhos possíveis entre duas antenas no grafo   
 * 
 * @param origem Ponteiro para a antena de origem do caminho
 * @param destino Ponteiro para a antena de destino do caminho
 * @param caminho Vetor que armazena o caminho atual durante a busca
 * @param posicao Índice que representa a posição atual no vetor `caminho`
 * @param caminhos Ponteiro para a lista de caminhos onde os caminhos encontrados serão armazenados
 * @param validar Ponteiro para uma variável booleana que indica se a operação foi bem-sucedida
 * @return Caminho* Ponteiro para a lista de caminhos atualizada com os novos caminhos encontrados
 */
Caminho* CalcularCaminhosEntreAntenas(Antena* origem, Antena* destino, Antena* caminho[], int posicao, Caminho* caminhos, bool* validar);

#pragma endregion
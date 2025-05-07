/**
 * @file main.c
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief Programa principal que testa as funções
 * @version 0.1
 * @date 2025-03-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include "funcoes.h"
#include "matriz.h"

/**
 * @brief Executa as seguintes operações:
 * 1. Carrega as antenas a partir do ficheiro "cidade.txt"
 * 2. Insere antenas em posições especificas
 * 3. Remove antenas em determinadas posições
 * 4. Calcula os efeitos nefastos das antenas e insere os mesmos
 * 5. Remove as antenas em conflito de posições com efeito nefasto e atualiza estes
 * 6. Grava a lista ligada das antenas num ficheiro binário
 * 7. Destroi a lista ligada das antenas
 * 8. Lê os dados das antenas do ficheiro binário e guarda-os na lista ligada 
 * 
 * @return * int Retorna 0 para indicar que o programa foi executado com sucesso
 */
int main (){
    // Ponteiro para o início da lista de antenas
    Antena* inicio= NULL;
    Antena* nova;

    // Ponteiro para início da lista de efeitos
    EfeitoNefasto* Lista_Efeitos= NULL;

    bool sucesso;
    bool sucesso2;

    // Carrega antenas a partir do ficheiro .txt
    printf("\n Matriz com ficheiro carregado:\n\n");
    inicio=CarregarFicheiro("cidade.txt", &sucesso);
    if(sucesso){
    MostrarAntenas(inicio);
    }else{
        printf("\n Erro ao carregar o ficheiro!\n");
    }

    // Insere algumas antenas manualmente
    printf("\n Matriz após inserir antenas:\n\n");
    nova=CriarAntena('A', 2, 4, &sucesso);
    if(sucesso){
        inicio=InserirAntena(inicio, nova, &sucesso2);
        if(sucesso2){
            MostrarAntenas(inicio);
        }else{
            printf("\n Erro ao inserir Antena!\n");
        }
    }else{
        printf("\n Erro ao criar antena!\n");
    }
   

    // Remove uma antena em coordenadas específicas
    printf("\n Matriz após remover antenas:\n\n");
    inicio=RemoverAntena(inicio, 2, 4, &sucesso);
    if(sucesso){
        MostrarAntenas(inicio);
    }else{
        printf("\n Erro ao remover antena!\n");
    }
    
    // Calcula efeitos
    printf("\n Matriz com antenas e devidos efeitos nefastos:\n\n");
    Lista_Efeitos=CalcularEfeito(inicio, &sucesso);
    if(sucesso){
        MostrarAntenasEEfeitos(inicio, Lista_Efeitos);
    }else{
        printf("\n Erro ao calcular efeitos nefastos!\n");
    }
   

    // Remove as antenas em que coincidem com a posição de efeito nefasto e atualiza a posição do mesmo
    printf("\n Matriz com antenas e efeitos nefastos sem conflitos: \n\n");
    inicio=RemoverAntenasComConflito(Lista_Efeitos, inicio, &sucesso);
    if(sucesso){
        printf("\n Antenas em conflito removidas com sucesso!\n\n");
    }else{
        printf("\n Erro ao remover antenas em conflito!\n");
    }

    Lista_Efeitos=CalcularEfeito(inicio, &sucesso2);
    if(sucesso){
        MostrarAntenasEEfeitos(inicio, Lista_Efeitos);
    }else{
        printf(" Erro ao calcular efeitos!\n");
    }
    
    // Grava a lista ligada das antenas num ficheiro binário
    sucesso=GravarFicheiroBin("Antenas.bin", inicio);
    if(sucesso){
        printf("\n Dados guardados com sucesso!\n");
    }else{
        printf("\n Erro ao guardar dados no ficheiro!\n");
    }

    // Destroi a lista ligada das antenas
    inicio= DestroiLista(inicio, &sucesso);
    if(sucesso){
        printf("\n Lista das antenas foi removida com sucesso! \n\n");
    }else{
        printf("\n Erro ao destruir lista!\n");
    }
    
    // Lê o ficheiro binário e voltamos a ter as posições das antenas (lista)
    inicio=LerFicheiroBin("Antenas.bin", &sucesso);
    if(sucesso){
        printf("\n Matriz das antenas após a leitura do ficheiro binário: \n\n");
        MostrarAntenas(inicio);
    }else{
        printf("\n Erro ao ler ficheiro!\n");
    }

    return 0;
}

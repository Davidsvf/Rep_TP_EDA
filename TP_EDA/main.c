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

    // Ponteiro para início da lista de efeitos
    EfeitoNefasto* Lista_Efeitos= NULL;

    // Carrega antenas a partir do ficheiro .txt
    printf("\n Matriz com ficheiro carregado:\n\n");
    inicio=CarregarFicheiro("cidade.txt");
    MostrarAntenas(inicio);

    // Insere algumas antenas manualmente
    printf("\n Matriz após inserir antenas:\n\n");
    inicio=InserirAntena(inicio, 'A', 2, 4);
    inicio=InserirAntena(inicio, 'B', 5, 5);
    inicio=InserirAntena(inicio, 'C', 1, 8);
    MostrarAntenas(inicio);

    // Remove uma antena em coordenadas específicas
    printf("\n Matriz após remover antenas:\n\n");
    inicio=RemoverAntena(inicio, 2, 4);
    inicio=RemoverAntena(inicio, 5, 5);
    inicio=RemoverAntena(inicio, 1, 8);
    MostrarAntenas(inicio);

    // Calcula efeitos
    printf("\n Matriz com antenas e devidos efeitos nefastos:\n\n");
    Lista_Efeitos=CalcularEfeito(inicio);
    MostrarAntenasEEfeitos(inicio, Lista_Efeitos);

    // Remove as antenas em que coincidem com a posição de efeito nefasto e atualiza a posição do mesmo
    printf("\n Matriz com antenas e efeitos nefastos sem conflitos: \n\n");
    inicio=RemoverAntenasComConflito(Lista_Efeitos, inicio);
    Lista_Efeitos=CalcularEfeito(inicio);
    MostrarAntenasEEfeitos(inicio, Lista_Efeitos);

    // Grava a lista ligada das antenas num ficheiro binário
    GravarFicheiroBin("Antenas.bin", inicio);

    // Destroi a lista ligada das antenas
    inicio= DestroiLista(inicio);
    printf("\n Matriz das antenas depois da lista ser destruida: \n\n");
    MostrarAntenas(inicio);

    // Lê o ficheiro binário e voltamos a ter as posições das antenas
    inicio=LerFicheiroBin("Antenas.bin");
    printf("\n Matriz das antenas após a leitura do ficheiro binário: \n\n");
    MostrarAntenas(inicio);

    return 0;
}

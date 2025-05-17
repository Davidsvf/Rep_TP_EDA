/**
 * @file ecra.h
 * @author David Faria (a31517@alunos.ipca.pt)
 * @brief Define as funções para apresentar no ecrã
 * @version 0.1
 * @date 2025-05-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include "grafos.h"

/**
 * @brief Mostra o grafo de antenas na consola
 * 
 * @param inicio Ponteiro para o início da lista de antenas
 */
void MostraGrafo(Antena* inicio);

/**
 * @brief Lista todos os caminhos armazenados possiveis
 * 
 * @param caminhos Ponteiro para o início da lista de caminhos a listar
 */
void ListarCaminhos(Caminho* caminhos);
#ifndef TARQUIVO_H_
#define TARQUIVO_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tJogo.h"

typedef struct {
    /*Número de frutas obtidas com aquele movimento*/
    int frutas;

    /*Número de colisões geradas por aquele movimento*/
    int colisoes;

    /*Número de usos daquele movimento*/
    int usos;

    /*Tipo daquele movimento*/
    char tipo;
} tComandos;

/**
 * Gera um arquivo de inicialização contendo o mapa e a posição
 * de início do pacman.
 * \param jogo jogo
 */
void GeraInicializacao(tJogo* jogo);

/**
 * Apenas chama a função SalvaTrilhaPacman do tPacman.
 * \param jogo jogo
 */
void GeraTrilha(tJogo* jogo);

/**
 * Gera um arquivo de estatística, contendo o número de
 * movimentos, número de movimentos sem pontuar, número de colisões com parede, número
 * de movimentos para baixo, número de movimentos para cima, número de movimentos para a
 * esquerda e número de movimentos para a direita.
 * \param jogo jogo
 */
void GeraEstatistica(tJogo* jogo);

/**
 * Gera um ranking de melhores movimentos junto
 * de características desses movimentos ao fim do jogo. A ordem dos critérios é:
 * maior número de comida obtida, menor número de colisões, maior número de usos e 
 * ordem alfabética.
 * \param jogo jogo
 */
void GeraRanking(tJogo* jogo);

/**
 * Gera um resumo, que deverá conter uma descrição do que houve em 
 * cada movimento em que houve alguma variação significativa: 
 * pegou comida, colidiu com a parede ou colidiu com um fantasma.
 * \param jogo jogo
 */
void GeraResumo(tJogo* jogo);

#endif
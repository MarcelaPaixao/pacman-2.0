#ifndef TTUNEL_H_
#define TTUNEL_H_

#include <stdlib.h>
#include <stdio.h>

#include "tPosicao.h"
#include "tPacman.h"
#include "tMapa.h"

#define DIREITA 1
#define ESQUERDA -1
#define BAIXO 2
#define CIMA -2

typedef struct{
    tPosicao * posicaoAtualFant;
    tPosicao * posicaoAntigaFant;
    char tipo;
    int direcao;
    int tocaFruta;
    int tocaParede;
} tFantasma;

/**
 * Cria o fantasma dinamicamente. Caso dê erro na alocação da estrutura tFantasma, 
 * retorna NULL. 
 * Caso a posição passada como parâmetro seja NULL, retorna NULL.
 * Caso não dê erros, retorna o ponteiro para o tFantasma alocado.
 * \param posicao Ponteiro para tPosicao
 */
tFantasma* CriaFantasma(tPosicao* posicao, char tipo);

/**
 * Retorna a posição do fantasma.
 * 
 * \param fantasma fantasma
 */
tPosicao* ObtemPosicaoFantasma(tFantasma* fantasma);

/**
 * Retorna o tipo do fantasma.
 * 
 * \param fantasma fantasma
 */
char ObtemTipoFantasma(tFantasma* fantasma);

//Atualoza posicao

 /* Função que irá mover o pacman no mapa, atualizando sua posição.
 * Dado o pacman, o mapa, e o comando do jogador, a posição do pacman
 * é atualizada. Consultas ao mapa deverão ser feitas para ver se
 * a posição pode ser realmente atualizada ou não, como por exemplo,
 * se o pacman encontrou uma parede ele não se move.
 * 
 * \param pacman pacman
 * \param mapa o mapa que contem o pacman
 * \param comando o comando para onde irá o pacman
 */
void MoveFantasma(tFantasma* fantasma, tMapa* mapa);
//pode usar a obtem tipo e obtem direcao aqui dentro pra saber pra onde ele vai;
#endif
#ifndef TFANTASMA_H_
#define TFANTASMA_H_

#include <stdbool.h>
#include "tPosicao.h"
#include "tPacman.h"
#include "tMapa.h"

#define DIREITA 1
#define ESQUERDA -1
#define BAIXO 1
#define CIMA -1

typedef struct{
    /*Posição atual do fantasma*/
    tPosicao * posicaoAtualFant;

    /*Posição anterior do fantasma*/
    tPosicao * posicaoAntigaFant;

    /*Tipo do fantasma*/
    char tipo;

    /*Tipo do fantasma*/
    int direcao;

    /*Variável para controlar se o fantasma está sobre uma fruta ou não*/
    int tocaFruta;

    /*Variável para controlar se fantasma existe ou não*/
    int existe;
} tFantasma;

/**
 * Cria o fantasma dinamicamente. Caso dê erro na alocação da estrutura tFantasma, 
 * retorna NULL. 
 * Caso a posição passada como parâmetro seja NULL, retorna NULL.
 * Caso não dê erros, retorna o ponteiro para o tFantasma alocado.
 * \param posicao Ponteiro para tPosicao
 * \param tipo tipo do fantasma
 */
tFantasma* CriaFantasma(tPosicao* posicao, char tipo);

/**
 * Inverte a direção do fantasma. Por exemplo: Caso seja direita, sua direção passa a ser esquerda;
 * \param fantasma fantasma
 */
void InverteDirecaoFant(tFantasma* fantasma);

/**
 *  Função que irá mover o fantasma no mapa, atualizando sua posição.
 * Dado o fantasma e o mapa, a posição do fantasma é atualizada. 
 * Se o fantasma encontrou uma parede, ele muda a direção.
 * \param fantasma fantasma
 * \param mapa o mapa que contem os fantasmas
 */
void MoveFantasma(tFantasma* fantasma, tMapa* mapa);

/**
 *  Função que irá verificar se o fantasma matou o pacman e garantir que eles não se cruzaram;
 * \param mapa o mapa que contem os fantasmas
 * \param fantasma fantasma
 * \param pacman pacman
 * \param posAntigaPcman posição anterior do pacman
 */
void VerificaSeMatouPacmanFantasma(tMapa* mapa, tFantasma* fantasma, tPacman* pacman, tPosicao* posAntigaPacman);

/**
 * Caso o fantasma seja diferente de NULL, libera o espaço 
 * alocado para a estrutura tFantasma.
 * Sempre verificar se é NULL antes de dar free.
 * 
 * \param fantasma fantasma
 */
void DesalocaFantasmas(tFantasma* fantasma);

/**
 * Retorna o tipo do fantasma.
 * 
 * \param fantasma fantasma
 */
char ObtemTipoFantasma(tFantasma* fantasma);

/**
 * Retorna a direção do fantasma.
 * 
 * \param fantasma fantasma
 */
int ObtemDirecaoFantasma(tFantasma* fantasma);

/**
 * Retorna verdadeiro se o fantasma está sobre fruta,
 * e falso caso contrário;
 *
 * \param fantasma fantasma
 */
bool TocouFrutaFantasma(tFantasma* fantasma);

/**
 * Retorna verdadeiro se o fantasma existe,
 * e falso caso contrário;
 *
 * \param fantasma fantasma
 */
bool ExisteFantasma(tFantasma* fantasma);

/**
 * Retorna a posição atual do fantasma.
 * 
 * \param fantasma fantasma
 */
tPosicao* ObtemPosicaoAtualFantasma(tFantasma* fantasma);

/**
 * Retorna a posição antiga do fantasma.
 * 
 * \param fantasma fantasma
 */
tPosicao* ObtemPosicaoAntigaFantasma(tFantasma* fantasma);

#endif
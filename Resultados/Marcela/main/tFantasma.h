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
    tPosicao * posicaoAtualFant;
    tPosicao * posicaoAntigaFant;
    char tipo;
    int direcao;
    int tocaFruta;
    int existe;
} tFantasma;

/**
 * Cria o fantasma dinamicamente. Caso dê erro na alocação da estrutura tFantasma, 
 * retorna NULL. 
 * Caso a posição passada como parâmetro seja NULL, retorna NULL.
 * Caso não dê erros, retorna o ponteiro para o tFantasma alocado.
 * \param posicao Ponteiro para tPosicao
 */
tFantasma* CriaFantasma(tPosicao* posicao, char tipo);

void InverteDirecaoFant(tFantasma* fantasma);

 /* Função que irá mover o fantasma no mapa, atualizando sua posição.
 * Dado o fantasma e o mapa,  a posição do fantasma é atualizada. 
 * Se o fantasma encontrou uma parede, ele muda a direção.
 * 
 * \param fantasma fantasma
 * \param mapa o mapa que contem os fantasmas
 */
void MoveFantasma(tFantasma* fantasma, tMapa* mapa, tPacman* pacman, tPosicao* posAntigaPacman, COMANDO comando);


void VerificaSeMatouPacmanFantasma(tMapa* mapa, tFantasma* fantasma, tPacman* pacman, tPosicao* posAntigaPacman);

/**
 * Caso o fantasma seja diferente de NULL, libera o espaço 
 * alocado para a estrutura tFantasma.
 * Sempre verificar se é NULL antes de dar free.
 * 
 * \param fantasma fantasma
 */
void DesalocaFantasma(tFantasma* fantasma);

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
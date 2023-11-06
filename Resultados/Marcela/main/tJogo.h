#ifndef TJOGO_H_
#define TJOGO_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "tPacman.h"
#include "tMapa.h"
#include "tFantasma.h"

#define GANHOU 1
#define PAC_MORREU 2

typedef struct{
    /*Pacman do jogo*/
    tPacman *pacman;
    
    /*Mapa do jogo*/
    tMapa *mapa;
    
    /*Fantasma do tipo B, que anda na horizontal e inicia indo para a esquerda*/
    tFantasma *fantB;
    
    /*Fantasma do tipo C, que anda na horizontal e inicia indo para a direita*/
    tFantasma *fantC;
    
    /*Fantasma do tipo I, que anda na vertical e inicia indo para baixo*/
    tFantasma *fantI;
   
    /*Fantasma do tipo P, que anda na vertical e inicia indo para cima*/
    tFantasma *fantP;
    
    /*Estado do jogo podem ser 3:
    - pacman ganhou
    -pacman morreu por colidir com fantasma
    -nada acima aconteceu*/
    int estadoJogo;
} tJogo; 

/**
 * Cria o jogo dinamicamente. Caso dê erro na alocação da estrutura tJogo, 
 * retorna NULL. 
 * Caso não dê erros, retorna o ponteiro para o tJogo alocado.
 * \param mapa Ponteiro para o mapa
 */
tJogo* InicializaJogo(tMapa* mapa);

/**
 * Retorna verdadeiro se for necessário atualizar a posição passada como parâmetro
 * com um espaço vazio no mapa, e falso caso esse posição já seja ocupada por um dos
 * fantasmas do jogo;
 * \param jogo Ponteiro para o jogo
 * \param posAntigaPac Ponteiro para a posição anterior do pacman
 */
bool VerificaSeAtualizaVazio(tJogo *jogo, tPosicao *posAntigaPac);

/**
 * Após o movimento do pacman, verifica se algum fantasma está setado como tocando uma fruta, e 
 * caso esteja, atualiza sua posição no mapa com seu determinado caracter;
 * \param jogo Ponteiro para o jogo
 */
void AtualizaFantasma(tJogo *jogo);

/**
 * Executa a jogada de acordo com o comando passado, fazendo as atualizações
 * necessrárias no mapa e nas posições do pacman e dos fantasmas;
 * \param jogo Ponteiro para o jogo
 * \param comando comando
 */
void ExecutaJogada(tJogo* jogo, COMANDO comando);

/**
 * Retorna verdadeiro se o pacman obteve todas as frutas do mapa, e falso caso contrário;
 * \param jogo Ponteiro para o jogo
 */
bool GanhouJogo(tJogo* jogo);

/**
 * Retorna verdadeiro se o pacman está setado como morto, ou se o número máximo de 
 * jogadas foi atingido sem que o jogador obtivesse todas as frutas, e falso caso contrário;
 * \param jogo Ponteiro para o jogo
 */
bool EhGameOver(tJogo* jogo);

/**
 * Imprime o estado em que se encontra o jogo após cada movimento; 
 * \param jogo Ponteiro para o jogo
 * \param direcao direção da jogada do usuário
 */
void ImprimeEstadoAtualJogo(tJogo* jogo, char direcao);

/**
 * Caso seja diferente de NULL, desaloca a estrutura tJogo passada;
 * \param jogo Ponteiro para o jogo
 */
void DesalocaJogo(tJogo* jogo);

/**
 * Retorna o estado do jogo;
 * \param jogo Ponteiro para o jogo
 */
int ObtemEstadoJogo(tJogo* jogo);

/**
 * Retorna o ponteiro para o pacman da estrutura tJogo;
 * \param jogo Ponteiro para o jogo
 */
tPacman* ObtemPacman(tJogo* jogo);

#endif
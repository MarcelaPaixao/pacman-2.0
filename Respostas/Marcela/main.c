#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tPosicao.h"
#include "tFantasma.h"
#include "tMovimento.h"
#include "tTunel.h"
#include "tPacman.h"
#include "tMapa.h"

typedef struct{
    tPacman *pacman;
    tMapa *mapa;
    tFantasma *fantB;
    tFantasma *fantC;
    tFantasma *fantI;
    tFantasma *fantP;
} tJogo; 

tJogo* InicializaJogo(tMapa* mapa);

void ExecutaJogo(tJogo* jogo);

bool EhGameOver(tJogo* jogo);

void GeraEstatistica(tJogo* jogo);

void GeraTrilha(tJogo* jogo); //Precisa?? as funcoes de trilha estão no tPacman

void GeraRanking(tJogo* jogo);

void GeraResumo(tJogo* jogo);
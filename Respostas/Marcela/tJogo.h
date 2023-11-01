#ifndef TJOGO_H_
#define TJOGO_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "tPacman.h"
#include "tMapa.h"
#include "tFantasma.h"

#define ATIVO 1
#define PAC_MORREU 0
#define MOV_ESGOTADO 2

typedef struct{
    tPacman *pacman;
    tMapa *mapa;
    tFantasma *fantB;
    tFantasma *fantC;
    tFantasma *fantI;
    tFantasma *fantP;
    int estadoJogo;
} tJogo; 

tJogo* InicializaJogo(tMapa* mapa);

void ExecutaJogada(tJogo* jogo, COMANDO comando);

bool EhGameOver(tJogo* jogo);

bool GanhouJogo(tJogo* jogo);

void ImprimeEstadoAtualJogo(tJogo* jogo);

void DesalocaJogo(tJogo* jogo);

#endif
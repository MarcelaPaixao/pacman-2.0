#ifndef TARQUIVO_H_
#define TARQUIVO_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tJogo.h"

void GeraInicializacao(tJogo* jogo);

void GeraTrilha(tJogo* jogo);

void GeraEstatistica(tJogo* jogo);

void GeraRanking(tJogo* jogo);

void GeraResumo(tJogo* jogo);

#endif
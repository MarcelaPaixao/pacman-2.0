#ifndef TARQUIVO_H_
#define TARQUIVO_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tJogo.h"

void GeraInicializacao(tJogo* jogo, char *diretorio);

void GeraTrilha(tJogo* jogo);

void GeraEstatistica(tJogo* jogo, char *diretorio);

void GeraRanking(tJogo* jogo, char *diretorio);

void GeraResumo(tJogo* jogo, char *diretorio);

#endif
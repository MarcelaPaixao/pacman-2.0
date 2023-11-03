#ifndef TARQUIVO_H_
#define TARQUIVO_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tJogo.h"

typedef struct {
    int frutas;
    int colisoes;
    int usos;
    char tipo;
} tComandos;

void GeraInicializacao(tJogo* jogo);

void GeraTrilha(tJogo* jogo);

void GeraEstatistica(tJogo* jogo);

void GeraRanking(tJogo* jogo);

void GeraResumo(tJogo* jogo);

#endif
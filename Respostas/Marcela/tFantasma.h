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


/*typedef struct {
  int x;
  int y;
  char tipo;
  int cima;
  int baixo;
  int direita;
  int esquerda;
  int tocafruta;
} tFantasma;*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tPosicao.h"
#include "tPacman.h"
#include "tMapa.h"
#include "tFantasma.h"
#include "tMovimento.h"
#include "tTunel.h"

//int main(){
  
 // return 0;
//}

//criar vetor tfantasmas pra alocar se achar fantasmas na main


int main(){
  tMapa *mapa;
  int c=0;
  mapa = CriaMapa("./");
  
  tPacman * pac = CriaPacman(ObtemPosicaoItemMapa(mapa, '>'));
  tFantasma *C = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'C'), 'C');
  tFantasma *I = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'I'), 'I');
  //tPosicao * posPac = CriaPosicao(pac->posicaoAtual->linha, pac->posicaoAtual->coluna);
  CriaTrilhaPacman(pac, mapa->nLinhas, mapa->nColunas);

  while(c != 0){
      scanf("%i", &c);
      //posPac = pac->posicaoAtual;
      MovePacman(pac, mapa, c);
      
      MoveFantasma(I, mapa);
      MoveFantasma(C, mapa);
        
      for(int i=0; i < mapa->nLinhas; i++){
          for(int j=0; j < mapa->nColunas; j++){
            printf("%c", mapa->grid[i][j]);
          }   
          printf("\n");
        }
        //if(MatouPacmanFantasma(C, pac, posPac));
    }
  //DesalocaFantasma(C);
  //DesalocaFantasma(I);


    return 0;
}
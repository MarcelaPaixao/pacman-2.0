#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tJogo.h"
#include "tArquivo.h"

#define GANHOU 1
#define PAC_MORREU 2

int ConverteComando(char direcao){
    if(direcao == 'a'){
        return MOV_ESQUERDA;
    }
    if(direcao == 'w'){
        return MOV_CIMA;
    }
    if(direcao == 's'){
        return MOV_BAIXO;
    }
    if(direcao == 'd'){
        return MOV_DIREITA;
    }
    return -1;
}

void ImprimeMsg(tJogo *jogo){ 
    int pontuacao =  ObtemPontuacaoAtualPacman(ObtemPacman(jogo));
    if(ObtemEstadoJogo(jogo) == GANHOU){
        printf("Voce venceu!\nPontuacao final: %d\n", pontuacao);
    }
    else {
        printf("Game over!\nPontuacao final: %d\n", pontuacao);
    }
}

int main(int argc, char *argv[]){
    tJogo *jogo = NULL;
    
	char diretorio[1000], direcao;
    int comando;

	// Se diretório nao for informado, finaliza o programa
	if (argc <= 1) {
		printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
		exit(0);
	}

	sprintf(diretorio, "%s", argv[1]);
    jogo = InicializaJogo(CriaMapa(diretorio));

    GeraInicializacao(jogo);

    while(1){
        scanf("%c", &direcao);
        comando = ConverteComando(direcao);

        ExecutaJogada(jogo, comando);

        ImprimeEstadoAtualJogo(jogo, direcao);

        if(EhGameOver(jogo) || GanhouJogo(jogo)){
            ImprimeMsg(jogo);
            if(ObtemEstadoJogo(jogo) == PAC_MORREU){
                InsereNovoMovimentoSignificativoPacman(ObtemPacman(jogo), comando, 
                                                       "fim de jogo por encostar em um fantasma");
            }
            break;
        }
        scanf("%*c");

    }
    
    GeraTrilha(jogo);
    GeraEstatistica(jogo);
    GeraRanking(jogo);
    GeraResumo(jogo);
    DesalocaJogo(jogo);

    return 0;
}
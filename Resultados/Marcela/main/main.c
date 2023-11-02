#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tJogo.h"
#include "tArquivo.h"

#define GANHOU 1
#define PAC_MORREU 2

char LeComandoTeclado(){
    char comando;
    scanf("%c", &comando);
    return comando;
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
    
	char diretorio[1000], comando;

	// Se diretório nao for informado, finaliza o programa
	if (argc <= 1) {
		printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
		exit(0);
	}

	sprintf(diretorio, "%s", argv[1]);
    jogo = InicializaJogo(CriaMapa(diretorio));

    GeraInicializacao(jogo, diretorio);

    while(1){
        comando = LeComandoTeclado();

        ExecutaJogada(jogo, comando);
        
        ImprimeEstadoAtualJogo(jogo, comando);

        if(EhGameOver(jogo) || GanhouJogo(jogo)){
            ImprimeMsg(jogo);
            if(ObtemEstadoJogo(jogo) == PAC_MORREU){
                InsereNovoMovimentoSignificativoPacman(ObtemPacman(jogo), comando, 
                                                       "fim de jogo por encostar em um fantasma");
            }
            break;
        }
    }
    
    GeraTrilha(jogo);
    GeraEstatistica(jogo, diretorio);
    GeraRanking(jogo, diretorio);
    GeraResumo(jogo, diretorio);
    DesalocaJogo(jogo);

    return 0;
}
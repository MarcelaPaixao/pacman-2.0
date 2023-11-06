#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tJogo.h"
#include "tArquivo.h"

#define GANHOU 1
#define PAC_MORREU 2

/**
 * Converte e retorna a direção passada como parâmetro para um inteiro;
 * \param direcao direcao
*/
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

/**
 * Imprime uma mensagem de acordo com o estado do jogo, podendo ser uma mensagem de vitória
 * ou de derrota;
 * \param jogo jogo;
*/
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

	//Se diretório não for informado, finaliza o programa;
	if (argc <= 1) {
		printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
		exit(0);
	}

	sprintf(diretorio, "%s", argv[1]);
    
    //Inicializa o jogo a partir do diretório informado;
    jogo = InicializaJogo(CriaMapa(diretorio));

    //Gera o arquivo de inicialização;
    GeraInicializacao(jogo);

    //Inicia o jogo e, enquanto não houver game over ou vitória, ele continua;
    while(1){
        scanf("%c", &direcao);
        comando = ConverteComando(direcao);

        //Executa a jogada lida acima;
        ExecutaJogada(jogo, comando);

        ImprimeEstadoAtualJogo(jogo, direcao);

        if(EhGameOver(jogo) || GanhouJogo(jogo)){
            ImprimeMsg(jogo);
            //Caso o pacman tenha morrido por fantasma, insere um novo movimento significativo 
            //com essa informação;
            if(ObtemEstadoJogo(jogo) == PAC_MORREU){
                InsereNovoMovimentoSignificativoPacman(ObtemPacman(jogo), comando, 
                                                       "fim de jogo por encostar em um fantasma");
            }
            break;
        }
        scanf("%*c");
    }
    
    //Gera os arquivos com as informações sobre o jogo antes de finalizar o programa;
    GeraTrilha(jogo);
    GeraEstatistica(jogo);
    GeraRanking(jogo);
    GeraResumo(jogo);
    DesalocaJogo(jogo);

    return 0;
}
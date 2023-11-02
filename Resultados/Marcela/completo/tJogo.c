#include "tJogo.h"

#define PACMAN '>'

tJogo* InicializaJogo(tMapa* mapa){
    tJogo* jogo = (tJogo*) malloc (sizeof(tJogo));

    if(jogo == NULL){
        return NULL;
    }
    jogo->estadoJogo = 0;
    jogo->mapa = mapa;
    jogo->fantB = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'B'), 'B');
    jogo->fantC = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'C'), 'C');
    jogo->fantI = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'I'), 'I');
    jogo->fantP = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'P'), 'P');
    jogo->pacman = CriaPacman(ObtemPosicaoItemMapa(mapa, PACMAN));
    CriaTrilhaPacman(jogo->pacman, ObtemNumeroLinhasMapa(jogo->mapa), ObtemNumeroColunasMapa(jogo->mapa));

    return jogo;
}

bool GanhouJogo(tJogo* jogo){
    if(ObtemQuantidadeFrutasIniciaisMapa(jogo->mapa) == ObtemPontuacaoAtualPacman(jogo->pacman)){
        jogo->estadoJogo = GANHOU;
        return true;
    }
    return false;
}

void ExecutaJogada(tJogo* jogo, COMANDO comando){
    tPosicao * posAntigaPac = ClonaPosicao(ObtemPosicaoPacman(jogo->pacman));
    MovePacman(jogo->pacman, jogo->mapa, comando);
    MoveFantasma(jogo->fantB, jogo->mapa);
    MoveFantasma(jogo->fantC, jogo->mapa);
    MoveFantasma(jogo->fantI, jogo->mapa);
    MoveFantasma(jogo->fantP, jogo->mapa);

    VerificaSeMatouPacmanFantasma(jogo->fantB, jogo->pacman, posAntigaPac); 
    VerificaSeMatouPacmanFantasma(jogo->fantC, jogo->pacman, posAntigaPac); 
    VerificaSeMatouPacmanFantasma(jogo->fantI, jogo->pacman, posAntigaPac); 
    VerificaSeMatouPacmanFantasma(jogo->fantP, jogo->pacman, posAntigaPac); 

    DesalocaPosicao(posAntigaPac);  
}

bool EhGameOver(tJogo* jogo){ 
    if(!EstaVivoPacman(jogo->pacman)){
        jogo->estadoJogo = PAC_MORREU;
        return true;
    }
    if(ObtemNumeroAtualMovimentosPacman(jogo->pacman) == ObtemNumeroMaximoMovimentosMapa(jogo->mapa)){
        if(ObtemPontuacaoAtualPacman(jogo->pacman) < ObtemQuantidadeFrutasIniciaisMapa(jogo->mapa)){
            return true;
        }
    }
    return false;
}

void ImprimeMapaJogo(tJogo* jogo){
    for (int i=0; i < ObtemNumeroLinhasMapa(jogo->mapa); i++) {
		for (int j=0; j < ObtemNumeroColunasMapa(jogo->mapa); j++) {
			printf("%c", jogo->mapa->grid[i][j]);
		}
		printf("\n");
	}
}

void ImprimeEstadoAtualJogo(tJogo* jogo, COMANDO comando){
    printf("Estado do jogo apos o movimento '%c':\n", comando);
    ImprimeMapaJogo(jogo);
    printf("Pontuacao: %d\n\n", ObtemPontuacaoAtualPacman(jogo->pacman));
}

void DesalocaJogo(tJogo* jogo){
    if(jogo != NULL){
        DesalocaMapa(jogo->mapa);
        DesalocaPacman(jogo->pacman);
        DesalocaFantasma(jogo->fantB);
        DesalocaFantasma(jogo->fantC);
        DesalocaFantasma(jogo->fantI);
        DesalocaFantasma(jogo->fantP);
    }
    free(jogo);
}

int ObtemEstadoJogo(tJogo* jogo){
    return jogo->estadoJogo;
}

tPacman* ObtemPacman(tJogo* jogo){
    return jogo->pacman;
}
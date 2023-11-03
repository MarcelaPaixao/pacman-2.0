#include "tJogo.h"

#define PACMAN '>'
#define VAZIO ' '
#define TUNEL '@'

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
    AtualizaTrilhaPacman(jogo->pacman);

    return jogo;
}

bool VerificaSeAtualiza(tJogo *jogo, tPosicao *posAntigaPac){
    if(ExisteFantasma(jogo->fantB) && SaoIguaisPosicao(ObtemPosicaoAtualFantasma(jogo->fantB), posAntigaPac)){
        return false;
    }
    if(ExisteFantasma(jogo->fantC) && SaoIguaisPosicao(ObtemPosicaoAtualFantasma(jogo->fantC), posAntigaPac)){
        return false;
    }
    if(ExisteFantasma(jogo->fantI) && SaoIguaisPosicao(ObtemPosicaoAtualFantasma(jogo->fantI), posAntigaPac)){
        return false;
    }
    if(ExisteFantasma(jogo->fantP) && SaoIguaisPosicao(ObtemPosicaoAtualFantasma(jogo->fantP), posAntigaPac)){
        return false;
    }

    return true; 
}

void ExecutaJogada(tJogo* jogo, COMANDO comando){

    MoveFantasma(jogo->fantB, jogo->mapa, jogo->pacman, comando);
    MoveFantasma(jogo->fantC, jogo->mapa, jogo->pacman, comando);
    MoveFantasma(jogo->fantI, jogo->mapa, jogo->pacman, comando);
    MoveFantasma(jogo->fantP, jogo->mapa, jogo->pacman, comando);

    tPosicao * posAntigaPac = ClonaPosicao(ObtemPosicaoPacman(jogo->pacman));
    MovePacman(jogo->pacman, jogo->mapa, comando);
    
    if(VerificaSeAtualiza(jogo, posAntigaPac)){
        AtualizaItemMapa(jogo->mapa, posAntigaPac, VAZIO);
    }//o problema ta em ouytro lugar q atualiza essa parte
    
    AtualizaItemMapa(jogo->mapa, ObtemPosicaoPacman(jogo->pacman), PACMAN);

    if (PossuiTunelMapa(jogo->mapa)){
        if (AcessouTunelMapa(jogo->mapa, posAntigaPac)){
            AtualizaItemMapa(jogo->mapa, posAntigaPac, TUNEL);
        }
    }

    VerificaSeMatouPacmanFantasma(jogo->mapa, jogo->fantB, jogo->pacman, posAntigaPac); 
    VerificaSeMatouPacmanFantasma(jogo->mapa, jogo->fantC, jogo->pacman, posAntigaPac); 
    VerificaSeMatouPacmanFantasma(jogo->mapa, jogo->fantI, jogo->pacman, posAntigaPac); 
    VerificaSeMatouPacmanFantasma(jogo->mapa, jogo->fantP, jogo->pacman, posAntigaPac); 

    DesalocaPosicao(posAntigaPac);  
}

bool GanhouJogo(tJogo* jogo){
    if(ObtemQuantidadeFrutasIniciaisMapa(jogo->mapa) == ObtemPontuacaoAtualPacman(jogo->pacman)){
        jogo->estadoJogo = GANHOU;
        return true;
    }
    return false;
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

void ImprimeEstadoAtualJogo(tJogo* jogo, char direcao){
    printf("Estado do jogo apos o movimento '%c':\n", direcao);
    for (int i=0; i < ObtemNumeroLinhasMapa(jogo->mapa); i++) {
		for (int j=0; j < ObtemNumeroColunasMapa(jogo->mapa); j++) {
			printf("%c", jogo->mapa->grid[i][j]);
		}
		printf("\n");
	}
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
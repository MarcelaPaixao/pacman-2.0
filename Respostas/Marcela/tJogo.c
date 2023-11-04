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

bool VerificaSeAtualizaVazio(tJogo *jogo, tPosicao *posAntigaPac){
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

void AtualizaFantasma(tJogo *jogo){
    if(ExisteFantasma(jogo->fantB) && TocouFrutaFantasma(jogo->fantB)){
        AtualizaItemMapa(jogo->mapa, ObtemPosicaoAtualFantasma(jogo->fantB), ObtemTipoFantasma(jogo->fantB));
    }
    if(ExisteFantasma(jogo->fantC) && TocouFrutaFantasma(jogo->fantC)){
        AtualizaItemMapa(jogo->mapa, ObtemPosicaoAtualFantasma(jogo->fantC), ObtemTipoFantasma(jogo->fantC));
    }
    if(ExisteFantasma(jogo->fantI) && TocouFrutaFantasma(jogo->fantI)){
        AtualizaItemMapa(jogo->mapa, ObtemPosicaoAtualFantasma(jogo->fantI), ObtemTipoFantasma(jogo->fantI));
    }
    if(ExisteFantasma(jogo->fantP) && TocouFrutaFantasma(jogo->fantP)){
        AtualizaItemMapa(jogo->mapa, ObtemPosicaoAtualFantasma(jogo->fantP), ObtemTipoFantasma(jogo->fantP));
    }
}

void ExecutaJogada(tJogo* jogo, COMANDO comando){

    MoveFantasma(jogo->fantB, jogo->mapa, comando);
    MoveFantasma(jogo->fantC, jogo->mapa, comando);
    MoveFantasma(jogo->fantI, jogo->mapa, comando);
    MoveFantasma(jogo->fantP, jogo->mapa, comando);

    tPosicao * posAntigaPac = ClonaPosicao(ObtemPosicaoPacman(jogo->pacman));
    
    if(VerificaSeAtualizaVazio(jogo, posAntigaPac)){
        AtualizaItemMapa(jogo->mapa, posAntigaPac, VAZIO);
    }
    
    MovePacman(jogo->pacman, jogo->mapa, comando);
    
    AtualizaFantasma(jogo);

    if (PossuiTunelMapa(jogo->mapa)){
        if (AcessouTunelMapa(jogo->mapa, posAntigaPac)){
        AtualizaItemMapa(jogo->mapa, posAntigaPac, TUNEL);
        }
    }

    AtualizaItemMapa(jogo->mapa, ObtemPosicaoPacman(jogo->pacman), PACMAN);

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
        DesalocaFantasmas(jogo->fantB);
        DesalocaFantasmas(jogo->fantC);
        DesalocaFantasmas(jogo->fantI);
        DesalocaFantasmas(jogo->fantP);
    }
    free(jogo);
}

int ObtemEstadoJogo(tJogo* jogo){
    return jogo->estadoJogo;
}

tPacman* ObtemPacman(tJogo* jogo){
    return jogo->pacman;
}
#include "tJogo.h"

#define PACMAN '>'


tJogo* InicializaJogo(tMapa* mapa){
    tJogo* jogo = (tJogo*) malloc (sizeof(tJogo));

    if(jogo == NULL){
        return NULL;
    }
    jogo->estadoJogo = ATIVO;
    jogo->mapa = mapa;
    jogo->fantB = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'B'), 'B');
    jogo->fantC = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'C'), 'C');
    jogo->fantI = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'I'), 'I');
    jogo->fantP = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'P'), 'P');
    jogo->pacman = CriaPacman(ObtemPosicaoItemMapa(mapa, PACMAN));

    return jogo;
}

bool GanhouJogo(tJogo* jogo){
    if(ObtemQuantidadeFrutasIniciaisMapa(jogo->mapa) == ObtemPontuacaoAtualPacman(jogo->pacman)){
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
}

bool EhGameOver(tJogo* jogo){ //chamar na main e caso tenha dado game over, verifica o motivo(estado do jogo)
    if(!EstaVivoPacman(jogo->pacman)){
        jogo->estadoJogo = PAC_MORREU;
        return true;
    }
    if(ObtemNumeroAtualMovimentosPacman(jogo->pacman) == ObtemNumeroMaximoMovimentosMapa(jogo->mapa)){
        if(ObtemPontuacaoAtualPacman(jogo->pacman) < ObtemQuantidadeFrutasIniciaisMapa(jogo->mapa)){
            jogo->estadoJogo = MOV_ESGOTADO;
            return true;
        }
    }
    return false;
}

bool GanhouJogo(tJogo* jogo){
    if(ObtemPontuacaoAtualPacman(jogo->pacman) == ObtemQuantidadeFrutasIniciaisMapa(jogo->mapa)){
        return true;
    }
    return false;
}

void ImprimeEstadoAtualJogo(tJogo* jogo);

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
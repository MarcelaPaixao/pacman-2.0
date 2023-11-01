#include "tFantasma.h"

/**
 * Cria o fantasma dinamicamente. Caso dê erro na alocação da estrutura tFantasma, 
 * retorna NULL. 
 * Caso a posição passada como parâmetro seja NULL, retorna NULL.
 * Caso não dê erros, retorna o ponteiro para o tFantasma alocado.
 * \param posicao Ponteiro para tPosicao
 */
tFantasma* CriaFantasma(tPosicao* posicao, char tipo){ //pode usar a obtem item mapa pra descobrir a posicao dele
    tFantasma * fantasma = (tFantasma *) malloc (sizeof(tFantasma));
    if(fantasma == NULL){
        return NULL;
    }
    
    fantasma->tipo = tipo;
    fantasma->tocaFruta = 0;
    fantasma->tocaParede = 0;
    fantasma->posicaoAntigaFant = NULL;
    fantasma->posicaoAtualFant = posicao;

    if(tipo == 'B'){
        fantasma->direcao = ESQUERDA;
    } 
    else if(tipo == 'C'){
        fantasma->direcao = DIREITA;
    }
    else if(tipo == 'I'){
        fantasma->direcao = BAIXO;
    }
    else if(tipo == 'P'){
        fantasma->direcao = CIMA;
    }

    return fantasma;
}

void InverteDirecaoFant(tFantasma* fantasma){
    fantasma->direcao = fantasma->direcao * (-1);
}

 /* Função que irá mover o fantasma no mapa, atualizando sua posição.
 * Dado o fantasma e o mapa,  a posição do fantasma é atualizada. 
 * Se o fantasma encontrou uma parede, ele muda a direção.
 * 
 * \param fantasma fantasma
 * \param mapa o mapa que contem os fantasmas
 */
void MoveFantasma(tFantasma* fantasma, tMapa* mapa){
    int lin = ObtemLinhaPosicao(fantasma->posicaoAtualFant);
    int col = ObtemColunaPosicao(fantasma->posicaoAtualFant);

    tPosicao * novaPosicao = NULL;
    tPosicao * PosicaoFinal = NULL;

    AtualizaPosicao(fantasma->posicaoAntigaFant, fantasma->posicaoAtualFant);

    if(fantasma->tocaFruta){
        AtualizaItemMapa(mapa, fantasma->posicaoAntigaFant, '*');
        fantasma->tocaFruta = 0;
    }

    if(fantasma->tipo == 'B' || fantasma->tipo == 'C'){
        novaPosicao = CriaPosicao(lin, col+fantasma->direcao);
        if(EncontrouParedeMapa(mapa, novaPosicao)){
            InverteDirecaoFant(fantasma);
            //fantasma->tocaParede = 1;
            PosicaoFinal = CriaPosicao(lin, ObtemColunaPosicao(fantasma->posicaoAntigaFant)+fantasma->direcao);
        }
        else {
            AtualizaPosicao(PosicaoFinal, novaPosicao);
        } 
    }

    if(fantasma->tipo == 'I' || fantasma->tipo == 'P'){
        novaPosicao = CriaPosicao(lin+fantasma->direcao, col);
        if(EncontrouParedeMapa(mapa, novaPosicao)){
            InverteDirecaoFant(fantasma);
            //fantasma->tocaParede = 1;
            PosicaoFinal = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAntigaFant)+fantasma->direcao, col);
        }
        else {
            AtualizaPosicao(PosicaoFinal, novaPosicao);
        } 
    }

    if(EncontrouFrutaMapa(mapa, PosicaoFinal)){
        fantasma->tocaFruta = 1;
    }
    else{
        fantasma->tocaFruta = 0;
    }

    char tipo = fantasma->tipo;
    AtualizaItemMapa(mapa, PosicaoFinal, tipo);
    
    AtualizaPosicao(fantasma->posicaoAtualFant, PosicaoFinal);
    
    if(novaPosicao != NULL){
        DesalocaPosicao(novaPosicao);
    }
    if(PosicaoFinal != NULL){
        DesalocaPosicao(PosicaoFinal);
    }
}

/**
 * Retorna verdadeiro se a posição do fantasma e a do pacman são iguais,
 * ou se eles se cruzaram, e falso caso contrário;
 *
 * \param fantasma fantasma
 * \param pacman pacman
 * \param posicao posição antiga do pacman
 */
bool MatouPacmanFantasma(tFantasma* fantasma, tPacman* pacman, tPosicao* posAntigaPacman){ //pac anda primeiro e mandar a posicao antiga do pacman, obtem item mapa
    if(SaoIguaisPosicao(ObtemPosicaoPacman(pacman), fantasma->posicaoAtualFant)){
        return true;
    }
    if(SaoIguaisPosicao(posAntigaPacman, fantasma->posicaoAtualFant) && 
       SaoIguaisPosicao(ObtemPosicaoPacman(pacman), fantasma->posicaoAntigaFant)){
        return true;
    }
    return false;
}

/*Função inutil
void AtualizaPosicaoFantasma(tFantasma* fantasma, tPosicao* posicaoNova){
    AtualizaPosicao(fantasma->posicaoAtualFant, posicaoNova);
}*/

/**
 * Caso o fantasma seja diferente de NULL, libera o espaço 
 * alocado para a estrutura tFantasma.
 * Sempre verificar se é NULL antes de dar free.
 * 
 * \param fantasma fantasma
 */
void DesalocaFantasma(tFantasma* fantasma){
    if(fantasma != NULL){
        DesalocaPosicao(fantasma->posicaoAtualFant);
        DesalocaPosicao(fantasma->posicaoAntigaFant);
        free(fantasma);
    }
}

/**
 * Retorna o tipo do fantasma.
 * 
 * \param fantasma fantasma
 */
char ObtemTipoFantasma(tFantasma* fantasma){
    return fantasma->tipo;
}

/**
 * Retorna a direção do fantasma.
 * 
 * \param fantasma fantasma
 */
int ObtemDirecaoFantasma(tFantasma* fantasma){
    return fantasma->direcao;
}

/**
 * Retorna verdadeiro se o fantasma está sobre fruta,
 * e falso caso contrário;
 *
 * \param fantasma fantasma
 */
bool TocouFrutaFantasma(tFantasma* fantasma){
    if(fantasma->tocaFruta){
        return true;
    }
    return false;
}

/**
 * Retorna verdadeiro se o fantasma tocou a parede,
 * e falso caso contrário;
 *
 * \param fantasma fantasma
 */
bool TocouParedeFantasma(tFantasma* fantasma){
    if(fantasma->tocaParede){
        return true;
    }
    return false;
}

/**
 * Retorna a posição atual do fantasma.
 * 
 * \param fantasma fantasma
 */
tPosicao* ObtemPosicaoAtualFantasma(tFantasma* fantasma){
    return fantasma->posicaoAtualFant;
}

/**
 * Retorna a posição antiga do fantasma.
 * 
 * \param fantasma fantasma
 */
tPosicao* ObtemPosicaoAntigaFantasma(tFantasma* fantasma){
    return fantasma->posicaoAntigaFant;
}

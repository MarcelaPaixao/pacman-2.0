#include "tFantasma.h"

#define PAC '>'
#define COMIDA '*'
#define VAZIO ' '

/**
 * Cria o fantasma dinamicamente. Caso dê erro na alocação da estrutura tFantasma, 
 * retorna NULL. 
 * Caso a posição passada como parâmetro seja NULL, retorna NULL.
 * Caso não dê erros, retorna o ponteiro para o tFantasma alocado.
 * \param posicao Ponteiro para tPosicao
 */
tFantasma* CriaFantasma(tPosicao* posicao, char tipo){ 
    tFantasma * fantasma = (tFantasma *) malloc (sizeof(tFantasma));
    if(fantasma == NULL){
        return NULL;
    }
    else if(posicao == NULL){
        fantasma->existe = 0;
        fantasma->posicaoAntigaFant = NULL;
        fantasma->posicaoAtualFant = NULL;
    }
    else {
        fantasma->tipo = tipo;
        fantasma->existe = 1;
        fantasma->tocaFruta = 0;
        fantasma->posicaoAntigaFant = CriaPosicao(-1, -1);
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
void MoveFantasma(tFantasma* fantasma, tMapa* mapa, tPacman* pacman, tPosicao* posAntigaPacman, COMANDO comando){
    if(fantasma->existe){
        int lin = ObtemLinhaPosicao(fantasma->posicaoAtualFant);
        int col = ObtemColunaPosicao(fantasma->posicaoAtualFant);
        int jaAtualizouMapa=0;

        tPosicao * novaPosicao = NULL;
        tPosicao * PosicaoFinal = NULL;

        AtualizaPosicao(fantasma->posicaoAntigaFant, fantasma->posicaoAtualFant);

        if(fantasma->tocaFruta){
            if(SaoIguaisPosicao(ObtemPosicaoPacman(pacman), fantasma->posicaoAntigaFant)){
             //   AtualizaItemMapa(mapa, fantasma->posicaoAntigaFant, PAC);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
               if(comando == MOV_ESQUERDA){
                   pacman->nFrutasComidasEsquerda++;
               }
               if(comando == MOV_DIREITA){
                   pacman->nFrutasComidasDireita++;
               }
               if(comando == MOV_BAIXO){
                   pacman->nFrutasComidasBaixo++;
              }
              if(comando == MOV_CIMA){
                  pacman->nFrutasComidasCima++;
             }
            }
            else {
                AtualizaItemMapa(mapa, fantasma->posicaoAntigaFant, COMIDA);
            }
            fantasma->tocaFruta = 0;
            jaAtualizouMapa = 1;
        }

        if(fantasma->tipo == 'B' || fantasma->tipo == 'C'){
            novaPosicao = CriaPosicao(lin, col+fantasma->direcao);
            if(EncontrouParedeMapa(mapa, novaPosicao)){
                InverteDirecaoFant(fantasma);
                PosicaoFinal = CriaPosicao(lin, ObtemColunaPosicao(fantasma->posicaoAntigaFant)+fantasma->direcao);
            }
            else {
                PosicaoFinal = CriaPosicao(-1, -1);
                AtualizaPosicao(PosicaoFinal, novaPosicao);
            } 
        }

        if(fantasma->tipo == 'I' || fantasma->tipo == 'P'){
            novaPosicao = CriaPosicao(lin+fantasma->direcao, col);
            if(EncontrouParedeMapa(mapa, novaPosicao)){
                InverteDirecaoFant(fantasma);
                PosicaoFinal = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAntigaFant)+fantasma->direcao, col);
            }
            else {
                PosicaoFinal = CriaPosicao(-1, -1);
                AtualizaPosicao(PosicaoFinal, novaPosicao);
            } 
        }

        if(EncontrouComidaMapa(mapa, PosicaoFinal)){
            fantasma->tocaFruta = 1;
        }
        else{
            fantasma->tocaFruta = 0;
        }

        AtualizaItemMapa(mapa, PosicaoFinal, fantasma->tipo);
    
        if(!jaAtualizouMapa){
            AtualizaItemMapa(mapa, fantasma->posicaoAntigaFant, VAZIO);
        }
    
        AtualizaPosicao(fantasma->posicaoAtualFant, PosicaoFinal);
    
        if(novaPosicao != NULL){
            DesalocaPosicao(novaPosicao);
        }
        if(PosicaoFinal != NULL){
            DesalocaPosicao(PosicaoFinal);
        }
    }
}


void VerificaSeMatouPacmanFantasma(tMapa* mapa, tFantasma* fantasma, tPacman* pacman, tPosicao* posAntigaPacman){ 
    if(fantasma->existe){
        if(SaoIguaisPosicao(ObtemPosicaoPacman(pacman), fantasma->posicaoAtualFant)){
            MataPacman(pacman);
        }
        if(SaoIguaisPosicao(posAntigaPacman, fantasma->posicaoAtualFant) && 
            SaoIguaisPosicao(ObtemPosicaoPacman(pacman), fantasma->posicaoAntigaFant)){
            MataPacman(pacman);
        }
        if(!SaoIguaisPosicao(posAntigaPacman, fantasma->posicaoAtualFant) && 
            SaoIguaisPosicao(ObtemPosicaoPacman(pacman), fantasma->posicaoAntigaFant)){
            AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');
        }
    }
}

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

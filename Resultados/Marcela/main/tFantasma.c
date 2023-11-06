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
 * \param tipo tipo do fantasma
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
    
    //Inicaliza o fantasma, preenchendo suas variáveis de acordo com as informações
    //passadas como parâmetro;
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

/**
 * Inverte a direção do fantasma. Por exemplo: Caso seja direita, sua direção passa a ser esquerda;
 * \param fantasma fantasma
 */
void InverteDirecaoFant(tFantasma* fantasma){
    fantasma->direcao = fantasma->direcao * (-1);
}

/**
 *  Função que irá mover o fantasma no mapa, atualizando sua posição.
 * Dado o fantasma e o mapa, a posição do fantasma é atualizada. 
 * Se o fantasma encontrou uma parede, ele muda a direção.
 * \param fantasma fantasma
 * \param mapa o mapa que contem os fantasmas
 */
void MoveFantasma(tFantasma* fantasma, tMapa* mapa){
    //Caso o fantasma exista, realiza as atualizações;
    if(fantasma->existe){
        int lin = ObtemLinhaPosicao(fantasma->posicaoAtualFant);
        int col = ObtemColunaPosicao(fantasma->posicaoAtualFant);
        int jaAtualizouMapa=0;

        tPosicao * novaPosicao = NULL;
        tPosicao * PosicaoFinal = NULL;

        //Atualiza a variável de posição anterior do fantasma com a posição que ele está atualmente;
        AtualizaPosicao(fantasma->posicaoAntigaFant, fantasma->posicaoAtualFant);

        //Verifica se ele estava sobre a fruta na posição anterior;
        if(fantasma->tocaFruta){
            AtualizaItemMapa(mapa, fantasma->posicaoAntigaFant, COMIDA);
            fantasma->tocaFruta = 0;
            jaAtualizouMapa = 1;
        }

        //Realiza o próximo movimento de acordo com o tipo do fantasma;
        //Caso ncontre parede, inverte a direção;
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

        //Informa se encontrou ou não comida na nova posição e, somente se não tiver encontrado, 
        //atualiza a posição atual do fantasma no mapa com seu caracter;
        if(EncontrouComidaMapa(mapa, PosicaoFinal)){
            fantasma->tocaFruta = 1;
        }
        else{
            fantasma->tocaFruta = 0;
            AtualizaItemMapa(mapa, PosicaoFinal, fantasma->tipo);
        }

        AtualizaPosicao(fantasma->posicaoAtualFant, PosicaoFinal);
    
        //Caso a posição antiga do fantasma no mapa não tenha sido atualizada com comida 
        //no início da função, atualiza agora com um espaço em branco;
        if(!jaAtualizouMapa){
            AtualizaItemMapa(mapa, fantasma->posicaoAntigaFant, VAZIO);
        }
    
        if(novaPosicao != NULL){
            DesalocaPosicao(novaPosicao);
        }
        if(PosicaoFinal != NULL){
            DesalocaPosicao(PosicaoFinal);
        }
    }
}

/**
 *  Função que irá verificar se o fantasma matou o pacman e garantir que eles não se cruzaram;
 * \param mapa o mapa que contem os fantasmas
 * \param fantasma fantasma
 * \param pacman pacman
 * \param posAntigaPcman posição anterior do pacman
 */
void VerificaSeMatouPacmanFantasma(tMapa* mapa, tFantasma* fantasma, tPacman* pacman, tPosicao* posAntigaPacman){ 
     //Caso o fantasma exista, realiza as atualizações;
    if(fantasma->existe){

        //Se as posições do fantasma e do pacman forem iguais, atualiza o mapa com 
        // o char do fantasme e seta o pacman para morto;
        if(SaoIguaisPosicao(ObtemPosicaoPacman(pacman), fantasma->posicaoAtualFant)){
            AtualizaItemMapa(mapa, fantasma->posicaoAtualFant, fantasma->tipo);
            MataPacman(pacman);
        }

        //Se o pacman e o fantasma se cruzaram, atualiza a posição atual do fantasma no mapa
        //com seu char e a posição do pacman no mapa com espaço em branco, 
        //e seta o pacman para morto;
        if(SaoIguaisPosicao(posAntigaPacman, fantasma->posicaoAtualFant) && 
            SaoIguaisPosicao(ObtemPosicaoPacman(pacman), fantasma->posicaoAntigaFant)){
            AtualizaItemMapa(mapa, fantasma->posicaoAtualFant, fantasma->tipo);
            AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), VAZIO);
            MataPacman(pacman);
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
void DesalocaFantasmas(tFantasma* fantasma){
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
 * Retorna verdadeiro se o fantasma existe,
 * e falso caso contrário;
 *
 * \param fantasma fantasma
 */
bool ExisteFantasma(tFantasma* fantasma){
    if(fantasma->existe){
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

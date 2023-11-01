#define DIREITA 1
#define ESQUERDA -1
#define BAIXO 2
#define CIMA -2

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
    
    fantasma->tipo = tipo;
    fantasma->tocaFruta = 0;
    fantasma->tocaParede = 0;
    fantasma->posicaoAntigaFant = NULL:
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

 /* Função que irá mover o fantasma no mapa, atualizando sua posição.
 * Dado o fantasma e o mapa,  a posição do fantasma é atualizada. 
 * Se o fantasma encontrou uma parede, ele muda a direção.
 * 
 * \param fantasma fantasma
 * \param mapa o mapa que contem os fantasmas
 */
void MoveFantasma(tFantasma* fantasma, tMapa* mapa);
//pode usar a obtem tipo e obtem direcao aqui dentro pra saber pra onde ele vai;

/**
 * Retorna verdadeiro se a posição do fantasma e a do pacman são iguais,
 * ou se eles se cruzaram, e falso caso contrário;
 *
 * \param fantasma fantasma
 * \param pacman pacman
 */
bool MatouPacmanFantasma(tFantasma* fantasma, tPacman* pacman);

/**
 * Chama a função AtualizaPosição do tPosicao;
 * \param fantasma fantasma
 * \param posicaoNova posição nova
 */
void AtualizaPosicaoFantasma(tFantasma* fantasma, tPosicao* posicaoNova){
    AtualizaPosicao(fantasma->posicaoAtualFant, posicaoNova);
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

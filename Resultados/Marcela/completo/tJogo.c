#include "tJogo.h"

#define PACMAN '>'
#define VAZIO ' '
#define TUNEL '@'

/**
 * Cria o jogo dinamicamente. Caso dê erro na alocação da estrutura tJogo, 
 * retorna NULL. 
 * Caso não dê erros, retorna o ponteiro para o tJogo alocado.
 * \param mapa Ponteiro para o mapa
 */
tJogo* InicializaJogo(tMapa* mapa){
    tJogo* jogo = (tJogo*) malloc (sizeof(tJogo));

    if(jogo == NULL){
        return NULL;
    }
    
    //Inicaliza o jogo, preenchendo suas variáveis de acordo com as informações
    //do mapa passado como parâmetro;
    jogo->estadoJogo = 0;
    jogo->mapa = mapa;
    jogo->fantB = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'B'), 'B');
    jogo->fantC = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'C'), 'C');
    jogo->fantI = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'I'), 'I');
    jogo->fantP = CriaFantasma(ObtemPosicaoItemMapa(mapa, 'P'), 'P');
    jogo->pacman = CriaPacman(ObtemPosicaoItemMapa(mapa, PACMAN));

    //Inicializa a trilha e preenche a primeira posição com o número atual de movimentos 
    //do pacman (que é 0), na posição em que ele incicia;
    CriaTrilhaPacman(jogo->pacman, ObtemNumeroLinhasMapa(jogo->mapa), ObtemNumeroColunasMapa(jogo->mapa));
    AtualizaTrilhaPacman(jogo->pacman);

    return jogo;
}

/**
 * Retorna verdadeiro se for necessário atualizar a posição passada como parâmetro
 * com um espaço vazio no mapa, e falso caso esse posição já seja ocupada por um dos
 * fantasmas do jogo;
 * \param jogo Ponteiro para o jogo
 * \param posAntigaPac Ponteiro para a posição anterior do pacman
 */
bool VerificaSeAtualizaVazio(tJogo *jogo, tPosicao *posAntigaPac){
    //Para cada fantasma, verifica se ele existe e se sua posição é igual à passada como parâmetro;
    //Se um deles for, já retorna falso;
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

/**
 * Após o movimento do pacman, verifica se algum fantasma está setado como tocando uma fruta, e 
 * caso esteja, atualiza sua posição no mapa com seu determinado caracter;
 * \param jogo Ponteiro para o jogo
 */
void AtualizaFantasma(tJogo *jogo){
    //Para cada fantasma, verifica se ele existe e se está tocando uma fruta;
    //Caso esteja, atualiza sua posição no mapa, até então ocupada por um caracter de fruta,
    //com o caracter do fantasma;
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

/**
 * Executa a jogada de acordo com o comando passado, fazendo as atualizações
 * necessrárias no mapa e nas posições do pacman e dos fantasmas;
 * \param jogo Ponteiro para o jogo
 * \param comando comando
 */
void ExecutaJogada(tJogo* jogo, COMANDO comando){
    //Primeiro se movem os fantasmas;
    MoveFantasma(jogo->fantB, jogo->mapa);
    MoveFantasma(jogo->fantC, jogo->mapa);
    MoveFantasma(jogo->fantI, jogo->mapa);
    MoveFantasma(jogo->fantP, jogo->mapa);

    //Obtem a posição do pacman antes de realizar o novo movimento;
    tPosicao * posAntigaPac = ClonaPosicao(ObtemPosicaoPacman(jogo->pacman));
    
    //Caso a função retorne verdadeiro, atualiza a posição antiga do pacman
    //com um espaço em branco;
    if(VerificaSeAtualizaVazio(jogo, posAntigaPac)){
        AtualizaItemMapa(jogo->mapa, posAntigaPac, VAZIO);
    }
    
    MovePacman(jogo->pacman, jogo->mapa, comando);
    
    //Após mover o pacman, verifica se é preciso atualizar algum fantasma no mapa;
    AtualizaFantasma(jogo);

    //Caso o  pacman tenha acessado o túnel, atualiza o mapa de acordo;
    if(PossuiTunelMapa(jogo->mapa)){
        if(AcessouTunelMapa(jogo->mapa, posAntigaPac)){
            AtualizaItemMapa(jogo->mapa, posAntigaPac, TUNEL);
        }
    }

    //Atualiza a posição do pacman no mapa com seu caracter;
    AtualizaItemMapa(jogo->mapa, ObtemPosicaoPacman(jogo->pacman), PACMAN);

    //Verifica se algum fantasma matou o pacman;
    VerificaSeMatouPacmanFantasma(jogo->mapa, jogo->fantB, jogo->pacman, posAntigaPac); 
    VerificaSeMatouPacmanFantasma(jogo->mapa, jogo->fantC, jogo->pacman, posAntigaPac); 
    VerificaSeMatouPacmanFantasma(jogo->mapa, jogo->fantI, jogo->pacman, posAntigaPac); 
    VerificaSeMatouPacmanFantasma(jogo->mapa, jogo->fantP, jogo->pacman, posAntigaPac); 

    DesalocaPosicao(posAntigaPac);  
}

/**
 * Retorna verdadeiro se o pacman obteve todas as frutas do mapa, e falso caso contrário;
 * \param jogo Ponteiro para o jogo
 */
bool GanhouJogo(tJogo* jogo){
    if(ObtemQuantidadeFrutasIniciaisMapa(jogo->mapa) == ObtemPontuacaoAtualPacman(jogo->pacman)){
        jogo->estadoJogo = GANHOU;
        return true;
    }
    return false;
}

/**
 * Retorna verdadeiro se o pacman está setado como morto, ou se o número máximo de 
 * jogadas foi atingido sem que o jogador obtivesse todas as frutas, e falso caso contrário;
 * \param jogo Ponteiro para o jogo
 */
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

/**
 * Imprime o estado em que se encontra o jogo após cada movimento; 
 * \param jogo Ponteiro para o jogo
 * \param direcao direção da jogada do usuário
 */
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

/**
 * Caso seja diferente de NULL, desaloca a estrutura tJogo passada;
 * \param jogo Ponteiro para o jogo
 */
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

/**
 * Retorna o estado do jogo;
 * \param jogo Ponteiro para o jogo
 */
int ObtemEstadoJogo(tJogo* jogo){
    return jogo->estadoJogo;
}

/**
 * Retorna o ponteiro para o pacman da estrutura tJogo;
 * \param jogo Ponteiro para o jogo
 */
tPacman* ObtemPacman(tJogo* jogo){
    return jogo->pacman;
}
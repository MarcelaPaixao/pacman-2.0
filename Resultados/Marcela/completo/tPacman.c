#include "tPacman.h"

#define VIVO 1
#define MORTO 0

#define ESQUERDA 0
#define CIMA 1
#define BAIXO 2
#define DIREITA 3

#define PAC '>'

/**
 * Cria o pacman dinamicamente. Caso dê erro na alocação da estrutura tPacman, 
 * retorna NULL. 
 * Caso a posição passada como parâmetro seja NULL, retorna NULL.
 * Caso não dê erros, retorna o ponteiro para o tPacman alocado.
 * \param posicao Ponteiro para tPosicao
 */
tPacman* CriaPacman(tPosicao* posicao){
    tPacman * pacman = (tPacman *) malloc (sizeof(tPacman));
    if(pacman == NULL || posicao == NULL){
        return NULL;
    }
    //pacman->posicaoAtual = CriaPosicao(ObtemLinhaPosicao(posicao), ObtemColunaPosicao(posicao));
    pacman->posicaoAtual = posicao;
    pacman->historicoDeMovimentosSignificativos = (tMovimento **) malloc (sizeof(tMovimento*));
    pacman->trilha = NULL;
    pacman->estaVivo = VIVO;
    pacman->nMovimentosBaixo = 0;
    pacman->nFrutasComidasBaixo = 0;
    pacman->nColisoesParedeBaixo = 0;
    pacman->nMovimentosCima = 0;
    pacman->nFrutasComidasCima = 0;
    pacman->nColisoesParedeCima = 0;
    pacman->nMovimentosEsquerda = 0;
    pacman->nFrutasComidasEsquerda = 0;
    pacman->nColisoesParedeEsquerda = 0;
    pacman->nMovimentosDireita = 0;
    pacman->nFrutasComidasDireita = 0;
    pacman->nColisoesParedeDireita = 0;
    pacman->nMovimentosSignificativos = 0;
    pacman->nLinhasTrilha = 0;
    pacman->nColunasTrilha = 0;
    
    return pacman;
}

/**
 * Clona o pacman dinamicamente, apenas com relação a posição.
 * Aloca outro pacman apenas copiando as informações de linha e coluna do original (passado como parâmetro).
 * \param pacman pacman
 */
tPacman* ClonaPacman(tPacman* pacman){
    tPacman * clone = CriaPacman(pacman->posicaoAtual);
    return clone;
}

/**
 * Clona a lista historico de movimentos significativos do pacman.
 * Aloca dinamicamente todas as estruturas do histórico de
 * movimentos do pacman original (passado como parâmetro): a lista e os movimentos da lista.
 * E por fim copia as informações do histórico original para o clone.
 * Retorna um ponteiro para o tMovimento** clone.
 * \param pacman pacman
 */
tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman){
    tMovimento **cloneHistorico = (tMovimento **) malloc (sizeof(tMovimento*));
    cloneHistorico = pacman->historicoDeMovimentosSignificativos;
    return cloneHistorico;
}

/**
 * Retorna a posição do pacman.
 * 
 * \param pacman pacman
 */
tPosicao* ObtemPosicaoPacman(tPacman* pacman){
    return pacman->posicaoAtual;
}

/**
 * Retorna se o pacman está vivo ou morto.
 * 
 * \param pacman pacman
 */
int EstaVivoPacman(tPacman* pacman){
    return pacman->estaVivo;
}

/**
 * Função que irá mover o pacman no mapa, atualizando sua posição.
 * Dado o pacman, o mapa, e o comando do jogador, a posição do pacman
 * é atualizada. Consultas ao mapa deverão ser feitas para ver se
 * a posição pode ser realmente atualizada ou não, como por exemplo,
 * se o pacman encontrou uma parede ele não se move.
 * 
 * \param pacman pacman
 * \param mapa o mapa que contem o pacman
 * \param comando o comando para onde irá o pacman
 */
void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando){
    tPosicao * novaPosicao;
    int lin = ObtemLinhaPosicao(pacman->posicaoAtual);
    int col = ObtemColunaPosicao(pacman->posicaoAtual);
    int parede=0, fruta=0, tunel=0;
    
    if(PossuiTunelMapa(mapa)){
        tunel = 1;
    }
    
    if(comando == ESQUERDA){
        novaPosicao = CriaPosicao(lin, col-1);
        if(EncontrouParedeMapa(mapa, novaPosicao)){
            pacman->nColisoesParedeEsquerda++;
            parede = 1;
        }
        else if(tunel == 1 && (AcessouTunelMapa(mapa, novaPosicao))){
                EntraTunelMapa(mapa, novaPosicao);
                AtualizaItemMapa(mapa, novaPosicao, PAC);
        }
        else {
            if(EncontrouComidaMapa(mapa,novaPosicao)){
                pacman->nFrutasComidasEsquerda++;
                fruta = 1;
            }
            if(AtualizaItemMapa(mapa, novaPosicao, PAC)){
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                pacman->nMovimentosEsquerda++;
            }  
        }
    }

    else if(comando == DIREITA){
        novaPosicao = CriaPosicao(lin, col+1);
        if(EncontrouParedeMapa(mapa, novaPosicao)){
            pacman->nColisoesParedeDireita++;
            parede = 1;
        }
        else if(tunel == 1 && (AcessouTunelMapa(mapa, novaPosicao))){
                EntraTunelMapa(mapa, novaPosicao);
                AtualizaItemMapa(mapa, novaPosicao, PAC);
        }
        else {
            if(EncontrouComidaMapa(mapa,novaPosicao)){
                pacman->nFrutasComidasDireita++;
                fruta = 1;
            }
            if(AtualizaItemMapa(mapa, novaPosicao, PAC)){
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                pacman->nMovimentosDireita++;
            }  
        }
    }
    
    else if(comando == CIMA){
        novaPosicao = CriaPosicao(lin-1, col);
        if(EncontrouParedeMapa(mapa, novaPosicao)){
            pacman->nColisoesParedeCima++;
            parede = 1;
        }
        else if(tunel == 1 && (AcessouTunelMapa(mapa, novaPosicao))){
                EntraTunelMapa(mapa, novaPosicao);
                AtualizaItemMapa(mapa, novaPosicao, PAC);
        }
        else {
            if(EncontrouComidaMapa(mapa,novaPosicao)){
                pacman->nFrutasComidasCima++;
                fruta = 1;
            }
            if(AtualizaItemMapa(mapa, novaPosicao, PAC)){
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                pacman->nMovimentosCima++;
            }  
        }
    }

    else if(comando == BAIXO){
        novaPosicao = CriaPosicao(lin+1, col);
        if(EncontrouParedeMapa(mapa, novaPosicao)){
            pacman->nColisoesParedeBaixo++;
            parede = 1;
        }
        else if(tunel == 1 && (AcessouTunelMapa(mapa, novaPosicao))){
                EntraTunelMapa(mapa, novaPosicao);
                AtualizaItemMapa(mapa, novaPosicao, PAC);
        }
        else {
            if(EncontrouComidaMapa(mapa,novaPosicao)){
                pacman->nFrutasComidasBaixo++;
                fruta = 1;
            }
            if(AtualizaItemMapa(mapa, novaPosicao, PAC)){
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                pacman->nMovimentosBaixo++;
            }  
        }
    }
    
    if(parede > 0){
        pacman->nMovimentosSignificativos++;
        InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
    }
    if(fruta > 0){
        pacman->nMovimentosSignificativos++;
        InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
    }
    AtualizaTrilhaPacman(pacman);
    DesalocaPosicao(novaPosicao);
}

/**
 * Aloca a trilha dinamicamente.
 * Caso a trilha seja igual a NULL, a matriz int** deverá ser
 * alocada dinamicamente com os valores de linha e coluna.
 * 
 * \param pacman pacman
 * \param nLinhas número de linhas da trilha
 * \param nColunas número de colunas da trilha
 */
void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas){
    if(pacman->trilha == NULL){
        pacman->trilha = (int **)malloc(nLinhas * sizeof(int *));
        for (int i = 0; i < nLinhas; i++) {
            pacman->trilha[i] = (int *)malloc(nColunas * sizeof(int));
        }
        for(int i = 0; i < nLinhas; i++){
            for(int j = 0; j < nColunas; j++){
                pacman->trilha[i][j] = -1;
            }
        }
    }
}

/**
 * Atualiza na trilha a posição por onde passou o pacman.
 * Dado o pacman, com suas informações de posição e trilha na estrutura,
 * atualiza o item da trilha, referente a posição atual do pacman,
 * para o valor int correspondente ao número do movimento atual do pacman.
 * \param pacman pacman
 */
void AtualizaTrilhaPacman(tPacman* pacman){
    int lin=0, col=0;
    lin = ObtemLinhaPosicao(pacman->posicaoAtual);
    col = ObtemColunaPosicao(pacman->posicaoAtual);
    pacman->trilha[lin][col] = ObtemNumeroAtualMovimentosPacman(pacman);
}

/**
 * Salva a trilha em um arquivo na raíz junto com o binário.
 * 
 * \param pacman pacman
 */
void SalvaTrilhaPacman(tPacman* pacman){
    FILE *arq_trilha;
    char nome_trilha[1000];
    sprintf(nome_trilha, "saida/trilha.txt");
    arq_trilha = fopen(nome_trilha, "w");
    fclose(arq_trilha); 
}

/**
 * Insere na lista de movimentos um novo movimento significativo.
 * Dado o pacman, o comando do jogador, e a ação significativa,
 * cria um movimento significativo tMovimento com essas informações e
 * insere na lista de movimentos significativos do pacman.
 * 
 * \param pacman pacman
 * \param comando o comando do movimento
 * \param acao a ação do movimento
 */
void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao){
    pacman->nMovimentosSignificativos++;
    pacman->historicoDeMovimentosSignificativos = realloc(pacman->historicoDeMovimentosSignificativos, 
                                                          pacman->nMovimentosSignificativos * sizeof(tMovimento*));
    tMovimento * mov = CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando, acao);
    pacman->historicoDeMovimentosSignificativos[pacman->nMovimentosSignificativos-1] = mov;
}

/**
 * Seta pacman para morto.
 * 
 * \param pacman pacman
 */
void MataPacman(tPacman* pacman){
    pacman->estaVivo = MORTO;
}

/**
 * Caso o pacman seja diferente de NULL, libera o espaço 
 * alocado para a estrutura tPacman
 * 
 * \param pacman pacman
 */
void DesalocaPacman(tPacman* pacman){
    if(pacman != NULL){

        for(int i=0; i < pacman->nLinhasTrilha; i++){
            free(pacman->trilha[i]);
        }
        free(pacman->trilha);
        
        //for(int i=0; i < pacman->nMovimentosSignificativos; i++){
        //    DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
        //}
        free(pacman->historicoDeMovimentosSignificativos);
        
        DesalocaPosicao(pacman->posicaoAtual);

        free(pacman); 
    }
}

/**
 * Retorna o número atual de movimentos do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroAtualMovimentosPacman(tPacman* pacman){
    int totalMov=0;
    totalMov = pacman->nMovimentosBaixo + pacman->nMovimentosCima;
    totalMov += pacman->nMovimentosDireita + pacman->nMovimentosEsquerda;
    return totalMov;
}

/**
 * Retorna o número de movimentos sem pontuar do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosSemPontuarPacman(tPacman* pacman){
    int movSemPontos=0, movPontos=0;
    movPontos = pacman->nFrutasComidasBaixo + pacman->nFrutasComidasCima;
    movPontos += pacman->nFrutasComidasDireita + pacman->nFrutasComidasEsquerda; 
    // funcao só deve ser usada no final, ent a qtd de mov já vai ser a total
    movSemPontos = ObtemNumeroAtualMovimentosPacman(pacman) - movPontos;
    return movSemPontos;
}

/**
 * Retorna o número de colisões com a parede do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedePacman(tPacman* pacman){
    int totalMov=0;
    totalMov = pacman->nColisoesParedeBaixo + pacman->nColisoesParedeCima;
    totalMov += pacman->nColisoesParedeDireita + pacman->nColisoesParedeEsquerda;
    return totalMov;
}

/**
 * Retorna o número de movimentos para baixo do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosBaixoPacman(tPacman* pacman){
    return pacman->nMovimentosBaixo;
}

/**
 * Retorna o número de frutas comidas para baixo pelo pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroFrutasComidasBaixoPacman(tPacman* pacman){
    return pacman->nFrutasComidasBaixo;
}

/**
 * Retorna o número de colisões com a parede para baixo
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedeBaixoPacman(tPacman* pacman){
    return pacman->nColisoesParedeBaixo;
}

/**
 * Retorna o número de movimentos para baixo do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosCimaPacman(tPacman* pacman){
    return pacman->nMovimentosCima;
}

/**
 * Retorna o número de frutas comidas para cima pelo pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroFrutasComidasCimaPacman(tPacman* pacman){
    return pacman->nFrutasComidasCima;
}

/**
 * Retorna o número de colisões com a parede para cima
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedeCimaPacman(tPacman* pacman){
    return pacman->nColisoesParedeCima;
}

/**
 * Retorna o número de movimentos para a esquerda do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosEsquerdaPacman(tPacman* pacman){
    return pacman->nMovimentosEsquerda;
}

/**
 * Retorna o número de frutas comidas para a esquerda pelo pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroFrutasComidasEsquerdaPacman(tPacman* pacman){
    return pacman->nFrutasComidasEsquerda;
}

/**
 * Retorna o número de colisões com a parede para esquerda
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedeEsquerdaPacman(tPacman* pacman){
    return pacman->nColisoesParedeEsquerda;
}

/**
 * Retorna o número de movimentos para a direita do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosDireitaPacman(tPacman* pacman){
    return pacman->nMovimentosDireita;
}

/**
 * Retorna o número de frutas comidas para a direita pelo pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroFrutasComidasDireitaPacman(tPacman* pacman){
    return pacman->nFrutasComidasDireita;
}

/**
 * Retorna o número de colisões com a parede para direita
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedeDireitaPacman(tPacman* pacman){
     return pacman->nColisoesParedeDireita;
}

/**
 * Retorna o número de movimentos significativos do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosSignificativosPacman(tPacman* pacman){
    return pacman->nMovimentosSignificativos;
}

/**
 * Retorna a pontuação atual do pacman
 * 
 * \param pacman pacman
 */
int ObtemPontuacaoAtualPacman(tPacman* pacman){
    int pontos=0;
    pontos = pacman->nFrutasComidasBaixo + pacman->nFrutasComidasCima;
    pontos += pacman->nFrutasComidasEsquerda + pacman->nFrutasComidasDireita;
    return pontos;
}

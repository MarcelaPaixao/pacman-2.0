#include "tPacman.h"

#define VIVO 1
#define MORTO 0

typedef struct tPacman{
    /* Posição atual do pacman (linha,coluna) */
    tPosicao* posicaoAtual;

    /* Estado de vida do pacman: vivo ou morto */
    int estaVivo;

    /* Estatísticas para quando o pacman se move para baixo */
    int nMovimentosBaixo;
    int nFrutasComidasBaixo;
    int nColisoesParedeBaixo;

    /* Estatísticas para quando o pacman se move para cima */
    int nMovimentosCima;
    int nFrutasComidasCima;
    int nColisoesParedeCima;

    /* Estatísticas para quando o pacman se move para a esquerda */
    int nMovimentosEsquerda;
    int nFrutasComidasEsquerda;
    int nColisoesParedeEsquerda;

    /* Estatísticas para quando o pacman se move para a direita */
    int nMovimentosDireita;
    int nFrutasComidasDireita;
    int nColisoesParedeDireita;

    /* Histórico de movimentos significativos do pacman */
    int nMovimentosSignificativos;
    tMovimento** historicoDeMovimentosSignificativos;

    /* Trilha gerada pelos passos do pacman. */
    int nLinhasTrilha;
    int nColunasTrilha;
    int** trilha;
} tPacman;

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
    acman->posicaoAtual = posicao;
    
    //inicializr todo mundo
    return pacman;
}

/**
 * Clona o pacman dinamicamente, construtor de cópia.
 * Aloca outro pacman com as informaçoes do original (passado como parâmetro).
 * \param pacman pacman
 */
tPacman* ClonaPacman(tPacman* pacman){
    tPacman * clonePacman = CriaPacman(pacman->posicaoAtual);
    clonePacman = pacman; //pode fazer isso ou tem q passar um por um???
}

/**
 * Clona a lista historico de movimentos significativos do pacman.
 * Aloca dinamicamente todas as estruturas do histórico de
 * movimentos do pacman original (passado como parâmetro): a lista e os movimentos da lista.
 * E por fim copia as informações do histórico original para o clone.
 * Retorna um ponteiro para o tMovimento** clone.
 * \param pacman pacman
 */
tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman);

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
void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando);

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
    pacman->trilha = (int **)malloc(nLinhas * sizeof(int *));
    if(pacman->trilha == NULL){
        for (int i = 0; i < nLinhas; i++) {
            pacman->trilha[i] = (int *)malloc(nColunas * sizeof(int));
        }
    }
}//tá certo isso??

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
    sprintf(nome_trilha, "trilha.txt");
    arq_trilha = fopen(nome_trilha, "w");
    fclose(arq_trilha); // é aqui msm?
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
    pacman->historicoDeMovimentosSignificativos = realloc(pacman->historicoDeMovimentosSignificativos, 
                                                          pacman->nMovimentosSignificativos+1);
    tMovimento * mov = CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando, acao);
    pacman->historicoDeMovimentosSignificativos[pacman->nMovimentosSignificativos] = mov;

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
       free(pacman->trilha);
       DesalocaMovimento(pacman->historicoDeMovimentosSignificativos);
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

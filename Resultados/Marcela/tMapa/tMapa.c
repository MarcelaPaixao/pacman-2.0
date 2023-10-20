#include "tMapa.h"
#include <string.h>

#define COMIDA '*'
#define PAREDE '#'
//#define TUNEL '@'


/**
 * Dado o arquivo de configurações, cria o mapa dinamicamente e 
 * retorna um ponteiro para o tipo tMapa.
 * Caso o arquivo de configurações não exista, retorna NULL.
 * \param caminho caminho do arquivo com as configurações do mapa
 */
tMapa* CriaMapa(const char* caminhoConfig){
    tMapa * mapa = (tMapa *)malloc(sizeof(tMapa));

    FILE *arq_entrada, *map;
    char nome_diretorio[1009], nome_mapa[1009];

    // Se diretório nao for informado, finaliza o programa
    if (strlen(caminhoConfig) <= 1) {
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        exit(0);
    }
    sprintf(nome_diretorio, "%s", caminhoConfig);
    arq_entrada = fopen(nome_diretorio, "r");

    sprintf(nome_mapa, "%s/mapa.txt", nome_diretorio);
    map = fopen(nome_mapa, "r");
    
    // Verifica se eh possivel encontrar o arquivo 'mapa.txt' e
    // caso nao encontre, finaliza o programa
    if (!map) {
        printf("O arquivo mapa.txt do diretorio %s nao existe!\n", nome_diretorio);
        exit(0);
    }
    printf("oi");
    /*fscanf(map, "%d\n", &mapa->nMaximoMovimentos);

    mapa->nLinhas = 0;
    mapa->nColunas = 0;
    mapa->nFrutasAtual = 0;
    mapa->tunel = NULL;

    char simb = '0';
    int flagQuebraDeLinha = 0;
    while(!feof(map)){
        while(flagQuebraDeLinha != 1 && mapa->nLinhas == 0){
            fscanf(map,"%*c");
            fscanf(map,"%c", &simb);
            mapa->nColunas++;
            if(simb == '\n'){
                flagQuebraDeLinha = 1;
            }
        }
        mapa->nLinhas++;
    }
    printf("%d %d\n", mapa->nLinhas, mapa->nColunas);
    mapa->grid = (char **) malloc (mapa->nLinhas * sizeof(char*));
    for(int i = 0; i < mapa->nLinhas; i++){
        mapa->grid[i] = (char *) malloc (mapa->nColunas * sizeof(char));
    }
	
    int i, j;
    for(i = 0; i < mapa->nLinhas; i++){
        for(i = 0; j < mapa->nColunas; j++){
            fscanf(map,"%c", &mapa->grid[i][j]);
        }
    }*/
    fclose(arq_entrada);
    fclose(map);
    return mapa;
}

/**
 * Obtem a posição de um item do mapa.
 * Dado um item do tipo char, o mapa deverá ser varrido até encontrar o item.
 * Caso o item seja encontrado cria um tipo tPosição e retorna.
 * Caso o item não seja encontrado, retorna NULL.
 * \param mapa mapa
 * \param item item a ser procurado no mapa
 */
tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item){
    for(int i=0; i < mapa->nLinhas; i++){
        for(int j=0; j < mapa->nColunas; j++){
            if(mapa->grid[i][j] == item){
                tPosicao *posicao = CriaPosicao(i, j);
                return posicao;
            }
        }
    }
    return NULL;
}

/**
 * Retorna um ponteiro para o túnel da estrutura tMapa.
 * \param mapa mapa
 */
tTunel* ObtemTunelMapa(tMapa* mapa){
    return mapa->tunel;
}

int EhValidaPosicao(tMapa* mapa, tPosicao* posicao){
    if(ObtemLinhaPosicao(posicao) > mapa->nLinhas || 
       ObtemLinhaPosicao(posicao) < 0 || 
       ObtemColunaPosicao(posicao) > mapa->nColunas ||
       ObtemColunaPosicao(posicao) < 0){
        return 0;
    }
    return 1;
}

/**
 * Dado o mapa e uma posição, retorna o item do mapa relacionado a aquela posição.
 * Caso o mapa ou o grid do mapa seja NULL, ou a posição esteja fora dos limites do mapa,
 * retorna '\0'.
 * \param mapa mapa
 * \param posicao posicao do item a ser retornado
 */
char ObtemItemMapa(tMapa* mapa, tPosicao* posicao){
    if(mapa == NULL || mapa->grid == NULL || !EhValidaPosicao(mapa, posicao)){
        return '\0';
    }
    return mapa->grid[posicao->linha][posicao->coluna];
}

/**
 * Retorna o número de linhas do mapa.
 * \param mapa mapa
 */
int ObtemNumeroLinhasMapa(tMapa* mapa){
    return mapa->nLinhas;
}

/**
 * Retorna o número de colunas do mapa
 * \param mapa mapa
 */
int ObtemNumeroColunasMapa(tMapa* mapa){
    return mapa->nColunas;
}

/**
 * Retorna a quantidade de frutas iniciais do mapa
 * \param mapa mapa
 */
int ObtemQuantidadeFrutasIniciaisMapa(tMapa* mapa){
    return mapa->nFrutasAtual;
    //ABRIR O ARQUIVO DNV P VERIFICAR A QTD INICIAL?
}

/**
 * Retorna o número máximo de movimentos permitidos do mapa
 * \param mapa mapa
 */
int ObtemNumeroMaximoMovimentosMapa(tMapa* mapa){
        return mapa->nMaximoMovimentos;
}

/**
 * Retorna se a posição passada como parâmetro representa uma comida no mapa.
 * Caso o grid do mapa seja NULL, ou a posição esteja fora dos limites do mapa,
 * retorna falso.
 * Caso a posição não represente uma comida, também retorna falso.
 * \param mapa mapa
 * \param posicao posicao a ser verificada
 */
bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao){
    if(mapa == NULL || mapa->grid == NULL || !EhValidaPosicao(mapa, posicao)){
        return false;
    }
    return(mapa->grid[posicao->linha][posicao->coluna] == COMIDA);
}

/**
 * Retorna se a posição passada como parâmetro representa uma parede no mapa.
 * Caso o grid do mapa seja NULL, ou a posição esteja fora dos limites do mapa,
 * retorna falso.
 * Caso a posição não represente uma parede, também retorna falso.
 * \param mapa mapa
 * \param posicao posicao a ser verificada
 */
bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao){
    if(mapa == NULL || mapa->grid == NULL || !EhValidaPosicao(mapa, posicao)){
        return false;
    }
    return(mapa->grid[posicao->linha][posicao->coluna] == PAREDE);
}

/**
 * Dado o mapa, uma posição e um item, atualiza a posição do mapa com aquele item.
 * Caso o mapa ou o grid do mapa seja NULL, ou a posição esteja fora dos limites do mapa,
 * retorna falso. 
 * Se conseguiu atualizar o item com sucesso, retorna verdadeiro.
 * \param mapa mapa
 * \param posicao posicao do item
 * \param item posicao item que vai atualizar o mapa
 */
bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item){
    if(mapa == NULL || mapa->grid == NULL || !EhValidaPosicao(mapa, posicao)){
        return false;
    }
    mapa->grid[posicao->linha][posicao->coluna] = item;
    return true;
}

/**
 * Verifica se o mapa possui tunel ou não.
 * Caso o campo tunel seja NULL retorna falso.
 * Caso contrário retorna verdadeiro.
 * \param mapa mapa
 */
bool PossuiTunelMapa(tMapa* mapa){
    if(mapa->tunel != NULL){ 
        return true;
    }
    return false;
}

/**
 * Apenas chama a função EntrouTunel na estrutura tTunel.h
 * \param mapa mapa
 * \param posicao posicao a ser verificada
 */
bool AcessouTunelMapa(tMapa* mapa, tPosicao* posicao){
    return(EntrouTunel(mapa->tunel, posicao));
}

/**
 * Apenas chama a função LevaFinalTunel na estrutura tTunel.h
 * \param mapa mapa
 * \param posicao posicao que vai entrar no túnel
 */
void EntraTunelMapa(tMapa* mapa, tPosicao* posicao){
    LevaFinalTunel(mapa->tunel, posicao);
}

/**
 * Libera o espaço alocado para a estrutura tMapa.
 * Apenas desaloca o mapa caso o mapa seja diferente de NULL.
 * \param mapa mapa
 */
void DesalocaMapa(tMapa* mapa){
    for(int i=0; i < mapa->nLinhas; i++){
        free(mapa->grid[i]);
    }
    DesalocaTunel(mapa->tunel); 
    free(mapa->grid);
    free(mapa);
}
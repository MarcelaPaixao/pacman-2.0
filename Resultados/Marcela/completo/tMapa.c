#include "tMapa.h"
#include <stdio.h>
#include <stdlib.h>

#define COMIDA '*'
#define PAREDE '#'
#define TUNEL '@'

/**
 * Dado o arquivo de configurações, cria o mapa dinamicamente e 
 * retorna um ponteiro para o tipo tMapa.
 * Caso o arquivo de configurações não exista, retorna NULL.
 * \param caminho caminho do arquivo com as configurações do mapa
 */
tMapa* CriaMapa(const char* caminhoConfig) {
    FILE *arq_mapa;
    char nome_mapa[1000];

    sprintf(nome_mapa, "%s/mapa.txt", caminhoConfig);
    arq_mapa = fopen(nome_mapa, "r");

    if (arq_mapa == NULL) {
        printf("O arquivo mapa.txt do diretorio %s nao existe!\n", caminhoConfig);
        return NULL;
    }
    
    tMapa * mapa = (tMapa *) malloc(sizeof(tMapa));

    int linha=0, coluna=0, fruta=0, tunel=0;
    int l_tunel1=0, l_tunel2=0, c_tunel1=0, c_tunel2=0; 

    fscanf(arq_mapa, "%d\n", &mapa->nMaximoMovimentos);
    
    mapa->grid = malloc(sizeof(char *)); 
    mapa->grid[0] = NULL;
    char simb;
    while(1){
        fscanf(arq_mapa, "%c", &simb);
        if(simb == '\n'){
            break;
        }
        coluna++;
        mapa->grid[0] = realloc(mapa->grid[0], coluna * sizeof(char));
        mapa->grid[0][coluna - 1] = simb; 
        if(simb == COMIDA){
            fruta++;
        }
    }
    
    while(fscanf(arq_mapa, "%c", &simb) == 1){
        linha++;
        mapa->grid = realloc(mapa->grid, (linha+1) * sizeof(char*)); 
        mapa->grid[linha] = malloc (coluna * sizeof(char));
        mapa->grid[linha][0] = simb;
        if(simb == COMIDA){
            fruta++;
        }
        for(int i=1; i < coluna; i++){
            fscanf(arq_mapa, "%c", &simb);
            if(simb != '\n'){
                mapa->grid[linha][i] = simb;  
                if(simb == COMIDA){
                    fruta++;
                }
                else if(simb == TUNEL){
                    if(tunel == 0){
                        l_tunel1 = linha;
                        c_tunel1 = i;
                        tunel = 1;
                    }
                    else {
                        l_tunel2 = linha;
                        c_tunel2 = i;
                    }
                }
            }
        } 
        fscanf(arq_mapa, "%*c");
    }
    fscanf(arq_mapa, "%*c");
    mapa->tunel = NULL;
    mapa->tunel = CriaTunel(l_tunel1 , c_tunel1, l_tunel2, c_tunel2);
    mapa->nLinhas = linha+1;
    mapa->nColunas = coluna;
    mapa->nFrutasAtual = fruta;
    
    fclose(arq_mapa);
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
    return mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)];
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
    return(mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)] == COMIDA);
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
    return(mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)] == PAREDE);
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
    mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)] = item;
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
    if(mapa != NULL){
        for(int i=0; i < mapa->nLinhas; i++){
            free(mapa->grid[i]);
        }
        free(mapa->grid);
        DesalocaTunel(mapa->tunel); 
        free(mapa);
    }
}
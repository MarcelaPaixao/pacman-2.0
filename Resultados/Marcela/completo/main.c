#include "tMapa.h"
#include <stdio.h>

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

    if (caminhoConfig == NULL) {
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        return NULL;
    }

    sprintf(nome_mapa, "%s/mapa.txt", caminhoConfig);
    arq_mapa = fopen(nome_mapa, "r");

    if (arq_mapa == NULL) {
        printf("O arquivo mapa.txt do diretorio %s nao existe!\n", caminhoConfig);
        return NULL;
    }
    
    tMapa * mapa = (tMapa *) malloc(sizeof(tMapa));

    int linha=1, coluna=0, fruta=0, tunel=0;
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
    
    fscanf(arq_mapa, "%*c");
    
    while(fscanf(arq_mapa, "%c", &simb) == 1){
        linha++;
        mapa->grid = realloc(mapa->grid, linha * sizeof(char*)); 
        mapa->grid[linha-1] = malloc (coluna * sizeof(char));
        mapa->grid[linha-1][0] = simb;
        if(simb == COMIDA){
            fruta++;
        }
        for(int i=1; i < coluna; i++){
            fscanf(arq_mapa, "%c", &simb);
            if(simb != '\n'){
                mapa->grid[linha-1][i] = simb;  
                if(simb == COMIDA){
                    fruta++;
                }
                else if(simb == TUNEL){
                    if(tunel = 0){
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
    mapa->nLinhas = linha;
    mapa->nColunas = coluna;
    mapa->nFrutasAtual = fruta;
    
    fclose(arq_mapa);
    return mapa;
    
}

int main(){
    char diret[1000] = "Casos/01";
    tMapa * mapa = CriaMapa(diret);
    return 0;
}
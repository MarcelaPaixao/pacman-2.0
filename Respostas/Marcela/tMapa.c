#include "tMapa.h"

#define COMIDA '*'
#define PAREDE '#'
//#define TUNEL '@'

typedef struct tMapa{
    /* Número de linhas e de colunas do mapa
       que deverão ser preenchidos com as informações 
       no arquivo de configurações 
       do mapa, passado na função CriaMapa */
    int nLinhas, nColunas;

    /* Número atual de frutas no mapa 
       que deverá ser preenchido com a informação no arquivo 
       de configurações do mapa, passado na função CriaMapa.
       Deverá ser atualizada a medida que o jogo prossegue */
    int nFrutasAtual;

    /* Número máximo permitido de movimentos do pacman no mapa
       que deverá ser preenchido com a informação no arquivo 
       de configurações do mapa, passado na função CriaMapa */
    int nMaximoMovimentos;

    /* O grid (matriz) de informações do mapa
       que deverá ser alocado dinamicamente e preenchido
       com as informações do arquivo de configurações 
       do mapa, passado na função CriaMapa */
    char** grid;

    /* O tunel do mapa contendo 2 acessos 
       que deverão ser preenchidos com as informações 
       no arquivo de configurações 
       do mapa, passado na função CriaMapa*/
    tTunel* tunel;
} tMapa;

/**
 * Dado o arquivo de configurações, cria o mapa dinamicamente e 
 * retorna um ponteiro para o tipo tMapa.
 * Caso o arquivo de configurações não exista, retorna NULL.
 * \param caminho caminho do arquivo com as configurações do mapa
 */
tMapa* CriaMapa(const char* caminhoConfig){
    tMapa * mapa = (tMapa *)malloc(sizeof(tMapa));
    
    mapa->tunel = NULL;

    


    /*tMapa InicializaJogo(FILE *entrada, char *dir) {
	FILE *inicializa;
	tMapa mapa;
	int i, j, comida = 0, l_inicial, c_inicial;
	char simb[40][100], nome_dir[1000];
	
	// Armazena nas variaveis adequadas as informacoes do arquivo de entrada
	fscanf(entrada, "%d", &mapa.limite_mov);
	fscanf(entrada, "\n");
	sprintf(nome_dir, "%s/saida/inicializacao.txt", dir);
	inicializa = fopen(nome_dir, "w");

	mapa.game_over = 0;
	mapa.comida = 0;
	mapa.qtd_parede = 0;
	mapa.tunel = 0;
	
	// Lê o arquivo de entrada e preenche arquivo de inicializacao
	for (i = 0; i < mapa.linhas; i++) {
		for (j = 0; j < mapa.colunas; j++) {

			fscanf(entrada, "%c", &simb[i][j]);
			fprintf(inicializa, "%c", simb[i][j]);
			mapa.matriz[i][j] = simb[i][j];
			// Preenche toda a matriz trilha com -1
			mapa.trilha[i][j] = -1;
			
			// Inicializa tipo Jogador e tipo Fantasma
			if (simb[i][j] == '>') {
				l_inicial = i;
				c_inicial = j;
				mapa.trilha[i][j] = 0;
				mapa.pacman = InicializaJogador(i, j, mapa.pacman);
			} else if (simb[i][j] == 'B') {
				mapa.fant_B = InicializaFantasma(i, j, simb[i][j], mapa.fant_B);
			} else if (simb[i][j] == 'P') {
				mapa.fant_P = InicializaFantasma(i, j, simb[i][j], mapa.fant_P);
			} else if (simb[i][j] == 'I') {
				mapa.fant_I = InicializaFantasma(i, j, simb[i][j], mapa.fant_I);
			} else if (simb[i][j] == 'C') {
				mapa.fant_C = InicializaFantasma(i, j, simb[i][j], mapa.fant_C);
			} else if (simb[i][j] == '*') {
				mapa.comida++; // Conta qtd total de comida
			}
		}
		fscanf(entrada, "\n");
		fprintf(inicializa, "\n");
	}
	fprintf(inicializa, "Pac-Man comecara o jogo na linha %d e coluna %d\n",
			l_inicial + 1, c_inicial + 1);
	fclose(inicializa);
	return mapa;
}*/
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
void AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item){
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
#include "tArquivo.h"

void GeraInicializacao(tJogo* jogo){
    FILE *inicializacao;
    char diretInicializacao[1000];
    sprintf(diretInicializacao, "inicializacao.txt"); 
	inicializacao = fopen(diretInicializacao, "w");

    int lin = ObtemLinhaPosicao(ObtemPosicaoPacman(ObtemPacman(jogo)));
    int col = ObtemColunaPosicao(ObtemPosicaoPacman(ObtemPacman(jogo)));

    //ImprimeMapaJogo(jogo);
    for (int i=0; i < ObtemNumeroLinhasMapa(jogo->mapa); i++) {
		for (int j=0; j < ObtemNumeroColunasMapa(jogo->mapa); j++) {
			printf("%c", jogo->mapa->grid[i][j]);
		}
		printf("\n");
	}
    fprintf(inicializacao, "Pac-Man comecara o jogo na linha %d e coluna %d\n",
			lin + 1, col + 1);

    fclose(inicializacao);
}

void GeraTrilha(tJogo* jogo){
    SalvaTrilhaPacman(ObtemPacman(jogo));
}

void GeraEstatistica(tJogo* jogo){
    FILE *estatistica;
    char diretEstatistica[1000];
    sprintf(diretEstatistica, "estatisticas.txt"); 
	estatistica = fopen( diretEstatistica, "w");

    fprintf(estatistica,"Numero de movimentos: %d\n", ObtemNumeroAtualMovimentosPacman(ObtemPacman(jogo)));
	fprintf(estatistica,"Numero de movimentos sem pontuar: %d\n", ObtemNumeroMovimentosSemPontuarPacman(ObtemPacman(jogo)));
	fprintf(estatistica,"Numero de colisoes com parede: %d\n", ObtemNumeroColisoesParedePacman(ObtemPacman(jogo)));
	fprintf(estatistica,"Numero de movimentos para baixo: %d\n", ObtemNumeroMovimentosBaixoPacman(ObtemPacman(jogo)));
	fprintf(estatistica,"Numero de movimentos para cima: %d\n", ObtemNumeroMovimentosCimaPacman(ObtemPacman(jogo)));
	fprintf(estatistica,"Numero de movimentos para esquerda: %d\n", ObtemNumeroMovimentosEsquerdaPacman(ObtemPacman(jogo)));
	fprintf(estatistica,"Numero de movimentos para direita: %d\n", ObtemNumeroMovimentosDireitaPacman(ObtemPacman(jogo)));

    fclose(estatistica);
}

void GeraRanking(tJogo* jogo){
    FILE *ranking;
    char diretRanking[1000];
    sprintf(diretRanking, "ranking.txt"); 
    ranking = fopen( diretRanking, "w");



    fclose(ranking);
}

void GeraResumo(tJogo* jogo){
    FILE *resumo;
    char diretResumo[1000];
    sprintf(diretResumo, "resumo.txt"); 
    resumo = fopen( diretResumo, "w");

    tMovimento **historico = ClonaHistoricoDeMovimentosSignificativosPacman(ObtemPacman(jogo));

    for(int i=0; i < ObtemNumeroMovimentosSignificativosPacman(ObtemPacman(jogo)); i++){
        printf("Movimento %d ", historico[i]->numeroDoMovimento);
        if(historico[i]->comando == MOV_ESQUERDA){
            printf("(a) ");
        }
         if(historico[i]->comando == MOV_CIMA){
            printf("(w) ");
        }
         if(historico[i]->comando == MOV_BAIXO){
            printf("(s) ");
        }
         if(historico[i]->comando == MOV_DIREITA){
            printf("(d) ");
        }
        printf("%s\n", historico[i]->acao);
    }

    for(int i=0; i < ObtemNumeroMovimentosSignificativosPacman(ObtemPacman(jogo)); i++){
        DesalocaMovimento(historico[i]);
    }
    free(historico);

    fclose(resumo);
}
#include "tArquivo.h"

void GeraInicializacao(tJogo* jogo, char *diretorio){
    FILE *inicializacao;
    char diretInicializacao[1000];
    sprintf(diretInicializacao, "%s/inicializacao.txt", diretorio); 
	inicializacao = fopen(diretInicializacao, "w");

    int lin = ObtemLinhaPosicao(ObtemPosicaoPacman(ObtemPacman(jogo)));
    int col = ObtemColunaPosicao(ObtemPosicaoPacman(ObtemPacman(jogo)));

    ImprimeMapaJogo(jogo);
    fprintf(inicializacao, "Pac-Man comecara o jogo na linha %d e coluna %d\n",
			lin + 1, col + 1);

    fclose(inicializacao);
}

void GeraTrilha(tJogo* jogo){
    SalvaTrilhaPacman(ObtemPacman(jogo));
}

void GeraEstatistica(tJogo* jogo, char *diretorio){
    FILE *estatistica;
    char diretEstatistica[1000];
    sprintf(diretEstatistica, "%s/estatisticas.txt", diretorio); 
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

void GeraRanking(tJogo* jogo, char *diretorio){
    FILE *ranking;
    char diretRanking[1000];
    sprintf(diretRanking, "%s/ranking.txt", diretorio); 
    ranking = fopen( diretRanking, "w");



    fclose(ranking);
}

void GeraResumo(tJogo* jogo, char *diretorio){
    FILE *resumo;
    char diretResumo[1000];
    sprintf(diretResumo, "%s/ranking.txt", diretorio); 
    resumo = fopen( diretResumo, "w");

    tMovimento **historico = ClonaHistoricoDeMovimentosSignificativosPacman(ObtemPacman(jogo));

    for(int i=0; i < ObtemNumeroMovimentosSignificativosPacman(ObtemPacman(jogo)); i++){
        printf("Movimento %d ", historico[i]->numeroDoMovimento);
        printf("(%c) ", historico[i]->comando);
        printf("%s\n", historico[i]->acao);
    }

    fclose(resumo);
}
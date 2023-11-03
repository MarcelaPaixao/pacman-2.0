#include "tArquivo.h"

void GeraInicializacao(tJogo* jogo){
    FILE *inicializacao;
    char diretInicializacao[1000];
    sprintf(diretInicializacao, "inicializacao.txt"); 
	inicializacao = fopen(diretInicializacao, "w");

    int lin = ObtemLinhaPosicao(ObtemPosicaoPacman(ObtemPacman(jogo)));
    int col = ObtemColunaPosicao(ObtemPosicaoPacman(ObtemPacman(jogo)));

    for (int i=0; i < ObtemNumeroLinhasMapa(jogo->mapa); i++) {
		for (int j=0; j < ObtemNumeroColunasMapa(jogo->mapa); j++) {
			fprintf(inicializacao, "%c", jogo->mapa->grid[i][j]);
		}
		fprintf(inicializacao, "\n");
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

    tComandos mov[4], aux;
    mov[0].frutas = ObtemNumeroFrutasComidasEsquerdaPacman(ObtemPacman(jogo));
    mov[0].colisoes = ObtemNumeroColisoesParedeEsquerdaPacman(ObtemPacman(jogo));
    mov[0].usos = ObtemNumeroMovimentosEsquerdaPacman(ObtemPacman(jogo));
    mov[0].tipo = 'a';
    
    mov[1].frutas = ObtemNumeroFrutasComidasCimaPacman(ObtemPacman(jogo));
    mov[1].colisoes = ObtemNumeroColisoesParedeCimaPacman(ObtemPacman(jogo));
    mov[1].usos = ObtemNumeroMovimentosCimaPacman(ObtemPacman(jogo));
    mov[1].tipo = 'w';

    mov[2].frutas = ObtemNumeroFrutasComidasBaixoPacman(ObtemPacman(jogo));
    mov[2].colisoes = ObtemNumeroColisoesParedeBaixoPacman(ObtemPacman(jogo));
    mov[2].usos = ObtemNumeroMovimentosBaixoPacman(ObtemPacman(jogo));
    mov[2].tipo = 's'; 

    mov[3].frutas = ObtemNumeroFrutasComidasDireitaPacman(ObtemPacman(jogo));
    mov[3].colisoes = ObtemNumeroColisoesParedeDireitaPacman(ObtemPacman(jogo));
    mov[3].usos = ObtemNumeroMovimentosDireitaPacman(ObtemPacman(jogo));
    mov[3].tipo = 'd';

    int n=4, max;
    for (int i = 0; i < n - 1; i++) {
		max = i;
		// Procura pelo maior no restante do vetor
		for (int j = i + 1; j < n; j++) {
			// Compara os elementos mov[j] e mov[max] de acordo com os criterios:
			// maior qtd de frutas obtidas com o movimento, menor qtd de colisoes, 
			// maior qtd de usos e ordem alfabetica;
			if (mov[j].frutas > mov[max].frutas ||
				mov[j].frutas == mov[max].frutas && mov[j].colisoes < mov[max].colisoes ||
				mov[j].frutas == mov[max].frutas && mov[j].colisoes == mov[max].colisoes 
				&& mov[j].usos > mov[max].usos ||
				mov[j].frutas == mov[max].frutas && mov[j].colisoes == mov[max].colisoes 
				&& mov[j].usos == mov[max].usos && mov[j].tipo < mov[max].tipo) {
					
			// Atualiza o indice do maior elemento
			max = j;
			}
		}
		// Faz a troca 
		aux = mov[i];
		mov[i] = mov[max];
		mov[max] = aux;
	}

	for (int i = 0; i < n; i++) {
		fprintf(ranking,"%c,%d,%d,%d\n", 
				mov[i].tipo, mov[i].frutas,
				mov[i].colisoes, mov[i].usos);
	}

    fclose(ranking);
}

void GeraResumo(tJogo* jogo){
    FILE *resumo;
    char diretResumo[1000];
    sprintf(diretResumo, "resumo.txt"); 
    resumo = fopen( diretResumo, "w");

    tMovimento **historico = ClonaHistoricoDeMovimentosSignificativosPacman(ObtemPacman(jogo));

    for(int i=0; i < ObtemNumeroMovimentosSignificativosPacman(ObtemPacman(jogo)); i++){
        fprintf(resumo, "Movimento %d ", historico[i]->numeroDoMovimento);
        if(historico[i]->comando == MOV_ESQUERDA){
            fprintf(resumo, "(a) ");
        }
         if(historico[i]->comando == MOV_CIMA){
            fprintf(resumo, "(w) ");
        }
         if(historico[i]->comando == MOV_BAIXO){
            fprintf(resumo, "(s) ");
        }
         if(historico[i]->comando == MOV_DIREITA){
            fprintf(resumo, "(d) ");
        }
        fprintf(resumo, "%s\n", historico[i]->acao);
    }

    for(int i=0; i < ObtemNumeroMovimentosSignificativosPacman(ObtemPacman(jogo)); i++){
        DesalocaMovimento(historico[i]);
    }
    free(historico);

    fclose(resumo);
}
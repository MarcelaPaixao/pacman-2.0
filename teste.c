tMapa* CriaMapa(const char* caminhoConfig) {
    FILE *arq_entrada, *arq_mapa;
    char nome_diretorio[1000], nome_mapa[1000];

    if (caminhoConfig == NULL) {
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        return NULL;
    }

    strcpy(nome_diretorio, caminhoConfig);
    arq_entrada = fopen(nome_diretorio, "r");

    if (arq_entrada == NULL) {
        printf("ERRO: O arquivo de configuracao nao pode ser aberto\n");
        return NULL;
    }

    sprintf(nome_mapa, "%s/mapa.txt", nome_diretorio);
    arq_mapa = fopen(nome_mapa, "r");

    if (arq_mapa == NULL) {
        printf("O arquivo mapa.txt do diretorio %s nao existe!\n", nome_diretorio);
        fclose(arq_entrada);
        exit(0);
    }
    
    tMapa * mapa = (tMapa *) malloc(sizeof(tMapa));
    if (mapa == NULL) {
        printf("ERRO: Falha na alocacao de memoria para mapa\n");
        exit(0);
    }
    mapa->nColunas = 0;
    mapa->nLinhas = 0;
    mapa->grid = NULL;
    mapa->grid[0] = NULL;
    fscanf(arq_mapa, "%d\n", &mapa->nMaximoMovimentos);
    
    char simb = '0';
    while(!feof(arq_mapa)){
        while(simb != '\n'){
            fscanf(arq_mapa, "%c", &simb);
            mapa->nColunas++;
        }
        fscanf(arq_mapa, "%*c");
        mapa->nLinhas++;
    }

    mapa->grid = (char **)malloc(mapa->nLinhas * sizeof(char *));
    for (int i = 0; i < mapa->nLinhas; i++) {
        mapa->grid[i] = (char *)malloc(mapa->nColunas * sizeof(char));
    }

    for (int i = 0; i < mapa->nLinhas; i++) {
        for (int j = 0; j < mapa->nColunas; j++) {
            simb = fscanf(arq_mapa, "%c", &simb);
            if(simb != '\n'){
                mapa->grid[i][j] = simb;
            }
            else if(simb == '\n'){
                fscanf(arq_mapa, "%*c");
            }
        }
    }

    fclose(arq_entrada);
    fclose(arq_mapa);
    return mapa;
    
}

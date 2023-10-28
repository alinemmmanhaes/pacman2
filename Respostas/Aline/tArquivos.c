#include "tArquivos.h"

tPosicao* Inicializacao(const char* diretorio, tMapa* mapa){
    FILE * pInicializacao;
    char dirinicio[1000];
    sprintf(dirinicio, "%s/inicializacao.txt", diretorio);
    pInicializacao = fopen(dirinicio, "w");

    tPosicao* posicao = NULL;
    int x = 0, y = 0;
    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
        for(int j=0; j<ObtemNumeroColunasMapa; j++){
            fprintf(pInicializacao, "%c", mapa->grid[i][j]);
            if(mapa->grid[i][j] == '>'){
                x = i;
                y = j;
                posicao = CriaPosicao(i, j);
            }
        }
        fprintf(pInicializacao, "\n");
    }
    fprintf(pInicializacao, "Pac-Man comecara o jogo na linha %d e coluna %d", x+1, y+1);

    fclose(pInicializacao);
    return posicao;
}

tMovimento** Resumo(tPacman* pacman, const char* diretorio){
    tMovimento** resumo = NULL;
    resumo = ClonaHistoricoDeMovimentosSignificativosPacman(pacman);
    for(int i=0; i<ObtemNumeroMovimentosSignificativosPacman(pacman); i++){
        printf("Movimento %d (%c) %s\n", resumo[i]->numeroDoMovimento, resumo[i]->comando, resumo[i]->acao);
    }
    return resumo;
}


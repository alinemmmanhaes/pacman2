#include "tArquivos.h"

tPosicao* Inicializacao(const char* diretorio, tMapa* mapa){
    FILE * pInicializacao;
    char dirinicio[1000];
    sprintf(dirinicio, "inicializacao.txt");
    pInicializacao = fopen(dirinicio, "w");

    tPosicao* posicao = NULL;
    int x = 0, y = 0;
    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
        for(int j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            fprintf(pInicializacao, "%c", mapa->grid[i][j]);
            if(mapa->grid[i][j] == '>'){
                x = i;
                y = j;
                posicao = CriaPosicao(i, j);
            }
        }
        fprintf(pInicializacao, "\n");
    }
    fprintf(pInicializacao, "Pac-Man comecara o jogo na linha %d e coluna %d\n", x+1, y+1);

    fclose(pInicializacao);
    return posicao;
}

tMovimento** Resumo(tPacman* pacman, const char* diretorio){
    FILE * pResumo;
    tMovimento** resumo = NULL;

    char diresumo[1000], comando;
    sprintf(diresumo, "resumo.txt");
    pResumo = fopen(diresumo, "w");

    resumo = ClonaHistoricoDeMovimentosSignificativosPacman(pacman);
    for(int i=0; i<ObtemNumeroMovimentosSignificativosPacman(pacman); i++){
        if(resumo[i]->comando == MOV_BAIXO){
            comando = 's';
        }
        else if(resumo[i]->comando == MOV_CIMA){
            comando = 'w';
        }
        else if(resumo[i]->comando == MOV_DIREITA){
            comando = 'd';
        }
        else if(resumo[i]->comando == MOV_ESQUERDA){
            comando = 'a';
        }
        fprintf(pResumo, "Movimento %d (%c) %s\n", resumo[i]->numeroDoMovimento, comando, resumo[i]->acao);
    }

    fclose(pResumo);
    return resumo;
}

void Estatisticas(tPacman* pacman){
    FILE * pEstatistica;
    char direstatistica[1000];
    sprintf(direstatistica, "estatisticas.txt");
    pEstatistica = fopen(direstatistica, "w");

    fprintf(pEstatistica, "Numero de movimentos: %d\n", ObtemNumeroAtualMovimentosPacman(pacman));
    fprintf(pEstatistica, "Numero de movimentos sem pontuar: %d\n", ObtemNumeroMovimentosSemPontuarPacman(pacman));
    fprintf(pEstatistica, "Numero de colisoes com parede: %d\n", ObtemNumeroColisoesParedePacman(pacman));
    fprintf(pEstatistica, "Numero de movimentos para baixo: %d\n", ObtemNumeroMovimentosBaixoPacman(pacman));
    fprintf(pEstatistica, "Numero de movimentos para cima: %d\n", ObtemNumeroMovimentosCimaPacman(pacman));
    fprintf(pEstatistica, "Numero de movimentos para esquerda: %d\n", ObtemNumeroMovimentosEsquerdaPacman(pacman));
    fprintf(pEstatistica, "Numero de movimentos para direita: %d\n", ObtemNumeroMovimentosDireitaPacman(pacman));

    fclose(pEstatistica);
}

void Ranking(tPacman* pacman){
    tRanking* ranking = malloc(4*sizeof(tRanking));
    char op;
    int indice = -1, fruta = -1, parede = -1, total = -1;

    ranking[0].mov = 'a';
    ranking[0].frutas = ObtemNumeroFrutasComidasEsquerdaPacman(pacman);
    ranking[0].parede = ObtemNumeroColisoesParedeEsquerdaPacman(pacman);
    ranking[0].numero = ObtemNumeroMovimentosEsquerdaPacman(pacman);
    ranking[1].mov = 'd';
    ranking[1].frutas = ObtemNumeroFrutasComidasDireitaPacman(pacman);
    ranking[1].parede = ObtemNumeroColisoesParedeDireitaPacman(pacman);
    ranking[1].numero = ObtemNumeroMovimentosDireitaPacman(pacman);
    ranking[2].mov = 's';
    ranking[2].frutas = ObtemNumeroFrutasComidasBaixoPacman(pacman);
    ranking[2].parede = ObtemNumeroColisoesParedeBaixoPacman(pacman);
    ranking[2].numero = ObtemNumeroMovimentosBaixoPacman(pacman);
    ranking[3].mov = 'w';
    ranking[3].frutas = ObtemNumeroFrutasComidasCimaPacman(pacman);
    ranking[3].parede = ObtemNumeroColisoesParedeCimaPacman(pacman);
    ranking[3].numero = ObtemNumeroMovimentosCimaPacman(pacman);

    
}
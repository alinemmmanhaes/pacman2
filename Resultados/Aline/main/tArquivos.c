#include "tArquivos.h"

tPosicao* Inicializacao(tMapa* mapa){
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

void Resumo(tPacman* pacman){
    FILE * pResumo;
    tMovimento** resumo = NULL;

    char diresumo[1000], comando;
    sprintf(diresumo, "resumo.txt");
    pResumo = fopen(diresumo, "w");

    resumo = ClonaHistoricoDeMovimentosSignificativosPacman(pacman);
    for(int i=0; i<ObtemNumeroMovimentosSignificativosPacman(pacman); i++){
        if(ObtemComandoMovimento(resumo[i]) == MOV_BAIXO){
            comando = 's';
        }
        else if(ObtemComandoMovimento(resumo[i]) == MOV_CIMA){
            comando = 'w';
        }
        else if(ObtemComandoMovimento(resumo[i]) == MOV_DIREITA){
            comando = 'd';
        }
        else if(ObtemComandoMovimento(resumo[i]) == MOV_ESQUERDA){
            comando = 'a';
        }
        fprintf(pResumo, "Movimento %d (%c) %s\n", ObtemNumeroMovimento(resumo[i]), comando, ObtemAcaoMovimento(resumo[i]));
    }

    DesalocaResumo(resumo, pacman);
    fclose(pResumo);
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

    tRanking melhor;
    FILE* pRanking;
    char diranking[1000];
    sprintf(diranking, "ranking.txt");
    pRanking = fopen(diranking, "w");

    for(int i=0; i<4; i++){
        melhor.mov = ranking[i].mov;
        indice = i;
        melhor.frutas = ranking[i].frutas;
        melhor.parede = ranking[i].parede;
        melhor.numero = ranking[i].numero;
        for(int j=i+1; j<4; j++){
            if(ranking[j].frutas > melhor.frutas){
                melhor.mov = ranking[j].mov;
                indice = j;
                melhor.frutas = ranking[j].frutas;
                melhor.parede = ranking[j].parede;
                melhor.numero = ranking[j].numero;
            }
            else if(ranking[j].frutas == melhor.frutas){
                if(ranking[j].parede < melhor.parede){
                    melhor.mov = ranking[j].mov;
                    indice = j;
                    melhor.frutas = ranking[j].frutas;
                    melhor.parede = ranking[j].parede;
                    melhor.numero = ranking[j].numero;
                }
                else if(ranking[j].parede == melhor.parede){
                    if(ranking[j].numero > melhor.numero){
                        melhor.mov = ranking[j].mov;
                        indice = j;
                        melhor.frutas = ranking[j].frutas;
                        melhor.parede = ranking[j].parede;
                        melhor.numero = ranking[j].numero;
                    }
                    else if(ranking[j].numero == melhor.numero){
                        if(ranking[j].mov < melhor.mov){
                            melhor.mov = ranking[j].mov;
                            indice = j;
                            melhor.frutas = ranking[j].frutas;
                            melhor.parede = ranking[j].parede;
                            melhor.numero = ranking[j].numero;
                        }
                    }
                }
            }
        }
        fprintf(pRanking, "%c,%d,%d,%d\n", melhor.mov, melhor.frutas, melhor.parede, melhor.numero);
        ranking[indice] = ranking[i];
        ranking[i] = melhor;
    }

    DesalocaRanking(ranking);
    fclose(pRanking);
}

void DesalocaRanking(tRanking* ranking){
    if(ranking != NULL){
        free(ranking);
    }
}

void DesalocaResumo(tMovimento** resumo, tPacman* pacman){
    if(resumo != NULL){
        for(int i=0; i<ObtemNumeroMovimentosSignificativosPacman(pacman); i++){
            if(resumo[i] != NULL){
                DesalocaMovimento(resumo[i]);
            }
        }
        free(resumo);
    }
}
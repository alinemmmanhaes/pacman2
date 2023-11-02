#include "tArquivos.h"

tPosicao* Inicializacao(tMapa* mapa){
    FILE * pInicializacao; //gera arquivo de inicializacao
    char dirinicio[1000];
    sprintf(dirinicio, "inicializacao.txt");
    pInicializacao = fopen(dirinicio, "w");

    tPosicao* posicaopm = NULL;
    int x = 0, y = 0;
    char c;
    //roda o mapa e o imprime no arquivo
    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
        for(int j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            //Cria uma posicao para acessar item da posicao sem usar mapa->grid
            tPosicao* posicao = CriaPosicao(i, j);
            c = ObtemItemMapa(mapa, posicao);
            fprintf(pInicializacao, "%c", c);
            if(c == '>'){ //armazena a posicao inicial do pacman e suas coordenadas
                x = i;
                y = j;
                posicaopm = CriaPosicao(i, j);
            }
            DesalocaPosicao(posicao);
        }
        fprintf(pInicializacao, "\n");
    }
    //imprime no arquivo a posicao inicial do pacman
    fprintf(pInicializacao, "Pac-Man comecara o jogo na linha %d e coluna %d\n", x+1, y+1);

    fclose(pInicializacao);
    return posicaopm; //retorna posicao inicial do pacman
}

void Resumo(tPacman* pacman){
    FILE * pResumo; //gera arquivo de resumo
    tMovimento** resumo = NULL;

    char diresumo[1000], comando;
    sprintf(diresumo, "resumo.txt");
    pResumo = fopen(diresumo, "w");

    resumo = ClonaHistoricoDeMovimentosSignificativosPacman(pacman);
    for(int i=0; i<ObtemNumeroMovimentosSignificativosPacman(pacman); i++){
        //traduz o tipo COMANDO do movimento lido para char
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
        //printa movimento significativo no arquivo
        fprintf(pResumo, "Movimento %d (%c) %s\n", ObtemNumeroMovimento(resumo[i]), comando, ObtemAcaoMovimento(resumo[i]));
    }

    DesalocaResumo(resumo, pacman);
    fclose(pResumo);
}

void Estatisticas(tPacman* pacman){
    FILE * pEstatistica; //gera arquivo de estatisticas
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
    //cria vetor de movimentos (tRanking) alocado dinamicamente
    tRanking* ranking = malloc(4*sizeof(tRanking));
    char op;
    int indice = -1, fruta = -1, parede = -1, total = -1;

    //passa as informacoes da cada movimento para o vetor
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
    FILE* pRanking; //gera arquivo de ranking
    char diranking[1000];
    sprintf(diranking, "ranking.txt");
    pRanking = fopen(diranking, "w");

    //ordena os movimentos
    for(int i=0; i<4; i++){
        //o primeiro movimento analisado é o melhor ate o momento
        melhor.mov = ranking[i].mov;
        indice = i;
        melhor.frutas = ranking[i].frutas;
        melhor.parede = ranking[i].parede;
        melhor.numero = ranking[i].numero;
        for(int j=i+1; j<4; j++){
            //se a quantidade de frutas (pontos) pegas for maior, esse movimento se torna o novo melhor
            if(ranking[j].frutas > melhor.frutas){
                melhor.mov = ranking[j].mov;
                indice = j;
                melhor.frutas = ranking[j].frutas;
                melhor.parede = ranking[j].parede;
                melhor.numero = ranking[j].numero;
            }
            else if(ranking[j].frutas == melhor.frutas){
                //se a quantidade de colisoes na parede for menor, esse movimento se torna o novo melhor
                if(ranking[j].parede < melhor.parede){
                    melhor.mov = ranking[j].mov;
                    indice = j;
                    melhor.frutas = ranking[j].frutas;
                    melhor.parede = ranking[j].parede;
                    melhor.numero = ranking[j].numero;
                }
                else if(ranking[j].parede == melhor.parede){
                    //se a quantidade de vezes que foi usado for maior, esse movimento se torna o novo melhor
                    if(ranking[j].numero > melhor.numero){
                        melhor.mov = ranking[j].mov;
                        indice = j;
                        melhor.frutas = ranking[j].frutas;
                        melhor.parede = ranking[j].parede;
                        melhor.numero = ranking[j].numero;
                    }
                    else if(ranking[j].numero == melhor.numero){
                        //se a letra que representa o mov vier antes na ordem alfabetica, esse movimento se torna o novo melhor
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
        //imprime no arquivo o melhor movimento da rodada de ordenacao
        fprintf(pRanking, "%c,%d,%d,%d\n", melhor.mov, melhor.frutas, melhor.parede, melhor.numero);
        //troca o melhor movimento de lugar com o primeiro movimento analisado
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
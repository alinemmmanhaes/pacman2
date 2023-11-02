#include "tPacman.h"
#include <stdlib.h>
#include <stdio.h>

tPacman* CriaPacman(tPosicao* posicao){
    tPacman * pacman =  malloc(sizeof(tPacman));
    if(pacman == NULL){
        return NULL;
    }
    if(posicao == NULL){
        return NULL;
    }
    pacman->posicaoAtual = posicao;
    pacman->estaVivo = 1;

    pacman->nMovimentosBaixo = 0;
    pacman->nMovimentosCima = 0;
    pacman->nMovimentosDireita = 0;
    pacman->nMovimentosEsquerda = 0;
    pacman->nFrutasComidasBaixo = 0;
    pacman->nFrutasComidasCima = 0;
    pacman->nFrutasComidasDireita = 0;
    pacman->nFrutasComidasEsquerda = 0;
    pacman->nColisoesParedeBaixo = 0;
    pacman->nColisoesParedeCima = 0;
    pacman->nColisoesParedeDireita = 0;
    pacman->nColisoesParedeEsquerda = 0;

    pacman->nMovimentosSignificativos = 0;
    pacman->historicoDeMovimentosSignificativos = NULL;
    pacman->nLinhasTrilha = 0;
    pacman->nColunasTrilha = 0;
    pacman->trilha = NULL;
    return pacman;
}

tPacman* ClonaPacman(tPacman* pacman){
    tPacman* pacman2 = malloc(sizeof(tPacman));
    pacman2->posicaoAtual = ClonaPosicao(ObtemPosicaoPacman(pacman));
    pacman2->historicoDeMovimentosSignificativos = NULL;
    pacman2->trilha = NULL;
    return pacman2;
}

tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman){
    tMovimento** clone = malloc(pacman->nMovimentosSignificativos*sizeof(tMovimento*));
    int i;
    for(i=0; i<pacman->nMovimentosSignificativos; i++){
        clone[i] = CriaMovimento(ObtemNumeroMovimento(pacman->historicoDeMovimentosSignificativos[i]), ObtemComandoMovimento(pacman->historicoDeMovimentosSignificativos[i]), ObtemAcaoMovimento(pacman->historicoDeMovimentosSignificativos[i]));
    }
    return clone;
}

tPosicao* ObtemPosicaoPacman(tPacman* pacman){
    return pacman->posicaoAtual;
}

int EstaVivoPacman(tPacman* pacman){
    return pacman->estaVivo;
}

void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando){
    //clona a posicao do pacman para fazer alteracoes iniciais na posicao clonada
    tPosicao *pacman2 = ClonaPosicao(ObtemPosicaoPacman(pacman));

    //para cada movimento, move a posicao clonada de acordo com o movimento
    //analisa se encontrou paredes. caso haja, incrementa o numero de colisoes e nao atualiza a posicao do pacman
    //analisa se encontrou comida. caso tenha, incrementa o numero de comida, a atualiza no mapa para ' ' e atualiza posicao do pacman
    //se nao ocorrer nada acima, apenas atualiza a posicao do pacman com a do clone
    //insere movimentos significativos quando necessario
    if(comando == MOV_ESQUERDA){
        pacman->nMovimentosEsquerda++;
        pacman2->coluna--;
        if(EncontrouParedeMapa(mapa, pacman2)){
            pacman->nColisoesParedeEsquerda++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
        }
        else if(EncontrouComidaMapa(mapa, pacman2)){
            pacman->nFrutasComidasEsquerda++;
            AtualizaItemMapa(mapa, pacman2, ' ');
            AtualizaPosicao(ObtemPosicaoPacman(pacman), pacman2);
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), pacman2);
        }
        pacman2->coluna++; //retorna posicao clonada para a original para posterior analise de tunel
    }
    else if(comando == MOV_DIREITA){
        pacman->nMovimentosDireita++;
        pacman2->coluna++;
        if(EncontrouParedeMapa(mapa, pacman2)){
            pacman->nColisoesParedeDireita++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
        }
        else if(EncontrouComidaMapa(mapa, pacman2)){
            pacman->nFrutasComidasDireita++;
            AtualizaItemMapa(mapa, pacman2, ' ');
            AtualizaPosicao(ObtemPosicaoPacman(pacman), pacman2);
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), pacman2);
        }
        pacman2->coluna--;
    }
    else if(comando == MOV_CIMA){
        pacman->nMovimentosCima++;
        pacman2->linha--;
        if(EncontrouParedeMapa(mapa, pacman2)){
            pacman->nColisoesParedeCima++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
        }
        else if(EncontrouComidaMapa(mapa, pacman2)){
            pacman->nFrutasComidasCima++;
            AtualizaItemMapa(mapa, pacman2, ' ');
            AtualizaPosicao(ObtemPosicaoPacman(pacman), pacman2);
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), pacman2);
        }
        pacman2->linha++;
    }
    else if(comando == MOV_BAIXO){
        pacman->nMovimentosBaixo++;
        pacman2->linha++;
        if(EncontrouParedeMapa(mapa, pacman2)){
            pacman->nColisoesParedeBaixo++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
        }
        else if(EncontrouComidaMapa(mapa, pacman2)){
            pacman->nFrutasComidasBaixo++;
            AtualizaItemMapa(mapa, pacman2, ' ');
            AtualizaPosicao(ObtemPosicaoPacman(pacman), pacman2);
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), pacman2);
        }
        pacman2->linha--;
    }

    //analisa a presenca de tunel no mapa
    //caso haja, ve se foi acessado
    if(PossuiTunelMapa(mapa)){
        //verifica se o pacman alterou de posicao da rodada anterior para essa. so verifica se acessou tunel caso as posicoes sejam diferentes
        if(!SaoIguaisPosicao(pacman2, ObtemPosicaoPacman(pacman))){
            if(AcessouTunelMapa(mapa, ObtemPosicaoPacman(pacman))){
                //atualiza a trilha antes de alterar a posicao do pacman, que entrarah no tunel
                //e posteriormente entra no tunel (leva pacman ao outro lado do tunel)
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
            }
        }
    }
    DesalocaPosicao(pacman2);
    AtualizaTrilhaPacman(pacman);
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas){
    if(pacman->trilha == NULL){ //inicializa a trilha caso esta seja null, com o numero de linhas e colunas passados
        pacman->trilha = malloc(nLinhas*sizeof(int*));
        int i, j;
        for(i=0; i<nLinhas; i++){
            pacman->trilha[i] = malloc(nColunas*sizeof(int));
        }

        pacman->nLinhasTrilha = nLinhas;
        pacman->nColunasTrilha = nColunas;
        //inicializa todas as posicoes da trilha como -1, que equivalerah a # na hora de printar
        for(i=0; i<pacman->nLinhasTrilha; i++){
            for(j=0; j<pacman->nColunasTrilha; j++){
                pacman->trilha[i][j] = -1;
            }
        }
    }
}

void AtualizaTrilhaPacman(tPacman* pacman){
    tPosicao * posicao = ObtemPosicaoPacman(pacman);
    int linha, coluna;
    linha = ObtemLinhaPosicao(posicao);
    coluna = ObtemColunaPosicao(posicao);
    //atualiza a trilha com o numero atual de movimentos na posicao atual do pacman
    pacman->trilha[linha][coluna] = ObtemNumeroAtualMovimentosPacman(pacman);
}

void SalvaTrilhaPacman(tPacman* pacman){
    FILE *trilha;
    char * dirtrilha = "trilha.txt"; //gera arquivo trilha.txt
    trilha = fopen(dirtrilha, "w");
    int i, j;
    //roda a trilha, imprimindo # quando for -1 e o numero do movimento quando nao for -1
    for(i=0; i<pacman->nLinhasTrilha; i++){
        for(j=0; j<pacman->nColunasTrilha; j++){
            if(pacman->trilha[i][j] == -1 && j!=(pacman->nColunasTrilha-1)){ //se a posicao (i,j) for -1, printa "#"
                fprintf(trilha, "# "); //se j nao for a coluna final, printa com um espaco depois do #
            }else if(pacman->trilha[i][j] == -1){
                fprintf(trilha, "#");
            }else{ //se a posicao (i,j) nao for -1, printa o numero presente nela
                fprintf(trilha, "%d ", pacman->trilha[i][j]);
            }
        }
        fprintf(trilha, "\n");
    }
    fclose(trilha);
}

void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao){
    pacman->nMovimentosSignificativos++;
    int i = pacman->nMovimentosSignificativos;
    //aumenta a qtd de mov significativos e realloca, adicionando o novo movimento
    pacman->historicoDeMovimentosSignificativos = realloc(pacman->historicoDeMovimentosSignificativos, i*sizeof(tMovimento*));
    pacman->historicoDeMovimentosSignificativos[i-1] = CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando, acao);
}

void MataPacman(tPacman* pacman){
    pacman->estaVivo = 0;
}

void DesalocaPacman(tPacman* pacman){
    if(pacman != NULL){
        if(pacman->posicaoAtual != NULL){
            DesalocaPosicao(pacman->posicaoAtual);
        }
        int i;
        if(pacman->historicoDeMovimentosSignificativos!=NULL){
            for(i=0; i<ObtemNumeroMovimentosSignificativosPacman(pacman); i++){
                if(pacman->historicoDeMovimentosSignificativos[i]!=NULL){
                    DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
                }
            }
            free(pacman->historicoDeMovimentosSignificativos);
        }
        if(pacman->trilha != NULL){
            for(i=0; i<pacman->nLinhasTrilha; i++){
                free(pacman->trilha[i]);
            }
            free(pacman->trilha);
        }
        free(pacman);
    }
}

int ObtemNumeroAtualMovimentosPacman(tPacman* pacman){
    int total=0;
    total += ObtemNumeroMovimentosBaixoPacman(pacman);
    total += ObtemNumeroMovimentosCimaPacman(pacman);
    total += ObtemNumeroMovimentosDireitaPacman(pacman);
    total += ObtemNumeroMovimentosEsquerdaPacman(pacman);
    return total;
}

int ObtemNumeroMovimentosSemPontuarPacman(tPacman* pacman){
    return (ObtemNumeroAtualMovimentosPacman(pacman) - ObtemPontuacaoAtualPacman(pacman));
}

int ObtemNumeroColisoesParedePacman(tPacman* pacman){
    int total=0;
    total += ObtemNumeroColisoesParedeBaixoPacman(pacman);
    total += ObtemNumeroColisoesParedeCimaPacman(pacman);
    total += ObtemNumeroColisoesParedeDireitaPacman(pacman);
    total += ObtemNumeroColisoesParedeEsquerdaPacman(pacman);
    return total;
}

int ObtemNumeroMovimentosBaixoPacman(tPacman* pacman){
    return pacman->nMovimentosBaixo;
}

int ObtemNumeroFrutasComidasBaixoPacman(tPacman* pacman){
    return pacman->nFrutasComidasBaixo;
}

int ObtemNumeroColisoesParedeBaixoPacman(tPacman* pacman){
    return pacman->nColisoesParedeBaixo;
}

int ObtemNumeroMovimentosCimaPacman(tPacman* pacman){
    return pacman->nMovimentosCima;
}

int ObtemNumeroFrutasComidasCimaPacman(tPacman* pacman){
    return pacman->nFrutasComidasCima;
}

int ObtemNumeroColisoesParedeCimaPacman(tPacman* pacman){
    return pacman->nColisoesParedeCima;
}

int ObtemNumeroMovimentosEsquerdaPacman(tPacman* pacman){
    return pacman->nMovimentosEsquerda;
}

int ObtemNumeroFrutasComidasEsquerdaPacman(tPacman* pacman){
    return pacman->nFrutasComidasEsquerda;
}

int ObtemNumeroColisoesParedeEsquerdaPacman(tPacman* pacman){
    return pacman->nColisoesParedeEsquerda;
}

int ObtemNumeroMovimentosDireitaPacman(tPacman* pacman){
    return pacman->nMovimentosDireita;
}

int ObtemNumeroFrutasComidasDireitaPacman(tPacman* pacman){
    return pacman->nFrutasComidasDireita;
}

int ObtemNumeroColisoesParedeDireitaPacman(tPacman* pacman){
    return pacman->nColisoesParedeDireita;
}

int ObtemNumeroMovimentosSignificativosPacman(tPacman* pacman){
    return pacman->nMovimentosSignificativos;
}

int ObtemPontuacaoAtualPacman(tPacman* pacman){
    int total = 0;
    total += ObtemNumeroFrutasComidasBaixoPacman(pacman);
    total += ObtemNumeroFrutasComidasCimaPacman(pacman);
    total += ObtemNumeroFrutasComidasDireitaPacman(pacman);
    total += ObtemNumeroFrutasComidasEsquerdaPacman(pacman);
    return total;
}
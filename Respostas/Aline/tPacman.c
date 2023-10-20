#include "tPacman.h"

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
    pacman->nLinhasTrilha = 0;
    pacman->nColunasTrilha = 0;
    pacman->trilha = NULL;
    return pacman;
}

tPacman* ClonaPacman(tPacman* pacman){
    tPacman* pacman2 = malloc(sizeof(tPacman));
    pacman2->posicaoAtual = ClonaPosicao(ObtemPosicaoPacman(pacman));
    return pacman2;
}

tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman){
    tMovimento** clone = malloc(pacman->nMovimentosSignificativos*sizeof(tMovimento*));
    int i;
    for(i=0; i<pacman->nMovimentosSignificativos; i++){
        clone[i] = pacman->historicoDeMovimentosSignificativos[i];
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
    tPacman *pacman2 = ClonaPacman(pacman);
    if(comando == MOV_ESQUERDA){
        pacman2->posicaoAtual->coluna--;
        if(EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nColisoesParedeEsquerda++;
        }
        else if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nFrutasComidasEsquerda++;
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoPacman(pacman2));
        }
    }
    else if(comando == MOV_DIREITA){
        pacman2->posicaoAtual->coluna++;
        if(EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nColisoesParedeDireita++;
        }
        else if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nFrutasComidasDireita++;
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoPacman(pacman2));
        }
    }
    else if(comando == MOV_CIMA){
        pacman2->posicaoAtual->linha++;
        if(EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nColisoesParedeCima++;
        }
        else if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nFrutasComidasCima++;
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoPacman(pacman2));
        }
    }
    else if(comando == MOV_BAIXO){
        pacman2->posicaoAtual->linha--;
        if(EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nColisoesParedeBaixo++;
        }
        else if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nFrutasComidasBaixo++;
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoPacman(pacman2));
        }
    }
    DesalocaPacman(pacman2);
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas){
    if(pacman->trilha == NULL){
        pacman->trilha = malloc(nLinhas*sizeof(int*));
        int i, j;
        for(i=0; i<nLinhas; i++){
            pacman->trilha[i] = malloc(nColunas*sizeof(int));
        }
    }
}

void AtualizaTrilhaPacman(tPacman* pacman){
    tPosicao * posicao = ObtemPosicaoPacman(pacman);
    int linha, coluna;
    linha = ObtemLinhaPosicao(posicao);
    coluna = ObtemColunaPosicao(posicao);
    pacman->trilha[linha][coluna] = pacman->nMovimentosSignificativos;
}


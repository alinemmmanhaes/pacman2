#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tPosicao.h"

tPosicao* CriaPosicao(int linha, int coluna){
    tPosicao * posicao = (tPosicao*) malloc(sizeof(tPosicao));

    posicao->coluna = coluna;
    posicao->linha = linha;

    return posicao;
}

tPosicao* ClonaPosicao(tPosicao* posicao){
    tPosicao * posicao2 = malloc(sizeof(tPosicao));
    *posicao2 = *posicao;
    return posicao2;
}

int ObtemLinhaPosicao(tPosicao* posicao){
    return posicao->linha;
}

int ObtemColunaPosicao(tPosicao* posicao){
    return posicao->coluna;
}

void AtualizaPosicao(tPosicao* posicaoAtual, tPosicao* posicaoNova){
    *posicaoAtual = *posicaoNova;
}

bool SaoIguaisPosicao(tPosicao* posicao1, tPosicao* posicao2){
    //compara as linhas e colunas das posicoes 1 e 2
    if(posicao1->coluna == posicao2->coluna && posicao1->linha == posicao2->linha){
        return true;
    }
    return false;
}

void DesalocaPosicao(tPosicao* posicao){
    free(posicao);
}

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tTunel.h"
#include "tPosicao.h"

tTunel* CriaTunel(int linhaAcesso1, int colunaAcesso1, int linhaAcesso2, int colunaAcesso2){
    tTunel *tunel = (tTunel*) malloc(sizeof(tTunel));
    tunel->acesso1 = CriaPosicao(linhaAcesso1, colunaAcesso1);
    tunel->acesso2 = CriaPosicao(linhaAcesso2, colunaAcesso2);

    return tunel;
}

bool EntrouTunel(tTunel* tunel, tPosicao* posicao){
    //verifica se a posicao passada por parametro corresponde a uma das duas pontas do tunel
    if(SaoIguaisPosicao(tunel->acesso1, posicao) || SaoIguaisPosicao(tunel->acesso2, posicao)){
        return true;
    }
    return false;
}

void LevaFinalTunel(tTunel* tunel, tPosicao* posicao){
    //se estiver sobre o tunel, altera a posicao em que estah para a da ponta oposta
    if(EntrouTunel(tunel, posicao)){
        if(SaoIguaisPosicao(tunel->acesso1, posicao)){
            *posicao = *(tunel->acesso2);
        }
        else if(SaoIguaisPosicao(tunel->acesso2, posicao)){
            *posicao = *(tunel->acesso1);
        }
    }
}

void DesalocaTunel(tTunel* tunel){
    if(tunel != NULL){
        DesalocaPosicao(tunel->acesso1);
        DesalocaPosicao(tunel->acesso2);
        free(tunel);
    }
}
#include "tFantasma.h"

tFantasma* CriaFantasma(tMapa* mapa, char nome){
    tFantasma* fantasma = malloc(sizeof(tFantasma));
    if(fantasma == NULL){
        return NULL;
    }

    fantasma->nome = nome;
    fantasma->existe = 0;
    fantasma->posicaoanterior = NULL;
    fantasma->posicaoatual = NULL; 

    if(ObtemNomeFantasma(fantasma) == 'B' || ObtemNomeFantasma(fantasma) == 'I'){
        fantasma->direita = 0;
        fantasma->cima = 0;
    }
    if(ObtemNomeFantasma(fantasma) == 'C'){
        fantasma->direita = 1;
        fantasma->cima = 0;
    }
    if(ObtemNomeFantasma(fantasma) == 'P'){
        fantasma->direita = 0;
        fantasma->cima = 1;
    }

    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
        for(int j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            if(mapa->grid[i][j] == nome){
                fantasma->existe = 1;
                fantasma->posicaoatual = CriaPosicao(i, j);
                break;
            }
        }
    }

    return fantasma;
}

bool ExisteFantasma(tFantasma* fantasma){
    if(fantasma->existe == 1){
        return true;
    }
    return false;
}

void AndaFantasmaHorizontal(tFantasma* fantasma, tMapa* mapa){
    if(ExisteFantasma(fantasma)){
        fantasma->posicaoanterior = ClonaPosicao(ObtemPosicaoFantasma(fantasma));
        if(fantasma->direita == 0){
            fantasma->posicaoatual->coluna--;
        }
        else{
            fantasma->posicaoatual->coluna++;
        }
        if(fantasma->direita==0 && (EncontrouParedeMapa(mapa, ObtemPosicaoFantasma(fantasma)))){
            fantasma->posicaoatual->coluna += 2;
            fantasma->direita = 1;
        }
        else if(fantasma->direita==1 && (EncontrouParedeMapa(mapa, ObtemPosicaoFantasma(fantasma)))){
            fantasma->posicaoatual->coluna -= 2;
            fantasma->direita = 0;
        }
    }
    return fantasma;
}

void AndaFantasmaVertical(tFantasma* fantasma, tMapa* mapa){
    if(ExisteFantasma(fantasma)){
        fantasma->posicaoanterior = ClonaPosicao(ObtemPosicaoFantasma(fantasma));
        if(fantasma->cima == 0){
            fantasma->posicaoatual->linha++;
        }
        else{
            fantasma->posicaoatual->linha--;
        }
        if(fantasma->cima==0 && (EncontrouParedeMapa(mapa, ObtemPosicaoFantasma(fantasma)))){
            fantasma->posicaoatual->linha -= 2;
            fantasma->cima = 1;
        }
        else if(fantasma->cima==1 && (EncontrouParedeMapa(mapa, ObtemPosicaoFantasma(fantasma)))){
            fantasma->posicaoatual->linha += 2;
            fantasma->cima = 0;
        }
    }
    return fantasma;
}

int VerificaComida(tFantasma* fantasma){
    return fantasma->comida;
}

void TiraComida(tFantasma* fantasma){
    if(VerificaComida(fantasma)){
        fantasma->comida = 0;
    }
    else{
        fantasma->comida = 1;
    }
}

char ObtemNomeFantasma(tFantasma* fantasma){
    return fantasma->nome;
}

tPosicao* ObtemPosicaoFantasma(tFantasma* fantasma){
    return fantasma->posicaoatual;
}

void DesalocaPacman(tFantasma* fantasma){
    DesalocaPosicao(fantasma->posicaoanterior);
    DesalocaPosicao(fantasma->posicaoatual);
    free(fantasma);
}
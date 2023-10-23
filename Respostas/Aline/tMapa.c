#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tPosicao.h"
#include "tTunel.h"
#include "tMapa.h"

tMapa* CriaMapa(const char* caminhoConfig){
    tMapa* mapa = malloc(sizeof(tMapa));
    FILE * pMapa;
    char dirmapa[1000];
    sprintf(dirmapa, "%s/mapa.txt", caminhoConfig);
    pMapa = fopen(dirmapa, "r");
    if(!pMapa){
        return NULL;
    }

    fscanf(pMapa, "%d\n", &mapa->nMaximoMovimentos);
    mapa->tunel = NULL;
    
    mapa->grid = malloc(sizeof(char*));
    mapa->grid[0] = malloc(sizeof(char));
    int i = 1, j = 0;
    char c;
    while(1){
        fscanf(pMapa, "%c", &c);
        if(c == '\n'){
            break;
        }
        j++;
        mapa->grid[i-1] = realloc(mapa->grid[i-1], j*sizeof(char));
        mapa->grid[i-1][j-1] = c;
    }
    mapa->nColunas = j;

    i++;
    j = 0;
    mapa->grid = realloc(mapa->grid, i*sizeof(char*));
    mapa->grid[i-1] = malloc(mapa->nColunas * sizeof(char));
    while(fscanf(pMapa, "%c", &c) == 1){
        if(c == '\n'){
            i++;
            mapa->grid = realloc(mapa->grid, i*sizeof(char*));
            mapa->grid[i-1] = malloc(mapa->nColunas * sizeof(char));
            j = 0;
        }
        else{
            j++;
            mapa->grid[i-1][j-1] = c;
        }
    }
    if(c=='\n'){
        i--;
        free(mapa->grid[i]);
        mapa->grid = realloc(mapa->grid, i*sizeof(char*));
    }
    mapa->nLinhas = i;

    mapa->nFrutasAtual = 0;
    int flagtunel = 0;
    int p1x = 0, p1y = 0, p2x = 0, p2y = 0;
    for(i=0; i<mapa->nLinhas; i++){
        for(j=0; j<mapa->nColunas; j++){
            if(mapa->grid[i][j] == '*'){
                mapa->nFrutasAtual++;
            }
            if(mapa->grid[i][j] == '@' && flagtunel==0){
                p1x = i;
                p1y = j;
                flagtunel = 1;
            }
            else if(mapa->grid[i][j] == '@' && flagtunel==1){
                p2x = i;
                p2y = j;
                mapa->tunel = CriaTunel(p1x, p1y, p2x, p2y);
                flagtunel = 2;
            }
        }
    }
    fclose(pMapa);

    return mapa;
}

tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item){
    int i, j;
    for(i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
        for(j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            if(mapa->grid[i][j] == item){
                tPosicao* posicao;
                posicao = CriaPosicao(i, j);
                return posicao;
            }
        }
    }
    return NULL;
}

tTunel* ObtemTunelMapa(tMapa* mapa){
    return mapa->tunel;
}

char ObtemItemMapa(tMapa* mapa, tPosicao* posicao){
    int l, c;
    l = ObtemLinhaPosicao(posicao);
    c = ObtemColunaPosicao(posicao);
    if(mapa == NULL || mapa->grid == NULL){
        return '\0';
    }
    if(c >= ObtemNumeroColunasMapa(mapa) || l >= ObtemNumeroLinhasMapa(mapa) || c < 0 || l < 0){
        return '\0';
    }
    return mapa->grid[l][c];
}

int ObtemNumeroLinhasMapa(tMapa* mapa){
    return mapa->nLinhas;
}

int ObtemNumeroColunasMapa(tMapa* mapa){
    return mapa->nColunas;
}

int ObtemQuantidadeFrutasIniciaisMapa(tMapa* mapa){
    return mapa->nFrutasAtual;
}

int ObtemNumeroMaximoMovimentosMapa(tMapa* mapa){
    return mapa->nMaximoMovimentos;
}

bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao){
    int l, c;
    l = ObtemLinhaPosicao(posicao);
    c = ObtemColunaPosicao(posicao);
    if(mapa == NULL || mapa->grid == NULL){
        return false;
    }
    if(c >= ObtemNumeroColunasMapa(mapa) || l >= ObtemNumeroLinhasMapa(mapa) || c < 0 || l < 0){
        return false;
    }
    return (ObtemItemMapa(mapa, posicao) == '*');
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao){
    int l, c;
    l = ObtemLinhaPosicao(posicao);
    c = ObtemColunaPosicao(posicao);
    if(mapa == NULL || mapa->grid == NULL){
        return false;
    }
    if(c >= ObtemNumeroColunasMapa(mapa) || l >= ObtemNumeroLinhasMapa(mapa) || c < 0 || l < 0){
        return false;
    }
    return (ObtemItemMapa(mapa, posicao) == '#');
}

bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item){
    int l, c;
    l = ObtemLinhaPosicao(posicao);
    c = ObtemColunaPosicao(posicao);
    if(mapa == NULL || mapa->grid == NULL){
        return false;
    }
    if(c >= ObtemNumeroColunasMapa(mapa) || l >= ObtemNumeroLinhasMapa(mapa) || c < 0 || l < 0){
        return false;
    }
    mapa->grid[l][c] = item;
    if(mapa->grid[l][c] == item){
        return true;
    }
    return false;
}

bool PossuiTunelMapa(tMapa* mapa){
    if(mapa->tunel == NULL){
        return false;
    }
    return true;
}

bool AcessouTunelMapa(tMapa* mapa, tPosicao* posicao){
    return EntrouTunel(mapa->tunel, posicao);
}

void EntraTunelMapa(tMapa* mapa, tPosicao* posicao){
    LevaFinalTunel(mapa->tunel, posicao);
}

void DesalocaMapa(tMapa* mapa){
    int i;
    if(mapa != NULL){
        for(i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
            free(mapa->grid[i]);
        }
        free(mapa->grid);
        DesalocaTunel(mapa->tunel);
        free(mapa);
    }
}
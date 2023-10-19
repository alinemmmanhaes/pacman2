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
    
    mapa->grid = malloc(sizeof(int*));
    mapa->grid[0] = malloc(sizeof(int));
    int j = 0;
    char c;
    while(1){
        fscanf(pMapa, "%c", &c);
        if(c == '\n'){
            break;
        }
        j++;
        mapa->grid[0] = realloc(mapa->grid[0], j);
        mapa->grid[0][j-1] = c;
    }
    mapa->nColunas = j;

    int i = 2;
    j = 0;
    mapa->grid = realloc(mapa->grid, i);
    mapa->grid[i-1] = malloc(mapa->nColunas * sizeof(int));
    while(1){
        fscanf(pMapa, "%c", &c);
        if(c == '\n' && !feof(pMapa)){
            i++;
            mapa->grid = realloc(mapa->grid, i);
            mapa->grid[i-1] = malloc(mapa->nColunas * sizeof(int));
            j = 0;
        }
        if(feof(pMapa)){
            break;
        }
        mapa->grid[i-1][j] = c;
        j++;
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
            if(mapa->grid[i][j] == '@' && flagtunel==1){
                p2x = i;
                p2y = j;
                flagtunel = 2;
            }
            if(flagtunel == 2){
                mapa->tunel = CriaTunel(p1x, p1y, p2x, p2y);
                flagtunel = 3;
            }
        }
    }
    fclose(pMapa);

    return mapa;
}

tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item){
    int i, j;
    for(i=0; i<mapa->nLinhas; i++){
        for(j=0; j<mapa->nColunas; j++){
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
    if(c >= mapa->nColunas || l >= mapa->nLinhas || c < 0 || l < 0){
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
    if(c >= mapa->nColunas || l >= mapa->nLinhas || c < 0 || l < 0){
        return false;
    }
    if(mapa->grid[l][c] == '*'){
        return true;
    }
    return false;
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao){
    int l, c;
    l = ObtemLinhaPosicao(posicao);
    c = ObtemColunaPosicao(posicao);
    if(mapa == NULL || mapa->grid == NULL){
        return false;
    }
    if(c >= mapa->nColunas || l >= mapa->nLinhas || c < 0 || l < 0){
        return false;
    }
    if(mapa->grid[l][c] == '#'){
        return true;
    }
    return false;
}

bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item){
    int l, c;
    l = ObtemLinhaPosicao(posicao);
    c = ObtemColunaPosicao(posicao);
    if(mapa == NULL || mapa->grid == NULL){
        return false;
    }
    if(c >= mapa->nColunas || l >= mapa->nLinhas || c < 0 || l < 0){
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
    for(i=0; i<mapa->nLinhas; i++){
        free(mapa->grid[i]);
    }
    DesalocaTunel(mapa->tunel);
    free(mapa);
}
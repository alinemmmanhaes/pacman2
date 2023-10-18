#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tPosicao.h"
#include "tTunel.h"
#include "tMapa.h"

tMapa* CriaMapa(const char* caminhoConfig){
    tMapa* mapa = malloc(sizeof(tMapa));

     /*
     tJogo LeMapa(FILE * pMapa, tJogo jogo){
    int i, j;
    
    fscanf(pMapa, "%d %d %d\n", &jogo.linhas, &jogo.colunas, &jogo.jogadas);
    
    for(i=0; i<jogo.linhas; i++){
        for(j=0; j<jogo.colunas; j++){
            fscanf(pMapa, "%c", &jogo.mapa[i][j]);
        }
        fscanf(pMapa, "\n");
    }
    
    return jogo;
*/

/*
    sprintf(dirmapa, "%s/mapa.txt", argv[1]);
    pMapa = fopen(dirmapa,"r");*/
}
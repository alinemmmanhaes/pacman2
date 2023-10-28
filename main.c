#include "tFantasma.h"
#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include "tArquivos.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    tMapa* mapa = NULL;
    tPosicao* posicaopm = NULL;
    tMovimento** resumo = NULL;

    //Analisa se o diretório foi informado, avisa e finaliza o programa caso não tenha sido
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        return 1;
    }

    mapa = CriaMapa(argv[1]);
    //Analisa se o arquivo de mapa foi achado, informa e finaliza o programa caso não tenha sido
    if(mapa == NULL){
        printf("ERRO: nao foi possível ler o arquivo %s/mapa.txt\n", argv[1]);
        return 1;
    }

    posicaopm = Inicializacao(argv[1], mapa);
}
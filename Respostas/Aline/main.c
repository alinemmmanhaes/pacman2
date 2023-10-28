#include "tFantasma.h"
#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include "tArquivos.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct tJogo{
    tFantasma* B;
    tFantasma* P;
    tFantasma* I;
    tFantasma* C;
    tPacman* pacman;
    tMapa* mapa;
} tJogo;

void JogaJogo(tJogo* jogo){
    char comando, x, y;
    tPosicao* anteriorpm = NULL;

    for(int i=1; i<=ObtemNumeroMaximoMovimentosMapa(jogo->mapa); i++){
        scanf("%c%*c", &comando);
        x = ObtemLinhaPosicao(ObtemPosicaoPacman(jogo->pacman));
        y = ObtemColunaPosicao(ObtemPosicaoPacman(jogo->pacman));
        anteriorpm = CriaPosicao(x, y);

        MovePacman(jogo->pacman, jogo->mapa, comando);
        AndaFantasmaHorizontal(jogo->B, jogo->mapa);
        AndaFantasmaHorizontal(jogo->C, jogo->mapa);
        AndaFantasmaVertical(jogo->I, jogo->mapa);
        AndaFantasmaVertical(jogo->P, jogo->mapa);

        AtualizaMapa(jogo->B, jogo->C, jogo->I, jogo->P, jogo->pacman, jogo->mapa, anteriorpm);
    }
}

int main(int argc, char * argv[]){
    tJogo* jogo = malloc(sizeof(tJogo));
    tPosicao* posicaopm = NULL;

    //Analisa se o diretório foi informado, avisa e finaliza o programa caso não tenha sido
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        return 1;
    }

    jogo->mapa = CriaMapa(argv[1]);
    //Analisa se o arquivo de mapa foi achado, informa e finaliza o programa caso não tenha sido
    if(jogo->mapa == NULL){
        printf("ERRO: nao foi possível ler o arquivo %s/mapa.txt\n", argv[1]);
        return 1;
    }

    posicaopm = Inicializacao(argv[1], jogo->mapa);

    jogo->pacman = CriaPacman(posicaopm);
    jogo->B = CriaFantasma(jogo->mapa, 'B');
    jogo->I = CriaFantasma(jogo->mapa, 'I');
    jogo->C = CriaFantasma(jogo->mapa, 'C');
    jogo->P = CriaFantasma(jogo->mapa, 'P');

    JogaJogo(jogo);
}
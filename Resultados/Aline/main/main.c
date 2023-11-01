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

void DesalocaJogo(tJogo* jogo){
    DesalocaFantasma(jogo->B);
    DesalocaFantasma(jogo->P);
    DesalocaFantasma(jogo->I);
    DesalocaFantasma(jogo->C);
    DesalocaPacman(jogo->pacman);
    DesalocaMapa(jogo->mapa);
    free(jogo);
}

void ImprimeEstadoAtual(char comando, tMapa* mapa, tPacman* pacman){
    printf("Estado do jogo apos o movimento '%c':\n", comando);

    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
        for(int j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            printf("%c", mapa->grid[i][j]);
        }
        printf("\n");
    }
    printf("Pontuacao: %d\n\n", ObtemPontuacaoAtualPacman(pacman));
}

void JogaJogo(tJogo* jogo){
    int resp = -1, caso = 0, pontosantes = -1;
    char comando, x, y;
    COMANDO acao;
    tPosicao* anteriorpm = NULL;

    AtualizaTrilhaPacman(jogo->pacman);

    for(int i=1; i<=ObtemNumeroMaximoMovimentosMapa(jogo->mapa); i++){
        scanf("%c%*c", &comando);
        x = ObtemLinhaPosicao(ObtemPosicaoPacman(jogo->pacman));
        y = ObtemColunaPosicao(ObtemPosicaoPacman(jogo->pacman));
        anteriorpm = CriaPosicao(x, y);
        pontosantes = ObtemPontuacaoAtualPacman(jogo->pacman);

        if(comando == 'a'){
            acao = MOV_ESQUERDA;
        }
        else if(comando == 's'){
            acao = MOV_BAIXO;
        }
        else if(comando == 'd'){
            acao = MOV_DIREITA;
        }
        else if(comando == 'w'){
            acao = MOV_CIMA;
        }

        MovePacman(jogo->pacman, jogo->mapa, acao);
        AndaFantasmaHorizontal(jogo->B, jogo->mapa);
        AndaFantasmaHorizontal(jogo->C, jogo->mapa);
        AndaFantasmaVertical(jogo->I, jogo->mapa);
        AndaFantasmaVertical(jogo->P, jogo->mapa);

        AtualizaMapa(jogo->B, jogo->C, jogo->I, jogo->P, jogo->pacman, jogo->mapa, anteriorpm, acao);

        resp = MorreuPacman(jogo->pacman, jogo->mapa, jogo->B, anteriorpm);
        if(resp == 1 || resp == 2){
            caso = 1;
        }
        if(resp == 2){
            RemovePacManMapa(jogo->mapa, jogo->pacman);
        }
        resp = MorreuPacman(jogo->pacman, jogo->mapa, jogo->C, anteriorpm);
        if(resp == 1 || resp == 2){
            caso = 1;
        }
        if(resp == 2){
            RemovePacManMapa(jogo->mapa, jogo->pacman);
        }
        resp = MorreuPacman(jogo->pacman, jogo->mapa, jogo->I, anteriorpm);
        if(resp == 1 || resp == 2){
            caso = 1;
        }
        if(resp == 2){
            RemovePacManMapa(jogo->mapa, jogo->pacman);
        }
        resp = MorreuPacman(jogo->pacman, jogo->mapa, jogo->P, anteriorpm);
        if(resp == 1 || resp == 2){
            caso = 1;
        }
        if(resp == 2){
            RemovePacManMapa(jogo->mapa, jogo->pacman);
        }

        ImprimeEstadoAtual(comando, jogo->mapa, jogo->pacman);
        DesalocaPosicao(anteriorpm);

        if(caso == 1){
            MataPacman(jogo->pacman);
            InsereNovoMovimentoSignificativoPacman(jogo->pacman, acao, "fim de jogo por encostar em um fantasma");
            break;
        }
        if(ObtemQuantidadeFrutasIniciaisMapa(jogo->mapa) == ObtemPontuacaoAtualPacman(jogo->pacman)){
            caso = 2;
            break;
        }
        if(i == ObtemNumeroMaximoMovimentosMapa(jogo->mapa)){
            caso = 3;
            break;
        }
    }
    if(caso == 2){
        printf("Voce venceu!\n");
    }
    else{
        printf("Game over!\n");
    }
    printf("Pontuacao final: %d\n", ObtemPontuacaoAtualPacman(jogo->pacman));
}

int main(int argc, char * argv[]){
    tJogo* jogo = malloc(sizeof(tJogo));
    tPosicao* posicaopm = NULL;
    //tMovimento** resumo = NULL;

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

    posicaopm = Inicializacao(jogo->mapa);

    jogo->pacman = CriaPacman(posicaopm);
    jogo->B = CriaFantasma(jogo->mapa, 'B');
    jogo->I = CriaFantasma(jogo->mapa, 'I');
    jogo->C = CriaFantasma(jogo->mapa, 'C');
    jogo->P = CriaFantasma(jogo->mapa, 'P');

    CriaTrilhaPacman(jogo->pacman, ObtemNumeroLinhasMapa(jogo->mapa), ObtemNumeroColunasMapa(jogo->mapa));
    JogaJogo(jogo);

    //resumo = Resumo(jogo->pacman);
    Resumo(jogo->pacman);
    SalvaTrilhaPacman(jogo->pacman);
    Estatisticas(jogo->pacman);
    Ranking(jogo->pacman);

    //DesalocaPosicao(posicaopm);
    DesalocaJogo(jogo);
    
    return 0;
}
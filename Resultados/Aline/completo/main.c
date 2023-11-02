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

//Desaloca cada um dos itens do tJogo
void DesalocaJogo(tJogo* jogo){
    DesalocaFantasma(jogo->B);
    DesalocaFantasma(jogo->P);
    DesalocaFantasma(jogo->I);
    DesalocaFantasma(jogo->C);
    DesalocaPacman(jogo->pacman);
    DesalocaMapa(jogo->mapa);
    free(jogo);
}

//Imprime o estado atual do jogo (mapa e pontuacao) na saida padrao
void ImprimeEstadoAtual(char comando, tMapa* mapa, tPacman* pacman){
    printf("Estado do jogo apos o movimento '%c':\n", comando); //informa o ultimo comando

    char c;
    //printa mapa
    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
        for(int j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            //Cria uma posicao para acessar item da posicao sem usar mapa->grid
            tPosicao* posicao = CriaPosicao(i, j);
            c = ObtemItemMapa(mapa, posicao);
            printf("%c", c);
            DesalocaPosicao(posicao);
        }
        printf("\n");
    }
    //printa a pontuacao atual
    printf("Pontuacao: %d\n\n", ObtemPontuacaoAtualPacman(pacman));
}

//Atualiza a posicao antiga do pacman para um espaco ' '
void RemovePacManMapa(tMapa* mapa, tPacman* pacman){
    AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), ' ');
}

void ResetaMapa(tFantasma* B, tFantasma* C, tFantasma* I, tFantasma* P, tPacman* pacman, tMapa* mapa, tPosicao* anteriorpm){
    char c;
    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){ //roda o mapa
        for(int j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            //Cria uma posicao para acessar item da posicao sem usar mapa->grid
            tPosicao* posicao = CriaPosicao(i, j);
            c = ObtemItemMapa(mapa, posicao);
            if(c == 'B'){ //analisa se cada um dos fantasmas tinha uma comida embaixo deles
                if(VerificaComida(B)){ //se sim, coloca a comida de volta na posicao
                    AtualizaItemMapa(mapa, posicao, '*');
                    TiraComida(B);
                }
                else{ //se nao, coloca um espaco vazio no lugar do fantasma
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            else if(c == 'C'){
                if(VerificaComida(C)){
                    AtualizaItemMapa(mapa, posicao, '*');
                    TiraComida(C);
                }
                else{
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            else if(c == 'I'){
                if(VerificaComida(I)){
                    AtualizaItemMapa(mapa, posicao, '*');
                    TiraComida(I);
                }
                else{
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            else if(c == 'P'){
                if(VerificaComida(P)){
                    AtualizaItemMapa(mapa, posicao, '*');
                    TiraComida(P);
                }
                else{
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            else if(c == '>'){
                if(PossuiTunelMapa(mapa)){ //analisa se o pacman estava em cima de um tunel
                    if(EntrouTunel(mapa->tunel, anteriorpm)){
                        AtualizaItemMapa(mapa, posicao, '@'); //se sim, coloca o simbolo do tunel na posicao em que o pacman estava
                    }
                    else{
                        AtualizaItemMapa(mapa, posicao, ' ');
                    }
                }
                else{ //se nao, coloca um espaco vazio no lugar
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            DesalocaPosicao(posicao);
        }
    }
}

void AtualizaMapa(tFantasma* B, tFantasma* C, tFantasma* I, tFantasma* P, tPacman* pacman, tMapa* mapa, tPosicao* anteriorpm, COMANDO comando){
    /*char c;
    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){ //roda o mapa
        for(int j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            //Cria uma posicao para acessar item da posicao sem usar mapa->grid
            tPosicao* posicao = CriaPosicao(i, j);
            c = ObtemItemMapa(mapa, posicao);
            if(c == 'B'){ //analisa se cada um dos fantasmas tinha uma comida embaixo deles
                if(VerificaComida(B)){ //se sim, coloca a comida de volta na posicao
                    AtualizaItemMapa(mapa, posicao, '*');
                    TiraComida(B);
                }
                else{ //se nao, coloca um espaco vazio no lugar do fantasma
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            else if(c == 'C'){
                if(VerificaComida(C)){
                    AtualizaItemMapa(mapa, posicao, '*');
                    TiraComida(C);
                }
                else{
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            else if(c == 'I'){
                if(VerificaComida(I)){
                    AtualizaItemMapa(mapa, posicao, '*');
                    TiraComida(I);
                }
                else{
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            else if(c == 'P'){
                if(VerificaComida(P)){
                    AtualizaItemMapa(mapa, posicao, '*');
                    TiraComida(P);
                }
                else{
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            else if(c == '>'){
                if(PossuiTunelMapa(mapa)){ //analisa se o pacman estava em cima de um tunel
                    if(EntrouTunel(mapa->tunel, anteriorpm)){
                        AtualizaItemMapa(mapa, posicao, '@'); //se sim, coloca o simbolo do tunel na posicao em que o pacman estava
                    }
                    else{
                        AtualizaItemMapa(mapa, posicao, ' ');
                    }
                }
                else{ //se nao, coloca um espaco vazio no lugar
                    AtualizaItemMapa(mapa, posicao, ' ');
                }
            }
            DesalocaPosicao(posicao);
        }
    }

    //analisa se o pacman pegou alguma fruta devolvida por algum fantasma
    if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman))){
        if(comando == MOV_BAIXO){ //se sim, a contabiliza
            pacman->nFrutasComidasBaixo++;
        }
        else if(comando == MOV_CIMA){
            pacman->nFrutasComidasCima++;
        }
        else if(comando == MOV_ESQUERDA){
            pacman->nFrutasComidasEsquerda++;
        }
        else if(comando == MOV_DIREITA){
            pacman->nFrutasComidasDireita++;
        }// e gera um novo movimento significativo
        InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
    }*/
    //coloca o pacman em sua nova posicao no mapa
    AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');

    //analisa se o fantasma existe. Caso sim, o coloca em sua nova posicao no mapa
    if(ExisteFantasma(B)){
        if(EncontrouComidaMapa(mapa, ObtemPosicaoFantasma(B))){
            TiraComida(B);
        }
        AtualizaItemMapa(mapa, ObtemPosicaoFantasma(B), 'B');
    }
    if(ExisteFantasma(C)){
        if(EncontrouComidaMapa(mapa, ObtemPosicaoFantasma(C))){
            TiraComida(C);
        }
        AtualizaItemMapa(mapa, ObtemPosicaoFantasma(C), 'C');
    }
    if(ExisteFantasma(I)){
        if(EncontrouComidaMapa(mapa, ObtemPosicaoFantasma(I))){
            TiraComida(I);
        }
        AtualizaItemMapa(mapa, ObtemPosicaoFantasma(I), 'I');
    }
    if(ExisteFantasma(P)){
        if(EncontrouComidaMapa(mapa, ObtemPosicaoFantasma(P))){
            TiraComida(P);
        }
        AtualizaItemMapa(mapa, ObtemPosicaoFantasma(P), 'P');
    }
}

void JogaJogo(tJogo* jogo){
    int resp = -1, caso = 0;
    char comando, x, y;
    COMANDO acao;
    tPosicao* anteriorpm = NULL;

    //Atualiza a trilha com a posicao inicial do pacman no mov 0
    AtualizaTrilhaPacman(jogo->pacman);

    for(int i=1; i<=ObtemNumeroMaximoMovimentosMapa(jogo->mapa); i++){
        scanf("%c%*c", &comando);
        x = ObtemLinhaPosicao(ObtemPosicaoPacman(jogo->pacman));
        y = ObtemColunaPosicao(ObtemPosicaoPacman(jogo->pacman));
        anteriorpm = CriaPosicao(x, y); //guarda a posicao do pacman antes de movimenta-lo

        //traduz o char lido para o tipo COMANDO
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

        ResetaMapa(jogo->B, jogo->C, jogo->I, jogo->P, jogo->pacman, jogo->mapa, anteriorpm);

        //Movimenta os personagens do jogo
        MovePacman(jogo->pacman, jogo->mapa, acao);
        AndaFantasmaHorizontal(jogo->B, jogo->mapa);
        AndaFantasmaHorizontal(jogo->C, jogo->mapa);
        AndaFantasmaVertical(jogo->I, jogo->mapa);
        AndaFantasmaVertical(jogo->P, jogo->mapa);

        //Atualiza todas as posicoes de fantasmas e pacman no mapa
        AtualizaMapa(jogo->B, jogo->C, jogo->I, jogo->P, jogo->pacman, jogo->mapa, anteriorpm, acao);

        //Analisa possiveis casos de colisao do pacman com cada um dos fantasmas
        resp = ColidiuFantasmaPacman(jogo->pacman, jogo->mapa, jogo->B, anteriorpm);
        if(resp == 1 || resp == 2){
            caso = 1;
        }
        if(resp == 2){
            RemovePacManMapa(jogo->mapa, jogo->pacman);
        }
        resp = ColidiuFantasmaPacman(jogo->pacman, jogo->mapa, jogo->C, anteriorpm);
        if(resp == 1 || resp == 2){
            caso = 1;
        }
        if(resp == 2){
            RemovePacManMapa(jogo->mapa, jogo->pacman);
        }
        resp = ColidiuFantasmaPacman(jogo->pacman, jogo->mapa, jogo->I, anteriorpm);
        if(resp == 1 || resp == 2){
            caso = 1;
        }
        if(resp == 2){
            RemovePacManMapa(jogo->mapa, jogo->pacman);
        }
        resp = ColidiuFantasmaPacman(jogo->pacman, jogo->mapa, jogo->P, anteriorpm);
        if(resp == 1 || resp == 2){
            caso = 1;
        }
        if(resp == 2){
            RemovePacManMapa(jogo->mapa, jogo->pacman);
        }

        ImprimeEstadoAtual(comando, jogo->mapa, jogo->pacman);
        DesalocaPosicao(anteriorpm);

        //Caso1 = morte por fantasmas/ Caso2 = pontuacao max/ Caso3 = numero maximo de jogadas
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
    //Aloca dinamicamente o tipo tJogo, que conterah todos os elementos do jogo (pacman, fantasmas, mapa)
    tJogo* jogo = malloc(sizeof(tJogo));
    //Inicializa como NULL o que futuramente serah a posicao inicial do pacman
    tPosicao* posicaopm = NULL;

    //Analisa se o diretório foi informado, avisa e finaliza o programa caso não tenha sido
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        return 1;
    }

    //Cria e le o mapa atraves de alocacao dinamica
    jogo->mapa = CriaMapa(argv[1]);
    //Analisa se o arquivo de mapa foi achado, informa e finaliza o programa caso não tenha sido
    if(jogo->mapa == NULL){
        printf("ERRO: nao foi possível ler o arquivo %s/mapa.txt\n", argv[1]);
        return 1;
    }

    //Gera arquivo de inicializacao e retorna a posicao inicial do pacman, utilizada para cria-lo logo abaixo
    posicaopm = Inicializacao(jogo->mapa);

    //Cria por alocacao dinamica o pacman e os fantasmas do jogo
    jogo->pacman = CriaPacman(posicaopm);
    jogo->B = CriaFantasma(jogo->mapa, 'B');
    jogo->I = CriaFantasma(jogo->mapa, 'I');
    jogo->C = CriaFantasma(jogo->mapa, 'C');
    jogo->P = CriaFantasma(jogo->mapa, 'P');

    //Cria a trilha que sera alocada no pacman
    CriaTrilhaPacman(jogo->pacman, ObtemNumeroLinhasMapa(jogo->mapa), ObtemNumeroColunasMapa(jogo->mapa));

    //Recebe os comandos, movimenta os personagens e analisa possiveis derrotas ou vitorias
    JogaJogo(jogo);

    //Gera arquivos resumo, trilha, estatisticas e ranking
    Resumo(jogo->pacman);
    SalvaTrilhaPacman(jogo->pacman);
    Estatisticas(jogo->pacman);
    Ranking(jogo->pacman);

    //Desaloca todos os itens que foram alocados no jogo
    DesalocaJogo(jogo);

    return 0;
}
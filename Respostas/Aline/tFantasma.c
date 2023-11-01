#include "tFantasma.h"

tFantasma* CriaFantasma(tMapa* mapa, char nome){
    tFantasma* fantasma = malloc(sizeof(tFantasma));
    if(fantasma == NULL){
        return NULL;
    }

    fantasma->nome = nome;
    fantasma->existe = 0;
    fantasma->comida = 0;
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
        DesalocaPosicao(fantasma->posicaoanterior);
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
}

void AndaFantasmaVertical(tFantasma* fantasma, tMapa* mapa){
    if(ExisteFantasma(fantasma)){
        DesalocaPosicao(fantasma->posicaoanterior);
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
}

int ColidiuFantasmaPacman(tPacman* pacman, tMapa* mapa, tFantasma* fantasma, tPosicao* posicaoanteriorPM){
    if(ExisteFantasma(fantasma)){
        if(SaoIguaisPosicao(ObtemPosicaoFantasma(fantasma), ObtemPosicaoPacman(pacman))){
            MataPacman(pacman);
            return 1;
        }
        else if(SaoIguaisPosicao(ObtemPosicaoAnteriorFantasma(fantasma), ObtemPosicaoPacman(pacman))){
            if(SaoIguaisPosicao(ObtemPosicaoFantasma(fantasma), posicaoanteriorPM)){
                MataPacman(pacman);
                return 2;
            }
        }
    }
    return 0;
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

tPosicao* ObtemPosicaoAnteriorFantasma(tFantasma* fantasma){
    return fantasma->posicaoanterior;
}

void AtualizaMapa(tFantasma* B, tFantasma* C, tFantasma* I, tFantasma* P, tPacman* pacman, tMapa* mapa, tPosicao* anteriorpm, COMANDO comando){
    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
        for(int j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            if(mapa->grid[i][j] == 'B'){
                if(VerificaComida(B)){
                    mapa->grid[i][j] = '*';
                    TiraComida(B);
                }
                else{
                    mapa->grid[i][j] = ' ';
                }
            }
            else if(mapa->grid[i][j] == 'C'){
                if(VerificaComida(C)){
                    mapa->grid[i][j] = '*';
                    TiraComida(C);
                }
                else{
                    mapa->grid[i][j] = ' ';
                }
            }
            else if(mapa->grid[i][j] == 'I'){
                if(VerificaComida(I)){
                    mapa->grid[i][j] = '*';
                    TiraComida(I);
                }
                else{
                    mapa->grid[i][j] = ' ';
                }
            }
            else if(mapa->grid[i][j] == 'P'){
                if(VerificaComida(P)){
                    mapa->grid[i][j] = '*';
                    TiraComida(P);
                }
                else{
                    mapa->grid[i][j] = ' ';
                }
            }
            else if(mapa->grid[i][j] == '>'){
                if(PossuiTunelMapa(mapa)){
                    if(EntrouTunel(mapa->tunel, anteriorpm)){
                        mapa->grid[i][j] = '@';
                    }
                    else{
                        mapa->grid[i][j] = ' ';
                    }
                }
                else{
                    mapa->grid[i][j] = ' ';
                }
            }
        }
    }

    if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman))){
        if(comando == MOV_BAIXO){
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
        }
        InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
    }
    AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');
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

void RemovePacManMapa(tMapa* mapa, tPacman* pacman){
    AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), ' ');
}

void DesalocaFantasma(tFantasma* fantasma){
    if(fantasma->posicaoanterior != NULL){
        DesalocaPosicao(fantasma->posicaoanterior);
    }
    if(fantasma->posicaoatual != NULL){
        DesalocaPosicao(fantasma->posicaoatual);
    }
    free(fantasma);
}
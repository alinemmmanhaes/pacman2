#include "tPacman.h"

tPacman* CriaPacman(tPosicao* posicao){
    tPacman * pacman =  malloc(sizeof(tPacman));
    if(pacman == NULL){
        return NULL;
    }
    if(posicao == NULL){
        return NULL;
    }
    pacman->posicaoAtual = posicao;
    pacman->estaVivo = 1;

    pacman->nMovimentosBaixo = 0;
    pacman->nMovimentosCima = 0;
    pacman->nMovimentosDireita = 0;
    pacman->nMovimentosEsquerda = 0;
    pacman->nFrutasComidasBaixo = 0;
    pacman->nFrutasComidasCima = 0;
    pacman->nFrutasComidasDireita = 0;
    pacman->nFrutasComidasEsquerda = 0;
    pacman->nColisoesParedeBaixo = 0;
    pacman->nColisoesParedeCima = 0;
    pacman->nColisoesParedeDireita = 0;
    pacman->nColisoesParedeEsquerda = 0;

    pacman->nMovimentosSignificativos = 0;
    pacman->historicoDeMovimentosSignificativos = malloc(sizeof(tMovimento*));
    pacman->nLinhasTrilha = 0;
    pacman->nColunasTrilha = 0;
    pacman->trilha = NULL;
    return pacman;
}

tPacman* ClonaPacman(tPacman* pacman){
    tPacman* pacman2 = malloc(sizeof(tPacman));
    pacman2->posicaoAtual = ClonaPosicao(ObtemPosicaoPacman(pacman));
    return pacman2;
}

tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman){
    tMovimento** clone = malloc(pacman->nMovimentosSignificativos*sizeof(tMovimento*));
    int i;
    for(i=0; i<pacman->nMovimentosSignificativos; i++){
        clone[i] = pacman->historicoDeMovimentosSignificativos[i];
    }
    return clone;
}

tPosicao* ObtemPosicaoPacman(tPacman* pacman){
    return pacman->posicaoAtual;
}

int EstaVivoPacman(tPacman* pacman){
    return pacman->estaVivo;
}

void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando){
    tPacman *pacman2 = ClonaPacman(pacman);
    if(comando == MOV_ESQUERDA){
        pacman2->posicaoAtual->coluna--;
        if(EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nColisoesParedeEsquerda++;
        }
        else if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nFrutasComidasEsquerda++;
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoPacman(pacman2));
        }
        pacman->nMovimentosEsquerda++;
    }
    else if(comando == MOV_DIREITA){
        pacman2->posicaoAtual->coluna++;
        if(EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nColisoesParedeDireita++;
        }
        else if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nFrutasComidasDireita++;
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoPacman(pacman2));
        }
        pacman->nMovimentosDireita++;
    }
    else if(comando == MOV_CIMA){
        pacman2->posicaoAtual->linha++;
        if(EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nColisoesParedeCima++;
        }
        else if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nFrutasComidasCima++;
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoPacman(pacman2));
        }
        pacman->nMovimentosCima++;
    }
    else if(comando == MOV_BAIXO){
        pacman2->posicaoAtual->linha--;
        if(EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nColisoesParedeBaixo++;
        }
        else if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman2))){
            pacman->nFrutasComidasBaixo++;
        }
        else{
            AtualizaPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoPacman(pacman2));
        }
        pacman->nMovimentosBaixo++;
    }
    DesalocaPacman(pacman2);
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas){
    if(pacman->trilha == NULL){
        pacman->trilha = malloc(nLinhas*sizeof(int*));
        int i, j;
        for(i=0; i<nLinhas; i++){
            pacman->trilha[i] = malloc(nColunas*sizeof(int));
        }

        pacman->nLinhasTrilha = nLinhas;
        pacman->nColunasTrilha = nColunas;
        for(i=0; i<pacman->nLinhasTrilha; i++){
            for(j=0; j<pacman->nColunasTrilha; j++){
                pacman->trilha[i][j] = -1;
            }
        }
    }
}

void AtualizaTrilhaPacman(tPacman* pacman){
    tPosicao * posicao = ObtemPosicaoPacman(pacman);
    int linha, coluna;
    linha = ObtemLinhaPosicao(posicao);
    coluna = ObtemColunaPosicao(posicao);
    pacman->trilha[linha][coluna] = ObtemNumeroAtualMovimentosPacman(pacman);
}

void SalvaTrilhaPacman(tPacman* pacman){
    FILE *trilha;
    char * dirtrilha = 'trilha.txt';
    trilha = fopen(dirtrilha, "w");
    int i, j;
    for(i=0; i<pacman->nLinhasTrilha; i++){
        for(j=0; j<pacman->nColunasTrilha; j++){
            if(pacman->trilha[i][j] == -1 && j!=(pacman->nColunasTrilha-1)){ //se a posicao (i,j) for -1, printa "#"
                fprintf(trilha, "# "); //se j nao for a coluna final, printa com um espaco depois do #
            }else if(pacman->trilha[i][j] == -1){
                fprintf(trilha, "#");
            }else{ //se a posicao (i,j) nao for -1, printa o numero presente nela
                fprintf(trilha, "%d ", pacman->trilha[i][j]);
            }
        }
        fprintf(trilha, "\n");
    }
}

void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao){
    pacman->nMovimentosSignificativos++;
    int i = pacman->nMovimentosSignificativos;
    pacman->historicoDeMovimentosSignificativos = realloc(pacman->historicoDeMovimentosSignificativos, i*sizeof(tMovimento*));
    pacman->historicoDeMovimentosSignificativos[i-1] = CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando, acao);
}

void MataPacman(tPacman* pacman){
    pacman->estaVivo = 0;
}

void DesalocaPacman(tPacman* pacman){
    if(pacman != NULL){
        DesalocaPosicao(pacman->posicaoAtual);
        int i;
        for(i=0; i<ObtemNumeroMovimentosSignificativosPacman(pacman); i++){
            DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
        }
        free(pacman->historicoDeMovimentosSignificativos);
        for(i=0; i<pacman->nLinhasTrilha; i++){
            free(pacman->trilha[i]);
        }
        free(pacman->trilha);
        free(pacman);
    }
}

int ObtemNumeroAtualMovimentosPacman(tPacman* pacman){
    int total=0;
    total += pacman->nMovimentosBaixo;
    total += pacman->nMovimentosCima;
    total += pacman->nMovimentosDireita;
    total += pacman->nMovimentosEsquerda;
    return total;
}

int ObtemNumeroMovimentosSemPontuarPacman(tPacman* pacman){
    return ObtemNumeroAtualMovimentosPacman(pacman) - ObtemPontuacaoAtualPacman(pacman);
}


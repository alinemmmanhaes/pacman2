#ifndef TARQUIVOS_H_
#define TARQUIVOS_H_

#include <stdlib.h>
#include <stdio.h>
#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"

typedef struct tRanking{
    char mov;
    int frutas;
    int parede;
    int numero;
} tRanking;

/**
 * Gera conteudo do arquivo inicializacao.txt
 * Imprime o mapa e informa a posicao inicial do pacman.
 * \param diretorio diretorio do arquivo
 * \param mapa ponteiro para mapa do jogo
*/
tPosicao* Inicializacao(tMapa* mapa);

void Resumo(tPacman* pacman);

void Estatisticas(tPacman* pacman);

void Ranking(tPacman* pacman);

void DesalocaRanking(tRanking* ranking);

void DesalocaResumo(tMovimento** resumo, tPacman* pacman);

#endif
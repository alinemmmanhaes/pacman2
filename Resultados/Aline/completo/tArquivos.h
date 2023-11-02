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
 * Gera conteudo do arquivo inicializacao.txt.
 * Imprime o mapa e informa a posicao inicial do pacman.
 * \param mapa ponteiro para mapa do jogo
*/
tPosicao* Inicializacao(tMapa* mapa);

/**
 * Gera conteudo do arquivo resumo.txt.
 * Imprime os movimentos significativos do jogo.
 * \param pacman ponteiro para o pacman do jogo
*/
void Resumo(tPacman* pacman);

/**
 * Gera conteudo do arquivo estatisticas.txt.
 * Imprime os dados de cada tipo de movimento e colisao com a parede.
 * \param pacman ponteiro para pacman do jogo
*/
void Estatisticas(tPacman* pacman);

/**
 * Gera conteudo do arquivo ranking.txt.
 * Imprime os dados de cada movimento, comida e colisao com a parede.
 * Ordena os movimentos como especificado na descricao do trabalho.
 * \param pacman ponteiro para pacman do jogo
*/
void Ranking(tPacman* pacman);

/**
 * Libera o espaco alocado pelo vetor de movimentos usado no arquivo ranking.txt.
 * \param ranking ponteiro para ranking de movimentos do jogo
*/
void DesalocaRanking(tRanking* ranking);

/**
 * Libera o espaco alocado pelo vetor de movimentos significativos clonado para o resumo.txt.
 * \param resumo ponteiro para os movimentos significativos clonados
 * \param pacman ponteiro para pacman do jogo
*/
void DesalocaResumo(tMovimento** resumo, tPacman* pacman);

#endif
#ifndef TFANTASMA_H_
#define TFANTASMA_H_

#include "tPosicao.h"
#include "tMovimento.h"
#include "tMapa.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct tFantasma{
    /* Posição atual do fantasma (linha,coluna) */
    tPosicao *posicaoatual;
    /* Posição anterior do fantasma (linha,coluna) */
    tPosicao *posicaoanterior;

    /*guarda 1 se estiver feito indo para a direita e 0 caso va para a esquerda*/
    int direita;
    /*guarda 1 se estiver feito indo para cima e 0 caso va para baixo*/
    int cima;
    /*guarda 1 se ele existir e 0 caso nao*/
    int existe;
    /*guarda 1 se estiver em uma posição que tinha uma comida e 0 caso nao*/
    int comida;
    /*Letra do Fantasma*/
    char nome;
} tFantasma;

/**
 * Cria o fantasma dinamicamente. Caso dê erro na alocação da estrutura tPacman, 
 * retorna NULL. 
 * Roda o mapa procurando se o fantasma existe.
 * Caso não dê erros, retorna o ponteiro para o tFantasma alocado.
 * \param mapa Ponteiro para tMapa do jogo
 * \param nome Caractere do fantasma a ser criado
 */
tFantasma* CriaFantasma(tMapa* mapa, char nome);

/**
 * Retorna true se o fantasma existe e false caso não.
 * \param fantasma Ponteiro para o tFantasma analisado
*/
bool ExisteFantasma(tFantasma* fantasma);

/**
 * Funcao para fantasmas que se movem na horizontal.
 * Verifica se o fantasma esta na ponta. 
 * Caso esteja, altera o seu sentido e o move. 
 * Caso não esteja, apenas o move.
 * \param fantasma Ponteiro para o tFantasma analisado
 * \param mapa Ponteiro para o tMapa do jogo
*/
void AndaFantasmaHorizontal(tFantasma* fantasma, tMapa* mapa);

/**
 * Funcao para fantasmas que se movem na vertical.
 * Verifica se o fantasma esta na ponta. 
 * Caso esteja, altera o seu sentido e o move. 
 * Caso não esteja, apenas o move.
 * \param fantasma Ponteiro para o tFantasma analisado
 * \param mapa Ponteiro para o tMapa do jogo
*/
void AndaFantasmaVertical(tFantasma* fantasma, tMapa* mapa);

/**
 * Verifica se o fantasma f estava em cima de uma posicao de comida na ultima rodada.
 * Retorna 1 caso tenha comida e 0 caso nao.
 * \param fantasma Ponteiro para o tFantasma analisado
*/
int VerificaComida(tFantasma* fantasma);

/**
 * Altera o valor da variavel comida para seu complemento
 * \param fantasma Ponteiro para o tFantasma analisado
*/
void TiraComida(tFantasma* fantasma);

/**
 * Retorna o nome do fantasma.
 * \param fantasma Ponteiro para o tFantasma analisado
*/
char ObtemNomeFantasma(tFantasma* fantasma);

/**
 * Retorna a posicao do fantasma.
 * \param fantasma Ponteiro para o tFantasma analisado
*/
tPosicao* ObtemPosicaoFantasma(tFantasma* fantasma);

/**
 * Caso o fantasma seja diferente de NULL, libera o espaço 
 * alocado para a estrutura tFantasma.
 * \param fantasma Ponteiro para o tFantasma analisado
 */
void DesalocaPacman(tFantasma* fantasma);

#endif
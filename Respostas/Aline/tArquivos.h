#ifndef TARQUIVOS_H_
#define TARQUIVOS_H_

#include <stdlib.h>
#include <stdio.h>
#include "tMapa.h"

/**
 * Gera conteudo do arquivo inicializacao.txt
 * Imprime o mapa e informa a posicao inicial do pacman.
 * \param diretorio diretorio do arquivo
 * \param mapa ponteiro para mapa do jogo
*/
tPosicao* Inicializacao(const char* diretorio, tMapa* mapa);

#endif
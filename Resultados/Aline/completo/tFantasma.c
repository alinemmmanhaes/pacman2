#include "tFantasma.h"

tFantasma* CriaFantasma(tMapa* mapa, char nome){
    tFantasma* fantasma = malloc(sizeof(tFantasma));
    if(fantasma == NULL){
        return NULL;
    }

    //cria fantasma com o nome enviado por paramentro e inicializa variaveis zeradas (ou NULL)
    fantasma->nome = nome;
    fantasma->existe = 0; //inicializa fantasma como inexistente
    fantasma->comida = 0;
    fantasma->posicaoanterior = NULL;
    fantasma->posicaoatual = NULL;

    //coloca as direcoes e sentidos com base no nome (tipo) do fantasma
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

    char c;
    //tenta localizar o fantasma com o nome dado no mapa
    for(int i=0; i<ObtemNumeroLinhasMapa(mapa); i++){
        for(int j=0; j<ObtemNumeroColunasMapa(mapa); j++){
            //Cria uma posicao para acessar item da posicao sem usar mapa->grid
            tPosicao* posicao = CriaPosicao(i, j);
            c = ObtemItemMapa(mapa, posicao);
            DesalocaPosicao(posicao);
            if(c == nome){ //se o achar, o coloca como existente e guarda sua posicao
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
    if(ExisteFantasma(fantasma)){//se o fantasma existir
        DesalocaPosicao(fantasma->posicaoanterior); //desaloca sua posicao anterior
        fantasma->posicaoanterior = ClonaPosicao(ObtemPosicaoFantasma(fantasma)); //e guarda uma nova posicao anterior (pre movimentacao)
        //movimenta o fantasma de acordo com o seu sentido
        if(fantasma->direita == 0){
            fantasma->posicaoatual->coluna--;
        }
        else{
            fantasma->posicaoatual->coluna++;
        }
        //se ele encontrar uma parede, inverte o sentido e atualiza a posicao
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
    if(ExisteFantasma(fantasma)){//se o fantasma existir
        DesalocaPosicao(fantasma->posicaoanterior);//desaloca sua posicao anterior
        fantasma->posicaoanterior = ClonaPosicao(ObtemPosicaoFantasma(fantasma));//e guarda uma nova posicao anterior (pre movimentacao)
        //movimenta o fantasma de acordo com o seu sentido
        if(fantasma->cima == 0){
            fantasma->posicaoatual->linha++;
        }
        else{
            fantasma->posicaoatual->linha--;
        }
        //se ele encontrar uma parede, inverte o sentido e atualiza a posicao
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
        //posicoes iguais = morte
        if(SaoIguaisPosicao(ObtemPosicaoFantasma(fantasma), ObtemPosicaoPacman(pacman))){
            MataPacman(pacman);
            return 1;
        }
        //posicoes anteriores iguais as atuais do outro = cruzamento = morte
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
    return fantasma->comida; //retorna a variavel comida do fantasma
}

void TiraComida(tFantasma* fantasma){
    //altera o valor de comida, para quando o fantasma sair ou entrar em cima de uma comida no mapa
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

void DesalocaFantasma(tFantasma* fantasma){
    //desaloca o fantasma e suas estruturas internas que foram alocadas tambem
    if(fantasma->posicaoanterior != NULL){
        DesalocaPosicao(fantasma->posicaoanterior);
    }
    if(fantasma->posicaoatual != NULL){
        DesalocaPosicao(fantasma->posicaoatual);
    }
    free(fantasma);
}
#ifndef MAO_H
#define MAO_H

#include "carta.h"
#include "rodada.h"

int comparar_cartas(Carta a, Carta b, Valor manilha);
int resolver_mao(Jogada* jogadas, int num_jogadores, Valor manilha);

#endif

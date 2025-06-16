#ifndef ALEATORIO2_H
#define ALEATORIO2_H

#include "../carta.h"
#include "../mao.h"

void iniciar_aleatorio2(int id, int total_jogadores);
void nova_rodada_aleatorio2(int rodada, Carta carta_virada, int n_cartas, Carta* mao);
int apostar_aleatorio2(const int* apostas);
int jogar_aleatorio2(const Carta* mesa, int num_na_mesa);
const char* nome_aleatorio2();

#endif

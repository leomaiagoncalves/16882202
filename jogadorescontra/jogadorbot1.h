#ifndef ALEATORIO1_H
#define ALEATORIO1_H

#include "../carta.h"

void iniciar_aleatorio1(int id, int total_jogadores);
void nova_rodada_aleatorio1(int rodada, Carta carta_virada, int n_cartas, Carta* mao);
int apostar_aleatorio1(const int* apostas);
int jogar_aleatorio1(const Carta* mesa, int num_na_mesa);
const char* nome_aleatorio1();

#endif

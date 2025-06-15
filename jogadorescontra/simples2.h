#ifndef simples2_H
#define simples2_H

#include "../carta.h"

void iniciar_simples2(int id, int total_jogadores);
void nova_rodada_simples2(int rodada, Carta carta_virada, int n_cartas, Carta* mao);
int apostar_simples2(const int* apostas);
int jogar_simples2(const Carta* mesa, int num_na_mesa);
const char* nome_simples2();

#endif

#ifndef simples_H
#define simples_H

#include "../carta.h"

void iniciar_simples(int id, int total_jogadores);
void nova_rodada_simples(int rodada, Carta carta_virada, int n_cartas, Carta* mao);
int apostar_simples(const int* apostas);
int jogar_simples(const Carta* mesa, int num_na_mesa);
const char* nome_simples();

#endif

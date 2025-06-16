#ifndef JOGADOR_16882202_H
#define JOGADOR_16882202_H

#include "../carta.h"
#include "../mao.h"

void iniciar_jogador_16882202(int id, int total);
void nova_rodada_jogador_16882202(int rodada, Carta carta_virada, int n_cartas, Carta* mao);
int apostar_jogador_16882202(int* apostas);
int jogar_jogador_16882202(Carta* mesa, int num_na_mesa, int* cartas_jogadas, int n_cartas_restantes);
const char* nome_jogador_16882202(void);

#endif

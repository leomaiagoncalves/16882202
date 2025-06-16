#ifndef RODADA_H
#define RODADA_H

#include "carta.h"

#define MAX_JOGADORES 6
#define MAX_CARTAS_MAO 6

typedef struct {
    Carta carta;
    int jogador;
} Jogada;

typedef struct {
    int numero;
    int num_jogadores;
    int cartas_por_jogador;
    int jogador_inicial;

    Carta carta_virada;
    Valor manilha;

    Carta maos[MAX_JOGADORES][MAX_CARTAS_MAO];
    int cartas_restantes[MAX_JOGADORES];
    int apostas[MAX_JOGADORES];
    int vitorias[MAX_JOGADORES];
    int pontos_acumulados;
} Rodada;

void iniciar_rodada(Rodada* r, int numero, int num_jogadores, int jogador_inicial, Carta* baralho);
void imprimir_maos(const Rodada* r);
void atualizar_jogador_inicial(Rodada* r, int vencedor);

void embaralhar_e_distribuir_maos(Rodada* r, int num_jogadores, Carta* baralho);
void processar_resultado_turno(Rodada* r, int vencedor);
void atualizar_pontuacoes(Rodada* r, int* placar);

#endif

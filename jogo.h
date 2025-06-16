#ifndef JOGO_H
#define JOGO_H

#include "mao.h"
#include "rodada.h"
#include "baralho.h"

#define MAX_JOGADORES 6
#define NUM_RODADAS 5

typedef struct {
    Carta baralho[TOTAL_CARTAS];
    int penalidades[MAX_JOGADORES];
    const char* nomes[MAX_JOGADORES];
    int jogador_inicial_mao;
    int jogador_inicial_rodada;
    int num_jogadores;
    int num_rodadas;
    Rodada rodadas[NUM_RODADAS];
} Jogo;

// Variável global que representa o estado do jogo
extern Jogo jogo;

// Funções principais do jogo
int checar_e_processar_descarte(int idx, int jogador, Rodada* r, Jogada* jogadas);
void imprimir_maos_jogadores(int rodada, const Rodada* r);
void imprimir_mesa(const Jogada* jogadas);
void imprimir_resultados_rodada(int rodada, const Rodada* r);
void processar_resultado_mao(int vencedor, Rodada* r);
void executar_rodada(int rodada);
void imprimir_resultado_final();
void jogar_rodada(Rodada* r);

void embaralhar_e_distribuir_maos(Jogo* jogo);
void processar_resultado_turno(Rodada* r, Jogada* jogadas);
void atualizar_pontuacoes(Rodada* r);


void iniciar_jogadores();
void informar_maos_para_jogadores(int rodada, const Rodada* r);
void coletar_apostas(Rodada* r);
int processar_jogadas(Rodada* r, Jogada* jogadas);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../baralho.h"
#include "../mao.h"
#include "../carta.h"

static int meu_id = 0;
static int total_jogadores = 0;
static int num_cartas = 0;
static Carta minha_mao[6];

void iniciar_simples(int id, int total) {
    meu_id = id;
    total_jogadores = total;
    srand(time(NULL) + id * 303);
}

void nova_rodada_simples(int rodada, Carta carta_virada, int n_cartas, Carta* mao) {
    num_cartas = n_cartas;
    for (int i = 0; i < n_cartas; i++) {
        minha_mao[i] = mao[i];
    }
}

int apostar_simples(const int* apostas) {
    return rand() % (num_cartas + 1);
}

int jogar_simples(const Carta* mesa, int num_na_mesa) {
    int tentativas = 0;
    int idx;
    do {
        idx = rand() % num_cartas;
        tentativas++;
        if (tentativas > 100) return -1;  // evita loop infinito
    } while (minha_mao[idx].valor == USADA.valor && minha_mao[idx].naipe == USADA.naipe);

    minha_mao[idx] = USADA;
    return idx;
}

const char* nome_simples() {
    return "Simples";
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../baralho.h"
#include "../mao.h"

static int meu_id = 0;
static int total_jogadores = 0;
static int num_cartas = 0;
static Carta minha_mao[6];

void iniciar_aleatorio1(int id, int total) {
    meu_id = id;
    total_jogadores = total;
    srand(time(NULL) + id * 101); // semente diferente para cada jogador
}

void nova_rodada_aleatorio1(int rodada, Carta carta_virada, int n_cartas, Carta* mao) {
    num_cartas = n_cartas;
    for (int i = 0; i < n_cartas; i++) {
        minha_mao[i] = mao[i];
    }
}

int apostar_aleatorio1(const int* apostas) {
    // aposta aleatória entre 0 e num_cartas
    return rand() % (num_cartas + 1);
}

int jogar_aleatorio1(const Carta* mesa, int num_na_mesa) {
    // escolhe uma carta aleatória válida
    int idx;
    do {
        idx = rand() % num_cartas;
    } while (minha_mao[idx].valor == -1); // carta já usada

    minha_mao[idx] = (Carta){-1, -1}; // marca como usada
    return idx;
}

const char* nome_aleatorio1() {
    return "Aleatório 1";
}

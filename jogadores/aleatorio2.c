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

void iniciar_aleatorio2(int id, int total) {
    meu_id = id;
    total_jogadores = total;
    srand(time(NULL) + id * 202);
}

void nova_rodada_aleatorio2(int rodada, Carta carta_virada, int n_cartas, Carta* mao) {
    num_cartas = n_cartas;
    for (int i = 0; i < n_cartas; i++) {
        minha_mao[i] = mao[i];
    }
}

int apostar_aleatorio2(const int* apostas) {
    return rand() % (num_cartas + 1);
}

int jogar_aleatorio2(const Carta* mesa, int num_na_mesa) {
    int tentativas = 0;
    int idx;
    do {
        idx = rand() % num_cartas;
        tentativas++;
        if (tentativas > 100) {
            return -1;
        }
    } while (minha_mao[idx].valor == USADA.valor && minha_mao[idx].naipe == USADA.naipe);

    minha_mao[idx] = USADA;
    return idx;
}

const char* nome_aleatorio2() {
    return "Aleatório 2";
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../baralho.h"
#include "../mao.h"
#include "../carta.h"  // inclua para usar USADA

static int meu_id = 0;
static int total_jogadores = 0;
static int num_cartas = 0;
static Carta minha_mao[6];

void iniciar_aleatorio1(int id, int total) {
    meu_id = id;
    total_jogadores = total;
    srand(time(NULL) + id * 101);
}

void nova_rodada_aleatorio1(int rodada, Carta carta_virada, int n_cartas, Carta* mao) {
    num_cartas = n_cartas;
    for (int i = 0; i < n_cartas; i++) {
        minha_mao[i] = mao[i];
    }
}

int apostar_aleatorio1(const int* apostas) {
    return rand() % (num_cartas + 1);
}

int jogar_aleatorio1(const Carta* mesa, int num_na_mesa) {
    int tentativas = 0;
    int idx;
    do {
        idx = rand() % num_cartas;
        tentativas++;
        if (tentativas > 100) {
            // Todas as cartas usadas ou loop evitado
            return -1;
        }
    } while (minha_mao[idx].valor == USADA.valor && minha_mao[idx].naipe == USADA.naipe);

    minha_mao[idx] = USADA;
    return idx;
}

const char* nome_aleatorio1() {
    return "Aleatório 1";
}

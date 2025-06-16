#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../mao.h"

static int meu_id;
static int total_jogadores;
static int rodada_atual;
static Carta carta_manilha;
static int n_cartas_mao;
static Carta minha_mao[6];

int comparar_cartas_jogador_16882202(Carta a, Carta b, Valor manilha) {
    if (a.valor == manilha && b.valor != manilha) return 1;
    if (b.valor == manilha && a.valor != manilha) return -1;
    if (a.valor == manilha && b.valor == manilha) return a.naipe - b.naipe;
    return a.valor - b.valor;
}

void iniciar_jogador_16882202(int id, int total) {
    meu_id = id;
    total_jogadores = total;
    srand((unsigned int)(time(NULL) + meu_id));
}

void nova_rodada_jogador_16882202(int rodada, Carta carta_virada, int n_cartas, Carta* mao) {
    rodada_atual = rodada;
    carta_manilha = definir_manilha(carta_virada);
    n_cartas_mao = n_cartas;
    for (int i = 0; i < n_cartas; i++) {
        minha_mao[i] = mao[i];
    }
}

int apostar_jogador_16882202(int* apostas) {
    int aposta_base = 0;
    for (int i = 0; i < n_cartas_mao; i++) {
        if (minha_mao[i].valor == carta_manilha) {
            aposta_base += 2;
        } else if (minha_mao[i].valor >= carta_manilha - 1) {
            aposta_base += 1;
        }
    }
    if (aposta_base > n_cartas_mao)
        aposta_base = n_cartas_mao;
    if ((rand() % 100) < 20 && aposta_base < n_cartas_mao) {
        aposta_base++;
    }
    if (aposta_base == 0 && n_cartas_mao > 0) {
        aposta_base = 1;
    }
    return aposta_base;
}

int jogar_jogador_16882202(Carta* mesa, int num_na_mesa, int* cartas_jogadas, int n_cartas_restantes) {
    int vence(Carta a, Carta b) {
        int cmp = comparar_cartas_jogador_16882202(a, b, carta_manilha);
        return cmp > 0;
    }

    if (num_na_mesa == 0) {
        int idx_min = 0;
        for (int i = 1; i < n_cartas_mao; i++) {
            if (comparar_cartas_jogador_16882202(minha_mao[i], minha_mao[idx_min], carta_manilha) < 0)
                idx_min = i;
        }
        for (int i = idx_min; i < n_cartas_mao - 1; i++)
            minha_mao[i] = minha_mao[i+1];
        n_cartas_mao--;
        return idx_min;
    }

    int idx_vencedor = 0;
    Carta carta_vencedora = mesa[0];
    for (int i = 1; i < num_na_mesa; i++) {
        if (vence(mesa[i], carta_vencedora)) {
            carta_vencedora = mesa[i];
            idx_vencedor = i;
        }
    }

    int idx_carta_jogar = -1;
    Carta melhor_carta;
    for (int i = 0; i < n_cartas_mao; i++) {
        if (vence(minha_mao[i], carta_vencedora)) {
            if (idx_carta_jogar == -1 || comparar_cartas_jogador_16882202(minha_mao[i], melhor_carta, carta_manilha) < 0) {
                idx_carta_jogar = i;
                melhor_carta = minha_mao[i];
            }
        }
    }

    if (idx_carta_jogar != -1) {
        for (int i = idx_carta_jogar; i < n_cartas_mao - 1; i++)
            minha_mao[i] = minha_mao[i+1];
        n_cartas_mao--;
        return idx_carta_jogar;
    }

    int idx_min = 0;
    for (int i = 1; i < n_cartas_mao; i++) {
        if (comparar_cartas_jogador_16882202(minha_mao[i], minha_mao[idx_min], carta_manilha) < 0)
            idx_min = i;
    }
    for (int i = idx_min; i < n_cartas_mao - 1; i++)
        minha_mao[i] = minha_mao[i+1];
    n_cartas_mao--;
    return idx_min;
}

const char* nome_jogador_16882202(void) {
    return "AnaliticoBlefador_16882202";
}

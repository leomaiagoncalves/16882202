#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "baralho.h"
#include "rodada.h"
#include "mao.h"
#include "jogo.h"

#include "jogadores/aleatorio1.h"
#include "jogadores/aleatorio2.h"
#include "jogadores/simples1.h"
#include "jogadores/jogador_16882202.h"

#define NUM_JOGADORES 4

Jogo jogo;

void iniciar_jogadores() {
    jogo.nomes[0] = nome_aleatorio1();
    jogo.nomes[1] = nome_aleatorio2();
    jogo.nomes[2] = nome_simples1();  // <- renomeado aqui
    jogo.nomes[3] = nome_jogador_16882202();

    iniciar_aleatorio1(0, NUM_JOGADORES);
    iniciar_aleatorio2(1, NUM_JOGADORES);
    iniciar_simples1(2, NUM_JOGADORES);  // <- renomeado aqui
    iniciar_16882202(3, NUM_JOGADORES);

    memset(jogo.penalidades, 0, sizeof(jogo.penalidades));
    jogo.jogador_inicial_mao = jogo.jogador_inicial_rodada = 0;
    jogo.num_jogadores = NUM_JOGADORES;
}

void informar_maos_para_jogadores(int rodada, const Rodada* r) {
    nova_rodada_aleatorio1(rodada, r->carta_virada, r->cartas_por_jogador, r->maos[0]);
    nova_rodada_aleatorio2(rodada, r->carta_virada, r->cartas_por_jogador, r->maos[1]);
    nova_rodada_simples1(rodada, r->carta_virada, r->cartas_por_jogador, r->maos[2]);  // <- renomeado aqui
    nova_rodada_16882202(rodada, r->carta_virada, r->cartas_por_jogador, r->maos[3]);
}

// Coleta apostas em ordem circular
void coletar_apostas(Rodada* r) {
    printf("Apostas:\n");

    for (int i = 0; i < NUM_JOGADORES; i++) {
        r->apostas[i] = -1;
    }

    for (int i = 0; i < NUM_JOGADORES; i++) {
        int j = (jogo.jogador_inicial_rodada + i) % NUM_JOGADORES;

        if (j == 0) r->apostas[j] = apostar_aleatorio1(r->apostas);
        else if (j == 1) r->apostas[j] = apostar_aleatorio2(r->apostas);
        else if (j == 2) r->apostas[j] = apostar_simples1(r->apostas);  // <- renomeado aqui
        else if (j == 3) r->apostas[j] = apostar_16882202(r->apostas);

        printf("%s:\t%d", jogo.nomes[j], r->apostas[j]);
        getchar();
    }
    printf("\n");
}

// Processa jogadas dos jogadores em ordem circular
int processar_jogadas(Rodada* r, Jogada* jogadas) {
    int novo_jogador_inicial = jogo.jogador_inicial_mao;

    for (int i = 0; i < jogo.num_jogadores; i++) {
        int j = (jogo.jogador_inicial_mao + i) % NUM_JOGADORES;

        int idx = -1;

        if (j == 0) idx = jogar_aleatorio1(NULL, 0);
        else if (j == 1) idx = jogar_aleatorio2(NULL, 0);
        else if (j == 2) idx = jogar_simples1(NULL, 0);  // <- renomeado aqui
        else if (j == 3) idx = jogar_16882202(NULL, 0);

        if (checar_e_processar_descarte(idx, j, r, jogadas)) {
            printf("Jogador %s tentou descartar uma carta inválida e foi eliminado!\n", jogo.nomes[j]);

            if (j == novo_jogador_inicial) {
                novo_jogador_inicial = (novo_jogador_inicial + 1) % jogo.num_jogadores;
            }
        }
    }

    return novo_jogador_inicial;
}

int main() {
    iniciar_jogadores();

    for (int rodada = 1; rodada <= NUM_RODADAS; rodada++) {
        executar_rodada(rodada);
    }

    imprimir_resultado_final();
    return 0;
}

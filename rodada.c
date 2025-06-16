#include "cartas.h"
#include "rodada.h"
#include "baralho.h"
#include <stdio.h>
#include <string.h>

void distribuir_cartas(Rodada* r, int num_jogadores, Carta* baralho, int* idx) {
    for (int j = 0; j < num_jogadores; j++) {
        for (int c = 0; c < r->cartas_por_jogador; c++) {
            r->maos[j][c] = baralho[(*idx)++];
        }
    }
}

void iniciar_rodada(Rodada* r, int numero, int num_jogadores, int jogador_inicial, Carta* baralho) {
    r->numero = numero;
    r->num_jogadores = num_jogadores;
    r->cartas_por_jogador = numero + 1;
    r->jogador_inicial = jogador_inicial;
    r->pontos_acumulados = 0;

    embaralhar(baralho, TOTAL_CARTAS);

    int idx = 0;
    distribuir_cartas(r, num_jogadores, baralho, &idx);

    for (int j = 0; j < num_jogadores; j++) {
        r->cartas_restantes[j] = r->cartas_por_jogador;
        r->apostas[j] = 0;
        r->vitorias[j] = 0;
    }

    r->carta_virada = baralho[idx++];
    r->manilha = definir_manilha(r->carta_virada);
}

void atualizar_jogador_inicial(Rodada* r, int vencedor) {
    if (vencedor != -1) {
        r->jogador_inicial = vencedor;
    }
}

void imprimir_maos(const Rodada* r) {
    for (int j = 0; j < r->num_jogadores; j++) {
        printf("Jogador %d: ", j);
        for (int c = 0; c < r->cartas_restantes[j]; c++) {
            imprimir_carta(r->maos[j][c]);
            printf(" ");
        }
        printf("\n");
    }
}

void embaralhar_e_distribuir_maos(Rodada* r, int num_jogadores, Carta* baralho) {
    embaralhar(baralho, TOTAL_CARTAS);
    int idx = 0;
    distribuir_cartas(r, num_jogadores, baralho, &idx);
}

void processar_resultado_turno(Rodada* r, int vencedor) {
    if (vencedor >= 0 && vencedor < r->num_jogadores) {
        r->vitorias[vencedor]++;
        r->pontos_acumulados++;
    }
}

void atualizar_pontuacoes(Rodada* r, int* placar) {
    for (int i = 0; i < r->num_jogadores; i++) {
        placar[i] += r->vitorias[i];
    }
}

// Função para calcular o vencedor de uma rodada, dado o vetor de jogadas
int calcular_vencedor(Rodada* r, Jogada* jogadas) {
    int vencedor = -1;
    Carta carta_maior = { .valor = QUATRO, .naipe = OUROS }; // Carta inicial mínima
    for (int i = 0; i < r->num_jogadores; i++) {
        Carta c = jogadas[i].carta;
        if (comparar_cartas(c, carta_maior, r->manilha) > 0) {
            carta_maior = c;
            vencedor = i;
        }
    }
    return vencedor;
}

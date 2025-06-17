#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../mao.h"

// Definindo manilha: próximo valor (com módulo 13 para ciclo)
Valor definir_manilha(Carta carta_virada) {
    return (carta_virada.valor + 1) % 13;
}

// Variáveis internas do jogador
static int meu_id;
static int total_jogadores;
static int rodada_atual;
static Valor carta_manilha;
static int n_cartas_mao;
static Carta minha_mao[6];

// Comparação de cartas considerando manilha e naipe
int comparar_cartas_jogador_16882202(Carta a, Carta b, Valor manilha) {
    if (a.valor == manilha && b.valor != manilha) return 1;
    if (b.valor == manilha && a.valor != manilha) return -1;
    if (a.valor == manilha && b.valor == manilha) return b.naipe - a.naipe; // naipe mais forte ganha
    return a.valor - b.valor;
}

// Inicializa o jogador
void iniciar_jogador_16882202(int id, int total) {
    meu_id = id;
    total_jogadores = total;
    srand((unsigned int)(time(NULL) + meu_id));
}

// Recebe nova rodada
void nova_rodada_jogador_16882202(int rodada, Carta carta_virada, int n_cartas, Carta* mao) {
    rodada_atual = rodada;
    carta_manilha = definir_manilha(carta_virada);
    n_cartas_mao = n_cartas;

    for (int i = 0; i < n_cartas; i++) {
        minha_mao[i] = mao[i];
        printf("[Rodada %d] Carta recebida %d: valor=%d, naipe=%d\n", rodada, i, mao[i].valor, mao[i].naipe);
    }
}

// Função de aposta
int apostar_jogador_16882202(int* apostas) {
    int aposta = 0;

    for (int i = 0; i < n_cartas_mao; i++) {
        if (minha_mao[i].valor == carta_manilha) {
            aposta += 2;
        } else if (minha_mao[i].valor >= carta_manilha - 1) {
            aposta += 1;
        }
    }

    if (aposta > n_cartas_mao) aposta = n_cartas_mao;

    // Adiciona chance de blefar
    if ((rand() % 100) < 20 && aposta < n_cartas_mao) {
        aposta++;
        printf("[BLEFE] Aumentando aposta!\n");
    }

    // Nunca aposta 0 se tiver cartas
    if (aposta == 0 && n_cartas_mao > 0) {
        aposta = 1;
        printf("[MIN APOSTA] Forçando aposta mínima\n");
    }

    printf("[APOSTA] Rodada %d: Apostando %d com manilha %d\n", rodada_atual, aposta, carta_manilha);
    return aposta;
}

// Função para jogar carta
int jogar_jogador_16882202(Carta* mesa, int num_na_mesa, int* cartas_jogadas, int n_cartas_restantes) {
    int vence(Carta a, Carta b) {
        return comparar_cartas_jogador_16882202(a, b, carta_manilha) > 0;
    }

    int idx_jogada = 0;

    // Se for o primeiro a jogar
    if (num_na_mesa == 0) {
        for (int i = 1; i < n_cartas_mao; i++) {
            if (comparar_cartas_jogador_16882202(minha_mao[i], minha_mao[idx_jogada], carta_manilha) < 0)
                idx_jogada = i;
        }
    } else {
        // Tem cartas na mesa, tentar vencer
        Carta carta_mesa = mesa[0];
        for (int i = 1; i < num_na_mesa; i++) {
            if (vence(mesa[i], carta_mesa)) {
                carta_mesa = mesa[i];
            }
        }

        int idx_candidato = -1;
        for (int i = 0; i < n_cartas_mao; i++) {
            if (vence(minha_mao[i], carta_mesa)) {
                if (idx_candidato == -1 || comparar_cartas_jogador_16882202(minha_mao[i], minha_mao[idx_candidato], carta_manilha) < 0) {
                    idx_candidato = i;
                }
            }
        }

        if (idx_candidato != -1) {
            idx_jogada = idx_candidato;
        } else {
            for (int i = 1; i < n_cartas_mao; i++) {
                if (comparar_cartas_jogador_16882202(minha_mao[i], minha_mao[idx_jogada], carta_manilha) < 0)
                    idx_jogada = i;
            }
        }
    }

    // Remover a carta da mão
    Carta carta_jogada = minha_mao[idx_jogada];
    for (int i = idx_jogada; i < n_cartas_mao - 1; i++) {
        minha_mao[i] = minha_mao[i + 1];
    }
    n_cartas_mao--;

    printf("[JOGADA] Rodada %d: Jogando carta valor=%d, naipe=%d\n", rodada_atual, carta_jogada.valor, carta_jogada.naipe);
    return idx_jogada;
}

// Nome visível do jogador
const char* nome_jogador_16882202(void) {
    return "Jogador_16882202";
}

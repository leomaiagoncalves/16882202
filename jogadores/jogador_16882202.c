#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "carta.h"

// Variáveis globais para estado do jogador
static int meu_id;
static int total_jogadores;
static int rodada_atual;
static Carta carta_manilha;
static int n_cartas_mao;
static Carta minha_mao[6];

// Função para comparar cartas considerando manilha e naipe
int comparar_cartas_16882202(Carta a, Carta b, Valor manilha) {
    if (a.valor == manilha && b.valor != manilha) return 1;
    if (b.valor == manilha && a.valor != manilha) return -1;
    if (a.valor == manilha && b.valor == manilha) return a.naipe - b.naipe;
    return a.valor - b.valor;
}

// Inicializa o jogador com ID e total de jogadores
void iniciar_16882202(int id, int total) {
    meu_id = id;
    total_jogadores = total;

    // Semente de aleatoriedade baseada no ID para blefes controlados
    srand((unsigned int)(time(NULL) + meu_id));
}

// Prepara para nova rodada recebendo a carta virada e cartas na mão
void nova_rodada_16882202(int rodada, Carta carta_virada, int n_cartas, Carta* mao) {
    rodada_atual = rodada;
    carta_manilha = definir_manilha(carta_virada);
    n_cartas_mao = n_cartas;

    for (int i = 0; i < n_cartas; i++) {
        minha_mao[i] = mao[i];
    }
}

// Decide a aposta com base nas cartas na mão e estratégia analítica + blefe
int apostar_16882202(int* apostas) {
    int aposta_base = 0;

    // Conta quantas cartas são manilhas ou próximas da manilha
    for (int i = 0; i < n_cartas_mao; i++) {
        if (minha_mao[i].valor == carta_manilha) {
            aposta_base += 2;  // Manilha forte
        } else if (minha_mao[i].valor >= carta_manilha - 1) {
            aposta_base += 1;  // Cartas altas próximas
        }
    }

    // Limitar aposta máxima ao número de cartas na mão
    if (aposta_base > n_cartas_mao)
        aposta_base = n_cartas_mao;

    // Blefe aleatório: 20% chance de apostar 1 a mais que base (máximo n_cartas_mao)
    if ((rand() % 100) < 20 && aposta_base < n_cartas_mao) {
        aposta_base++;
    }

    // Segurança: não aposta 0 nunca, aposta mínima 1 se a mão tiver cartas
    if (aposta_base == 0 && n_cartas_mao > 0) {
        aposta_base = 1;
    }

    return aposta_base;
}

// Escolhe a carta para jogar de forma analítica + blefe + segurança
int jogar_16882202(Carta* mesa, int num_na_mesa, int* cartas_jogadas, int n_cartas_restantes) {
    // Estratégia simplificada:
    // 1) Se for o primeiro a jogar na rodada, jogar a carta mais fraca (segurança)
    // 2) Se houver cartas na mesa, tenta vencer se possível (joga a menor carta que vence)
    // 3) Caso não consiga vencer, blefa jogando a carta mais fraca

    // Função auxiliar para saber se carta a vence carta b
    int vence(Carta a, Carta b) {
        int cmp = comparar_cartas_16882202(a, b, carta_manilha);
        return cmp > 0;
    }

    // Se primeira jogada da mão
    if (num_na_mesa == 0) {
        // joga a carta mais fraca (menor valor considerando manilha)
        int idx_min = 0;
        for (int i = 1; i < n_cartas_mao; i++) {
            if (comparar_cartas_16882202(minha_mao[i], minha_mao[idx_min], carta_manilha) < 0)
                idx_min = i;
        }
        Carta escolhida = minha_mao[idx_min];
        // Remove carta da mão (marcar como inválida)
        for (int i = idx_min; i < n_cartas_mao - 1; i++)
            minha_mao[i] = minha_mao[i+1];
        n_cartas_mao--;
        return idx_min;
    }

    // Se não for o primeiro a jogar, tenta vencer a jogada mais forte na mesa
    int idx_vencedor = 0;
    Carta carta_vencedora = mesa[0];
    for (int i = 1; i < num_na_mesa; i++) {
        if (vence(mesa[i], carta_vencedora)) {
            carta_vencedora = mesa[i];
            idx_vencedor = i;
        }
    }

    // Tenta achar a menor carta que vence a carta vencedora na mesa
    int idx_carta_jogar = -1;
    Carta melhor_carta;
    for (int i = 0; i < n_cartas_mao; i++) {
        if (vence(minha_mao[i], carta_vencedora)) {
            if (idx_carta_jogar == -1 || comparar_cartas_16882202(minha_mao[i], melhor_carta, carta_manilha) < 0) {
                idx_carta_jogar = i;
                melhor_carta = minha_mao[i];
            }
        }
    }

    if (idx_carta_jogar != -1) {
        // Jogar a menor carta que vence
        Carta escolhida = minha_mao[idx_carta_jogar];
        for (int i = idx_carta_jogar; i < n_cartas_mao - 1; i++)
            minha_mao[i] = minha_mao[i+1];
        n_cartas_mao--;
        return idx_carta_jogar;
    }

    // Não tem carta para vencer, blefa jogando a carta mais fraca
    int idx_min = 0;
    for (int i = 1; i < n_cartas_mao; i++) {
        if (comparar_cartas_16882202(minha_mao[i], minha_mao[idx_min], carta_manilha) < 0)
            idx_min = i;
    }
    Carta escolhida = minha_mao[idx_min];
    for (int i = idx_min; i < n_cartas_mao - 1; i++)
        minha_mao[i] = minha_mao[i+1];
    n_cartas_mao--;
    return idx_min;
}

// Retorna o nome do jogador para exibição
const char* nome_16882202() {
    return "AnaliticoBlefador_16882202";
}

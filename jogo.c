#include <stdio.h>
#include <stdlib.h>

#include "baralho.h"
#include "rodada.h"
#include "mao.h"
#include "jogo.h"

Jogo jogo;

int checar_e_processar_descarte(int idx, int jogador, Rodada* r, Jogada* jogadas) {
    if (idx < 0 || idx >= r->cartas_por_jogador) {
        jogo.penalidades[jogador] = 9999;
        jogadas[jogador].jogador_id = jogador;
        return 1;
    }

    Carta carta_escolhida = r->maos[jogador][idx];

    if (carta_foi_usada(carta_escolhida)) {
        jogo.penalidades[jogador] = 9999;
        jogadas[jogador].jogador_id = jogador;
        return 1;
    }

    jogadas[jogador].jogador_id = jogador;
    jogadas[jogador].carta = carta_escolhida;

    r->maos[jogador][idx] = USADA;
    r->cartas_restantes[jogador]--;

    return 0;
}

void imprimir_maos_jogadores(int rodada, const Rodada* r) {
    printf("Rodada %d\n", rodada);
    for (int j = 0; j < jogo.num_jogadores; j++) {
        printf("Jogador %s:\t", jogo.nomes[j]);
        for (int c = 0; c < r->cartas_por_jogador; c++) {
            imprimir_carta(r->maos[j][c]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

void imprimir_mesa(const Jogada* jogadas) {
    printf("Mesa:\n");
    for (int i = 0; i < jogo.num_jogadores; i++) {
        int j = (jogo.jogador_inicial_mao + i) % jogo.num_jogadores;
        printf("%s:\t", jogo.nomes[jogadas[j].jogador_id]);
        imprimir_carta(jogadas[j].carta);
        printf("\n");
    }
    printf("\n");
}

void imprimir_resultados_rodada(int rodada, const Rodada* r) {
    printf("Resultados da rodada %d:\n", rodada);
    for (int j = 0; j < jogo.num_jogadores; j++) {
        int erro = abs(r->apostas[j] - r->vitorias[j]);
        jogo.penalidades[j] += erro;
        printf("%s:\t|%d - %d| = %d\n", jogo.nomes[j], r->vitorias[j], r->apostas[j], erro);
    }
    printf("\n");
}

void processar_resultado_mao(int vencedor, Rodada* r) {
    if (vencedor != -1) {
        printf("Vencedor da mão: %s\n\n", jogo.nomes[vencedor]);
        r->vitorias[vencedor]++;
        jogo.jogador_inicial_mao = vencedor;
    } else {
        printf("Mão empatada!\n\n");
        r->pontos_acumulados++;
    }
}

void jogar_rodada(Rodada* r) {
    for (int i = 0; i < r->cartas_por_jogador; i++) {
        Jogada jogadas[jogo.num_jogadores];
        processar_jogadas(r, jogadas);
        imprimir_mesa(jogadas);
        int vencedor = resolver_mao(jogadas, jogo.num_jogadores, r->manilha);
        processar_resultado_mao(vencedor, r);
        getchar();
    }
}

void executar_rodada(int rodada) {
    Rodada r;
    inicializar_baralho(jogo.baralho);
    iniciar_rodada(&r, rodada, jogo.num_jogadores, jogo.jogador_inicial_rodada, jogo.baralho);
    informar_maos_para_jogadores(rodada, &r);
    imprimir_maos_jogadores(rodada, &r);

    printf("Carta virada: ");
    imprimir_carta(r.carta_virada);
    printf("\n\n");
    getchar();

    coletar_apostas(&r);
    jogar_rodada(&r);
    imprimir_resultados_rodada(rodada, &r);
    getchar();

    jogo.jogador_inicial_rodada = (jogo.jogador_inicial_rodada + 1) % jogo.num_jogadores;
    jogo.jogador_inicial_mao = jogo.jogador_inicial_rodada;
}

void imprimir_resultado_final() {
    printf("Resultado Final:\n");
    for (int j = 0; j < jogo.num_jogadores; j++) {
        printf("%s:\t%d\n", jogo.nomes[j], jogo.penalidades[j]);
    }
}

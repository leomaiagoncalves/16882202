CC = gcc
CFLAGS = -Wall -Wextra -std=c99
JOGADORES = jogadores/aleatorio1.c jogadores/aleatorio2.c jogadores/simples.c jogadores/jogador_16882202.c

OBJ = baralho.o mao.o rodada.o jogo.o

all: main teste_baralho teste_mao teste_rodada

main: main.c $(OBJ) $(JOGADORES)
	$(CC) $(CFLAGS) -o main main.c $(OBJ) $(JOGADORES)

baralho.o: baralho.c
	$(CC) $(CFLAGS) -c baralho.c

mao.o: mao.c
	$(CC) $(CFLAGS) -c mao.c

rodada.o: rodada.c
	$(CC) $(CFLAGS) -c rodada.c

jogo.o: jogo.c
	$(CC) $(CFLAGS) -c jogo.c

teste_baralho: baralho.c teste_baralho.c
	$(CC) $(CFLAGS) -o teste_baralho baralho.c teste_baralho.c

teste_mao: $(OBJ) teste_mao.c
	$(CC) $(CFLAGS) -o teste_mao $(OBJ) teste_mao.c

teste_rodada: rodada.c baralho.c teste_rodada.c
	$(CC) $(CFLAGS) -o teste_rodada rodada.c baralho.c teste_rodada.c

clean:
	rm -f *.o teste_baralho teste_mao main

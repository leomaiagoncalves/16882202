CC = gcc
CFLAGS = -Wall -Wextra -std=c99

JOGADORES_SRC = jogadores/aleatorio1.c jogadores/aleatorio2.c jogadores/simples.c jogadores/jogador_16882202.c
JOGADORES_OBJ = jogadores/aleatorio1.o jogadores/aleatorio2.o jogadores/simples.o jogadores/jogador_16882202.o

OBJ = baralho.o mao.o rodada.o jogo.o $(JOGADORES_OBJ)

all: main

main: main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ main.o $(OBJ)

main.o: main.c
	$(CC) $(CFLAGS) -c $<

baralho.o: baralho.c baralho.h
	$(CC) $(CFLAGS) -c $<

mao.o: mao.c mao.h
	$(CC) $(CFLAGS) -c $<

rodada.o: rodada.c rodada.h carta.h
	$(CC) $(CFLAGS) -c $<

jogo.o: jogo.c jogo.h
	$(CC) $(CFLAGS) -c $<

jogadores/%.o: jogadores/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o jogadores/*.o main

.PHONY: clean all

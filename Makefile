CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Lista dos arquivos-fonte dos jogadores
JOGADORES = jogadores/aleatorio1.c jogadores/aleatorio2.c jogadores/simples.c jogadores/jogador_16882202.c

# Objetos do sistema principal
OBJ = baralho.o mao.o rodada.o jogo.o \
      jogadores/aleatorio1.o jogadores/aleatorio2.o jogadores/simples.o jogadores/jogador_16882202.o

# Alvo principal
all: main

# Compilação final
main: main.o $(OBJ)
	$(CC) $(CFLAGS) -o main main.o $(OBJ)

# Compilações individuais
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

baralho.o: baralho.c baralho.h
	$(CC) $(CFLAGS) -c baralho.c

mao.o: mao.c mao.h
	$(CC) $(CFLAGS) -c mao.c

rodada.o: rodada.c rodada.h
	$(CC) $(CFLAGS) -c rodada.c

jogo.o: jogo.c jogo.h
	$(CC) $(CFLAGS) -c jogo.c

# Compilação dos jogadores
jogadores/aleatorio1.o: jogadores/aleatorio1.c
	$(CC) $(CFLAGS) -c jogadores/aleatorio1.c -o jogadores/aleatorio1.o

jogadores/aleatorio2.o: jogadores/aleatorio2.c
	$(CC) $(CFLAGS) -c jogadores/aleatorio2.c -o jogadores/aleatorio2.o

jogadores/simples.o: jogadores/simples.c
	$(CC) $(CFLAGS) -c jogadores/simples.c -o jogadores/simples.o

jogadores/jogador_16882202.o: jogadores/jogador_16882202.c
	$(CC) $(CFLAGS) -c jogadores/jogador_16882202.c -o jogadores/jogador_16882202.o

# Limpeza dos arquivos compilados
clean:
	rm -f *.o jogadores/*.o main

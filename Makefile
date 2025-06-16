CC = gcc
CFLAGS = -Wall -Wextra -std=c99

JOGADORES = jogadores/aleatorio1.c jogadores/aleatorio2.c jogadores/simples.c jogadores/jogador_16882202.c

OBJ = baralho.o mao.o rodada.o jogo.o jogadores/aleatorio1.o jogadores/aleatorio2.o jogadores/simples.o jogadores/jogador_16882202.o

# Regra padrão para tudo
all: main teste_baralho teste_mao teste_rodada

# Linka todos os objetos
main: main.o $(OBJ)
	$(CC) $(CFLAGS) -o main main.o $(OBJ)

# Compilação dos objetos dos módulos
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

# Compilar objetos dos jogadores
jogadores/aleatorio1.o: jogadores/aleatorio1.c
	$(CC) $(CFLAGS) -c jogadores/aleatorio1.c -o jogadores/aleatorio1.o

jogadores/aleatorio2.o: jogadores/aleatorio2.c
	$(CC) $(CFLAGS) -c jogadores/aleatorio2.c -o jogadores/aleatorio2.o

jogadores/simples.o: jogadores/simples.c
	$(CC) $(CFLAGS) -c jogadores/simples.c -o jogadores/simples.o

jogadores/jogador_16882202.o: jogadores/jogador_16882202.c
	$(CC) $(CFLAGS) -c jogadores/jogador_16882202.c -o jogadores/jogador_16882202.o

# Testes (compila na hora, sem .o)
teste_baralho: baralho.c teste_baralho.c
	$(CC) $(CFLAGS) -o teste_baralho baralho.c teste_baralho.c

teste_mao: mao.c teste_mao.c
	$(CC) $(CFLAGS) -o teste_mao mao.c teste_mao.c

teste_rodada: rodada.c baralho.c teste_rodada.c
	$(CC) $(CFLAGS) -o teste_rodada rodada.c baralho.c teste_rodada.c

clean:
	rm -f *.o jogadores/*.o teste_baralho teste_mao teste_rodada main main.o

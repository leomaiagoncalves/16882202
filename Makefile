CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Fontes dos jogadores
JOGADORES_SRC = jogadores/aleatorio1.c jogadores/aleatorio2.c jogadores/simples.c jogadores/jogador_16882202.c
JOGADORES_OBJ = jogadores/aleatorio1.o jogadores/aleatorio2.o jogadores/simples.o jogadores/jogador_16882202.o

# Objetos principais do sistema
OBJ = baralho.o mao.o rodada.o jogo.o $(JOGADORES_OBJ)

# Alvo padrão
all: main

# Compilação final do executável
main: main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ main.o $(OBJ)

# Compila cada .c em .o
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

# Regra genérica para os jogadores
jogadores/%.o: jogadores/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos gerados
clean:
	rm -f *.o jogadores/*.o main

.PHONY: all clean

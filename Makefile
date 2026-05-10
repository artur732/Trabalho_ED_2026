main: main.c
	gcc -o trabalho main.c hashishi.c fila_dengao_negado.c fila.c etl.c pilha.c stringers.c -I/ -fsanitize=address -Wall

codigo = ./src/main.c
binario = ./build/biblioteca

all: compilar executar

compilar:
	gcc $(codigo) -o $(binario)

executar:
	./$(binario)

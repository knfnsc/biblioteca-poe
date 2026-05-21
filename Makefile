codigo = ./src/main.c
binario = ./build/biblioteca

all: compilar

compilar:
	gcc $(codigo) -o $(binario)

executar:
	./$(binario)

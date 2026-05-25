codigo = ./src/main.c
utilitarios = ./src/util.c
binario = ./build/biblioteca

all: compilar executar

compilar:
	gcc $(codigo) $(utilitarios) -o $(binario)

executar:
	./$(binario)

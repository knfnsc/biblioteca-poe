principal = ./main.c
utilitarios = ./util.c
livros = ./livros.c
usuarios = ./usuarios.c
emprestimos = ./emprestimos.c
binario = ./biblioteca.out

all: compilar executar

compilar:
	gcc \
		$(principal) \
		$(utilitarios) \
		$(livros) \
		$(usuarios) \
		$(emprestimos) \
		-o $(binario)

executar:
	./$(binario)

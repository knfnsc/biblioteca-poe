#ifndef LIVROS_H
#define LIVROS_H

typedef struct {
  unsigned long long codigo;
  char titulo[255];
  char autor[255];
  unsigned int ano;
  char genero[255];
  unsigned short qtd_total;
  unsigned short qtd_disponivel;
} Livro;

void carregar_livros();
void salvar_livros();

void cadastrar_livro();
void listar_livros();
void buscar_livro_codigo();
void buscar_livro_titulo();
void atualizar_livro();
void remover_livro();

Livro *livros_();
unsigned long long *qtd_livros_();

#endif

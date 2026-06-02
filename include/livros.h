#ifndef LIVROS_H
#define LIVROS_H

typedef struct {
  int codigo;
  char titulo[100];
  char autor[100];
  int ano;
  char genero[50];
  int qtd_total;
  int qtd_disponivel;
} Livro;

extern Livro *livros;
extern int total_livros;

void carregar_livros();
void salvar_livros();

void cadastrar_livro();
void listar_livros();
void buscar_livro_lodigo();
void buscar_livro_titulo();
void atualizar_livro();
void remover_livro();

#endif

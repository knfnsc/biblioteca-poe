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

void carregarLivros();
void salvarLivros();

void cadastrarLivro();
void listarLivros();
void buscarLivroCodigo();
void buscarLivroTitulo();
void atualizarLivro();
void removerLivro();

#endif
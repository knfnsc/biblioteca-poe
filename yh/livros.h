#ifndef LIVROS_H
#define LIVROS_H

#include <stdint.h>

typedef struct{
  uint64_t codigo;
  char *titulo;
  char *autor;
  time_t ano;
  genero_t genero;
  uint8_t total_livros;
  uint8_t qtd_disponivel;
  uint8_t total_emprestimos;
}Livro;

void cadastrar_livros();
void listar_livros();
void buscar_livros();
void listar_emprestimos();
void atualizar_livros();
void remover_livros();


#endif

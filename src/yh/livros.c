#ifndef LIVROS_H
#define LIVROS_H

typedef struct{
  uint64_t codigo;
  char *titulo;
  char *autor;
  time_t ano;
  genero_t genero;
  uint8_t qtd_total;
  uint8_t qtd_disponivel;
  uint8_t total_emprestimos;
}Livro;

#endif

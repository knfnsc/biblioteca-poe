#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

#include "livros.h"
#include <stdbool.h>
#include <time.h>

typedef struct {
  unsigned long long id;
  unsigned long long matricula_usuario;
  unsigned long long codigo_livro;
  time_t data_retirada;
  time_t data_prevista;
  time_t data_devolucao;
  bool devolvido;
} Emprestimo;

void carregar_emprestimos();
void salvar_emprestimos();

void registrar_emprestimo();
void registrar_devolucao();
void ler_emprestimos();

Emprestimo *emprestimos_();
unsigned long long *qtd_emprestimos_();

#endif

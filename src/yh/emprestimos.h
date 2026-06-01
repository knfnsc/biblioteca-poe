#ifndef EMPRESTIMOS_USUARIOS
#define EMPRESTIMOS_USUARIOS

#include <stdint.h>

typedef struct{
  uint64_t id;
  uint64_t matricula_usuario;
  uint64_t codigo_livro;
  time_t data_retirada;
  time_t data_prevista;
  time_t data_devolucao;
  bool devolvido;
}Emprestimo;

void autorizar_emprestimos();
void checar_emprestimos();
void devolucao_emprestimos();
void buscar_emprestimos();
void atrasos_emprestimos();

#endif

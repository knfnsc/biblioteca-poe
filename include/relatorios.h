#ifndef RELATORIOS_H
#define RELATORIOS_H

typedef struct {
  unsigned long long codigo;
  char titulo[256];
  unsigned long long total_emprestimos;
} RankingLivro;

void alunos_atrasados();
void livros_mais_emprestados();
void acervo_disponivel();
void historico_usuario();

#endif

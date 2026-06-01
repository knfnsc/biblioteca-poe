#include <stdbool.h>
#include <stdint.h>
#include <time.h>

typedef enum {
  ROMANCE,
  FICCAO_CIENTIFICA,
  FANTASIA,
  MISTERIO,
  TERROR,
  BIOGRAFIA,
  HISTORIA,
  POESIA,
  AVENTURA,
  DRAMA
} genero_t;

typedef enum {
  ENGENHARIA,
  ADMINISTRACAO,
  MEDICINA,
  DIREITO,
  PSICOLOGIA,
  COMPUTACAO,
} curso_t;

struct livro {
  uint64_t codigo;
  char *titulo;
  char *autor;
  time_t ano;
  genero_t genero;
  uint8_t qtd_total;
  uint8_t qtd_disponivel;
  uint8_t total_emprestimos;
};

struct aluno {
  uint64_t matricula;
  char *nome;
  curso_t curso;
  uint8_t qtd_emprestimos_ativos;
};

struct emprestimo {
  uint64_t id;
  uint64_t matricula_usuario;
  uint64_t codigo_livro;
  time_t data_retirada;
  time_t data_prevista;
  time_t data_devolucao;
  bool devolvido;
};

void limpar_buffer();
void limpar_tela();

void acessar_livros();
void acessar_usuarios();
void acessar_emprestimos_e_devolucoes();
void acessar_relatorios();
void sair(int codigo_de_erro);

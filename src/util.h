#include <stdbool.h>
#include <stdint.h>
#include <time.h>

typedef uint64_t identificador_t;

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

typedef struct {
  identificador_t codigo;
  char *titulo;
  char *autor;
  time_t ano;
  genero_t genero;
  uint8_t qtd_total;
  uint8_t qtd_disponivel;
  uint8_t total_emprestimos;
} livro;

typedef struct {
  identificador_t matricula;
  char *nome;
  curso_t curso;
  uint8_t qtd_emprestimos_ativos;
} usuario;

typedef struct {
  identificador_t id;
  identificador_t matricula_usuario;
  identificador_t codigo_livro;
  time_t data_retirada;
  time_t data_prevista;
  time_t data_devolucao;
  bool devolvido;
} emprestimo;

void limpar_buffer();

void acessar_livros();
void acessar_usuarios();
void acessar_emprestimos_e_devolucoes();
void acessar_relatorios();
void sair();

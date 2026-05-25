#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ENDERECO_EMPRESTIMOS "emprestimos.dat"

uint64_t qtd_emprestimos = 0;
struct emprestimo *emprestimos;

int main(void) {
  emprestimos = malloc(sizeof(struct emprestimo) * 1000);
  if (emprestimos == NULL) {
    printf("Falha ao alocar memória!");
    exit(1);
  }

  FILE *emprestimos_arquivo = fopen(ENDERECO_EMPRESTIMOS, "rb");
  if (emprestimos_arquivo != NULL) {
    fread(&qtd_emprestimos, sizeof(uint64_t), 1, emprestimos_arquivo);
    fread(emprestimos, sizeof(struct emprestimo), qtd_emprestimos,
          emprestimos_arquivo);
    fclose(emprestimos_arquivo);
  }

  limpar_tela();

  for (;;) {
    char opcao;
    printf("Livros                   %15s\n", "[1]");
    printf("Usuários                 %15s\n", "[2]");
    printf("Empréstimos e Devoluções %15s\n", "[3]");
    printf("Relatórios               %15s\n", "[4]");
    printf("Sair                     %15s\n", "[5]");

    int erro = scanf("%c", &opcao);
    if (erro == EOF) {
      sair(0);
    }
    limpar_buffer();

    limpar_tela();

    switch (opcao) {
    case '1':
      acessar_livros();
      break;
    case '2':
      acessar_usuarios();
      break;
    case '3':
      acessar_emprestimos_e_devolucoes();
      break;
    case '4':
      acessar_relatorios();
      break;
    case '5':
      sair(0);
      break;
    default:
      printf("Opção inválida.\n");
      break;
    }
  }

  return 0;
}

void ler_emprestimos() {
  if (qtd_emprestimos == 0) {
    printf("Sem empréstimos registrados.\n");
    return;
  }

  struct emprestimo emprestimo_atual;

  // ponteiro de struct para converter "time_t" (segundos) para um formato
  // legível.
  struct tm *data_retirada;
  struct tm *data_prevista;
  struct tm *data_devolucao;

  uint8_t dia_retirada;
  uint8_t dia_prevista;
  uint8_t dia_devolucao;
  uint8_t mes_retirada;
  uint8_t mes_prevista;
  uint8_t mes_devolucao;

  for (int i = 0; i < qtd_emprestimos; i++) {
    data_retirada = localtime(&emprestimos[i].data_retirada);
    dia_retirada = data_retirada->tm_mday;
    mes_retirada = data_retirada->tm_mon + 1;

    data_prevista = localtime(&emprestimos[i].data_prevista);
    dia_prevista = data_prevista->tm_mday;
    mes_prevista = data_prevista->tm_mon + 1;

    printf("id: %03lu | matrícula: %03lu | código do livro: %03lu"
           " | retirada: %02d/%02d | prazo: %02d/%02d | devolvido: ",
           emprestimos[i].id, emprestimos[i].matricula_usuario,
           emprestimos[i].codigo_livro, dia_retirada, mes_retirada,
           dia_prevista, mes_prevista);

    if (emprestimo_atual.devolvido) {
      data_devolucao = localtime(&emprestimos[i].data_devolucao);
      dia_devolucao = data_devolucao->tm_mday;
      mes_devolucao = data_devolucao->tm_mon + 1;
      printf("%02d/%02d\n", dia_devolucao, mes_devolucao);
    } else {
      printf("pendente\n");
    }
  }
}

void salvar_emprestimos() {
  FILE *arquivo_emprestimos = fopen(ENDERECO_EMPRESTIMOS, "wb");
  if (arquivo_emprestimos != NULL) {
    // escreve o contador de empréstimos (primeiros 64 bits do arquivo)
    fwrite(&qtd_emprestimos, sizeof(uint64_t), 1, arquivo_emprestimos);
    fwrite(emprestimos, sizeof(struct emprestimo), qtd_emprestimos,
           arquivo_emprestimos);
    fclose(arquivo_emprestimos);
  }
}

void registrar_emprestimo() {
  uint64_t matricula_usuario, codigo_livro;
  printf("Digite a matrícula: ");
  scanf("%lu", &matricula_usuario);
  printf("Digite o código do livro: ");
  scanf("%lu", &codigo_livro);

  limpar_buffer();

  const uint32_t dia = 24 * 3600;
  time_t agora = time(NULL);
  time_t prazo = agora + (14 * dia);
  struct emprestimo novo_emprestimo = {
      .id = qtd_emprestimos + 1,
      .matricula_usuario = matricula_usuario,
      .codigo_livro = codigo_livro,
      .data_retirada = agora,
      .data_prevista = prazo,
      .data_devolucao = 0,
      .devolvido = false,
  };

  emprestimos[qtd_emprestimos] = novo_emprestimo;
  qtd_emprestimos += 1;

  salvar_emprestimos();
  printf("Empréstimo registrado!\n");
};

void registrar_devolucao() {
  if (qtd_emprestimos == 0) {
    printf("Sem empréstimos registrados.\n");
    return;
  }

  uint64_t matricula_usuario, codigo_livro;
  printf("Digite a matrícula: ");
  scanf("%lu", &matricula_usuario);
  printf("Digite o código do livro: ");
  scanf("%lu", &codigo_livro);

  limpar_buffer();

  struct emprestimo emprestimo_atual;
  bool encontrado;
  for (int i = 0; i < qtd_emprestimos; i++) {
    encontrado = emprestimos[i].matricula_usuario == matricula_usuario &&
                 emprestimos[i].codigo_livro == codigo_livro &&
                 !emprestimos[i].devolvido;

    if (encontrado) {
      time_t agora = time(NULL);
      emprestimos[i].data_devolucao = agora;
      emprestimos[i].devolvido = true;

      salvar_emprestimos();
      printf("Devolução registrada!\n");
      return;
    }
  }

  printf("Nenhum empréstimo correspondente encontrado.\n");
};

void acessar_emprestimos_e_devolucoes() {
  for (;;) {
    char opcao;
    printf("Empréstimos %15s\n", "[1]");
    printf("Devoluções  %15s\n", "[2]");
    printf("Registros   %15s\n", "[3]");
    printf("Voltar      %15s\n", "[4]");

    int erro = scanf("%c", &opcao);
    if (erro == EOF) {
      sair(0);
    }
    limpar_buffer();

    limpar_tela();

    switch (opcao) {
    case '1':
      registrar_emprestimo();
      break;
    case '2':
      registrar_devolucao();
      break;
    case '3':
      ler_emprestimos();
      break;
    case '4':
      return;
      break;
    default:
      printf("Opção inválida.\n");
      break;
    }

    printf("-----------------------------------\n");
  }
}

void sair(int codigo_de_erro) {
  printf("Encerrando programa...\n");
  exit(codigo_de_erro);
}

void acessar_livros() {}
void acessar_usuarios() {}
void acessar_relatorios() {}

#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

emprestimo *emprestimos;
uint64_t qtd_emprestimos = 0;

int main(void) {
  emprestimos = malloc(sizeof(emprestimo) * 1000);
  if (emprestimos == NULL) {
    printf("Falha ao alocar memória");
    return 1;
  }

  FILE *emprestimos_arquivo = fopen("emprestimos.dat", "rb");
  if (emprestimos_arquivo != NULL) {
    fread(&qtd_emprestimos, sizeof(uint64_t), 1, emprestimos_arquivo);
    fread(emprestimos, sizeof(emprestimo), qtd_emprestimos,
          emprestimos_arquivo);
    fclose(emprestimos_arquivo);
  }

  printf("\e[1;1H\e[2J");

  for (;;) {
    char opcao;
    printf("Biblioteca              \t[opções]\n");
    printf("Livros                  \t[1]\n");
    printf("Usuários                \t[2]\n");
    printf("Empréstimos e Devoluções\t[3]\n");
    printf("Relatórios              \t[4]\n");
    printf("Sair                    \t[5]\n");

    int error = scanf("%c", &opcao);
    if (error == EOF) {
      sair();
    }

    limpar_buffer();

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
      sair();
      break;
    default:
      printf("Opção inválida.\n");
      break;
    }
  }

  free(emprestimos);

  return 0;
}

void acessar_livros() {
  printf("Acessando livros.\n");
  system("sleep 999");
}

void acessar_usuarios() {
  printf("Acessando usuários.\n");
  system("sleep 999");
}

void ler_emprestimos() {
  if (qtd_emprestimos == 0) {
    printf("Sem empréstimos registrados\n");
    return;
  }

  emprestimo emprestimo_lido;
  struct tm *data_retirada;
  struct tm *data_prevista;
  struct tm *data_devolucao;

  uint8_t dia_retirada;
  uint8_t mes_retirada;
  uint8_t dia_prevista;
  uint8_t mes_prevista;
  uint8_t dia_devolucao;
  uint8_t mes_devolucao;

  for (int i = 0; i < qtd_emprestimos; i++) {
    emprestimo_lido = emprestimos[i];

    data_retirada = localtime(&emprestimos[i].data_retirada);
    dia_retirada = data_retirada->tm_mday;
    mes_retirada = data_retirada->tm_mon + 1;

    data_prevista = localtime(&emprestimos[i].data_prevista);
    dia_prevista = data_prevista->tm_mday;
    mes_prevista = data_prevista->tm_mon + 1;

    data_devolucao = localtime(&emprestimos[i].data_devolucao);
    dia_devolucao = data_devolucao->tm_mday;
    mes_devolucao = data_devolucao->tm_mon + 1;

    printf("id: %03lu | matrícula: %03lu | código do livro: %03lu | retirada: "
           "%02d/%02d "
           "| prazo: %02d/%02d | devolução: ",
           emprestimos[i].id, emprestimos[i].matricula_usuario,
           emprestimos[i].codigo_livro, dia_retirada, mes_retirada,
           dia_prevista, mes_prevista);

    if (emprestimo_lido.devolvido) {
      printf("%02d/%02d", dia_devolucao, mes_devolucao);
    } else {
      printf("pendente");
    }

    printf("\n");
  }
}

void salvar_emprestimos() {
  FILE *emprestimos_arquivo = fopen("emprestimos.dat", "wb");
  if (emprestimos_arquivo != NULL) {
    fwrite(&qtd_emprestimos, sizeof(uint64_t), 1, emprestimos_arquivo);
    fwrite(emprestimos, sizeof(emprestimo), qtd_emprestimos,
           emprestimos_arquivo);
    fclose(emprestimos_arquivo);
  }
}

void registrar_emprestimo() {
  identificador_t matricula_usuario, codigo_livro;
  printf("Digite sua matrícula: ");
  scanf("%lu", &matricula_usuario);
  printf("Digite o código do livro: ");
  scanf("%lu", &codigo_livro);

  limpar_buffer();

  time_t agora = time(NULL);
  time_t prazo = agora + (14 * 24 * 3600);
  emprestimo novo_emprestimo = {
      .id = qtd_emprestimos + 1,
      .matricula_usuario = matricula_usuario,
      .codigo_livro = codigo_livro,
      .data_retirada = agora,
      .data_prevista = prazo,
      .data_devolucao = 0,
      .devolvido = false,
  };

  emprestimos[qtd_emprestimos] = novo_emprestimo;
  qtd_emprestimos++;

  salvar_emprestimos();
  printf("Empréstimo registrado\n");
};

void registrar_devolucao() {
  identificador_t matricula_usuario, codigo_livro;
  printf("Digite sua matrícula: ");
  scanf("%lu", &matricula_usuario);
  printf("Digite o código do livro: ");
  scanf("%lu", &codigo_livro);

  limpar_buffer();

  bool emprestimo_correspondente;
  for (int i = 0; i < qtd_emprestimos; i++) {
    emprestimo_correspondente =
        emprestimos[i].matricula_usuario == matricula_usuario &&
        emprestimos[i].codigo_livro == codigo_livro &&
        !emprestimos[i].devolvido;

    if (emprestimo_correspondente) {
      time_t agora = time(NULL);
      emprestimos[i].data_devolucao = agora;
      emprestimos[i].devolvido = true;

      salvar_emprestimos();
      printf("Devolução registrada\n");
      return;
    }
  }

  printf("Nenhum empréstimo correspondente encontrado\n");
};

void acessar_emprestimos_e_devolucoes() {
  printf("\e[1;1H\e[2J");

  char opcao;
  printf("Empréstimos             \t[1]\n");
  printf("Devoluções              \t[2]\n");
  printf("Registros               \t[3]\n");

  int error = scanf("%c", &opcao);
  if (error == EOF) {
    sair();
  }

  limpar_buffer();

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
  default:
    printf("Opção inválida.\n");
    break;
  }
}

void acessar_relatorios() {
  printf("Acessando relatórios.\n");
  system("sleep 999");
}

void sair() {
  printf("Encerrando programa...\n");
  exit(0);
}

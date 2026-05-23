#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

emprestimo *emprestimos;
uint64_t qtd_emprestimos = 0;

int main(void) {
  emprestimos = malloc(sizeof(emprestimo) * 100000);

  FILE *emprestimos_arquivo = fopen("emprestimos.dat", "rb");
  if (emprestimos_arquivo != NULL) {
    fread(&qtd_emprestimos, sizeof(int), 1, emprestimos_arquivo);
    fread(emprestimos, sizeof(emprestimo), qtd_emprestimos,
          emprestimos_arquivo);
    fclose(emprestimos_arquivo);
  }

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

    getchar();
  }

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

void registrar_emprestimo(identificador_t matricula_usuario,
                          identificador_t codigo_livro) {
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
};

void acessar_emprestimos_e_devolucoes() {
  identificador_t matricula_usuario, codigo_livro;
  printf("Digite sua matrícula: ");
  scanf("%lu", &matricula_usuario);
  printf("Digite o código do livro: ");
  scanf("%lu", &codigo_livro);

  registrar_emprestimo(matricula_usuario, codigo_livro);

  emprestimo ultimo_emprestimo = emprestimos[qtd_emprestimos - 1];
  printf("matrícula do usuário: %lu, código do livro: %lu\n",
         ultimo_emprestimo.matricula_usuario, ultimo_emprestimo.codigo_livro);
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

void acessar_relatorios() {
  printf("Acessando relatórios.\n");
  system("sleep 999");
}

void sair() {
  printf("Encerrando programa...\n");
  exit(0);
}

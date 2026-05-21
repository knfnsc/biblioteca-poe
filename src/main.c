#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void acessar_livros();
void acessar_usuarios();
void acessar_emprestimos();
void acessar_relatorios();
void sair();

int main(void) {
  for (;;) {
    char opcao;
    printf("Biblioteca \t[opções]\n");
    printf("Livros     \t[1]\n");
    printf("Usuários   \t[2]\n");
    printf("Empréstimos\t[3]\n");
    printf("Relatórios \t[4]\n");
    printf("Sair       \t[5]\n");

    // recebe o valor de erro na leitura do commando; caso o usuário pressione
    // CTRL-D, fecha o programa.
    int error = scanf("%c", &opcao);
    if (error == EOF) {
      sair();
    }

    // Menu
    switch (opcao) {
    case '1':
      acessar_livros();
      break;
    case '2':
      acessar_usuarios();
      break;
    case '3':
      acessar_emprestimos();
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

    getchar(); // Limpa o buffer de entrada
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

void acessar_emprestimos() {
  printf("Acessando empréstimos.\n");
  system("sleep 999");
}

void acessar_relatorios() {
  printf("Acessando relatórios.\n");
  system("sleep 999");
}

void sair() {
  printf("Encerrando programa...\n");
  exit(0);
}

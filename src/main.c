#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/utilitarios.h"
#include <stdio.h>

void acessar_usuarios() {};
void acessar_livros() {};
void acessar_emp_e_dev() {};

int main() {
  printf("Biblioteca\n");

  for (;;) {
    char opcao;
    if (scanf("%c", &opcao) == EOF) {
      printf("Encerrando o programa...\n");
      return 0;
    }

    while (getchar() != '\n')
      continue;

    switch (opcao) {
    case '1':
      acessar_usuarios();
      break;
    case '2':
      acessar_livros();
      break;
    case '3':
      acessar_emp_e_dev();
      break;
    case '5':
      printf("Encerrando programa...\n");
      return 0;
      break;
    default:
      printf("Opção inválida.\n");
      break;
    }
  }

  return 0;
}

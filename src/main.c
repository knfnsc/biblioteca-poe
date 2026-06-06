#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/utilitarios.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long qtd_usuarios = 0;
Usuario *usuarios = NULL;

unsigned long long qtd_livros = 0;
Livro *livros = NULL;

unsigned long long qtd_emprestimos = 0;
Emprestimo *emprestimos = NULL;

void acessar_usuarios() {
  for (;;) {
    printf("Cadastrar   [1]\n");
    printf("Buscar      [2]\n");
    printf("Listar      [3]\n");
    printf("Atualizar   [4]\n");
    printf("Remover     [5]\n");
    printf("Empréstimos [6]\n");
    printf("Voltar      [0]\n");

    char opcao;
    if (scanf("%c", &opcao) == EOF) {
      return;
    }
    limpar_buffer();

    limpar_tela();

    switch (opcao) {
    case '1':
      cadastrar_usuario();
      break;
    case '2':
      printf("ola");
      break;
    case '3':
      listar_usuarios();
      break;
    case '4':
      atualizar_usuario();
      break;
    case '5':
      remover_usuario();
      break;
    case '6':
      emprestimos_usuario();
      break;
    case '0':
      return;
      break;
    default:
      printf("Opção inválida.\n");
      break;
    }

    printf("-----------------------------------\n");
  }
};

void acessar_livros() {
  for (;;) {
    printf("Cadastrar         [1]\n");
    printf("Listar            [2]\n");
    printf("Buscar por código [3]\n");
    printf("Buscar por título [4]\n");
    printf("Atualizar         [5]\n");
    printf("Remover           [6]\n");
    printf("Voltar            [0]\n");

    char opcao;
    if (scanf("%c", &opcao) == EOF) {
      return;
    }
    limpar_buffer();

    limpar_tela();

    switch (opcao) {
    case '1':
      cadastrar_livro();
      break;
    case '2':
      listar_livros();
      break;
    case '3':
      buscar_livro_codigo();
      break;
    case '4':
      buscar_livro_titulo();
      break;
    case '5':
      atualizar_livro();
      break;
    case '6':
      remover_livro();
      break;
    case '0':
      return;
    default:
      printf("Opcão inválida.\n");
    }

    printf("-----------------------------------\n");
  }
};

void acessar_emp_e_dev() {
  for (;;) {
    printf("Empréstimos [1]\n");
    printf("Devoluções  [2]\n");
    printf("Registros   [3]\n");
    printf("Voltar      [0]\n");

    char opcao;
    if (scanf("%c", &opcao) == EOF) {
      return;
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
    case '0':
      return;
    default:
      printf("Opção inválida.\n");
      break;
    }

    printf("-----------------------------------\n");
  }
}

int main() {
  carregar_usuarios();
  carregar_livros();
  carregar_emprestimos();

  printf("Bem-vindo a Biblioteca Poe!\n");

  for (;;) {
    printf("Usuários    [1]\n");
    printf("Livros      [2]\n");
    printf("Empréstimos [3]\n");
    printf("Relátorios  [4]\n");
    printf("Sair        [0]\n");

    char opcao;
    if (scanf("%c", &opcao) == EOF) {
      return 0;
    }
    limpar_buffer();

    limpar_tela();

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
    case '0':
      printf("Encerrando programa...\n");
      return 0;
    default:
      printf("Opção inválida.\n");
      break;
    }
  }

  free(usuarios);
  free(livros);
  free(emprestimos);

  return 0;
}

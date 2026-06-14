#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/relatorios.h"
#include "../include/usuarios.h"
#include "../include/utilitarios.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Inicializa as variáveis e vetores dos arquivos
unsigned long long qtd_usuarios = 0;
Usuario *usuarios = NULL;

unsigned long long qtd_livros = 0;
Livro *livros = NULL;

unsigned long long qtd_emprestimos = 0;
Emprestimo *emprestimos = NULL;

void acessar_usuarios();
void acessar_livros();
void acessar_emp_e_dev();
void acessar_relatorios();

int main() {
  carregar_usuarios();
  carregar_livros();
  carregar_emprestimos();

  printf("Bem-vindo a Biblioteca Poe!\n");

  // Loop principal da aplicação, permite que o programa execute até que o
  // usuário decida encerra-lo
  for (;;) {
    printf("Usuários    [1]\n");
    printf("Livros      [2]\n");
    printf("Empréstimos [3]\n");
    printf("Relatórios  [4]\n");
    printf("Sair        [0]\n");

    char opcao;
    char_valido(&opcao);

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
    case '4':
      acessar_relatorios();
      break;
    case '0':
      printf("Encerrando programa...\n");
      free(usuarios);
      free(livros);
      free(emprestimos);
      return 0;
    default:
      printf("Opção inválida.\n");
      break;
    }
  }
}

void acessar_usuarios() {
  for (;;) {
    printf("Cadastrar        [1]\n");
    printf("Buscar matrícula [2]\n");
    printf("Buscar nome      [3]\n");
    printf("Listar           [4]\n");
    printf("Atualizar        [5]\n");
    printf("Remover          [6]\n");
    printf("Empréstimos      [7]\n");
    printf("Voltar           [0]\n");

    char opcao;
    char_valido(&opcao);

    limpar_tela();

    switch (opcao) {
    case '1':
      cadastrar_usuario();
      break;
    case '2':
      buscar_usuario_matricula();
      break;
    case '3':
      buscar_usuario_nome();
      break;
    case '4':
      listar_usuarios();
      break;
    case '5':
      atualizar_usuario();
      break;
    case '6':
      remover_usuario();
      break;
    case '7':
      emprestimos_usuario();
      break;
    case '0':
      return;
    default:
      printf("Opção inválida.\n");
      break;
    }

    printf(SEPARADOR);
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
    char_valido(&opcao);

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

    printf(SEPARADOR);
  }
};

void acessar_relatorios() {
  for (;;) {
    printf("Alunos atrasados        [1]\n");
    printf("Livros mais emprestados [2]\n");
    printf("Acervo disponível       [3]\n");
    printf("Histórico de usuário    [4]\n");
    printf("Voltar                  [0]\n");

    char opcao;
    char_valido(&opcao);

    limpar_tela();

    switch (opcao) {
    case '1':
      alunos_atrasados();
      break;
    case '2':
      livros_mais_emprestados();
      break;
    case '3':
      acervo_disponivel();
      break;
    case '4':
      historico_usuario();
      break;
    case '0':
      return;
    default:
      printf("Opção inválida.\n");
      break;
    }

    printf(SEPARADOR);
  };
}

void acessar_emp_e_dev() {
  for (;;) {
    printf("Empréstimos [1]\n");
    printf("Devoluções  [2]\n");
    printf("Registros   [3]\n");
    printf("Voltar      [0]\n");

    char opcao;
    char_valido(&opcao);

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

    printf(SEPARADOR);
  }
}

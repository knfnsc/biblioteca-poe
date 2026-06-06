#include "../include/usuarios.h"
#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/utilitarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long long qtd_usuarios;
extern Usuario *usuarios;

void carregar_usuarios() {
  usuarios = malloc(sizeof(Usuario) * 1000);
  if (usuarios == NULL) {
    printf("Falha ao alocar memória!");
    return;
  }

  FILE *arquivo = fopen("usuarios.dat", "rb");
  if (arquivo != NULL) {
    fread(&qtd_usuarios, sizeof(unsigned long long), 1, arquivo);
    fread(usuarios, sizeof(Usuario), qtd_usuarios, arquivo);
    fclose(arquivo);
  }
}

void salvar_usuarios() {
  FILE *arquivo = fopen("usuarios.dat", "wb");
  if (arquivo == NULL)
    return;

  fwrite(&qtd_usuarios, sizeof(unsigned long long), 1, arquivo);
  fwrite(usuarios, sizeof(Usuario), qtd_usuarios, arquivo);
  fclose(arquivo);
}

void cadastrar_usuario() {
  Usuario novo_usuario;
  unsigned long long maior_matricula = 0;

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (usuarios[i].matricula > maior_matricula) {
      maior_matricula = usuarios[i].matricula;
    }
  }

  novo_usuario.matricula = maior_matricula + 1;

  printf("Nome do usuário: ");
  fgets(novo_usuario.nome, sizeof(novo_usuario.nome), stdin);
  tratar_string(novo_usuario.nome);

  printf("Curso do usuário: ");
  fgets(novo_usuario.curso, sizeof(novo_usuario.curso), stdin);
  tratar_string(novo_usuario.curso);

  novo_usuario.qtd_emprestimos_ativos = 0;

  usuarios[qtd_usuarios] = novo_usuario;
  qtd_usuarios++;

  salvar_usuarios();
  printf("Novo usuário cadastrado.\n");
}

void buscar_usuarios_matricula() {
  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  int encontrado = 0;
  printf("Inserir matrícula do usuario: ");
  unsigned long long matricula = inteiro_valido();

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (usuarios[i].matricula ==
        matricula) { // comparar a matrícula digitada pelo usuário com as
                     // matrículas salvas na struct usuario
      encontrado = 1;
      printf("matrícula: %llu\n", usuarios[i].matricula);
      printf("nome: %s\n", usuarios[i].nome);
      printf("curso: %s\n", usuarios[i].curso);
      break; // interrompe o laço assim que encontra o usuário
    }
  }

  if (!encontrado)
    printf("Usuário não encontrado.\n");
}

void buscar_usuarios_nome() {
  int encontrado = 0;

  char nome[100];
  printf("Inserir nome completo do usuário:\n");
  fgets(nome, sizeof(nome), stdin);
  tratar_string(
      nome); // serve para padronizar a entrada do usuário com o padrão de
             // escrita nos arquivos, facilitando a buscar_usuarios

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (strcmp(nome, usuarios[i].nome) ==
        0) { // comparar o nome digitado pelo usuario com os nomes salvos na
             // struct usuario
      encontrado = 1;
      printf("matrícula: %llu\n", usuarios[i].matricula);
      printf("nome: %s\n", usuarios[i].nome);
      printf("curso: %s\n", usuarios[i].curso);
      break; // interrompe o laço assim que encontra o usuário
    }
  }

  if (!encontrado) // informa mensagem de erro antes de solicitar novamente o
                   // nome, caso não tenha sido encontrado
    printf("Usuário não encontrado.\n");
}

void atualizar_usuario() {
  int encontrado = 0;
  printf("Matrícula do usuário: ");
  unsigned long long matricula = inteiro_valido();

  for (unsigned long long i = 0; i < qtd_usuarios;
       i++) { // laço relacionado com a busca dentro da struct usuarios
    if (usuarios[i].matricula ==
        matricula) { // comparar a matrícula digitada pelo usuario com as
                     // matrículas salvas na struct usuario
      encontrado = 1;
      printf("Novo nome: ");
      fgets(usuarios[i].nome, sizeof(usuarios[i].nome), stdin);
      tratar_string(usuarios[i].nome);

      printf("Novo curso: ");
      fgets(usuarios[i].curso, sizeof(usuarios[i].curso), stdin);
      tratar_string(usuarios[i].curso);

      salvar_usuarios();
      printf("Usuário atualizado.\n");
      break; // interrompe o laço assim que encontra o usuário após os comandos
             // acima
    }
  }

  if (!encontrado)                       // se encontrado == 0 (falso)
    printf("Usuário não encontrado.\n"); // Verifica se o usuário deseja
                                         // continuar tentando; se ele não
                                         // quiser, ele sai da função
}

void listar_usuarios() {
  if (qtd_usuarios ==
      0) { // considera as duas possibilidades: 1 - sistema já em funcionamento
           // e com usuários já cadastrados; 2 - primeira execução, quando não
           // existem usuários cadastrados
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    printf("matrícula: %llu | nome: %s | curso: %s | empréstimos ativos: %d\n",
           usuarios[i].matricula, usuarios[i].nome, usuarios[i].curso,
           usuarios[i].qtd_emprestimos_ativos);
  }
}

void remover_usuario() {
  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  unsigned long long matricula;
  int encontrado = 0;
  printf("Inserir matrícula do usuário: ");
  matricula = inteiro_valido();

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {

    if (usuarios[i].matricula == matricula) {
      encontrado = 1;

      if (usuarios[i].qtd_emprestimos_ativos != 0) {
        printf("Remoção não autorizada. O usuário possui empréstimos em "
               "aberto.\n");
        return;
      }

      for (unsigned long long k = i; k < qtd_usuarios - 1; k++) {
        usuarios[k] = usuarios[k + 1];
      }

      qtd_usuarios--;

      usuarios = realloc(usuarios, qtd_usuarios * sizeof(Usuario));
      salvar_usuarios();
      printf("Usuário removido.\n");
      break;
    }
  }

  if (!encontrado)
    printf("Usuário não encontrado.\n");
}

void emprestimos_usuario() {
  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  Emprestimo *emprestimos = emprestimos_();
  Livro *livros = livros_();
  unsigned long long *qtd_emprestimos = qtd_emprestimos_();
  unsigned long long *qtd_livros = qtd_livros_();

  unsigned long long matricula;
  int encontrado = 0;
  printf("Inserir matrícula do usuário: ");
  matricula = inteiro_valido();

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (usuarios[i].matricula == matricula) {
      encontrado = 1;

      if (usuarios[i].qtd_emprestimos_ativos == 0) {
        printf("Usuário sem empréstimos ativos.\n");
        return;
      }

      printf("empréstimos ativos: %d.\n", usuarios[i].qtd_emprestimos_ativos);

      printf("Livros emprestados:\n");
      for (unsigned long long j = 0; j < *qtd_emprestimos; j++) {
        if (usuarios[i].matricula == emprestimos[j].matricula_usuario) {
          for (unsigned long long k = 0; k < *qtd_livros; k++) {
            if (emprestimos[j].codigo_livro == livros[k].codigo) {
              printf("livro: %s\n", livros[k].titulo);
              printf("código: %llu\n", livros[k].codigo);
              printf("---------------------------\n");
            }
          }
        }
      }
      break;
    }
  }

  if (!encontrado)
    printf("Usuário não encontrado.\n");
}

Usuario *usuarios_() { return usuarios; }

unsigned long long *qtd_usuarios_() { return &qtd_usuarios; }

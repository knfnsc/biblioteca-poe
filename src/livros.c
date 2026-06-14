#include "../include/livros.h"
#include "../include/utilitarios.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long long qtd_livros;
extern Livro *livros;

void carregar_livros() {
  if ((livros = malloc(sizeof(Livro) * 1000)) == NULL) {
    printf("Falha ao alocar memória!");
    exit(1);
  }

  FILE *arquivo = fopen("livros.dat", "rb");
  if (arquivo != NULL) {
    fread(&qtd_livros, sizeof(unsigned long long), 1, arquivo);
    fread(livros, sizeof(Livro), qtd_livros, arquivo);
    fclose(arquivo);
  }
}

void salvar_livros() {
  FILE *arquivo = fopen("livros.dat", "wb");
  if (arquivo == NULL) {
    printf("Falha ao salvar livros!\n");
    exit(1);
  }

  fwrite(&qtd_livros, sizeof(unsigned long long), 1, arquivo);
  fwrite(livros, sizeof(Livro), qtd_livros, arquivo);
  fclose(arquivo);
}

void cadastrar_livro() {
  Livro novo;
  unsigned long long maior_codigo = 0;

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (livros[i].codigo > maior_codigo)
      maior_codigo = livros[i].codigo;
  }

  novo.codigo = maior_codigo + 1;

  printf("título: ");
  string_valido(novo.titulo);

  printf("autor: ");
  string_valido(novo.autor);

  printf("ano: ");
  inteiro_valido((unsigned long long *)&novo.ano);

  printf("gênero: ");
  string_valido(novo.genero);

  printf("quantidade de exemplares: ");
  inteiro_valido((unsigned long long *)&novo.qtd_total);

  novo.qtd_disponivel = novo.qtd_total;
  livros = realloc(livros, (qtd_livros + 1) * sizeof(Livro));
  livros[qtd_livros] = novo;
  qtd_livros++;
  salvar_livros();

  printf("Livro cadastrado com sucesso!\n");
}

void listar_livros() {
  if (qtd_livros == 0) {
    printf("Nenhum livro cadastrado.\n");
    return;
  }

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    printf("código: %llu\n", livros[i].codigo);
    printf("título: %s\n", livros[i].titulo);
    printf("autor: %s\n", livros[i].autor);
    printf("ano: %d\n", livros[i].ano);
    printf("gênero: %s\n", livros[i].genero);
    printf("quantidade total: %d\n", livros[i].qtd_total);
    printf("disponíveis: %d\n", livros[i].qtd_disponivel);
    if (i != qtd_livros - 1)
      printf(SEPARADOR);
  }
}

void buscar_livro_codigo() {
  unsigned long long codigo;
  bool encontrado = false;

  printf("digite o código: ");
  inteiro_valido(&codigo);

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (livros[i].codigo == codigo) {
      printf("código: %llu\n", livros[i].codigo);
      printf("título: %s\n", livros[i].titulo);
      printf("autor: %s\n", livros[i].autor);
      printf("ano: %d\n", livros[i].ano);
      printf("gênero: %s\n", livros[i].genero);

      encontrado = true;
      break;
    }
  }

  if (!encontrado)
    printf("Livro não encontrado.\n");
}

void buscar_livro_titulo() {
  char busca[256];
  bool encontrado = false;

  printf("digite parte do título: ");
  string_valido(busca);

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (strstr(livros[i].titulo, busca) != NULL) {
      printf("código: %llu\n", livros[i].codigo);
      printf("título: %s\n", livros[i].titulo);
      printf("autor: %s\n", livros[i].autor);
      printf("ano: %d\n", livros[i].ano);
      printf("gênero: %s\n", livros[i].genero);

      encontrado = true;
    }
  }

  if (!encontrado)
    printf("Nenhum livro encontrado.\n");
}

void atualizar_livro() {
  unsigned long long codigo;
  bool encontrado = false;

  printf("digite o código do livro: ");
  inteiro_valido(&codigo);

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (livros[i].codigo == codigo) {
      printf("novo título: ");
      string_valido(livros[i].titulo);

      printf("novo autor: ");
      string_valido(livros[i].autor);

      printf("novo ano: ");
      inteiro_valido((unsigned long long *)&livros[i].ano);

      printf("novo gênero: ");
      string_valido(livros[i].genero);

      salvar_livros();

      printf("Livro atualizado.\n");

      encontrado = true;
      break;
    }
  }

  if (!encontrado)
    printf("Livro não encontrado.\n");
}

void remover_livro() {
  unsigned long long codigo;
  bool encontrado = false;

  printf("digite o código do livro: ");
  inteiro_valido(&codigo);

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (livros[i].codigo == codigo) {
      if (livros[i].qtd_total != livros[i].qtd_disponivel) {
        printf("Não é possível remover. Livro possui empréstimos ativos.\n");
        return;
      }
      for (unsigned long long j = i; j < qtd_livros - 1; j++) {
        livros[j] = livros[j + 1];
      }

      qtd_livros--;
      livros = realloc(livros, qtd_livros * sizeof(Livro));
      salvar_livros();

      printf("Livro removido.\n");

      encontrado = true;
      break;
    }
  }

  if (!encontrado)
    printf("Livro nao encontrado.\n");
}

Livro *livros_() { return livros; }

unsigned long long *qtd_livros_() { return &qtd_livros; }

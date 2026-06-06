#include "../include/livros.h"
#include "../include/utilitarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long long qtd_livros;
extern Livro *livros;

void carregar_livros() {
  livros = malloc(sizeof(Livro) * 1000);
  if (livros == NULL) {
    printf("Falha ao alocar memória!");
  }

  FILE *arquivo = fopen("livros.dat", "rb");
  if (arquivo == NULL)
    return;
  fread(&qtd_livros, sizeof(unsigned long long), 1, arquivo);
  livros = malloc(qtd_livros * sizeof(Livro));
  fread(livros, sizeof(Livro), qtd_livros, arquivo);
  fclose(arquivo);
}

void salvar_livros() {
  FILE *arquivo = fopen("livros.dat", "wb");
  if (arquivo == NULL)
    return;
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
  scanf(" %[^\n]", novo.titulo);
  limpar_buffer();

  printf("autor: ");
  scanf(" %[^\n]", novo.autor);
  limpar_buffer();

  printf("ano: ");
  scanf("%d", &novo.ano);
  limpar_buffer();

  printf("gênero: ");
  scanf(" %[^\n]", novo.genero);
  limpar_buffer();

  printf("quantidade de exemplares: ");
  scanf("%hu", &novo.qtd_total);
  limpar_buffer();

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
  }
}

void buscar_livro_codigo() {
  unsigned long long codigo;
  int encontrado = 0;

  printf("digite o código: ");
  scanf("%llu", &codigo);
  limpar_buffer();

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (livros[i].codigo == codigo) {
      printf("código: %llu\n", livros[i].codigo);
      printf("título: %s\n", livros[i].titulo);
      printf("autor: %s\n", livros[i].autor);
      printf("ano: %d\n", livros[i].ano);
      printf("gênero: %s\n", livros[i].genero);

      encontrado = 1;
      break;
    }
  }

  if (!encontrado)
    printf("Livro não encontrado.\n");
}

void buscar_livro_titulo() {
  char busca[100];
  int encontrado = 0;

  printf("digite parte do título: ");
  scanf("%[^\n]", busca);
  limpar_buffer();

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (strstr(livros[i].titulo, busca) != NULL) {
      printf("código: %llu\n", livros[i].codigo);
      printf("título: %s\n", livros[i].titulo);
      printf("autor: %s\n", livros[i].autor);

      encontrado = 1;
    }
  }

  if (!encontrado)
    printf("Nenhum livro encontrado.\n");
}

void atualizar_livro() {
  unsigned long long codigo;
  int encontrado = 0;

  printf("digite o código do livro: ");
  scanf("%llu", &codigo);
  limpar_buffer();

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (livros[i].codigo == codigo) {
      printf("novo título: ");
      scanf("%[^\n]", livros[i].titulo);
      limpar_buffer();

      printf("novo autor: ");
      scanf("%[^\n]", livros[i].autor);
      limpar_buffer();

      printf("novo ano: ");
      scanf("%d", &livros[i].ano);
      limpar_buffer();

      printf("novo gênero: ");
      scanf("%[^\n]", livros[i].genero);
      limpar_buffer();

      salvar_livros();

      printf("Livro atualizado.\n");

      encontrado = 1;
      break;
    }
  }

  if (!encontrado)
    printf("Livro não encontrado.\n");
}

void remover_livro() {
  unsigned long long codigo;
  int encontrado = 0;

  printf("digite o código do livro: ");
  scanf("%llu", &codigo);
  limpar_buffer();

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (livros[i].codigo == codigo) {
      for (unsigned long long j = i; j < qtd_livros - 1; j++) {
        livros[j] = livros[j + 1];
      }

      qtd_livros--;

      livros = realloc(livros, qtd_livros * sizeof(Livro));
      salvar_livros();

      printf("Livro removido.\n");

      encontrado = 1;
      break;
    }
  }

  if (!encontrado)
    printf("Livro nao encontrado.\n");
}

Livro *livros_() { return livros; }

unsigned long long *qtd_livros_() { return &qtd_livros; }

#include "../include/livros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Livro *livros = NULL;
int total_livros = 0;

void salvar_livros() {
  FILE *arquivo = fopen("livros.dat", "wb");
  if (arquivo == NULL)
    return;
  fwrite(&total_livros, sizeof(int), 1, arquivo);
  fwrite(livros, sizeof(Livro), total_livros, arquivo);
  fclose(arquivo);
}

void carregar_livros() {
  FILE *arquivo = fopen("livros.dat", "rb");
  if (arquivo == NULL)
    return;
  fread(&total_livros, sizeof(int), 1, arquivo);
  livros = malloc(total_livros * sizeof(Livro));
  fread(livros, sizeof(Livro), total_livros, arquivo);
  fclose(arquivo);
}

void cadastrar_livro() {
  Livro novo;
  int maiorCodigo = 0;

  for (int i = 0; i < total_livros; i++) {
    if (livros[i].codigo > maiorCodigo)
      maiorCodigo = livros[i].codigo;
  }

  novo.codigo = maiorCodigo + 1;

  printf("Titulo: ");
  scanf(" %[^\n]", novo.titulo);

  printf("Autor: ");
  scanf(" %[^\n]", novo.autor);

  printf("Ano: ");
  scanf("%d", &novo.ano);

  printf("Genero: ");
  scanf(" %[^\n]", novo.genero);

  printf("Quantidade de exemplares: ");
  scanf("%d", &novo.qtd_total);

  novo.qtd_disponivel = novo.qtd_total;

  livros = realloc(livros, (total_livros + 1) * sizeof(Livro));
  livros[total_livros] = novo;

  total_livros++;

  salvarLivros();

  printf("\nLivro cadastrado com sucesso!\n");
}

void listar_livros() {
  if (total_livros == 0) {
    printf("Nenhum livro cadastrado.\n");
    return;
  }

  for (int i = 0; i < total_livros; i++) {
    printf("\nCodigo: %d\n", livros[i].codigo);
    printf("Titulo: %s\n", livros[i].titulo);
    printf("Autor: %s\n", livros[i].autor);
    printf("Ano: %d\n", livros[i].ano);
    printf("Genero: %s\n", livros[i].genero);
    printf("Quantidade Total: %d\n", livros[i].qtd_total);
    printf("Disponiveis: %d\n", livros[i].qtd_disponivel);

    printf("---------------------------\n");
  }
}

void buscar_livro_codigo() {
  int codigo;
  int encontrado = 0;

  printf("Digite o codigo: ");
  scanf("%d", &codigo);

  for (int i = 0; i < total_livros; i++) {
    if (livros[i].codigo == codigo) {
      printf("\nCodigo: %d\n", livros[i].codigo);
      printf("Titulo: %s\n", livros[i].titulo);
      printf("Autor: %s\n", livros[i].autor);
      printf("Ano: %d\n", livros[i].ano);
      printf("Genero: %s\n", livros[i].genero);

      encontrado = 1;
      break;
    }
  }

  if (!encontrado)
    printf("Livro nao encontrado.\n");
}

void buscar_livro_titulo() {
  char busca[100];
  int encontrado = 0;

  printf("Digite parte do titulo: ");
  scanf(" %[^\n]", busca);

  for (int i = 0; i < total_livros; i++) {
    if (strstr(livros[i].titulo, busca) != NULL) {
      printf("\nCodigo: %d\n", livros[i].codigo);
      printf("Titulo: %s\n", livros[i].titulo);
      printf("Autor: %s\n", livros[i].autor);

      encontrado = 1;
    }
  }

  if (!encontrado)
    printf("Nenhum livro encontrado.\n");
}

void atualizar_livro() {
  int codigo;
  int encontrado = 0;

  printf("Digite o codigo do livro: ");
  scanf("%d", &codigo);

  for (int i = 0; i < total_livros; i++) {
    if (livros[i].codigo == codigo) {

      printf("Novo titulo: ");
      scanf(" %[^\n]", livros[i].titulo);

      printf("Novo autor: ");
      scanf(" %[^\n]", livros[i].autor);

      printf("Novo ano: ");
      scanf("%d", &livros[i].ano);

      printf("Novo genero: ");
      scanf(" %[^\n]", livros[i].genero);

      salvarLivros();

      printf("Livro atualizado.\n");

      encontrado = 1;
      break;
    }
  }

  if (!encontrado)
    printf("Livro nao encontrado.\n");
}

void remover_livro() {
  int codigo;
  int encontrado = 0;

  printf("Digite o codigo do livro: ");
  scanf("%d", &codigo);

  for (int i = 0; i < total_livros; i++) {
    if (livros[i].codigo == codigo) {
      for (int j = i; j < total_livros - 1; j++) {
        livros[j] = livros[j + 1];
      }

      total_livros--;

      livros = realloc(livros, total_livros * sizeof(Livro));
      salvarLivros();

      printf("Livro removido.\n");

      encontrado = 1;
      break;
    }
  }

  if (!encontrado)
    printf("Livro nao encontrado.\n");
}

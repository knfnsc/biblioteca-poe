#include "../include/livros.h"
#include "../include/utilitarios.h"
#include "../include/emprestimos.h"
#include "../include/usuarios.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long long qtd_livros;
extern Livro *livros;

void carregar_livros() {
  if ((livros = malloc(sizeof(Livro) * 1024)) == NULL) {
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
      // encontra o maior código contido na array.
      maior_codigo = livros[i].codigo;
  }

  novo.codigo = maior_codigo + 1;

  printf("título: ");
  string_valido(novo.titulo);

  printf("autor: ");
  string_valido(novo.autor);

  printf("ano: ");
  // faz o casting do tipo 'unsigned int *' ('&novo.ano') para
  // 'unsigned long long *', pois esse é o tipo do
  // argumento que 'inteiro_valido' recebe.
  inteiro_valido((unsigned long long *)&novo.ano);

  printf("gênero: ");
  string_valido(novo.genero);

  printf("quantidade de exemplares: ");
  inteiro_valido((unsigned long long *)&novo.qtd_total);

  novo.qtd_disponivel = novo.qtd_total;
  // realoca a memória da array para abranger mais livros.
  livros = realloc(livros, (qtd_livros + 1) * sizeof(Livro));
  livros[qtd_livros] =
      novo; // atribui a última posição da array para o livro mais recente.
  qtd_livros++;
  salvar_livros();

  printf("Livro cadastrado com sucesso!\n");
}

void listar_livros() {
  if (qtd_livros == 0) {
    printf("Nenhum livro cadastrado.\n");
    return;
  }

  for (unsigned long long i = 0; i < qtd_livros; i++) { // percorre a array de livros e confere se o unsignd long long 'i' é menor que a quantidade de livros cadastrados.
    printf("título: %s\n", livros[i].titulo); //Caso seja, mostra as informações do livro na posição 'i'.
    printf("código: %llu\n", livros[i].codigo);// Mostra todas as informações de cada livro cadastrado.
    printf("autor: %s\n", livros[i].autor);
    printf("ano: %d\n", livros[i].ano);
    printf("gênero: %s\n", livros[i].genero);
    printf("quantidade total: %d\n", livros[i].qtd_total);
    printf("disponíveis: %d\n", livros[i].qtd_disponivel);
    // caso seja o último livro da lista, printa o separador.
    if (i != qtd_livros - 1)
      printf(SEPARADOR);
  }
}

void buscar_livro_codigo() {
  unsigned long long codigo;
  bool encontrado = false;

  printf("digite o código: ");
  inteiro_valido(&codigo);

  for (unsigned long long i = 0; i < qtd_livros; i++) { // percorre a array de livros e confere se o unsignd long long 'i' é menor que a quantidade de livros cadastrados.
    if (livros[i].codigo == codigo) { // se for, mostra as informações do livro buscado na posição 'i'.
      printf("código: %llu\n", livros[i].codigo);
      printf("título: %s\n", livros[i].titulo);
      printf("autor: %s\n", livros[i].autor);
      printf("ano: %d\n", livros[i].ano);
      printf("gênero: %s\n", livros[i].genero);

      encontrado = true;
      break;
    }
  }

  if (!encontrado) // se for diferente de 'true' do encontrado, retorna que o lirvo não foi encontrado.
    printf("Livro não encontrado.\n");
}

void buscar_livro_titulo() {
  char busca[256];
  bool encontrado = false;

  printf("digite parte do título: ");
  string_valido(busca);

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    // procura a string 'busca' na string 'livros[i].titulo'. Caso a segunda não
    // esteja contida na primeira, retorna NULL. Caso contrário, retorna a parte
    // da string que está contida (!= NULL).
    if (strstr(livros[i].titulo, busca) != NULL) { //compara a string 'busca' com o título do livro na posição 'i'.
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
      inteiro_valido((unsigned long long *)&livros[i].ano); //confere se o ano digitado é um número inteiro válido, e caso seja, atribui o valor à variável 'ano' do livro na posição 'i'.

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

  printf("digite o código do livro: ");
  inteiro_valido(&codigo);

  bool encontrado = false; // variável booleana para verificar se o livro foi encontrado.
  for (unsigned long long i = 0; i < qtd_livros; i++) { //se for, percorre a array de livros e confere se o unsignd long long 'i' é menor que a quantidade de livros cadastrados.
    if (livros[i].codigo == codigo) { // se os coigigos forem iguais, verifica se a quantidade total de livros é diferente da quantidade disponível. Caso seja, retorna que não é possível remover o livro, pois há empréstimos ativos.
      if (livros[i].qtd_total != livros[i].qtd_disponivel) {
        printf("Não é possível remover. Livro possui empréstimos ativos.\n");
        return;
      }
      // atualiza a lista para remover espaços vazios
      for (unsigned long long j = i; j < qtd_livros - 1; j++) {
        livros[j] = livros[j + 1];
      }

      qtd_livros--; // decrementa a quantidade de livros cadastrados, para que o último livro da lista seja o penúltimo, e assim por diante.
      // realoca a memória do vetor para preservar espaço.
      livros = realloc(livros, qtd_livros * sizeof(Livro));
      salvar_livros();

      printf("Livro removido.\n");

      encontrado = true;
      break;
    }
  }

  if (!encontrado)
    printf("Livro não encontrado.\n");
}

void consultar_usuarios_livro() { // função para consultar os usuários que possuem um livro emprestado.
  unsigned long long codigo;
  bool livro_encontrado = false; // variável booleana para verificar se o livro foi encontrado.
  bool possui_emprestimo = false; // variável booleana para verificar se o livro possui empréstimos ativos.

  printf("digite o código do livro: ");
  inteiro_valido(&codigo); //busca o código do livro e confere se é um número inteiro válido. Caso seja, atribui o valor à variável 'codigo'.

  for (unsigned long long i = 0; i < qtd_livros; i++) {
    if (livros[i].codigo == codigo) {

      livro_encontrado = true;

      printf("\nLivro encontrado:\n");
      printf("título: %s\n", livros[i].titulo);
      printf("autor: %s\n", livros[i].autor);
      printf("código: %llu\n", livros[i].codigo);

      Emprestimo *emprestimos = emprestimos_(); // ponteiro para a array de empréstimos, para que seja possível acessar os empréstimos registrados.
      unsigned long long *qtd_emprestimos = qtd_emprestimos_(); // ponteiro para a variável 'qtd_emprestimos', para que seja possível acessar a quantidade de empréstimos registrados.

      Usuario *usuarios = usuarios_();
      unsigned long long *qtd_usuarios = qtd_usuarios_(); // ponteiro para a array de usuários, para que seja possível acessar os usuários cadastrados, e ponteiro para a variável 'qtd_usuarios', para que seja possível acessar a quantidade de usuários cadastrados.

      printf("\nUsuários com este livro emprestado:\n");

      for (unsigned long long j = 0; j < *qtd_emprestimos; j++) {

        if (emprestimos[j].codigo_livro == codigo &&
            !emprestimos[j].devolvido) {

          for (unsigned long long k = 0; k < *qtd_usuarios; k++) {

            if (usuarios[k].matricula ==
                emprestimos[j].matricula_usuario) {

              printf("- %s (matrícula %llu)\n",
                     usuarios[k].nome,
                     usuarios[k].matricula);

              possui_emprestimo = true;
            }
          }
        }
      }

      if (!possui_emprestimo)
        printf("Este livro não possui empréstimos ativos.\n");

      return;
    }
  }

  if (!livro_encontrado) {
    printf("Livro não encontrado.\n");
  }
}

Livro *livros_() { return livros; } // retorna o ponteiro para a array de livros, para que outras partes do programa possam acessar os livros cadastrados.

unsigned long long *qtd_livros_() { return &qtd_livros; } // retorna o ponteiro para a variável 'qtd_livros', para que outras partes do programa possam acessar a quantidade de livros cadastrados.

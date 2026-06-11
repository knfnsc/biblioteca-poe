#include "../include/usuarios.h"
#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/utilitarios.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaração em extern para permitir que os outros módulos tenham acessado a essas mesmas variáveis e seus valores

extern unsigned long long qtd_usuarios;
extern Usuario *usuarios;

void carregar_usuarios() {

  usuarios = malloc(sizeof(Usuario) * 1000);
  if (usuarios == NULL) {
    printf("Falha ao alocar memória!");
    return;
  }

  /*
   * Aloca dinamicamente espaço para 1000 usuários com a função malloc de <stdlib.io>. Caso o retorno seja um ponteiro cujo
   * conteúdo é NULL, ou seja, não aponta para endereço algum, devolve uma mensagem de erro e sai da função imediatamente com return.
   */

  FILE *arquivo = fopen("usuarios.dat", "rb");
  if (arquivo != NULL) {
    fread(&qtd_usuarios, sizeof(unsigned long long), 1, arquivo);
    fread(usuarios, sizeof(Usuario), qtd_usuarios, arquivo);
    fclose(arquivo);
  }

  /*
   * 1 - Declara um ponteiro para tipo FILE que recebe o retorno da função fopen para leitura de dados binários em um arquivo;
   * 2 - Verifica o conteúdo do ponteiro. Caso seja diferente de NULL, ou seja, caso o arquivo exista e não tenha ocorrido erro
   * em sua abertura executa o bloco seguinte;
   * 3 - Lê do arquivo um dado com tamanho de memória de unsigned long long (8 bytes) e guarda como conteúdo da variável qtd_usuarios;
   * 4 - Lê do arquivo os dados dos usuários e guarda essas informações nos campos correspondentes dentro da "struct" de usuários;
   * 5 - Fecha o arquivo.
   */
}

void salvar_usuarios() {

  FILE *arquivo = fopen("usuarios.dat", "wb");
  if (arquivo == NULL)
    return;

  /*
   * 1 - Declara um ponteiro para tipo FILE que recebe o retorno da função fopen para escrita de dados binários em um arquivo;
   * 2 - Verifica o conteúdo do ponteiro. Caso seja igual a NULL, ou seja,se ocorrer erro, return é executado e sai da função.
   */

  fwrite(&qtd_usuarios, sizeof(unsigned long long), 1, arquivo);
  fwrite(usuarios, sizeof(Usuario), qtd_usuarios, arquivo);
  fclose(arquivo);

  /*
   * 3 -  Escreve no arquivo um dado com tamanho de memória de unsigned long long (8 bytes) e guarda como conteúdo da variável qtd_usuarios;
   * 4 - Escreve no arquivo os dados dos usuários e guarda essas informações nos campos correspondentes dentro da "struct" de usuários;
   * 5 - Fecha o arquivo.
   */

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

  /*
   * 1 - Declara um novo usuário e cria uma variável auxiliar maior_matricula para comparar cada matrícula já existentente com 0.
   * Término do laço, essa variável armazena a matrícula do último usuário que foi cadastrado. Para que não haver matrículas iguais,
   * soma 1 a esse valor e atribui esse valor à matrícula do novo usuário. Assim, as matrículas formam uma lista crescente.
   */

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

  /*
   * 2 - Recebe as entradas de nome e curso dadas pelo usuário do programa e aribui automaticamente o valor 0 para a quantidade
   * de empréstimos ativos do novo usuário;
   * 3 - Adiciona o novo usuário à "struct" de usuários e incrementa o valor da variável qtd_usuários para comportar o novo usuário;
   * 4 - Chama a função salvar_usuarios() para adicionar os novos dados no arquivo binário.
   */

}

void buscar_usuarios_matricula() {

  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o resto da função caso não. Evita execuções desnecessárias.
   */

  bool encontrado = false;
  printf("Inserir matrícula do usuário: ");
  unsigned long long matricula = inteiro_valido();

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (usuarios[i].matricula == matricula) {
      encontrado = true;
      printf("Matrícula: %llu\n", usuarios[i].matricula);
      printf("Nome: %s\n", usuarios[i].nome);
      printf("Curso: %s\n", usuarios[i].curso);
      printf("Empréstimos ativos: %hu\n", usuarios[i].qtd_emprestimos);
      break;
    }
  }

  if (!encontrado)
    printf("Usuário não encontrado.\n");


  /*
   * 2 - Recebe o valor digitado pelo usuário do programa, que deve corresponder a matrícula;
   * 3 - Executa um loop de busca, comparando cada matrícula cadastrada na "struct" de usuários com o valor digitado. Quando encontra,
   * imprime na tela a matrícula, o nome, o curso e a quatnidade de empréstimos ativos desse usuário, além de atribuir valor verdadeiro à vaíável encontrado;
   * 4 - Interrompe o laço com break;
   * 5 - Caso o usuário não tenha sido encontrado, continua armazenando o valor false inicial e devolve uma mensagem de erro para o usuário.
   */
}

void buscar_usuarios_nome() {

    if (qtd_usuarios == 0) {
      printf("Nenhum usuário cadastrado.\n");
      return;
    }

    /*
     * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o resto da função caso não. Evita execuções desnecessárias.
     */

  bool encontrado = false;

  char nome[100];
  printf("Inserir nome completo do usuário:\n");
  fgets(nome, sizeof(nome), stdin);
  tratar_string(nome);
  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (strcmp(nome, usuarios[i].nome) == 0) {
      encontrado = true;
      printf("Matrícula: %llu\n", usuarios[i].matricula);
      printf("Nome: %s\n", usuarios[i].nome);
      printf("Curso: %s\n", usuarios[i].curso);
      printf("Empréstimos ativos: %hu\n", usuarios[i].qtd_emprestimos);
      break;
    }
  }

  if (!encontrado)
    printf("Usuário não encontrado.\n");

  /*
   * 2 - Recebe o nome digitado pelo usuário do programa;
   * 3 - Executa um loop de busca, comparando cada nome cadastrado na "struct" de usuários com o nome digitado. Quando encontra,
   * imprime na tela a matrícula, o nome, o curso e a quatnidade de empréstimos ativos desse usuário, além de atribuir valor verdadeiro à vaíável encontrado;
   * 4 - Interrompe o laço com break;
   * 5 - Caso o usuário não tenha sido encontrado, continua armazenando o valor false inicial e devolve uma mensagem de erro para o usuário.
   */

}

void atualizar_usuario() {

    if (qtd_usuarios == 0) {
      printf("Nenhum usuário cadastrado.\n");
      return;
    }

    /*
     * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o resto da função caso não. Evita execuções desnecessárias.
     */

  bool encontrado = false;
  printf("Matrícula do usuário: ");
  unsigned long long matricula = inteiro_valido();

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (usuarios[i].matricula == matricula) {
      encontrado = true;

      printf("Novo nome: ");
      fgets(usuarios[i].nome, sizeof(usuarios[i].nome), stdin);
      tratar_string(usuarios[i].nome);

      printf("Novo curso: ");
      fgets(usuarios[i].curso, sizeof(usuarios[i].curso), stdin);
      tratar_string(usuarios[i].curso);

      salvar_usuarios();
      printf("Usuário atualizado.\n");
      break;
  }

  if (!encontrado)
    printf("Usuário não encontrado.\n");

  /*
   * 2 - Recebe o valor da matrícula digitada pelo usuário, compara com cada matrícula cadastrada na "struct" de usuário. Quando encontra,
   * solicita novo nome e novo curso, mantendo fixos os empréstimos e a matrícula já definidas. Além de atribuir valor true para a variável enocntrado;
   * 3 - Chama a função salvar_usuarios() para atualizar os dados;
   * 4 - Interrompe o laço com break;
   * 5 - Caso encontrado seja false, devolve uma mensagem de erro, pois o usuário não foi encontrado.
   */


}

void listar_usuarios() {

  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o resto da função caso não. Evita execuções desnecessárias.
   */


  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    printf("Matrícula: %llu | Nome: %s | Curso: %s | Empréstimos ativos: %hu\n", usuarios[i].matricula, usuarios[i].nome, usuarios[i].curso, usuarios[i].qtd_emprestimos_ativos);
  }

  /*
   * 2 - Percorre toda a "struct" de usuários e imprime na tela os dados de cada um.
   */

}

void remover_usuario() {

  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o resto da função caso não. Evita execuções desnecessárias.
   */

  unsigned long long matricula;
  bool encontrado = false;
  printf("Inserir matrícula do usuário: ");
  matricula = inteiro_valido();

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {

    if (usuarios[i].matricula == matricula) {
      encontrado = true;

      if (usuarios[i].qtd_emprestimos_ativos != 0) {
        printf("Remoção não autorizada. O usuário possui empréstimos em aberto.\n");
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


  /*
   * 2 - Solicita a matrícula do usuário e executa um loop para buscar a matrícula corresponde. Uma vez encontrado o usuário, atribui valor true para encontrado;
   * 3 - Verifica se o usuário possui empréstimos em aberto. Se possuir, devolve uma mensagem de proibição de remoção do usuário e sai da função com return;
   * 4 - Se o usuário não possui empréstimos em aberto, executa um novo laço que inicia a partir da posição do usuário encontra até a penúltima posição. A última posição é descontada,
   * já que, após a remoção do usuário, essa posição ficará vazia, pois dentro do laço, cada posição é deslocada para a posição anterior;
   * 5 - O total de usuários é diminui de 1 e a "struct" de usuários é realocada com a nova quantidade de usuários e suas novas posições;
   * 6 - Chama a função salvar_usuarios() para atualizar os dados e interrompe o laço com break;
   * 7 - Caso encontrado seja false, devolve uma mensagem de erro para o usuário.
   */

}

void emprestimos_usuario() {

  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o resto da função caso não. Evita execuções desnecessárias.
   */


  Emprestimo *emprestimos = emprestimos_();
  Livro *livros = livros_();
  unsigned long long *qtd_emprestimos = qtd_emprestimos_();
  unsigned long long *qtd_livros = qtd_livros_();

  /*
   * 2 - Declara variáveis para armazenar o retorno de funções dos módulos Livros e Empréstimos, mais especificamente, o total de livros e de empréstimos, bem como suas respectivas "structs";
   *
   */

  unsigned long long matricula;
  bool encontrado = false;
  printf("Inserir matrícula do usuário: ");
  matricula = inteiro_valido();

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (usuarios[i].matricula == matricula) {
      encontrado = true;

      if (usuarios[i].qtd_emprestimos_ativos == 0) {
        printf("Usuário sem empréstimos ativos.\n");
        return;
      }

      printf("Empréstimos ativos: %hu.\n", usuarios[i].qtd_emprestimos_ativos);

      printf("Livros emprestados:\n");
      for (unsigned long long j = 0; j < *qtd_emprestimos; j++) {
        if (usuarios[i].matricula == emprestimos[j].matricula_usuario) {
          for (unsigned long long k = 0; k < *qtd_livros; k++) {
            if (emprestimos[j].codigo_livro == livros[k].codigo) {
              printf("Livro: %s\n", livros[k].titulo);
              printf("Código: %llu\n", livros[k].codigo);
              printf("---------------------------\n\n");
            }
          }
        }
      }
      break;
    }
  }

  if (!encontrado)
    printf("Usuário não encontrado.\n");


  /*
   * 3 - Realiza a busca do usuário compara a matrícula digitada com as matrículas cadastradas na "struct" de usuários. Caso encontre, atribui
   * valor true para encontrado;
   * 4 - Verifica se o usuário possui empréstimos ativos. Se não, imprime uma mensagem para o usuário e sai da função com return;
   * 5 - Caso possua empréstimos ativos (qtd_emprestimos_ativos diferente de 0), informa a quantidade de empréstimos ativos;
   * 6 - Loop externo: compara a matrícula do usuário dentro da "struct" de usuário com a matrícula na "struct" de empréstimos, percorrendo todos os empréstimos;
   * 7 - Loop interno: se a matrícula do usuário for igual a do empréstimo, percorre todos os livros cadastrados, comparando o código do livro na "struct" de livro naquela posição com
   * o código na "struct" de empréstimo naquela posição. Quando encontra códigos iguais, imprime o título e o código de cada livro emprestado ao usuário;
   * 8 - O break força  a parada do loop externo após a execução do loop interno, evitando que ele continue a iterar o laço mesmo após o usuário já ter sido encontrado;
   * 9 - Caso encontrado seja false, imprime uma mensagem de erro para o usuário.
   */
}

/*
* As funções abaixo servem para permitir a relação entre o módulo Usuários com os demais, garantindo que os dados
* sejam iguais/correspondentes em cada módulo de forma isolada.
*/

Usuario *usuarios_() { return usuarios; } //Retorna um ponteiro da "struct" de usuários

unsigned long long *qtd_usuarios_() { return &qtd_usuarios; } //Retorna um ponteiro do total de usuários

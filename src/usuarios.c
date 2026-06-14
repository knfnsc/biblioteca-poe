#include "../include/usuarios.h"
#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/utilitarios.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaração em extern para permitir que os outros módulos tenham acessado a
// essas mesmas variáveis e seus valores

extern unsigned long long qtd_usuarios;
extern Usuario *usuarios;

void carregar_usuarios() {
  if ((usuarios = malloc(sizeof(Usuario) * 1000)) == NULL) {
    printf("Falha ao alocar memória!");
    exit(1);
  }

  /*
   * Aloca dinamicamente espaço para 1000 usuários com a função malloc de
   * <stdlib.io>. Caso o retorno seja um ponteiro cujo conteúdo é NULL, ou seja,
   * não aponta para endereço algum, devolve uma mensagem de erro e sai da
   * função imediatamente com return.
   */

  FILE *arquivo = fopen("usuarios.dat", "rb");
  if (arquivo != NULL) {
    fread(&qtd_usuarios, sizeof(unsigned long long), 1, arquivo);
    fread(usuarios, sizeof(Usuario), qtd_usuarios, arquivo);
    fclose(arquivo);
  }

  /*
   * 1 - Declara um ponteiro para tipo FILE que recebe o retorno da função fopen
   * para leitura de dados binários em um arquivo;
   * 2 - Verifica o conteúdo do ponteiro. Caso seja diferente de NULL, ou seja,
   * caso o arquivo exista e não tenha ocorrido erro em sua abertura executa o
   * bloco seguinte;
   * 3 - Lê do arquivo um dado com tamanho de memória de unsigned long long
   * (8 bytes) e guarda como conteúdo da variável qtd_usuarios;
   * 4 - Lê do arquivo os dados dos usuários e guarda essas informações nos
   * campos correspondentes dentro da "struct" de usuários;
   * 5 - Fecha o arquivo.
   */
}

void salvar_usuarios() {
  FILE *arquivo = fopen("usuarios.dat", "wb");
  if (arquivo == NULL) {
    printf("Falha ao salvar usuários!\n");
    exit(1);
  }

  /*
   * 1 - Declara um ponteiro para tipo FILE que recebe o retorno da função fopen
   * para escrita de dados binários em um arquivo;
   * 2 - Verifica o conteúdo doponteiro. Caso seja igual a NULL, ou seja, se
   * ocorrer erro, return é executado e sai da função.
   */

  fwrite(&qtd_usuarios, sizeof(unsigned long long), 1, arquivo);
  fwrite(usuarios, sizeof(Usuario), qtd_usuarios, arquivo);
  fclose(arquivo);

  /*
   * 3 -  Escreve no arquivo um dado com tamanho de memória de unsigned long
   * long (8 bytes) e guarda como conteúdo da variável qtd_usuarios;
   * 4 - Escreve no arquivo os dados dos usuários e guarda essas informações
   * nos campos correspondentes dentro da "struct" de usuários;
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
   * 1 - Declara um novo usuário e cria uma variável auxiliar maior_matricula
   * para comparar cada matrícula já existentente com 0. Término do laço, essa
   * variável armazena a matrícula do último usuário que foi cadastrado. Para
   * que não haver matrículas iguais, soma 1 a esse valor e atribui esse valor à
   * matrícula do novo usuário. Assim, as matrículas formam uma lista crescente.
   */

  printf("Nome do usuário: ");
  string_valido(novo_usuario.nome);

  printf("Curso do usuário: ");
  string_valido(novo_usuario.curso);

  novo_usuario.qtd_emprestimos_ativos = 0;

  usuarios[qtd_usuarios] = novo_usuario;
  qtd_usuarios++;

  salvar_usuarios();
  printf("Novo usuário cadastrado.\n");

  /*
   * 2 - Recebe as entradas de nome e curso dadas pelo usuário do programa e
   * aribui automaticamente o valor 0 para a quantidade de empréstimos ativos do
   * novo usuário;
   * 3 - Adiciona o novo usuário à "struct" de usuários eincrementa o valor da
   * variável qtd_usuários para comportar o novo usuário;
   * 4 - Chama a função salvar_usuarios() para adicionar os novos dados no
   * arquivo binário.
   */
}

void buscar_usuario_matricula() {
  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o
   * resto da função caso não. Evita execuções desnecessárias.
   */

  bool encontrado = false;
  printf("matrícula do usuario: ");
  unsigned long long matricula;
  inteiro_valido(&matricula);

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (usuarios[i].matricula ==
        matricula) { // comparar a matrícula digitada pelo usuário com as
                     // matrículas salvas na struct usuario
      encontrado = true;
      printf("matrícula: %llu\n", usuarios[i].matricula);
      printf("nome: %s\n", usuarios[i].nome);
      printf("curso: %s\n", usuarios[i].curso);
      break; // interrompe o laço assim que encontra o usuário
    }
  }

  if (!encontrado)
    printf("Usuário não encontrado.\n");

  /*
   * 2 - Recebe o valor digitado pelo usuário do programa, que deve corresponder
   * a matrícula;
   * 3 - Executa um loop de busca, comparando cada matrícula cadastrada na
   * "struct" de usuários com o valor digitado. Quando encontra,imprime na tela
   * a matrícula, o nome, o curso e a quatnidade de empréstimosativos desse
   * usuário, além de atribuir valor verdadeiro à vaíável encontrado;
   * 4 - Interrompe o laço com break;
   * 5 - Caso o usuário não tenhasido
   * encontrado, continua armazenando o valor false inicial e devolve uma
   * mensagem de erro para o usuário.
   */
}

void buscar_usuario_nome() {
  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o
   * resto da função caso não. Evita execuções desnecessárias.
   */

  bool encontrado = false;

  char nome[100];
  printf("nome completo do usuário: ");
  string_valido(nome);

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (strcmp(nome, usuarios[i].nome) ==
        0) { // comparar o nome digitado pelo usuario com os nomes salvos na
             // struct usuario
      encontrado = true;
      printf("matrícula: %llu\n", usuarios[i].matricula);
      printf("nome: %s\n", usuarios[i].nome);
      printf("curso: %s\n", usuarios[i].curso);
      break; // interrompe o laço assim que encontra o usuário
    }
  }

  if (!encontrado) // informa mensagem de erro antes de solicitar novamente o
                   // nome, caso não tenha sido encontrado
    printf("Usuário não encontrado.\n");

  /*
   * 2 - Recebe o nome digitado pelo usuário do programa;
   * 3 - Executa um loop de busca, comparando cada nome cadastrado na "struct"
   * de usuários com o nome digitado. Quando encontra, imprime na tela a
   * matrícula, o nome, o curso e a quatnidade de empréstimos ativos desse
   * usuário, além de atribuir valor verdadeiro à vaíável encontrado;
   * 4 - Interrompe o laço com break;
   * 5 - Caso o usuário não tenha sido encontrado, continua armazenando o valor
   * false inicial e devolve uma mensagem de erro para o usuário.
   */
}

void atualizar_usuario() {
  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o
   * resto da função caso não. Evita execuções desnecessárias.
   */

  bool encontrado = false;
  printf("matrícula do usuário: ");
  unsigned long long matricula;
  inteiro_valido(&matricula);

  // laço relacionado com a busca dentro da struct usuarios
  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    // comparar a matrícula digitada pelo usuario com as
    // matrículas salvas na struct usuario
    if (usuarios[i].matricula == matricula) {
      encontrado = true;
      printf("Novo nome: ");
      string_valido(usuarios[i].nome);

      printf("Novo curso: ");
      string_valido(usuarios[i].curso);

      salvar_usuarios();
      printf("Usuário atualizado.\n");
      // interrompe o laço assim que encontra o usuário após os comandos
      // acima
      break;
    }
  }

  if (!encontrado)                       // se encontrado == 0 (falso)
    printf("Usuário não encontrado.\n"); // Verifica se o usuário deseja
                                         // continuar tentando; se ele não
                                         // quiser, ele sai da função

  /*
   * 2 - Recebe o valor da matrícula digitada pelo usuário, compara com cada
   * matrícula cadastrada na "struct" de usuário. Quando encontra, solicita novo
   * nome e novo curso, mantendo fixos os empréstimos e a matrícula já
   * definidas. Além de atribuir valor true para a variável enocntrado;
   * 3 - Chama a função salvar_usuarios() para atualizar os dados;
   * 4 - Interrompe o laço com break;
   * 5 - Caso encontrado seja false, devolve uma mensagem de erro, pois o
   * usuário não foi encontrado.
   */
}

void listar_usuarios() {
  // considera as duas possibilidades:
  // 1 - sistema já em funcionamento e com usuários já cadastrados;
  // 2 - primeira execução, quando não existem usuários cadastrados.
  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o
   * resto da função caso não. Evita execuções desnecessárias.
   */

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    printf("matrícula: %llu | nome: %s | curso: %s | empréstimos ativos: %d\n",
           usuarios[i].matricula, usuarios[i].nome, usuarios[i].curso,
           usuarios[i].qtd_emprestimos_ativos);
  }

  /*
   * 2 - Percorre toda a "struct" de usuários e imprime na tela os dados de cada
   * um.
   */
}

void remover_usuario() {
  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o
   * resto da função caso não. Evita execuções desnecessárias.
   */

  unsigned long long matricula;
  bool encontrado = false;
  printf("matrícula do usuário: ");
  inteiro_valido(&matricula);

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {

    if (usuarios[i].matricula == matricula) {
      encontrado = true;

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

  /*
   * 2 - Solicita a matrícula do usuário e executa um loop para buscar a
   * matrícula corresponde. Uma vez encontrado o usuário, atribui valor true
   * para encontrado;
   * 3 - Verifica se o usuário possui empréstimos em aberto. Se possuir,
   * devolve uma mensagem de proibição de remoção do usuário e sai da
   * função com return;
   * 4 - Se o usuário não possui empréstimos em aberto, executa um novo laço
   * que inicia a partir da posição do usuário encontra atéa penúltima posição.
   * A última posição é descontada, já que, após a remoçãodo usuário, essa
   * posição ficará vazia, pois dentro do laço, cada posição é deslocada para a
   * posição anterior;
   * 5 - O total de usuários é diminui de 1 e a "struct" de usuários é
   * realocada com a nova quantidade de usuários e suas novas posições;
   * 6 - Chama a função salvar_usuarios() para atualizar osdados e interrompe
   * o laço com break;
   * 7 - Caso encontrado seja false, devolve uma mensagem de erro para o
   * usuário.
   */
}

void emprestimos_usuario() {
  if (qtd_usuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  /*
   * 1 - Verifica se já existe pelo menos um usuário cadastrado e suspende o
   * resto da função caso não. Evita execuções desnecessárias.
   */

  Emprestimo *emprestimos = emprestimos_();
  Livro *livros = livros_();
  unsigned long long *qtd_emprestimos = qtd_emprestimos_();
  unsigned long long *qtd_livros = qtd_livros_();

  /*
   * 2 - Declara variáveis para armazenar o retorno de funções dos módulos
   * Livros e Empréstimos, mais especificamente, o total de livros e de
   * empréstimos, bem como suas respectivas "structs";
   */

  unsigned long long matricula;
  bool encontrado = false;
  printf("matrícula do usuário: ");
  inteiro_valido(&matricula);

  for (unsigned long long i = 0; i < qtd_usuarios; i++) {
    if (usuarios[i].matricula == matricula) {
      encontrado = true;

      if (usuarios[i].qtd_emprestimos_ativos == 0) {
        printf("Usuário sem empréstimos ativos.\n");
        return;
      }

      printf("empréstimos ativos: %d\n", usuarios[i].qtd_emprestimos_ativos);

      printf("Livros emprestados:\n");
      for (unsigned long long j = 0; j < *qtd_emprestimos; j++) {
        if (usuarios[i].matricula == emprestimos[j].matricula_usuario) {
          for (unsigned long long k = 0; k < *qtd_livros; k++) {
            if (emprestimos[j].codigo_livro == livros[k].codigo) {
              printf("- %s | código: %llu\n", livros[k].titulo,
                     livros[k].codigo);
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
   * 3 - Realiza a busca do usuário compara a matrícula digitada com as
   * matrículas cadastradas na "struct" de usuários. Caso encontre, atribui
   * valor true para encontrado;
   * 4 - Verifica se o usuário possui empréstimos ativos. Se não, imprime uma
   * mensagem para o usuário e sai da função com return;
   * 5 - Caso possua empréstimos ativos (qtd_emprestimos_ativos diferente de 0),
   * informa a quantidade de empréstimos ativos;
   * 6 - Loop externo: compara a matrícula do usuário dentro da "struct" de
   * usuário com a matrícula na "struct" de empréstimos, percorrendo todos os
   * empréstimos;
   * 7 - Loop interno: se a matrícula do usuário for igual a do empréstimo,
   * percorre todos os livros cadastrados, comparando o código do livro na
   * "struct" de livro naquelaposição com o código na "struct" de empréstimo
   * naquela posição. Quando encontra códigos iguais, imprime o título e o
   * código de cada livro emprestado ao usuário;
   * 8 - O break força a parada do loop externo após a execução do loop interno,
   * evitando que ele continue a iterar o laço mesmo após o usuário já ter sido
   * encontrado;
   * 9 - Caso encontrado seja false, imprime uma mensagem de erro para o
   * usuário.
   */
}

Usuario *usuarios_() { return usuarios; }

unsigned long long *qtd_usuarios_() { return &qtd_usuarios; }

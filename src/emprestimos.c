#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/utilitarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern unsigned long long qtd_emprestimos;
extern Emprestimo *emprestimos;

void carregar_emprestimos() {
  // Inline if.
  // Declara a variável "emprestimos" e checa se operação ocorreu corretamente.
  if ((emprestimos = malloc(sizeof(Emprestimo) * 1000)) == NULL) {
    printf("Falha ao alocar memória!");
    exit(1);
  }

  FILE *arquivo = fopen("emprestimos.dat", "rb");
  if (arquivo != NULL) {
    fread(&qtd_emprestimos, sizeof(unsigned long long), 1, arquivo);
    fread(emprestimos, sizeof(Emprestimo), qtd_emprestimos, arquivo);
    fclose(arquivo);
  }
}

void salvar_emprestimos() {
  FILE *arquivo = fopen("emprestimos.dat", "wb");
  if (arquivo == NULL) {
    printf("Falha ao salvar arquivo!\n");
    exit(1);
  }

  // escreve o contador de empréstimos (primeiros 64 bits do arquivo)
  fwrite(&qtd_emprestimos, sizeof(unsigned long long), 1, arquivo);
  fwrite(emprestimos, sizeof(Emprestimo), qtd_emprestimos, arquivo);
  fclose(arquivo);
}

void ler_emprestimos() {
  if (qtd_emprestimos == 0) {
    printf("Sem empréstimos registrados.\n");
    return;
  }

  // ponteiro de struct para converter "time_t" (segundos) para um formato
  // legível.
  struct tm *data_retirada, *data_prevista, *data_devolucao;
  unsigned short dia_retirada, dia_prevista, dia_devolucao, mes_retirada,
      mes_prevista, mes_devolucao;

  for (unsigned long long i = 0; i < qtd_emprestimos; i++) {
    // localtime retorna um ponteiro de struct (struct tm *),
    // cada propriedade do struct é uma parte da data.
    // P. ex.: tm_mon -> mês do ano; retorna de 0-11, por isso o "+ 1".
    data_retirada = localtime(&emprestimos[i].data_retirada);
    dia_retirada = data_retirada->tm_mday;
    mes_retirada = data_retirada->tm_mon + 1;

    data_prevista = localtime(&emprestimos[i].data_prevista);
    dia_prevista = data_prevista->tm_mday;
    mes_prevista = data_prevista->tm_mon + 1;

    // %llu é o identificador do tipo unsigned long long, 03 significa que
    // possui três algarismos 0 de sobra.
    // P. ex.: 1 -> 0001.
    printf("id: %03llu | matrícula: %03llu | código do livro: %03llu"
           " | retirada: %02d/%02d | prazo: %02d/%02d | devolvido: ",
           emprestimos[i].id, emprestimos[i].matricula_usuario,
           emprestimos[i].codigo_livro, dia_retirada, mes_retirada,
           dia_prevista, mes_prevista);

    if (emprestimos[i].devolvido) {
      data_devolucao = localtime(&emprestimos[i].data_devolucao);
      dia_devolucao = data_devolucao->tm_mday;
      mes_devolucao = data_devolucao->tm_mon + 1;
      printf("%02d/%02d\n", dia_devolucao, mes_devolucao);
    } else {
      printf("pendente\n");
    }
  }
}

void registrar_emprestimo() {
  unsigned long long matricula_usuario, codigo_livro;

  printf("Digite a matrícula: ");
  inteiro_valido(&matricula_usuario);

  Usuario *usuarios = usuarios_();
  unsigned long long *qtd_usuarios = qtd_usuarios_();

  bool usuario_encontrado = false;
  for (unsigned long long i = 0; i < *qtd_usuarios; i++) {
    if (matricula_usuario == usuarios[i].matricula) {
      if (usuarios[i].qtd_emprestimos_ativos == 3) {
        printf("Número máximo de empréstimos realizados!\n");
        return;
      }
      usuario_encontrado = true;
      break;
    }
  }
  if (!usuario_encontrado) {
    printf("Nenhum usuário com essa matrícula encontrado!\n");
    return;
  }

  printf("Digite o código do livro: ");
  inteiro_valido(&codigo_livro);

  Livro *livros = livros_();
  unsigned long long *qtd_livros = qtd_livros_();

  bool livro_encontrado = false;
  for (unsigned long long i = 0; i < *qtd_livros; i++) {
    if (codigo_livro == livros[i].codigo) {
      if (livros[i].qtd_disponivel == 0) {
        printf("Esse livro não possui exemplares disponíveis.\n");
        return;
      }
      livro_encontrado = true;
      break;
    }
  }
  if (!livro_encontrado) {
    printf("Nenhum livro com esse código encontrado!\n");
    return;
  }

  for (unsigned long long i = 0; i < qtd_emprestimos; i++) {
    if (matricula_usuario == emprestimos[i].matricula_usuario &&
        codigo_livro == emprestimos[i].codigo_livro &&
        !emprestimos[i].devolvido) {
      printf("Não é possível emprestar o mesmo livro duas vezes.\n");
      return;
    }
  }

  const time_t segundos_no_dia = 24 * 3600;
  time_t agora =
      time(NULL); // time recebe um tempo inicial como parâmetro, como estamos
                  // partindo do momento atual, usamos NULL.
  time_t prazo = agora + (14 * segundos_no_dia);
  Emprestimo novo_emprestimo = {
      .id = qtd_emprestimos + 1,
      .matricula_usuario = matricula_usuario,
      .codigo_livro = codigo_livro,
      .data_retirada = agora,
      .data_prevista = prazo,
      .data_devolucao =
          0, // placeholder para uma data que ainda não foi definida
      .devolvido = false,
  };

  emprestimos[qtd_emprestimos] = novo_emprestimo;
  qtd_emprestimos++;
  for (unsigned long long i = 0; i < *qtd_usuarios; i++) {
    if (matricula_usuario == usuarios[i].matricula) {
      usuarios[i].qtd_emprestimos_ativos++;
      salvar_usuarios();
      break;
    }
  }
  for (unsigned long long i = 0; i < *qtd_livros; i++) {
    if (codigo_livro == livros[i].codigo) {
      livros[i].qtd_disponivel--;
      salvar_livros();
      break;
    }
  }

  salvar_emprestimos();
  printf("Empréstimo registrado!\n");
};

void registrar_devolucao() {
  if (qtd_emprestimos == 0) {
    printf("Sem empréstimos registrados.\n");
    return;
  }

  unsigned long long matricula_usuario, codigo_livro;

  printf("Digite a matrícula: ");
  inteiro_valido(&matricula_usuario);

  printf("Digite o código do livro: ");
  inteiro_valido(&codigo_livro);

  bool encontrado;
  for (unsigned long long i = 0; i < qtd_emprestimos; i++) {
    encontrado = emprestimos[i].matricula_usuario == matricula_usuario &&
                 emprestimos[i].codigo_livro == codigo_livro &&
                 !emprestimos[i].devolvido;

    if (encontrado) {
      time_t agora = time(NULL);
      emprestimos[i].data_devolucao = agora;
      emprestimos[i].devolvido = true;

      Usuario *usuarios = usuarios_();
      unsigned long long *qtd_usuarios = qtd_usuarios_();

      for (unsigned long long i = 0; i < *qtd_usuarios; i++) {
        if (matricula_usuario == usuarios[i].matricula) {
          usuarios[i].qtd_emprestimos_ativos--;
          salvar_usuarios();
          break;
        }
      }

      Livro *livros = livros_();
      unsigned long long *qtd_livros = qtd_livros_();

      for (unsigned long long i = 0; i < *qtd_livros; i++) {
        if (codigo_livro == livros[i].codigo) {
          livros[i].qtd_disponivel++;
          salvar_livros();
          break;
        }
      }

      salvar_emprestimos();
      printf("Devolução registrada!\n");
      return;
    }
  }

  printf("Nenhum empréstimo correspondente encontrado.\n");
};

Emprestimo *emprestimos_() { return emprestimos; }

unsigned long long *qtd_emprestimos_() { return &qtd_emprestimos; }

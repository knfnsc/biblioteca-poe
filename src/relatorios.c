#include "../include/relatorios.h"
#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/utilitarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void alunos_atrasados() {
  unsigned long long *qtd_emprestimos = qtd_emprestimos_();
  Emprestimo *emprestimos = emprestimos_();

  if (*qtd_emprestimos == 0) {
    printf("Sem empréstimos registrados.\n");
    return; // Encerra a função mais cedo
  }

  // time(NULL) pega o horário atual do sistema em segundos (timestamp Unix)
  time_t agora = time(NULL);
  struct tm *prazo; // Ponteiro para uma estrutura que divide o tempo em dia,
                    // mês, ano, etc.
  unsigned short dia, mes, dias_atraso;

  bool encontrado = false;
  // Percorre todo o array de empréstimos
  for (unsigned long long i = 0; i < *qtd_emprestimos; i++) {
    //  emprestimos[i].devolvido e agora > emprestimos[i].data_prevista -> O
    //  momento atual passou da data prevista de entrega.
    if (!emprestimos[i].devolvido && agora > emprestimos[i].data_prevista) {

      // difftime calcula a diferença em segundos entre dois tempos.
      // Dividimos por (24 * 3600), que é o total de segundos em um dia (24h *
      // 60min * 60seg), para converter o resultado de segundos para dias de
      // atraso.
      dias_atraso =
          (unsigned short)(difftime(agora, emprestimos[i].data_prevista) /
                           (24 * 3600));

      // localtime converte o timestamp (segundos) para a estrutura 'tm'
      // (horário local)
      prazo = localtime(&emprestimos[i].data_prevista);
      dia = prazo->tm_mday;    // Pega o dia do mês (1 a 31)
      mes = prazo->tm_mon + 1; // Pega o mês. Somamos 1 porque no C os meses vão
                               // de 0 (Janeiro) a 11 (Dezembro).

      // Exibe os dados formatados. O '%02d' garante que números menores que 10
      // ganhem um zero à esquerda (ex: 05/09).
      printf("matrícula: %llu | código do livro: %llu | prazo: %02d/%02d | "
             "atraso: %d dia(s)\n",
             emprestimos[i].matricula_usuario, emprestimos[i].codigo_livro, dia,
             mes, dias_atraso);

      encontrado = true;
    }
  }

  if (!encontrado)
    printf("Nenhum aluno possui atrasos.\n");
}

void livros_mais_emprestados() {
  // Busca a lista de livros e a quantidade total através de funções auxiliares
  Livro *livros = livros_();
  unsigned long long *qtd_livros = qtd_livros_();

  unsigned long long *qtd_emprestimos = qtd_emprestimos_();
  Emprestimo *emprestimos = emprestimos_();

  // Validação inicial: se não há livros no sistema, cancela o relatório
  if (*qtd_livros == 0) {
    printf("Nenhum livro cadastrado.\n");
    return;
  }

  // Alocando a struct em um vetor dinamico
  RankingLivro *ranking = malloc(sizeof(RankingLivro) * (*qtd_livros));
  if (ranking == NULL) {
    printf("Falha ao alocar memoria!\n");
    return; // Evita um crash caso o sistema fique sem memória
  }

  // Copiando os dados originais para a nossa struct auxiliar. Fazendo isso para
  // não bagunçar a ordem do struct normal.
  for (unsigned long long i = 0; i < *qtd_livros; i++) {
    ranking[i].codigo = livros[i].codigo;
    ranking[i].total_emprestimos = 0;
    strcpy(ranking[i].titulo, livros[i].titulo);
  }

  // Agora, com o contador total emprestimos vamos contar o total de vezes que
  // esse livro foi emprestado. Dito isso, vamos ordenar nossa struct ranking
  // livros para que o primeiro livro seja o mais emprestado.
  for (unsigned long long i = 0; i < *qtd_emprestimos; i++) {
    for (unsigned long long j = 0; j < *qtd_livros; j++) {
      if (emprestimos[i].codigo_livro == ranking[j].codigo) {
        ranking[j].total_emprestimos++;
      }
    }
  }

  // Bubble Sort para que o livro mais alugado apareça em primeiro e assim por
  // diante.
  RankingLivro temp;
  for (unsigned long long i = 0; i < *qtd_livros - 1; i++) {
    for (unsigned long long j = 0; j < *qtd_livros - 1 - i; j++) {
      if (ranking[j].total_emprestimos < ranking[j + 1].total_emprestimos) {
        temp = ranking[j];
        ranking[j] = ranking[j + 1];
        ranking[j + 1] = temp;
      }
    }
  }

  // Agora será mostrado os livros mais emprestados.
  for (unsigned long long i = 0; i < *qtd_livros; i++) {
    printf("%llu. %s | empréstimos: %llu\n", i + 1, ranking[i].titulo,
           ranking[i].total_emprestimos);
  }

  free(ranking);
}

// Essa função mostrará quantos livros estão disponiveis no acervo.
void acervo_disponivel() {
  Livro *livros = livros_();
  unsigned long long *qtd_livros = qtd_livros_();

  if (*qtd_livros == 0) {
    printf("Nenhum livro cadastrado.\n");
    return;
  }

  for (unsigned long long i = 0; i < *qtd_livros; i++) {
    if (livros[i].qtd_disponivel >
        0) { // Verificando se o livro está disponivel. Esse if faz isso.
      printf("código: %llu | título: %s | autor: %s | disponíveis: %hu\n",
             livros[i].codigo, livros[i].titulo, livros[i].autor,
             livros[i].qtd_disponivel);
    }
  }
}

// Essa função é responsavel por mostrar o historico de emprestimos do usuario.
void historico_usuario() {
  unsigned long long matricula;
  printf("matrícula do usuário: ");
  inteiro_valido(&matricula);

  Usuario *usuarios = usuarios_();
  unsigned long long *qtd_usuarios = qtd_usuarios_();

  unsigned long long *qtd_emprestimos = qtd_emprestimos_();
  Emprestimo *emprestimos = emprestimos_();

  // Verificando se a matricula do usuario está certa.
  bool encontrado = false;
  for (unsigned long long i = 0; i < *qtd_usuarios; i++) {
    if (usuarios[i].matricula == matricula) {
      printf("Histórico de %s:\n", usuarios[i].nome);
      encontrado = true;
      break;
    }
  }

  // Resposta caso o usuario não seja encontrado
  if (!encontrado) {
    printf("Nenhum usuário com essa matrícula encontrado.\n");
    return;
  }

  // A partir de agora estamos contando com um usuario existente.
  if (*qtd_emprestimos == 0) {
    printf("Sem emprestimos registrados.\n");
    return;
  }

  // Ponteiros para formatar as 3 datas possíveis de um empréstimo
  struct tm *data_retirada, *data_prevista, *data_devolucao;
  unsigned short dia_retirada, mes_retirada, dia_prevista, mes_prevista;

  // Procura por todos os empréstimo que o usuario fez
  for (unsigned long long i = 0; i < *qtd_emprestimos; i++) {
    if (emprestimos[i].matricula_usuario == matricula) {

      data_retirada = localtime(&emprestimos[i].data_retirada);
      dia_retirada = data_retirada->tm_mday;
      mes_retirada = data_retirada->tm_mon + 1;

      data_prevista = localtime(&emprestimos[i].data_prevista);
      dia_prevista = data_prevista->tm_mday;
      mes_prevista = data_prevista->tm_mon + 1;

      // Agora, após ajeitar os ponteiros para as posições, mostramos as
      // informações do emprestimo.
      printf("id: %llu | codigo do livro: %llu | retirada: %02d/%02d | prazo: "
             "%02d/%02d | devolvido: ",
             emprestimos[i].id, emprestimos[i].codigo_livro, dia_retirada,
             mes_retirada, dia_prevista, mes_prevista);

      // Verificando se o livro já foi devolvido. Para isso, comparamos as datas
      // de devolução
      if (emprestimos[i].devolvido) {
        data_devolucao = localtime(&emprestimos[i].data_devolucao);
        printf("%02d/%02d\n", data_devolucao->tm_mday,
               data_devolucao->tm_mon + 1);
      } else {
        // Se não devolveu, indica que a entrega está pendente
        printf("pendente\n");
      }
    }
  }
}

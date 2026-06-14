#include "../include/utilitarios.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void limpar_buffer() {
  /*
   * Limpa o STDIN até que os \n (remanescentes do scanf) sejam limpos.
   */

  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    if (c == EOF) {
      clearerr(stdin);
    }
  };
}

void limpar_tela() {
  /*
   * Limpa a tela do terminal.
   */
  printf("\e[2J\e[H"); // sequência ANSI para mover o cursor para a posição (1,
                       // 1) e limpar a tela.
  fflush(stdout);      // garante que o buffer seja enviado ao terminal
}

void tratar_string(char *str) {
  /*
   * Padroniza as string passadas para as structs.
   */
  str[strcspn(str, "\n")] = '\0';
  // limpa o buffer, trocando o "\n" por "\0"

  int tam = strlen(str);
  int p_nova = 1; // verifica se é início de uma nova palavra

  for (int i = 0; i < tam; i++) {
    if (str[i] == ' ') {
      p_nova = 1; // nova palavra se inicia após espaço
    } else if (p_nova) {
      p_nova = 0;
      str[i] = toupper(str[i]); // primeira letra maiúscula
    } else {
      str[i] = tolower(str[i]); // demais letras minúsculas
    }
  }

  const char *prep[] = {"De", "Da", "Do", "Dos", "Das", "E"};
  int qtd = sizeof(prep) / sizeof(*prep);

  char copia[256] = "";
  char *palavra = strtok(str, " "); // quebra a string nos espaços

  while (palavra) {
    for (int i = 0; i < qtd; i++) {
      if (strcmp(palavra, prep[i]) == 0) {
        palavra[0] = tolower(palavra[0]); // preposição volta para minúscula
      }
    }
    strcat(copia, palavra);
    strcat(copia, " ");
    palavra = strtok(NULL, " ");
  }

  copia[strlen(copia) - 1] = '\0'; // remove o último espaço adicionado
  strcpy(str, copia); // copia o resultado de volta para a string original
}

void inteiro_valido(unsigned long long *var) {
  /* realiza a leitura do caractere digitado pelo usuário -> enquanto não
   * for um caractere válido (enquanto != 1, ou seja, falso) do tipo int, repete
   * a leitura assim que o caractere for válido, pega o '\n' ou EOF, evitando
   * sujeira no buffer -> retorna o que o usuário digitou;
   */

  for (;;) {
    int retorno = scanf("%llu", var);

    if (retorno == 1) {
      limpar_buffer();
      return;
    }

    if (retorno == EOF) {
      clearerr(stdin);
    } else {
      limpar_buffer();
    }

    limpar_buffer();
    printf("Não é um número válido. Digite novamente: ");
  }
}

void char_valido(char *var) {
  /* realiza a leitura do caractere digitado pelo usuário -> enquanto não
   * for um caractere válido, repete a leitura, ignora whitespaces antes
   * de capturar o caractere, tratando EOF para não travar a execução */

  for (;;) {
    int retorno = scanf(" %c", var);

    if (retorno == 1) {
      limpar_buffer();
      return;
    }

    if (retorno == EOF) {
      clearerr(stdin);
    } else {
      limpar_buffer();
    }

    limpar_buffer();
    printf("Caractere inválido. Digite novamente: ");
  }
}

void string_valido(char *var) {
  /* realiza a leitura da string digitada pelo usuário -> enquanto não
   * for uma string válida, repete a leitura, tratando EOF para não
   * travar a execução e aplicando o tratamento de capitalização */

  for (;;) {
    int retorno = scanf("%s", var);

    if (retorno == 1) {
      limpar_buffer();
      tratar_string(var);
      return;
    }

    if (retorno == EOF) {
      clearerr(stdin);
    } else {
      limpar_buffer();
    }

    limpar_buffer();
    printf("String inválida. Digite novamente: ");
  }
}

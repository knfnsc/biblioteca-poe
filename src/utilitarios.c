#include "../include/utilitarios.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void limpar_buffer() {
  while (getchar() != '\n')
    continue;
};

void limpar_tela() { printf("\e[1;1H\e[2J"); };

void tratar_string(char *str) {
  // padronizar as entradas de texto sempre deixando as iniciais
  // de cada palavra como maiúscula + considerar preposições

  str[strcspn(str, "\n")] = '\0';
  // recebe a string e limpa o buffer, trocando o "\n" digitado pelo
  // usuário por "\0", recohecendo o fim da string

  int tam = strlen(str);
  int p_nova = 1;
  // funciona como um dado boolean, um verificador para
  // encontrar as repetições

  // percorrer cada caractere da string para padronizar a letra inicial de cada
  // palavra como maiúscula e o restante minúscula
  for (int i = 0; i < tam; i++) {

    if (str[i] == ' ') {
      // a cada ' ' reconhece que uma nova palavra se inicia,
      // atribuindo 1 (true) para p_nova
      p_nova = 1;
    } else if (p_nova) {
      // se é uma nova palavra, ou seja, se p_nova == 1,
      // então ele passa a string para maiúscula
      p_nova = 0;
      // p_nova recebe 0 para que na próxima iteração, não seja
      // reconhecido como uma nova palavra
      str[i] = toupper(str[i]);
    } else {
      p_nova = 0;
      // considera que mantém dentro de uma mesma palavra, então
      // mantém os caracteres minúsculos
      str[i] = tolower(str[i]);
    }
  }

  const char *prep[] = {"De", "Da", "Do", "Dos", "Das", "E"};
  // aponta para uma quantidade de endereços de memória igual
  // ao número de elementos de prep[]

  int qtd = sizeof(prep) / sizeof(*prep);
  // calcular quantidade de elementos de
  // prep[] baseado no tamanho total
  // do array dividido pelo tamanho de um único elemento, no caso, para o
  // primeiro termo do vetor (todos os elementos têm o mesmo tamanho)

  char copia[2000] = "";

  char *palavra = strtok(str, " ");
  // funcção para separar/quebrar a string em uma substring toda
  // vez que encontrar " " -> a string original é perdida

  while (palavra) {
    // enquanto a string existir
    for (int i = 0; i < qtd; i++) {
      // percorra todos os elementos de prep[]

      if (strcmp(palavra, prep[i]) == 0) {
        // verifique se a substring encontrada é igual a um dos elementos
        // de prep[]
        palavra[0] = tolower(palavra[0]);
        // se for igual, o primeiro caractere da
        // substring passa de minúsculo para maiúsculo
      }
    }

    strcat(copia, palavra);
    // concatena a substring com copia declarada antes e
    // deixa um espaço para começar a próxima palavra
    strcat(copia, " ");
    palavra = strtok(NULL, " ");
    // se desloca pela string, permitindo encontrar a
    // próxima substring dentro da string original
  }

  copia[strlen(copia) - 1] = '\0';
  // o último caractere dentro de copia no momento em que ele termina
  // de executar o laço acima é " ", mas
  // isso não é útil, então colocamos no lugar de " " o '\0' para marcar o fim
  // da string. Ex.:
  //  "bom_" -> strlen(copia) = 4
  //  copia[3] = " " -> copia[3] = '\0'

  strcpy(str, copia);
  // salva uma cópia das modificações no endereço da string
  // original -> resolve o problema de perda da string original
};

char char_valido() {
  // vai realizar a leitura do caractere digitado pelo
  // usuário -> enquanto não for um caractere válido
  // (enquanto != 1, ou seja, falso) do tipo char, repete a
  // leitura assim que o caractere for válido, pega o '\n' ou
  // EOF, evitando sujeira no buffer -> retorna o que o
  // usuário digitou;
  char resp;

  while (scanf("%c", &resp) != 1) {
    printf("Resposta inválida. Digite novamente:\n");
    limpar_buffer();
  }

  limpar_buffer();

  return resp;
};

// vai realizar a leitura do caractere digitado pelo usuário -> enquanto não for
// um caractere válido (enquanto != 1, ou seja, falso) do tipo int, repete a
// leitura assim que o caractere for válido, pega o '\n' ou EOF, evitando
// sujeira no buffer -> retorna o que o usuário digitou;
int inteiro_valido() {
  int valor;

  while (scanf("%d", &valor) != 1) {
    printf("Valor inválido. Digite novamente:\n");
    limpar_buffer();
  }

  limpar_buffer();

  return valor;
};

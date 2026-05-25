#include <stdio.h>

void limpar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void limpar_tela() { printf("\e[1;1H\e[2J"); }

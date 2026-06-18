#ifndef LIVROS_H
#define LIVROS_H

typedef struct { 
  unsigned long long codigo; // código único do livro, gerado automaticamente.
  char titulo[256];
  char autor[256];
  unsigned int ano;
  char genero[256];
  unsigned short qtd_total; // quantidade total de exemplares do livro. Inicialmente é igual à quantidade disponível, e é incrementada a cada cadastro, e decrementada a cada remoção. 
  unsigned short qtd_disponivel; // quantidade de exemplares disponíveis para empréstimo. Inicialmente é igual à quantidade total, e é decrementada a cada empréstimo, e incrementada a cada devolução.
} Livro;
// unsigned short é um tipo de dado inteiro sem sinal, que ocupa 2 bytes de memória e pode armazenar valores de 0 a 65535. 
//É utilizado para representar a quantidade total e disponível de exemplares do livro, pois é improvável que haja mais de 65535 exemplares de um mesmo livro em uma biblioteca.
void carregar_livros();
void salvar_livros();

void cadastrar_livro();
void listar_livros();
void buscar_livro_codigo();
void buscar_livro_titulo();
void atualizar_livro();
void remover_livro();
void consultar_usuarios_livro();

Livro *livros_(); // retorna o ponteiro para a array de livros, para que outras partes do programa possam acessar os livros cadastrados.
unsigned long long *qtd_livros_(); // retorna o ponteiro para a variável 'qtd_livros', para que outras partes do programa possam acessar a quantidade de livros cadastrados.

#endif 

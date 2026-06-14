#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#define SEPARADOR                                                              \
  "--------------------------------------------------------------------------" \
  "----------------------\n"

// evita problemas quando houver múltiplos tipos de entrada de texto
// para o usuário, evitando conflitos com fgets e scanf, por exemplo
void limpar_buffer();

// tornar a interface de interação com o usuário mais dinâmica e limpa
void limpar_tela();

// padroniza a escrita dentro dos arquivos, facilitando leitura e
// pesquisa
void tratar_string(char *str);

// objetivo: garantir que os valores passados pelo usuário sejam os adequados
// para executar as funções dentro do programa + evitar problemas de buffer
void inteiro_valido(unsigned long long *var);

void char_valido(char *var);

void string_valido(char *var);

#endif

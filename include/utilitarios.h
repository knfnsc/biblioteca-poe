#ifndef UTILITARIOS_H
#define UTILITARIOS_H

// objetivo: padronizar a escrita dentro dos arquivos, facilitando leitura e
// pesquisa
void tratar_string(char *string);

// objetivo: evitar problemas quando houver múltiplos tipos de entrada de texto
// para o usuário, evitando conflitos com fgets e scanf, por exemplo
void limpar_buffer();

// objetivo: tornar a interface de interação com o usuário mais dinâmica e limpa
void limpar_tela();

// objetivo: garantir que os valores passados pelo usuário sejam os adequados
// para executar as funções dentro do programa + evitar problemas de buffer
int inteiro_valido();
char char_valido();

#endif

#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "usuarios.h"
#include "emprestimos.h"
#include "livros.h"
#include <stdio.h>

//define qual biblioteca vai acessar para criar pastas em arquivos.c

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

//main > usuarios - livros - emprestimos > arquivos > util

/*
 * 1) Existe uma hierarquia entre as funções, ou seja, elas foram pensadas para serem executadas dentro do terminal de usuários
 * sendo que a função principal é carregar_usuarios, que deve acontecer antes de todas as funções dessa biblioteca
 * 2) As funções alterar_arquivo e relatorio_txt também são dependentes, ficando logo abaixo de carregar_usuarios
 * 3) As demais funções estão num mesmo patamar hierárquico
 *
*/

//declara de antemão o nome da pasta conde ficarão savos os arquivos referentes aos usuários
// o mesmo vale para os ponteiros dos arquivos txt, bin e temporário que serão utilizados na execução do programa

extern const char *biblioteca;
extern FILE *usuariost;
extern FILE *usuariosb;
extern FILE *temp;
extern FILE *emprestimost;
extern FILE *emprestimosb;
extern FILE *livrost;
extern FILE *livrosb;

//Por que são extern?
//Declarar que existe esse ponteiro, mas que ele só será inicializado em outro arquivo -> são de "atribuição externa"


Livro *carregar_livros();
Emprestimo *carregar_emprestimos();

//objetivo: ler os dados dos usuários já cadastrados e retornar a struct correspondente aos usuários lidos; também cria a pasta da Biblioteca se ela ainda não existir
Usuario *carregar_usuarios(Usuario *usuario, int *capacidade, int *total_usuarios);

//objetivo: permitir que os arquivos referentes aos dados dos usuários sejam alterados durante a execução do programa
//está conectado com a função relatoriotxt_usuarios -> a diferença é que a função atual altera os dados dentro do arquivo binário, para então alterar os arquivos de texto
//por que separar essas funções?
//Os arquivos em binário são mais fáceis e mais rápidos de serem lidos durante o programa, mas possuem a desvantagem de não serem compreensíveis para o usuário do programa.
//Para resolver isso, usamos o arquivo bin para as tarefas gerais do programa e, somente para gerar os relatórios de texto, usamos funções como fscanf e fprintf, otimizando a execução do programa
void alterar_arquivo_usuarios(int *total_usuarios, Usuario *usuario);

//objetivo: criar os arquivos de texto referentes aos dados dos usuários, tornando os dados antes guardados apenas em binário algo
//compreensível para o usuário
void relatoriotxt_usuarios(int *total_usuarios, Usuario *usuario);

//É necessário que os parâmetros das funções sejam ponteiros, já que, à medida que o programa é executado, novos usuários podem ser cadastrados ou deletados. Usar os ponteiros permite acessar diretamente
//os valores guardado nesses endereços -> se usar apenas um int e Usuario, estaríamos considerando uma situação estática, o que não é o caso

#endif

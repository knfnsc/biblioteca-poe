#ifndef USUARIOS_H
#define USUARIOS_H

#define LIMITE_INICIAL 10000 //definimos como uma variável de pré-processamente LIMITE = 10000 -> isso significa, que antes da execução do programa, esse valor já está definido;
//faz uma previsão de quantos usuários o sistema da biblioteca suporta

//biblioteca headers/cabeçalho para as funções e variáveis próprias dos usuários

//struct com os dados necessários dos usuários -> usa typedef para tornar a estrutura mais "limpa" visualmente quando for preciso acessar esses dados
typedef struct {
 int matricula;
 char nome[100];
 char curso[100];
 int qtd_emprestimos_ativos;
}Usuario;

//objetivo: adicionar usuários, preservando os dados dos demais. Ao final, salvar as alterações nos arquivos,
// atulizar o ponteiro de struct usuario e o valor em *total_usuarios, bem como a *capacidade
Usuario * cadastrar_usuarios(Usuario *usuario, int *capacidade, int *total_usuarios);

//objetivo: acessar os dados dos usuários, considerando a inicialização prévia da struct usuario
void buscar_usuarios(int *total_usuarios, Usuario *usuario);

//objetivo: garantindo que os dados de usuariosb já foram lidos, mostra os dados de todos os usuários cadastrados
void listar_usuarios(int *total_usuarios, Usuario *usuario);

//objetivo: alterar os dados de uma certa quantidade de usuários, preservando os dados dos demais usuários.
// Ao final, salvar as alterações nos arquivos, atulizar o ponteiro de struct usuario e o valor em *total_usuarios
void atualizar_usuarios(int *total_usuarios, Usuario *usuario);

//objetivo: remover uma certa quantidade de usuários somente se não tiver empréstimos ativos, preservando os dados dos demais usuários.
// Ao final, salvar as alterações nos arquivos, atulizar o ponteiro de struct usuario e o valor em *total_usuarios
Usuario * remover_usuarios(int *total_usuarios, Usuario *usuario);

//objetivo: verificar quantos e quais livros um usuário pegou

void emprestimos_usuarios(int *total_usuarios, int *total_emprestimos, int *total_livros, Usuario *usuario, Emprestimo *emprestimo, Livro *livro)

/*
 * 1 - Usamos ponteiros apenas para o cadastro e a remoção, situações em que o tamanho/total de bytes da struct usuarios pode ser alterada, retornando o endereço da nova struct
   2 - Para as demais funções: busca, atualização e listagem, o retorno void é suficiente, já que não há alteração no tamanho da struct, apenas leitura dos dados numa struct de tamanho já fixado.
No caso específico da atualização dos usuários, os dados são alterados diretamente manipulando os arquivos*/

#endif

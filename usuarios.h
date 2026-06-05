#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct {
 int matricula;
 char nome[100];
 char curso[100];
 int qtd_emprestimos_ativos;
}Usuario;

Usuario * acessar_struct_usuarios();
int * acessar_total_usuarios();
void carregar_usuario();
void salvar_usuario();
void cadastrar_usuario();
void buscar_usuario();
void listar_usuario();
void atualizar_usuario();
void remover_usuario();
void emprestimo_usuario();


#endif

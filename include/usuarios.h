#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct {
  unsigned long long matricula;
  char nome[256];
  char curso[256];
  unsigned short qtd_emprestimos_ativos;
} Usuario;

void carregar_usuarios();
void salvar_usuarios();
void cadastrar_usuario();
void buscar_usuario_matricula();
void buscar_usuario_nome();
void listar_usuarios();
void atualizar_usuario();
void remover_usuario();
void emprestimos_usuario();

Usuario *usuarios_();
unsigned long long *qtd_usuarios_();

#endif

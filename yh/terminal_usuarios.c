#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arquivos.h"
#include "usuarios.h"
#include "util.h"

Usuario * alocar_usuarios(){
    Usuario *usuario = calloc(LIMITE_INICIAL, sizeof(Usuario));

    if(usuario == NULL){
        printf("Falha no sistema.\n");
        exit(1);
    }

    return usuario;
};

//gcc util.c arquivos.c usuarios.c terminal_usuarios.c -o programa
// .\programa.exe

void main(void){

Usuario *u = alocar_usuarios();
int total_usuarios = 0;
int opcao;
int capacidade = LIMITE_INICIAL;
u = carregar_usuarios(u, &capacidade, &total_usuarios);

srand(time(NULL)); //usa srand para inicializar rand dentro da função de cadastro dos usuários, evitando que sejam geradas sequências matrículas repetidas
//captando o momento atual


    while(1){

    printf("\n-------------- BANCO DE DADOS DOS USUÁRIOS --------------\n");
       printf("      Cadastrar usuário                     [1]\n");
       printf("      Buscar usuário                        [2]\n");
       printf("      Listar usuário                        [3]\n");
       printf("      Atualizar usuário                     [4]\n");
       printf("      Remover usuário                       [5]\n");
       printf("      Empréstimos do usuário                [6]\n");
       printf("      Voltar                                [7]\n");
       printf("      Sair                                  [8]\n");
       printf("Digite sua opção: ");
       opcao = inteiro_valido();

    switch(opcao){
    case 1: {
        u = cadastrar_usuarios(u, &capacidade, &total_usuarios);
        break;}
    case 2: {
        buscar_usuarios(&total_usuarios, u);
        break;}
    case 3: {
        listar_usuarios(&total_usuarios, u);
        break;}
    case 4: {
       atualizar_usuarios(&total_usuarios,u);
       break;}
    case 5: {
        u = remover_usuarios(&total_usuarios, u);
        break;}
    case 6: {
        emprestimos_usuarios(&total_usuarios, u);
    }
    case 7: return;
    case 8: free(u); return;
    default: printf("Operação inválida. Tente novamente.\n"); break;
    }
}

return;

}

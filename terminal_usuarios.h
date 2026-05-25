#ifndef TERMINAL_USUARIOS
#define TERMINAL_USUARIOS
#include "funcoes_usuarios.h"

    void terminal_usuarios(Usuario *usuario){

    while(1){

    Usuario *u = usuario;
    int opcao;

    printf("\n-------------- BANCO DE DADOS DOS USUÁRIOS --------------\n");
    printf("      Cadastrar usuário                     [1]\n");
    printf("      Buscar usuário                        [2]\n");
    printf("      Listar usuário                        [3]\n");
    printf("      Atualizar usuásrio                    [4]\n");
    printf("      Remover usuário                       [5]\n");
    printf("      Emprestimos do usuário                [6]\n");
    printf("      Sair                                   [7]\n");
    printf("Digite sua opção: ");
    scanf("%d", &opcao);
    getchar();

    int total_usuarios = carregar_usuarios(u);

    switch(opcao){
    case 1: {
        cadastrar_usuarios(&total_usuarios, u);
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
        remover_usuarios(&total_usuarios, u);
        break;}
    //case 6: carregar_usuarios();emprestimo_usuarios(carregar_usuarios(u), u);break;
    case 7: free(u); return;
    default: printf("Operação inválida. Tente novamente.\n"); break;
    }


}

};

#endif

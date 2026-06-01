#include <stdio.h>
#include <stdlib.h>
#include "livros.h"

int main() {

    int opcao;

    carregarLivros();

    do {

        printf("\n===== MENU LIVROS =====\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar livros\n");
        printf("3 - Buscar por codigo\n");
        printf("4 - Buscar por titulo\n");
        printf("5 - Atualizar livro\n");
        printf("6 - Remover livro\n");
        printf("0 - Sair\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                cadastrarLivro();
                break;

            case 2:
                listarLivros();
                break;

            case 3:
                buscarLivroCodigo();
                break;

            case 4:
                buscarLivroTitulo();
                break;

            case 5:
                atualizarLivro();
                break;

            case 6:
                removerLivro();
                break;

            case 0:
                salvarLivros();
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(opcao != 0);

    free(livros);

    return 0;
}
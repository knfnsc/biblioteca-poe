#include "../include/usuarios.h"
#include "../include/utilitarios.h"
#include <stdlib.h>
#include <string.h>

int total_usuarios;
Usuario *usuarios;

Usuario * acessar_struct_usuarios(){
    return usuarios;
}

int * acessar_total_usuarios(){
    return *total_usuarios;
}

void carregar_usuarios(){

    FILE *arquivo_usuarios = fopen("usuarios.dat", "rb");

    if(arquivo_usuarios == NULL)
        return;

    fread(&total_usuarios, sizeof(int), 1, arquivo_usuarios);
    usuarios = malloc(total_usuarios*sizeof(usuarios));
    fread(usuarios, sizeof(Usuario), total_usuarios, arquivo_usuarios);
    fclose(arquivo_usuarios);
}

void salvar_usuarios(){
    FILE *arquivo_usuarios = fopen("usuarios.dat", "wb");

    if(arquivo_usuarios == NULL)
        return;

    fwrite(&total_usuarios, sizeof(int), 1, arquivo_usuarios);
    fwrite(usuarios, sizeof(Usuario), total_usuarios, arquivo_usuarios);
    fclose(arquivo_usuarios);
}

void cadastrar_usuarios(){

    Usuario novo_usuario;
    int maiorMatricula = 0;

    for(int i = 0; i < total_usuarios; i++){
        if(usuarios[i].matricula > maiorMatricula){
            maiorMatricula = usuarios[i].matricula;
        }
    }

    novo_usuario.matricula = maiorMatricula + 1;

    printf("Nome do usuário:\n");
    fgets(novo_usuario.nome, sizeof(novo_usuario.nome), stdin);
    tratar_string(novo_usuario.nome);

    printf("Curso do usuário:\n\n");
    fgets(novo_usuario.curso, sizeof(novo_usuario.curso), stdin);
    tratar_string(novo_usuario.curso);

    usuarios = realloc(usuario, (total_usuarios+1)*sizeof(Usuario));
    usuarios[total_usarios] = novo_usuario;
    total_usuarios++;

    salvar_usuarios();
    printf("Novo usuário cadastrado.\n");
}

void buscar_usuarios_matricula(){

    if(total_usuarios == 0){
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    int encontrado = 0;
    printf("Inserir matrícula do usuario:\n");
    int matricula = inteiro_valido();

    for(int i = 0; i < total_usuarios; i++){
        if(usuarios[i].matricula == matricula){//comparar a matrícula digitada pelo usuário com as matrículas salvas na struct usuario
            encontrado = 1;
            printf("Matrícula: %d\n", usuarios[i].matricula);
            printf("Nome: %s\n", usuarios[i].nome);
            printf("Curso: %s\n", usuarios[i].curso);
            break; //interrompe o laço assim que encontra o usuário
        }
    }

        if(!encontrado)
            printf("Usuário não encontrado.\n");
}

void buscar_usuarios_nome(){
    int encontrado = 0;

    char nome[100];
    printf("Inserir nome completo do usuário:\n");
    fgets(nome, sizeof(nome), stdin);
    tratar_string(nome); //serve para padronizar a entrada do usuário com o padrão de escrita nos arquivos, facilitando a buscar_usuarios

    for(int i = 0; i < total_usuarios; i++){
        if(strcmp(nome, usuarios[i].nome) == 0){//comparar o nome digitado pelo usuario com os nomes salvos na struct usuario
            encontrado = 1;
            printf("Matrícula: %d\n", usuarios[i].matricula);
            printf("Nome: %s\n", usuarios[i].nome);
            printf("Curso: %s\n", usuarios[i].curso);
            break; //interrompe o laço assim que encontra o usuário
        }
    }

        if(!encontrado)//informa mensagem de erro antes de solicitar novamente o nome, caso não tenha sido encontrado
            printf("Usuário não encontrado.\n");
}

void atualizar_usuarios(){
    int encontrado = 0;
    printf("Matrícula do usuário:\n");
    matricula = inteiro_valido();

    for(int i = 0; i < total_usuarios; i++){//laço relacionado com a busca dentro da struct usuarios
        if(usuarios[i].matricula == matricula){//comparar a matrícula digitada pelo usuario com as matrículas salvas na struct usuario
            encontrado = 1;
            printf("Novo nome:\n");
            fgets(usuarios[i].nome, sizeof(usuarios[i].nome), stdin);
            tratar_string(usuario[i].nome);

            printf("Novo curso:\n");
            fgets(usuarios[i].curso, sizeof(usuarios[i].curso), stdin);
            tratar_string(usuarios[i].curso);

            salvar_usuarios();
            printf("Usuário atualizado.\n");
            break; //interrompe o laço assim que encontra o usuário após os comandos acima
        }
    }

    if(!encontrado)//se encontrado == 0 (falso)
        printf("Usuário não encontrado.\n");  //Verifica se o usuário deseja continuar tentando; se ele não quiser, ele sai da função
}

void listar_usuarios(){
    if(total_usuarios == 0){//considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    printf("---------------------------USUÁRIOS---------------------------\n");

    for(int i = 0; i < total_usuarios; i++){
        printf("Matrícula: %d\nNome: %s\nCurso: %s\nEmpréstimos ativos: %d\n\n", usuarios[i].matricula, usuarios[i].nome, usuarios[i].curso, usuarios[i].qtd_emprestimos_ativos);
        printf("---------------------------\n");
    }

}

void remover_usuarios(){

    if(total_usuarios == 0){
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    int matricula, encontrado = 0;
    printf("Inserir matrícula do usuário:\n");
    matricula = inteiro_valido();

    for(int i = 0; i < total_usuarios; i++){
        if(usuarios[i].matricula == matricula){

            encontrado = 1;

            for(int j = 0; j < total_usuarios-1; j++){
                usuarios[j] = usuarios[j+1];
            }

            total_usuarios--;

            usuarios = realloc(usuarios, total_usuarios*sizeof(Usuario));
            salvar_usuarios();
            printf("Usuário removido.\n");
            break;
        }
    }

    if(!encontrado)
        printf("Usuário não encontrado.\n");

}

void emprestimos_usuarios(){

    if(total_usuarios == 0){
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    struct Emprestimo *emprestimos = acessar_struct_emprestimos();
    struct Livro *livros = acessar_struct_livros();
    int *total_emprestimos = acesssar_total_emprestimos();
    int *total_livros = acessar_total_livros();

    int matricula, encontrado = 0;
     printf("Inserir matrícula do usuário:\n");
     matricula = inteiro_valido();

     for(int i = 0; i < total_usuarios; i++){
         if(usuarios[i].matricula == matricula){
             encontrado = 1;

             if(usuarios[i].qtd_emprestimos_ativos == 0){
                 printf("Usuário sem empréstimos ativos.\n");
                 return;
             }

             printf("Empréstimos ativos: %d.\n", usuarios[i].qtd_emprestimos_ativos);

             printf("Livros emprestados:\n");
             for(int j = 0; j < *total_emprestimos; j++){
                 if(usuarios[i].matricula == emprestimos[j].matricula){
                     for(int k = 0; k < *total_livros; k++){
                         if(emprestimos[j].codigo == livros[k].codigo){
                             printf("Livro: %s\n", livros[k].titulo);
                             printf("Código: %d\n", livros[k].codigo);
                             printf("---------------------------\n");
                         }
                     }
                 }
             }
             break;
         }
     }

     if(!encontrado){
         printf("Usuário não encontrado.\n");
         return;
     }
}

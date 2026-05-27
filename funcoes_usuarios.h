#ifndef FUNCOES_USUARIOS
#define FUNCOES_USUARIOS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <direct.h>
#define LIMITE 1000
//corrigir para ser valido para linux tbm

//bin

void tratar_string(char *str){

    str[strcspn(str, "\n")] = '\0';

    int tam = strlen(str);
    int p_nova = 1;

    for(int i = 0; i < tam; i++){

        if(str[i] == ' '){
            p_nova = 1;
        }else if(p_nova){
            p_nova = 0;
            str[i] = toupper(str[i]);
        }else{
            p_nova = 0;
            str[i] = tolower(str[i]);
        }
    }

    const char *prep[] = {"De", "Da", "Do", "Dos", "Das", "E"};
    int qtd = sizeof(prep)/sizeof(prep[0]);

    char copia[200] = "";

    char *palavra = strtok(str, " ");

    while(palavra){

        for(int i = 0; i < qtd; i++){

             if(strcmp(palavra, prep[i]) == 0){
                 palavra[0] = tolower(palavra[0]);

             }
        }

        strcat(copia, palavra);
        strcat(copia, " ");
        palavra = strtok(NULL, " ");
    }

    copia[strlen(copia)-1] = '\0';

    strcpy(str, copia);

};

typedef struct {

int matricula;
char nome[100];
char curso[100];
int qtd_emprestimos_ativos;

}Usuario;

int total_usuarios = 0;

const char *pasta_usuarios = "Usuarios";
FILE *lista_usuariosb, *lista_usuariost, *temp;

/*
FILE *emprestimos_usuarios;
emprestimo_usuario();
*/

int carregar_usuarios(Usuario *usuario){

    if(_mkdir(pasta_usuarios) == 0){
            printf("Pasta de Usuários criada com sucesso!\n");
    }

    lista_usuariosb = fopen("Usuarios\\Lista_Usuarios.dat", "rb");

    if(lista_usuariosb == 0){

        printf("Criando o arquivo...\n");
        FILE *temp  = fopen("Usuarios\\Lista_Usuarios.dat", "wb");

        if(temp == 0){
            printf("Falha na criação do arquivo.\n");
            exit(1);
        }

        fclose(temp);
        lista_usuariosb = fopen("Usuarios\\Lista_Usuarios.dat", "rb");
    }

    int i = 0;
    while(fread(&usuario[i], sizeof(Usuario), 1, lista_usuariosb) == 1){
        i++;
    }

    fclose(lista_usuariosb);

    return i;

};

void relatoriotxt(int *total_usuarios, Usuario *usuario){

    temp = fopen("temporario.txt", "w");

    if(temp == NULL){
        printf("Falha na criação do arquivo.\n");
        exit(1);
    }

    fprintf(temp, "------------------ USUÁRIOS ------------------\n\n");
    for(int i = 0; i < *total_usuarios; i++){
        fprintf(temp, "Matrícula: %d\n", usuario[i].matricula);
        fprintf(temp, "Nome: %s\n", usuario[i].nome);
        fprintf(temp, "Curso: %s\n\n", usuario[i].curso);
    }

    fclose(temp);

    remove("Usuarios\\Lista_Usuarios.txt");
    rename("temporario.txt", "Usuarios\\Lista_Usuarios.txt");

};

void alterar_arquivo(int *total_usuarios, Usuario *usuario){

    temp = fopen("temporario.dat", "wb");

    if(temp == 0){
        printf("Falha na alteração do arquivo.\n");
        exit(1);
    }

    for(int i = 0; i < *total_usuarios-1; i++){
        for(int j = 0; j < *total_usuarios-i-1; j++){
            if(strcmp(usuario[j].nome, usuario[j+1].nome) > 0){
                Usuario temp = usuario[j];
                usuario[j] = usuario[j+1];
                usuario[j+1] = temp;
            }
        }
    }

        fwrite(usuario, sizeof(Usuario), *total_usuarios, temp);
        fclose(temp);

        remove("Usuarios\\Lista_Usuarios.dat");
        rename("temporario.dat", "Usuarios\\Lista_Usuarios.dat");

        relatoriotxt(total_usuarios, usuario);

    };


Usuario * cadastrar_usuarios(int *total_usuarios, Usuario *usuario){
    int limite = LIMITE;
    //criar temp evita perder os usuarios antigos se houver falha
    if(*total_usuarios >= limite){
        limite *= 2;
        Usuario *temp = realloc(usuario, limite*sizeof(Usuario));

        if(temp == NULL){
            printf("Falha na operação.\n");
            exit(1);
        }

        usuario = temp;
    }



    int qtd;
    printf("Quantidade de usuários a cadastrar:\n");
    scanf("%d", &qtd);
    getchar();

    for(int i = 0; i < qtd; i++){
    Usuario novo_usuario;
    printf("Nome do novo usuário:\n");
    fgets(novo_usuario.nome, sizeof(novo_usuario.nome), stdin);
    tratar_string(novo_usuario.nome);

    printf("Curso do novo usuário:\n");
    fgets(novo_usuario.curso, sizeof(novo_usuario.curso), stdin);
    tratar_string(novo_usuario.curso);

    int repetido = 0;

    //enquanto o numero sorteado for igual a um ja sorteado antes, ele sorteia um novo ate
    // ele ser diferente
    do{
        repetido = 0;
        novo_usuario.matricula = (rand()%10000)+1;
        for(int i = 0; i < *total_usuarios; i++){
            if(novo_usuario.matricula == usuario[i].matricula){
                repetido = 1;
                break;
            }
        }

    }while(repetido);

    printf("Matrícula do usuário: %d\n\n", novo_usuario.matricula);//adiciona o novo usuario a lista de usuarios ja cadastrado
    usuario[(*total_usuarios)++] = novo_usuario;

    }

    printf("Cadastro bem-sucedido!\n");
    alterar_arquivo(total_usuarios, usuario);

    return usuario;

};

Usuario * buscar_usuarios(int *total_usuarios, Usuario *usuario){

    if(*total_usuarios == 0){
        printf("Nenhum usuário cadastrado.\n");
        return NULL;
    }

  int escolha, encontrado = 0;

  printf("Buscar matrícula (1) ou nome (2)?\n");
  scanf("%d", &escolha);
  getchar();

  switch(escolha){

    case 1:{

        int matricula;
        printf("Inserir matrícula do usuario:\n");
        scanf("%d", &matricula);
        getchar();

        for(int i = 0; i < *total_usuarios; i++){

        if(usuario[i].matricula == matricula){
            encontrado = 1;
            printf("Matrícula: %d\n", usuario[i].matricula);
            printf("Nome: %s\n", usuario[i].nome);
            printf("Curso: %s\n", usuario[i].curso);
            break;}
        }

        if(!encontrado){
            printf("Usuário não encontrado.\n");}
        break;
    }

    case 2:{

        char nome[100];
        printf("Inserir nome do usuário:\n");
        fgets(nome, sizeof(nome), stdin);
        tratar_string(nome);

        for(int i = 0; i < *total_usuarios; i++){

            if(strcmp(nome, usuario[i].nome) == 0){
                encontrado = 1;
                printf("Matrícula: %d\n", usuario[i].matricula);
                printf("Nome: %s\n", usuario[i].nome);
                printf("Curso: %s\n", usuario[i].curso);
                break;}
        }

        if(!encontrado){
            printf("Usuário não encontrado.\n");}
        break;
    }

    default: printf("Comando inválido. Tente novamente.\n"); break;

  }

  return usuario;

};

Usuario * listar_usuarios(int *total_usuarios, Usuario *usuario){

    if(*total_usuarios == 0){
        printf("Nenhum usuário cadastrado.\n");
        return NULL;
    }

    printf("------------------ USUÁRIOS ------------------\n\n");
    for(int i = 0; i < *total_usuarios; i++){
        printf("Matricula: %d\nNome: %s\nCurso: %s\n\n", usuario[i].matricula, usuario[i].nome, usuario[i].curso);
    }

    return usuario;
};

Usuario * atualizar_usuarios(int *total_usuarios, Usuario *usuario){

    if(*total_usuarios == 0){
        printf("Nenhum usuário cadastrado.\n");
        return NULL;
    }

    int qtd, escolha;
    printf("Quantidade de usuários a atualizar:\n");
    scanf("%d", &qtd);

    printf("Buscar matricula (1) ou nome (2)?\n");
    scanf("%d", &escolha);
    getchar();

    switch(escolha){

        case 1:{
                int matricula;


                for(int j = 0; j < qtd; j++){
                    printf("Matrícula do usuário:\n");
                    scanf("%d", &matricula);
                    getchar();

                    int encontrado = 0;

                    for(int i = 0; i < *total_usuarios; i++){

                        if(usuario[i].matricula == matricula){
                            encontrado = 1;
                            printf("Novo nome:\n");
                            fgets(usuario[i].nome, sizeof(usuario[i].nome), stdin);
                            tratar_string(usuario[i].nome);
                            printf("Novo curso:\n");
                            fgets(usuario[i].curso, sizeof(usuario[i].curso), stdin);
                            tratar_string(usuario[i].curso);
                            break;
                        }

                    }

                    if(!encontrado){
                    printf("Usuário não encontrado.\n");}

                }

             alterar_arquivo(total_usuarios, usuario);
             printf("Atualização bem-sucedida!\n");
             break;

        }

        case 2:{

            for(int j = 0; j < qtd; j++){
                int encontrado = 0;
                char nome[100];
                printf("Nome do usuário:\n");
                fgets(nome, sizeof(nome), stdin);
                tratar_string(nome);

                    for(int i = 0; i < *total_usuarios; i++){
                        if(strcmp(nome, usuario[i].nome) == 0){
                            encontrado = 1;
                            printf("Novo nome:\n");
                            fgets(usuario[i].nome, sizeof(usuario[i].nome), stdin);
                            tratar_string(usuario[i].nome);
                            printf("Novo curso:\n");
                            fgets(usuario[i].curso, sizeof(usuario[i].curso), stdin);
                            tratar_string(usuario[i].curso);
                            break;
                        }
                    }

                    if(!encontrado){
                        printf("Usuário não encontrado.\n");}

            }

            alterar_arquivo(total_usuarios, usuario);
            printf("Atualização bem-sucedida!\n");
            break;
        }

        default: printf("Comando inválido. Tente novamente.\n"); break;

    }

    return usuario;
};


Usuario * remover_usuarios(int *total_usuarios, Usuario *usuario){

    int total;
    if(*total_usuarios == 0){
        printf("Nenhum usuário cadastrado.\n");
        return NULL;
    }

    total = *total_usuarios;

    int escolha, qtd;

    printf("Quantidade de usuários a remover:\n");
    scanf("%d", &qtd);

    printf("Buscar matrícula (1) ou nome (2)?\n");
    scanf("%d", &escolha);
    getchar();

    switch(escolha){

        case 1:{

            for(int j = 0; j < qtd; j++){
                int encontrado = 0;
                int matricula;
                printf("Inserir matrícula do usuário:\n");
                scanf("%d", &matricula);
                getchar();

                for(int i = 0; i < *total_usuarios; i++){

                    if(matricula == usuario[i].matricula){
                        encontrado = 1;

                        for(int k = i; k < (*total_usuarios)-1; k++){ //reorganiza os funcionarios sem deixar buracos no vetor
                                    usuario[k] = usuario[k+1];
                            }

                        (*total_usuarios)--;
                        i--;
                         printf("Remoção de usuário bem-sucedida!\n");
                    }

                }

                if(!encontrado){
                 printf("Usuário nao encontrado.\n");
                }

            }

            Usuario *temp = realloc(usuario, *total_usuarios*sizeof(Usuario));
            if(temp == NULL){
                printf("Falha na operação.\n");
                exit(1);}

            usuario = temp;

            alterar_arquivo(total_usuarios, usuario);
            break;

        }

        case 2: {

            for(int j = 0; j < qtd; j++){
                int encontrado = 0;
                char nome[100];
                printf("Inserir nome do usuário:\n");
                fgets(nome, sizeof(nome), stdin);
                tratar_string(nome);

                for(int i = 0; i < *total_usuarios; i++){

                    if(strcmp(nome, usuario[i].nome) == 0){
                        encontrado = 1;

                        for(int k = i; k < (*total_usuarios)-1; k++){ //reorganiza os funcionarios sem deixar buracos no vetor
                            usuario[k] = usuario[k+1];
                        }

                        (*total_usuarios)--;
                        i--;
                        printf("Remoção de usuário bem-sucedida!\n");
                    }


                }

                if(!encontrado){
                    printf("Usuário não encontrado.\n");}

            }

            Usuario *temp = realloc(usuario, *total_usuarios*sizeof(Usuario));

            if(temp ==  NULL && *total_usuarios > 0){
                printf("Falha na operação.\n");
                exit(1);}

            usuario = temp;

            alterar_arquivo(total_usuarios, usuario);
            break;

        }

        default: printf("Comando inválido. Tente novamente.\n"); break;

    }

    return usuario;

};

#endif

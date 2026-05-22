#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#usuario


/*
 * - livros emprestados
 */

void tratar_strings(char *string){

    string[strcspn(string, "\n")] = '\0';
    int tam = strlen(string);
    int p_nova = 1;

    for(int i = 0; i < tam; i++){

        if(string[i] == ' '){
            p_nova = 1;
        }else if(p_nova){
            p_nova = 0;
            string[i] = toupper(string[i]);
        }else{
            p_nova = 0;
            string[i] = tolower(string[i]);
        }
    }

};

struct Usuario{

char nome[100];
char curso[100];
int matricula;

};

struct Usuario *usuario = calloc(100, sizeof(struct Usuario));
int total_usuarios = 0;
int limite = 100;

//1
void cadastrar_usuarios(){

    //criar temp evita perder os usuarios antigos se houver falha
    if(total_usuarios >= limite){
        limite *= 2;
        struct Usuario *temp = realloc(usuario, limite*sizeof(struct Usuario));

        if(temp == NULL){
            printf("Falha na operacao.\n");
            return;
        }

        usuario = temp;
    }

    struct Usuario novo_usuario;

    printf("Nome do novo usuario:\n");
    fgets(novo_usuario.nome, sizeof(novo_usuario.nome), stdin);
    tratar_strings(novo_usuario.nome);

    printf("Curso do novo usuario:\n");
    fgets(novo_usuario.curso, sizeof(novo_usuario.curso), stdin);
    tratar_strings(novo_usuario.curso);

    int repetido;

    //enquanto o numero sorteado for igual a um ja sorteado antes, ele sorteia um novo ate
    // ele ser diferente
    do{
        repetido = 0;
        novo_usuario.matricula = (rand()%10000)+1;
        for(int i = 0; i < total_usuarios; i++){
            if(novo_usuario.matricula == usuario[i].matricula){
                repetido = 1;
                break;
            }
        }

    }while(repetido);

    printf("Matricula do usuario: %d\n", novo_usuario.matricula);
     usuario[total_usuarios++] = novo_usuario;//adiciona o novo usuario a lista de usuarios ja cadastrados
    printf("Usuario cadastrado com sucesso!\n");

};

//2
void buscar_usuarios(){

    int escolha, encontrado = 0;

    printf("Buscar matricula (1) ou nome (2)?\n");
    scanf("%d", &escolha);
    getchar();

    switch(escolha){

        case 1:{

            int matricula;
            printf("Inserir matricula do usuario:\n");
            scanf("%d", &matricula);
            getchar();

            for(int i = 0; i < total_usuarios; i++){
                if(usuario[i].matricula == matricula){
                    encontrado = 1;
                    printf("Matricula: %d\n", usuario[i].matricula);
                    printf("Nome: %s\n", usuario[i].nome);
                    printf("Curso: %s\n", usuario[i].curso);
                    break;
                }
            }

            if(!encontrado){
                printf("Usuario nao encontrado.\n");
            }
            break;
        }

        case 2:{

            char nome[100];
            printf("Inserir nome do usuario:\n");
            fgets(nome, sizeof(nome), stdin);
            tratar_strings(nome);

            for(int i = 0; i < total_usuarios; i++){
                if(strcmp(nome, usuario[i].nome) == 0){
                    encontrado = 1;
                    printf("Matricula: %d\n", usuario[i].matricula);
                    printf("Nome: %s\n", usuario[i].nome);
                    printf("Curso: %s\n", usuario[i].curso);
                    break;
                }
            }

            if(!encontrado){
                printf("Usuario nao encontrado.\n");
            }
            break;
        }
        default: printf("Comando invalido. Tente novamente.\n"); break;
    }

};

//3
void listar_usuarios(){

    if(total_usuarios == 0){
        printf("Nenhum usuario cadastrado.\n");
        return;
    }

    for(int i = 0; i < total_usuarios-1; i++){
        for(int j = 0; j < total_usuarios-i-1; j++){
            if(strcmp(usuario[j].nome, usuario[j+1].nome) > 0){
                struct Usuario temp = usuario[j];
                usuario[j] = usuario[j+1];
                usuario[j+1] = usuario[j];
            }
        }
    }

    printf("---------Lista de usuarios---------\n\n");
    for(int i = 0; i < total_usuarios; i++){
        printf("Matricula: %d\nNome: %s\nCurso: %s\n\n", usuario[i].matricula, usuario[i].nome, usuario[i].curso);
    }

};

//4
void atualizar_usuarios(){

    int escolha, encontrado = 0;

    printf("Buscar matricula (1) ou nome (2)?\n");
    scanf("%d", &escolha);
    getchar();

    switch(escolha){
        case 1:{

            int matricula;
            printf("Matricula do usuario:\n");
            scanf("%d", &matricula);
            getchar();

            for(int i = 0; i < total_usuarios; i++){
                if(usuario[i].matricula == matricula){
                    encontrado = 1;
                    printf("Novo nome:\n");
                    fgets(usuario[i].nome, sizeof(usuario[i].nome), stdin);
                    tratar_strings(usuario[i].nome);
                    printf("Novo curso:\n");
                    fgets(usuario[i].curso, sizeof(usuario[i].curso), stdin);
                    tratar_strings(usuario[i].curso);
                    break;
                }
            }

            if(!encontrado){
                printf("Usuario nao encontrado.\n");
            }
            break;
        }

        case 2:{
            char nome[100];
            printf("Nome do usuario:\n");
            fgets(nome, sizeof(nome), stdin);
            tratar_strings(nome);

            for(int i = 0; i < total_usuarios; i++){
                if(strcmp(nome, usuario[i].nome) == 0){
                    encontrado = 1;
                    printf("Novo nome:\n");
                   fgets(usuario[i].nome, sizeof(usuario[i].nome), stdin);
                   tratar_strings(usuario[i].nome);
                    printf("Novo curso:\n");
                    fgets(usuario[i].curso, sizeof(usuario[i].curso), stdin);
                    tratar_strings(usuario[i].curso);
                    break;
                }
            }

            if(!encontrado){
                printf("Usuario nao encontrado.\n");
            }
            break;
        }
        default: printf("Comando invalido. Tente novamente.\n"); break;

    }
};

//5
void remover_usuarios(){

    if(total_usuarios == 0){
        printf("Nao ha usuarios disponiveis.\n");
        return;
    }

    int escolha, encontrado = 0;

    printf("Buscar matricula (1) ou nome (2)?\n");
    scanf("%d", &escolha);
    getchar();

    switch(escolha){

        case 1:{

            int matricula;
            printf("Inserir matricula do usuario:\n");
            scanf("%d", &matricula);
            getchar();

            for(int i = 0; i < total_usuarios; i++){

                if(matricula == usuario[i].matricula){
                    encontrado = 1;

                    for(int j = i; j < total_usuarios-1; j++){ //reorganiza os funcionarios sem deixar buracos no vetor
                        usuario[j] = usuario[j+1];
                    }

                    total_usuarios--;

                    struct Usuario *temp = realloc(usuario, total_usuarios*sizeof(struct Usuario));

                    if(temp == NULL){
                        printf("Falha na operacao.\n");
                        return;
                    }

                    usuario = temp;

                    printf("Usuario removido com sucesso!\n");
                    break;
                }
            }

            if(!encontrado){
                printf("Usuario nao encontrado.\n");
            }
            break;
        }

        case 2: {

        char nome[100];
        printf("Inserir nome do usuario:\n");
        fgets(nome, sizeof(nome), stdin);
        tratar_strings(nome);

        for(int i = 0; i < total_usuarios; i++){

            if(strcmp(nome, usuario[i].nome) == 0){
                encontrado = 1;

                for(int j = i; j < total_usuarios-1; j++){ //reorganiza os funcionarios sem deixar buracos no vetor
                    usuario[j] = usuario[j+1];
                }
                total_usuarios--;
                struct Usuario *temp = realloc(usuario, total_usuarios*sizeof(struct Usuario));

                if(temp ==  NULL){
                    printf("Falha na operacao.\n");
                    return;
                }

                usuario = temp;

                printf("Usuario removido com sucesso!\n");
                break;
            }
        }

        if(!encontrado){
            printf("Usuario nao encontrado.\n");
        }
        break;
        }
        default: printf("Comando invalido. Tente novamente.\n"); break;
    }

};


int main(){

    /*
     *  teste
     *
     * FILE *user = fopen("arquivo.txt", "r");

     void alterando_arquivo(){

         if(user == NULL){
             printf("Arquivo vazio.\n");
             return;
         }

         FILE *teste = fopen("arquivo.txt", "a+b");

         if(teste == NULL){
             printf("Operacao falhou. Tente novamente.\n");
             return;
         }

         user = teste;

     };

     temp = fwrite( usuario,sizeof(struct Usuario),total_usuarios,user);


     */




    printf("\nMenu Banco de Dados de Usuarios:\n");
    printf("1. Cadastrar usuario.\n");
    printf("2. Buscar usuario.\n");
    printf("3. Listar usuario.\n");
    printf("4. Atualizar usuario.\n");
    printf("5. Remover usuario.\n");
    printf("6. Sair.\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);

switch(opcao){
case 1: {
    cadastrar_usuario();

}

break;
case 2: listar_usuario(); break;
case 3: buscar_usuario(); break;
case 4: listar_usuaario(); break;
case 5: atualizar_usuario(); break;
case 6: return; break;
default: printf("Operacao invalida. Tente novamente.\n"); break;
}

return 0;
}

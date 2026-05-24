#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void tratar_strings(char *string){

//entrada dat

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

typedef struct {

int matricula;
char nome[100];
char curso[100];
int qtd_emprestimos_ativos;

}Usuario;

Usuario *usuario = calloc(100, sizeof(Usuario));
int total_usuarios = 0;
int limite = 100;

const char *pasta_usuarios = "C:\\Usuarios";
FILE *lista_usuarios;

/*
FILE *emprestimos_usuarios;
emprestimo_usuario();
*/
FILE *temp;


int carregar_usuarios(){

    if(_mkdir(pasta_usuarios) == 0){
            printf("Pasta criada com sucesso.\n");
    }

    lista_usuarios = fopen("C:\\Usuarios\\Lista_Usuarios.dat", "rb");

    if(lista_usuarios == 0){

        printf("Criando o arquivo...\n");
        lista_usuarios = fopen("C:\\Usuarios\\Lista_Usuarios.dat", "wb");

        if(lista_usuarios == 0){
            printf("Falha na criacao do arquivo.\n");
            exit(1);
        }else{
            printf("Arquivo criado com sucesso.\n");
        }

    int i = 0;
    while(fread(&usuario[i], sizeof(Usuario), 1, lista_usuarios) == 1){
        i++;
    }

    fclose(lista_usuarios);

    return i;

};

    void alterar_arquivo(int total_usuarios){

        temp = fopen("C:\\temporario.txt", "wb");

        if(temp == 0){
            printf("Falha na alteracao do arquivo.\n");
            exit(1);
        }

        for(int i = 0; i < total_usuarios-1; i++){
            for(int j = 0; j < total_usuarios-i-1; j++){
                if(strcmp(usuario[j].nome, usuario[j+1].nome) > 0){
                    Usuario temp = usuario[j];
                    usuario[j] = usuario[j+1];
                    usuario[j+1] = usuario[j];
                }
            }
        }

        fwrite(usuario, sizeof(Usuario), total_usuarios, temp);
        fclose(temp);

        remove("C:\\Usuarios\\Lista_Usuarios.dat");
        rename("C:\\temporario.txt", "C:\\Usuarios\\Lista_Usuarios.dat");

    };



void cadastrar_usuarios(int total_usuarios){
    //criar temp evita perder os usuarios antigos se houver falha
    if(total_usuarios >= limite){
        limite *= 2;
        Usuario *temp = realloc(usuario, limite*sizeof(Usuario));

        if(temp == NULL){
            printf("Falha na operacao.\n");
            exit(1);
        }

        usuario = temp;
    }

    Usuario novo_usuario;

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
    alterar_arquivo(total_usuarios);
    free(usuario);

};

void buscar_usuarios(int total_usuarios){

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
            break;}
        }

        if(!encontrado){
            printf("Usuario nao encontrado.\n");}
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
                printf("Matricula: %d\n", &usuario[i].matricula);
                printf("Nome: %s\n", usuario[i].nome);
                printf("Curso: %s\n", usuario[i].curso);
                break;}
        }

        if(!encontrado){
            printf("Usuario nao encontrado.\n");}
        break;
    }

    default: printf("Comando invalido. Tente novamente.\n"); break;

  }

};

void listar_usuarios(int total_usuarios){

    lista_usuarios = fopen("C:\\Usuarios\\Lista_Usuarios.dat", "r");

    Usuario *temp;

    fread(temp, sizeof(Usuario), total_usuarios, lista_usuarios);

    for(int i = 0; i < total_usuarios; i++){
        printf("Matricula: %d\nNome: %s\nCurso: %s\n\n", temp[i].matricula, temp[i].nome, temp[i].curso);
    }


};


void atualizar_usuarios(int total_usuarios){

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
                    break;}
            }

            if(!encontrado){
                    printf("Usuario nao encontrado.\n");
                     }else{
                         alterar_arquivo(total_usuarios);
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
                    break;}
            }

        if(!encontrado){
            printf("Usuario nao encontrado.\n");
        }else{
            alterar_arquivo(total_usuarios);}

        break;
        }

    default: printf("Comando invalido. Tente novamente.\n"); break;

             }
};


void remover_usuarios(int total_usuarios){

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
                    Usuario *temp = realloc(usuario, total_usuarios*sizeof(Usuario));

                    if(temp == NULL){
                        printf("Falha na operacao.\n");
                        exit(1);}

                    usuario = temp;
                    printf("Usuario removido com sucesso!\n");
                    alterar_arquivo();
                    free(usuario);
                    break;}
            }

            if(!encontrado){
            printf("Usuario nao encontrado.\n");}
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
                        usuario[j] = usuario[j+1];}
                    total_usuarios--;
                    Usuario *temp = realloc(usuario, total_usuarios*sizeof(Usuario));

                    if(temp ==  NULL){
                        printf("Falha na operacao.\n");
                        exit(1);}

                    usuario = temp;

                    printf("Usuario removido com sucesso!\n");
                    alterar_arquivo();
                    free(usuario);
                    break;
                }
            }

            if(!encontrado){
                printf("Usuario nao encontrado.\n");}
            break;
                 }

        default: printf("Comando invalido. Tente novamente.\n"); break;
    }
};


int main(){


    void terminal_usuarios(){
    printf("\nMenu Banco de Dados de Usuarios:\n");
    printf("1. Cadastrar usuario.\n");
    printf("2. Buscar usuario.\n");
    printf("3. Listar usuario.\n");
    printf("4. Atualizar usuario.\n");
    printf("5. Remover usuario.\n");
    printf("6. Emprestimos do usuario\.n");
    printf("7. Sair.\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);

switch(opcao){
case 1: carregar_usuarios();cadastrar_usuario(carregar_usuarios()); break;
case 2: carregar_usuarios();listar_usuario(carregar_usuarios()); break;
case 3: carregar_usuarios();buscar_usuario(carregar_usuarios()); break;
case 4: carregar_usuarios();listar_usuario(carregar_usuarios()); break;
case 5: carregar_usuarios();atualizar_usuario(carregar_usuarios()); break;
case 6: carregar_usuarios();emprestimo_usuario(carregar_usuarios());break;
case 7: return; break;
default: printf("Operacao invalida. Tente novamente.\n"); break;
}

};

return 0;
}

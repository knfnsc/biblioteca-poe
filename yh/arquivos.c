#include "arquivos.h"
#include "usuarios.h"
#include <stdlib.h>

//incializa aqui os extern de arquivos.h
const char *biblioteca = "Biblioteca";
FILE *usuariosb = NULL;
FILE *usuariost = NULL;
FILE *temp = NULL;

Usuario * carregar_usuarios(Usuario *usuario, int *capacidade, int *total_usuarios){ //recebe o endereço da struct de usuarios alocada na main

    #ifdef _WIN32
        if(_mkdir(biblioteca) == 0){//se for Windows
            printf("Pasta de Usuários criada com sucesso!\n");
        }
    #else
        if(mkdir(biblioteca, 0777) == 0){//se for outro sistema operacional
            printf("Pasta de Usuários criada com sucesso!\n");
        }
    #endif

    //cria a pasta para os usuários, adaptando para o sistema operacional e verificar se já existe uma pasta de Usuários, se não houver, cria -> útil ao executar o programa na primeira vez

    usuariosb = fopen("Biblioteca/Usuarios.dat", "rb"); //abre o arquivo bin com os dados dos usuários para leitura

    if(usuariosb == NULL){//verificar se o arquivo já existe; se não existir, ele cria um arquivo do zero e informa ao usuário
        printf("Criando novo arquivo...\n");

        temp = fopen("Biblioteca/Usuarios.dat", "wb");

        if(temp == NULL){//verifica se houve erro na criação do arquivo; se houver, retorna para a tela inicial
            printf("Falha na criação do arquivo.\n");
            exit(1);
        }

        fclose(temp);
        usuariosb = fopen("Biblioteca/Usuarios.dat", "rb");

        //fechar o arquivo temporário e agora acessar esse mesmo arquivo, mas pelo seu "nome oficial"
        //criar o arquivo temporário garante que os dados dos usuários já salvos não serão perdidos
        // abre o arquivo para ler os dados dos usuários
    }

    int i = 0;
    while(1){//enquanto for true (boolean) -> executa indefinidamente

        if(i >= *capacidade){ //verifica se o total de usuários até então lidos supera a capacidade -> se superar, expande a memória para armazenar os usuários que excedem esse limite
            *capacidade *= 2;   //atualiza o valor da capacidade para que ela possa ser acessada por outras funções posteriormente
            Usuario *temp = realloc(usuario, (*capacidade)*sizeof(Usuario)); //usa um ponteiro temporário para verificar se a realoação foi bem-sucedida

            if(temp == NULL){
                printf("Falha ao alocar memória.\n"); //se não for, encerra o programa para não perder o que já foi alocado antes -> como usamos um ponteiro temporário, o ponteiro original de struct usuario é mantido
                fclose(usuariosb);
                exit(1);
            }

            usuario = temp; //se der certo, o ponteiro original de struct usuario recebe temp
        }

        if(fread(&usuario[i], sizeof(Usuario), 1, usuariosb) != 1){
            break;
        }

        i++;}

        //fread aloca em cada endereço da struct usuario os dados dentro do arquivo
        //guarde no endereço de usuario[i], lendo do arquivo usuariosb, cada unidade de tamanho/quantidade de bytes igual ao de struct Usuario, numa quantidade de 1
        //fread retorna a quantidade de espaços lidos -> se retornar 1, ele recebeu a totalidade dos dados de um único usuário, preenchendo cada campo
        // incrementa o contador i para ler os dados do próximo usuário
        // quando não houverem mais dados dentro do arquivo, o retorno do fread será diferente de 1, então o vetor de struct já foi completamente preenchido -> break sai do laço

     *total_usuarios = i; //atualiza o total de usuários para repassar para as próximas funções
     fclose(usuariosb); //sempre fechar o arquivo ao final da operação
     return usuario;
};

void relatoriotxt_usuarios(int *total_usuarios, Usuario *usuario){ //recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários.

    temp = fopen("temporario.txt", "w"); //cria um arquivo temporário e verifica se houve falha; se houver, retorna para a tela inicial

    if(temp == NULL){
        printf("Falha na criação do arquivo.\n");
        exit(1);
    }

    fprintf(temp, "------------------ USUÁRIOS ------------------\n\n"); //fprintf escreve no arquivo temporário os dados dos usuários, que já foram previamente lidos do arquivo em binário
    for(int i = 0; i < *total_usuarios; i++){// *total_usuarios (valor inteiro guardado nesse endereço) != total_usuarios (endereço propriamnete dito)
        fprintf(temp, "Matrícula: %d\n", usuario[i].matricula);
        fprintf(temp, "Nome: %s\n", usuario[i].nome);
        fprintf(temp, "Curso: %s\n", usuario[i].curso);
        fprintf(temp, "Empréstimos ativos: %d\n\n", usuario[i].qtd_emprestimos_ativos);
    }

    fclose(temp); //fechar o arquivo temporário, remove o antigo arquivo de dados dos dados dos usuários e renomeia o arquivo temporário para o nome antigo
    //usa o arquivo temporário, mais uma vez, para não acessar diretamente o arquivo original de primeira. Como queremos preservar esses dados a qualquer custo, se ocorresse uma falha
    //na abertura do arquivo usuariost, perderíamos tudo o que estava salvo
    remove("Biblioteca/Usuarios.txt");
    rename("temporario.txt", "Biblioteca/Usuarios.txt");

};

void alterar_arquivo_usuarios(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

    temp = fopen("temporario.dat", "wb"); //criação do arquivo bin temporário, onde as alterações serão salvas e depois repassadas para o arquivo "oficial" usuariosb

    if(temp == NULL){
        printf("Falha na alteração do arquivo.\n");
        exit(1);
    }

    //bubble sort -> reordena a posição dos usuários em ordem alfabética
    for(int i = 0; i < *total_usuarios-1; i++){
        for(int j = 0; j < *total_usuarios-i-1; j++){
            if(strcmp(usuario[j].nome, usuario[j+1].nome) > 0){ //verifica se o termo [j] começa com uma inicial, assim como as demais letras, mais à frente do que o termo [j+1]
                Usuario temp = usuario[j]; //se sim, realoca os dados dos usuários dentro da struct
                usuario[j] = usuario[j+1];
                usuario[j+1] = temp;
            }
        }
    }

        if(fwrite(usuario, sizeof(Usuario), *total_usuarios, temp) != *total_usuarios){ //verifica o retorno da função fwrite -> se a operação der certo, o retorno é igual ao total de usuários
            printf("Falha ao salvar os dados.\n"); //se houver falha, fecha o pograma sem prejudicar os dados em usuariosb, porque usamos arquivo temporário
            fclose(temp);
            exit(1);
        }

        //escreve no arquivo temporário os dados dentro de cada elemento de struct usuario, considerando o total de usuários
        //usuario -> dados que serão escritos no arquivo: nome, matrícula, curso, qtd_emprestimos_ativos
        // sizeof(Usuario) -> tamanho/quantidade de bytes de cada unidade que será escrita
        //*total_usuarios -> quantidade de unidades que serão escritas
        //temp -> arquivos onde ficarão escritos os dados em binário
        fclose(temp);

        remove("Biblioteca/Usuarios.dat");
        rename("temporario.dat", "Biblioteca/Usuarios.dat"); //fechar o arquivo temporário, remover o arquivo "oficial" e renomear o temporário como "oficial"

        relatoriotxt_usuarios(total_usuarios, usuario); //terminada a atualização dos dados em binário, eles serão também salvos no arquivo txt

    };

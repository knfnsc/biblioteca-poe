#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "livros.h"
#include "emprestimos.h"
#include "util.h"
#include "arquivos.h"

Usuario * cadastrar_usuarios(Usuario *usuario, int *capacidade, int *total_usuarios){//recebe o endereço do inteiro onde ficará guardado o total de usuários, recebe o endereço da struct alocada de usuários e a capacidade limite de cadastros

    int qtd;
    printf("Quantidade de usuários a cadastrar:\n");
    qtd = inteiro_valido();

    if(*total_usuarios + qtd > *capacidade){

        while(*total_usuarios + qtd > *capacidade){ //se o total de usuários já existentes somados aos novos ultrapassar a capacidade, dobramos a capacidade até a capacidade ser capaz de comportar esses usuários novos
            *capacidade *= 2;
        }
            Usuario *temp = realloc(usuario, (*capacidade)*sizeof(Usuario)); //fazemos uma realocação, expandindo o tamanho original da struct usuario
            //declara um ponteiro de struct que recebe a realocação de usuario, que terá um total de bytes igual ao novo limite definido e cada unidade tem o tamanho da struct Usuario

            if(temp == NULL){ //verifica se houve falha na alocação de temp -> se houver, retorna para a tela inicial sem perder os dados guardados em struct usuario
                printf("Falha na operação.\n");
                exit(1);
            }

            usuario = temp; //não havendo falha, a struct original recebe a temp -> ela mantém os dados antigos e adiciona os novos espaços para esse vetor de struct,
            //sendo que os novos espaços alocados ainda não foram inicializados
        }

    if(*total_usuarios >= LIMITE_INICIAL){
        printf("Limite de matrículas atingido.\n");
        return usuario;
    }

    for(int i = 0; i < qtd; i++){ //a cada iteração do laço, cria uma struct para cada novo usuario a ser cadastrado
    Usuario novo_usuario;
    novo_usuario.qtd_emprestimos_ativos = 0;
    printf("Nome do novo usuário:\n");
    fgets(novo_usuario.nome, sizeof(novo_usuario.nome), stdin);
    tratar_string(novo_usuario.nome);

    printf("Curso do novo usuário:\n\n");
    fgets(novo_usuario.curso, sizeof(novo_usuario.curso), stdin);
    tratar_string(novo_usuario.curso);

    //todas as entradas de strings passam pela função tratar_string

    int repetido = 0; //funciona como um dado boolean, um verificador para encontrar as repetições

    //enquanto o numero sorteado for igual a um já sorteado antes, ele sorteia um novo ate
    // ele ser diferente

    //definir a matrícula do usuário, sorteando um valor aleatório num intervalo entre 1 e 10000 + verificar se esse valor já existe
    //dentre as matrículas já cadastradas

    do {
        repetido = 0; //parte do pressuposto de que o número sorteado é diferente na primeira execução e, caso haja uma nova execução, zera a variável que antes estava igual a 1
        novo_usuario.matricula = (rand()%10000)+1;
        for(int i = 0; i < *total_usuarios; i++){
            if(novo_usuario.matricula == usuario[i].matricula){ //se o valor sorteado é igual a algum dentro os já definidos em matrícula, repetido recebe 1 e para de fazer novas buscas comparativas para fazer o novo sorteio
                repetido = 1;
                break;
            }
        }

    }while(repetido); //enquanto repetido for == 1, ou seja, enquanto o valor sorteado for repetido -> quando o valor sorteado por diferente de 1, sorteamos um valor válido e saímos do laço

    printf("Matrícula do usuário: %d\n\n", novo_usuario.matricula);
    usuario[(*total_usuarios)++] = novo_usuario;  //incrementamos ao valor guardado no endereço do ponteiro total_usuarios o novo usuário e a essa nova posição da struct usuario atribuímos o novo usuario
    }

    printf("Cadastro bem-sucedido!\n");
    alterar_arquivo_usuarios(total_usuarios, usuario); //altera os dados dentro dos arquivos lista_usuariost, usuariosb e salva do arquivo de texto

    return usuario; //retorna o ponteiro de struct usuario atualizada com os novos usuários

};

void buscar_usuarios(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

    if(*total_usuarios == 0){ //considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

  int escolha, encontrado = 0;

  printf("Buscar matrícula (1) ou nome (2)?\n");
  escolha = inteiro_valido();

  switch(escolha){

    case 1:{

        while(!encontrado){//enquanto encontrado == 0 (falso), repete a solicitação da matrícula
            int matricula;
            printf("\nInserir matrícula do usuario:\n");
            matricula = inteiro_valido();

            for(int i = 0; i < *total_usuarios; i++){

                if(usuario[i].matricula == matricula){//comparar a matrícula digitada pelo usuário com as matrículas salvas na struct usuario
                    encontrado = 1;
                    printf("Matrícula: %d\n", usuario[i].matricula);
                    printf("Nome: %s\n", usuario[i].nome);
                    printf("Curso: %s\n", usuario[i].curso);
                    break;} //interrompe o laço assim que encontra o usuário
            }

            if(!encontrado){//informa mensagem de erro antes de solicitar novamente a matrícula, caso não tenha sido encontrada
                printf("Usuário não encontrado. Deseja tentar novamente? [s/n]\n");
                char resp = char_valido();

                if(resp == 'n'){ //se o usuário não quiser tentar mais uma vez, sai do laço
                    break;
                }
            }
        }

        break;
    }

    case 2:{

        while(!encontrado){//enquanto encontrado == 0 (falso), repete a solicitação do nome
            char nome[100];
            printf("\nInserir nome completo do usuário:\n");
            fgets(nome, sizeof(nome), stdin);
            tratar_string(nome); //serve para padronizar a entrada do usuário com o padrão de escrita nos arquivos, facilitando a buscar_usuarios
            for(int i = 0; i < *total_usuarios; i++){

                if(strcmp(nome, usuario[i].nome) == 0){//comparar o nome digitado pelo usuario com os nomes salvos na struct usuario
                    encontrado = 1;
                    printf("Matrícula: %d\n", usuario[i].matricula);
                    printf("Nome: %s\n", usuario[i].nome);
                    printf("Curso: %s\n", usuario[i].curso);
                    break;} //interrompe o laço assim que encontra o usuário
            }


            if(!encontrado){//informa mensagem de erro antes de solicitar novamente o nome, caso não tenha sido encontrado
                printf("Usuário não encontrado. Deseja tentar novamente? [s/n]\n");
                char resp = char_valido();

                if(resp == 'n'){//se o usuário não quiser tentar mais uma vez, sai do laço
                    break;
                }

            }
        }

        break;
    }

    default: printf("Comando inválido. Tente novamente.\n"); break; //volta para a tela inicial caso o comando seja inválido, ou seja, diferente de 1(matrícula) ou 2(nome)

  }

};

void listar_usuarios(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

    if(*total_usuarios == 0){//considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    printf("------------------ USUÁRIOS ------------------\n\n");
    for(int i = 0; i < *total_usuarios; i++){
        printf("Matrícula: %d\nNome: %s\nCurso: %s\nEmpréstimos ativos: %d\n\n", usuario[i].matricula, usuario[i].nome, usuario[i].curso, usuario[i].qtd_emprestimos_ativos);
    }
};

void atualizar_usuarios(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

    if(*total_usuarios == 0){//considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    int qtd, escolha;
    printf("Quantidade de usuários a atualizar:\n");
    qtd = inteiro_valido();

    printf("Buscar matricula (1) ou nome (2)?\n");
    escolha = inteiro_valido();

    switch(escolha){

        case 1:{
                int matricula;
                for(int j = 0; j < qtd; j++){//laço relacionado a cada usuário a ser atualizado -> a cada incremento, uma nova atualização
                    int encontrado = 0;
                    printf("\nMatrícula do usuário:\n");
                    matricula = inteiro_valido();

                    for(int i = 0; i < *total_usuarios; i++){//laço relacionado com a busca dentro da struct usuarios

                        if(usuario[i].matricula == matricula){//comparar a matrícula digitada pelo usuario com as matrículas salvas na struct usuario
                            encontrado = 1;
                            printf("Novo nome:\n");
                            fgets(usuario[i].nome, sizeof(usuario[i].nome), stdin);
                            tratar_string(usuario[i].nome);
                            printf("Novo curso:\n");
                            fgets(usuario[i].curso, sizeof(usuario[i].curso), stdin);
                            tratar_string(usuario[i].curso);
                            break; //interrompe o laço assim que encontra o usuário após os comandos acima
                        }
                    }

                    if(!encontrado){//se encontrado == 0 (falso)
                        printf("Usuário não encontrado. Deseja tentar novamente? [s/n]\n"); //Verifica se o usuário deseja continuar tentando; se ele não quiser, ele sai da função
                        char resp = char_valido();

                        if(resp == 'n'){
                            return;
                        }

                        j--; //se ele quiser corrigir, volta para a posição anterior antes do laço j incrementar, mantendo a posição atual -> permite corrigir a matrícula não encontrada
                    }
                }

             printf("Atualização bem-sucedida!\n");
             alterar_arquivo_usuarios(total_usuarios, usuario); //só altera o arquivo ao final do programa -> mais eficiente salvar as alterações uma única vez depois que todos os usuários já foram atualizados
             break;

        }

        case 2:{

            for(int j = 0; j < qtd; j++){//laço relacionado a cada usuário a ser atualizado -> a cada incremento, uma nova atualização
                int encontrado = 0;
                char nome[100];
                printf("\nNome completo do usuário:\n");
                fgets(nome, sizeof(nome), stdin);
                tratar_string(nome);

                    for(int i = 0; i < *total_usuarios; i++){//laço relacionado com a busca dentro da struct usuarios

                        if(strcmp(nome, usuario[i].nome) == 0){//comparar o nome digitado pelo usuario com os nomes salvos na struct usuario
                            encontrado = 1;
                            printf("Novo nome:\n");
                            fgets(usuario[i].nome, sizeof(usuario[i].nome), stdin);
                            tratar_string(usuario[i].nome);
                            printf("Novo curso:\n");
                            fgets(usuario[i].curso, sizeof(usuario[i].curso), stdin);
                            tratar_string(usuario[i].curso);
                            break;} //interrompe o laço assim que encontra o usuário após os comandos acima

                    }

                    if(!encontrado){//se encontrado == 0 (falso)
                        printf("Usuário não encontrado. Deseja tentar novamente? [s/n]\n"); //Verifica se o usuário deseja continuar tentando; se ele não quiser, ele sai da função
                        char resp = char_valido();

                        if(resp == 'n'){
                            return;
                        }

                        j--;//se ele quiser fazer a correção, volta para a posição anterior antes do laço externo j incrementar para testar a busca mais uma vez
                    }

            }

            printf("Atualização bem-sucedida!\n");
            alterar_arquivo_usuarios(total_usuarios, usuario); //só altera o arquivo ao final do programa -> mais eficiente salvar as alterações uma única vez depois que todos os usuários já foram atualizados
            break;

        }

        default: printf("Comando inválido. Tente novamente.\n"); break; //volta para a tela inicial caso o comando seja inválido, ou seja, diferente de 1(matrícula) ou 2(nome)

    }

};

Usuario * remover_usuarios(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

    if(*total_usuarios == 0){//considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
        printf("Nenhum usuário cadastrado.\n");
        return usuario;
    }

    int escolha, qtd;

    printf("Quantidade de usuários a remover:\n");
    qtd = inteiro_valido();

    printf("Buscar matrícula (1) ou nome (2)?\n");
    escolha = inteiro_valido();

    switch(escolha){

        case 1:{

            for(int j = 0; j < qtd; j++){//laço relacionado a cada usuário a ser removido -> a cada incremento, uma nova remoção
                int matricula, encontrado = 0;
                printf("\nInserir matrícula do usuário:\n");
                matricula = inteiro_valido();

                for(int i = 0; i < *total_usuarios; i++){//laço relacionado com a busca dentro da struct usuarios

                    if(matricula == usuario[i].matricula){
                        encontrado = 1;

                        if(usuario[i].qtd_emprestimos_ativos != 0){ //verifica se o usuário possui empréstimos ativos -> se possuir, ele não permite a remoção, sai do laço i e passa para o próximo usuário a ser removido
                            printf("O usuário ainda possui empréstimos em aberto!\n");
                            printf("A remoção do usuário não é permitida.\n");
                            break;
                        }


                        for(int k = i; k < (*total_usuarios)-1; k++){//reorganiza os usuarios sem deixar "buracos" no vetor
                                    usuario[k] = usuario[k+1];
                            }

                        //o primeiro elemento do laço interno com k recebe a posição atual do laço com i, indo até a penúltima posição
                        //o primeiro k tem que receber a posição atual, preservando os dados dos usuários antes da posição atual, já que a partir dessa posição, todos os usuarios na posicao [k+1]
                        //são realocados para [k], fazendo os dados dos usuários nas posições posteriores ao usuário a ser removido serem preservados
                        // conta até total_usuarios-1 porque a última posição será a removida

                        (*total_usuarios)--; //atualiza o valor do total de usuários após a remoção do usuário
                        break;//sai do laço i e pula pro próximo usuário a ser removido j
                    }

                }

                    if(!encontrado){

                        printf("Usuário não encontrado. Deseja tentar novamente? [s/n]\n"); //Verifica se o usuário deseja continuar tentando; se ele não quiser, ele sai da função e retorna o ponteiro com os dados que já tiverem sido modificados + os não modificados
                        char resp = char_valido();

                        if(resp == 'n'){
                            alterar_arquivo_usuarios(total_usuarios, usuario); //salva as alterações feitas até então
                            return usuario; //se apenas retornar o ponteiro sem alterar os arquivos, numa nova execução esses dados já terão sido perdidos
                        }

                     j--;} //se ele quiser corrigir, volta para a posição anterior antes do laço externo j incrementar para testar a busca mais uma vez caso não tenha encontrado


            }

            Usuario *temp = realloc(usuario, (*total_usuarios)*sizeof(Usuario)); //cria um ponteiro temp que recebe o ponteiro de saída da realocação de struct usuario, considerando os usuários que foram removidos
            if(temp == NULL && *total_usuarios > 0){//verifica se houve falha na realocação; se houver, a struct original não será perdida
                printf("Falha na operação.\n"); //temp não pode ser NULL se o *total_usuarios é não nulo e positivo -> caso seja, há um erro grave
                exit(1);}

            usuario = temp; //não havendo falha na operação, atribuímos à struct "oficial" os dados da struct temporária
            printf("Remoção bem-sucedida!\n");
            alterar_arquivo_usuarios(total_usuarios, usuario);//só altera o arquivo ao final do programa -> mais eficiente salvar as alterações uma única vez depois que todos os usuários já foram atualizados
            break;

        }

        case 2: {

            for(int j = 0; j < qtd; j++){//laço relacionado a cada usuário a ser removido
                int encontrado = 0;
                char nome[100];
                printf("\nInserir nome completo do usuário:\n");
                fgets(nome, sizeof(nome), stdin);
                tratar_string(nome);

                for(int i = 0; i < *total_usuarios; i++){//laço relacionado com a busca dentro da struct usuario

                    if(strcmp(nome, usuario[i].nome) == 0){
                        encontrado = 1;

                        if(usuario[i].qtd_emprestimos_ativos != 0){//verifica se o usuário possui empréstimos ativos -> se possuir, ele não permite a remoção, sai do laço i e passa para o próximo usuário a ser removido
                            printf("O usuário ainda possui empréstimos em aberto!\n");
                            printf("A remoção do usuário não é permitida.\n");
                            break;
                        }

                        for(int k = i; k < (*total_usuarios)-1; k++){ //reorganiza os usuários sem deixar "buracos" no vetor
                            usuario[k] = usuario[k+1];
                        }

                        (*total_usuarios)--;
                        break;
                    }
                }

                if(!encontrado){//se encontrado == 0 (falso)

                    printf("Usuário não encontrado. Deseja tentar novamente? [s/n]\n"); //Verifica se o usuário deseja continuar tentando; se ele não quiser, ele sai da função e retorna o ponteiro com os dados que já tiverem sido modificados + os não modificados
                    char resp = char_valido();

                    if(resp == 'n'){
                        alterar_arquivo_usuarios(total_usuarios, usuario); //salva as alterações feitas até então
                        return usuario; //se apenas retornar o ponteiro sem alterar os arquivos, numa nova execução esses dados já terão sido perdidos
                    }

                    j--;} //se ele quiser corrigir, volta para a posição anterior antes do laço externo j incrementar para testar a busca mais uma vez caso não tenha encontrado
            }

        Usuario *temp = realloc(usuario, (*total_usuarios)*sizeof(Usuario)); //cria um ponteiro temp que recebe o ponteiro de saída da realocação de struct usuario considerando os usuários que foram removidos

        if(temp ==  NULL && *total_usuarios > 0){
            printf("Falha na operação.\n");
            exit(1);
        }

        usuario = temp; //não havendo falha na operação, atribuímos à struct "oficial" os dados da struct temporária

        printf("Remoção bem-sucedida!\n");
        alterar_arquivo_usuarios(total_usuarios, usuario); //só altera o arquivo ao final do programa -> mais eficiente salvar as alterações uma única vez depois que todos os usuários já foram atualizados
        break;
        }

        default: printf("Comando inválido. Tente novamente.\n"); break; //volta para a tela inicial caso o comando seja inválido, ou seja, diferente de 1(matrícula) ou 2(nome)

    }

    return usuario;
}


void emprestimos_usuarios(int *total_usuarios, int *total_emprestimos, int *total_livros, Usuario *usuario, Emprestimo *emprestimo, Livro *livro){

    if(*total_usuarios == 0){ //considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

   int encontrado = 0, j;

   while(!encontrado){//enquanto encontrado == 0 (falso), repete a solicitação da matrícula

       int matricula;
        printf("\nInserir matrícula do usuário:\n");
        matricula = inteiro_valido();

        for(int i = 0; i < *total_usuarios; i++){

        if(usuario[i].matricula == matricula){//comparar a matrícula digitada pelo usuário com as matrículas salvas na struct usuario
            encontrado = 1;
            j = i;
            break;} //interrompe o laço assim que encontra o usuário
        }

        if(!encontrado){//informa mensagem de erro antes de solicitar novamente a matrícula, caso não tenha sido encontrada
            printf("Usuário não encontrado. Deseja tentar novamente? [s/n]\n");
            char resp = char_valido();

            if(resp == 'n'){ //se o usuário não quiser tentar mais uma vez, sai do laço e da função
                return;
            }
        }

   }

   if (usuario[j].qtd_emprestimos_ativos == 0) {
       printf("Usuário sem empréstimos no momento.\n");
       return;
   }

   printf("Total de empréstimos ativos do usuário: %d", usuario[j].qtd_emprestimos_ativos);

       for(int i = 0; i < *total_emprestimos; i++){//buscar matrícula correspondente, percorrendo todos os empréstimos

           if(emprestimo[i].matricula_usuario == (uint64_t)usuario[j].matricula){//compara a matrícula de cada usuário que já fez um empréstimo com a matrícula inserida pelo usuário
                   //quando encontra a posição do empréstimo correspondente a esse usuário, compara o código do livro emprestado

                   for(int k = 0; k < *total_livros; k++){//percorre todos os livros cadastrados
                       if(emprestimo[i].codigo_livro == livro[k].codigo && !(emprestimo[i].devolvido)){//fixado o código do livro, percorre até encontrar o livro com o código correspondente
                           printf("Título: %s\nCódigo: %lu\n\n", livro[k].titulo, livro[k].codigo);  //verifica também se o livro já foi devolvido -> se não foi (0), ele informa o livro
                           break; //sai do laço k e volta para o i, buscando um novo possível empréstimo ativo desse mesmo usuário
                       }
                   }
           }
       }

}

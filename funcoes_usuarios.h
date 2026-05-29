#ifndef FUNCOES_USUARIOS //criação de uma "biblioteca" usando variáveis de pré-processamento, ou seja, antes da execução do programa, essa condição já está definida;
#define FUNCOES_USUARIOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //biblioteca para as funcções toupper e tolower
#include <sys/stat.h> //biblioteca para criação de pastas
#define LIMITE 1000

/*
 * 1) Existe uma hierarquia entre as funções, ou seja, elas foram pensadas para serem executadas dentro do terminal de usuários
 * sendo que a função principal é carregar_usuarios, que deve acontecer antes de todas as funções dessa biblioteca
 * 2) As funções alterar_arquivo e relatorio_txt também são dependentes, ficando logo abaixo de carregar_usuarios
 * 3) As demais funções estão num mesmo patamar hierárquico
 */

//função para receber o endereço de uma string e dar um retorno vazio
// objetio: padronizar a escrita dentro dos arquivos, facilitando leitura e pesquisa
void tratar_string(char *str){

    str[strcspn(str, "\n")] = '\0'; //recebe a string e limpa o buffer, trocando o "\n" digitado pelo usuário por "\0", recohecendo o fim da string

    int tam = strlen(str);
    int p_nova = 1; //funciona como um dado boolean, um verificador para encontrar as repetições

    //percorrer cada caractere da string para padronizar a letra inicial de cada palavra como maiúscula e o restante minúscula
    for(int i = 0; i < tam; i++){

        if(str[i] == ' '){ //a cada ' ' reconhece que uma nova palavra se inicia, atribuindo 1 (true) para p_nova
            p_nova = 1;
        }else if(p_nova){ //se é uma nova palavra, ou seja, se p_nova == 1, então ele passa a string para maiúscula
            p_nova = 0; //p_nova recebe 0 para que na próxima iteração, não seja reconhecido como uma nova palavra
            str[i] = toupper(str[i]);
        }else{
            p_nova = 0; //considera que mantém dentro de uma mesma palavra, então mantém os caracteres minúsculos
            str[i] = tolower(str[i]);
        }
    }

    const char *prep[] = {"De", "Da", "Do", "Dos", "Das", "E"}; //aponta para uma quantidade de endereços de memória igual ao número de elementos de prep[]

    int qtd = sizeof(prep)/sizeof(prep[0]); //calcular quantidade de elementos de prep[] baseado no tamanho total
    //do array dividido pelo tamanho de um único elemento (todos têm o mesmo tamanho)

    char copia[200] = "";

    char *palavra = strtok(str, " "); //funcção para separar/quebrar a string em uma substring toda vez que encontrar " "

    while(palavra){ //enquanto a string existir
        for(int i = 0; i < qtd; i++){ //percorra todos os elementos de prep[]

             if(strcmp(palavra, prep[i]) == 0){ //verifique se a substring encontrada é igual a um dos elementos de prep[]
                 palavra[0] = tolower(palavra[0]); //se for igual, o primeiro caractere da substring passa de minúsculo para maiúsculo

             }
        }

        strcat(copia, palavra); //concatena a substring com copia declarada antes e deixa um espaço para começar a próxima palavra
        strcat(copia, " ");
        palavra = strtok(NULL, " "); //se desloca pela string, permitindo encontrar a próxima substring dentro da string original
    }

    copia[strlen(copia)-1] = '\0'; //o último caractere dentro de copia no momento em que ele termina de executar o laço acima é " ", mas
    //isso não é útil, então colocamos no lugar de " " o '\0' para marcar o fim da string. Ex.:
    // "bom_" -> strlen(copia) = 4
    // copia[3] = " " -> copia[3] = '\0'

    strcpy(str, copia); //salva uma cópia das modificações no endereço da string original

};

//struct com os dados necessários dos usuários -> usa typedef para tornar a estrutura mais "limpa" visualmente quando for preciso acessar esses dados
typedef struct {
 int matricula;
 char nome[100];
 char curso[100];
 int qtd_emprestimos_ativos;
}Usuario;

int total_usuarios = 0;

//declara de antemão o nome da pasta conde ficarão savos os arquivos referentes aos usuários;
// o mesmo vale para os ponteiros dos arquivos txt, bin e temporário que serão utilizados na execução do programa
const char *pasta_usuarios = "Usuarios";
FILE *lista_usuariosb, *lista_usuariost, *emprestimos_usuarios, *livros_usuarios, *temp;


//função que, antes de fazer qualquer operação com os usuários, torna os dados deles acessíveis durante a execução do programa
int carregar_usuarios(Usuario *usuario){ //recebe um ponteiro para a struct de usuários, alocada no menu principal

    if(mkdir(pasta_usuarios) == 0){ //verificar se já existe uma pasta de Usuários, se não houver, cria -> útil ao executar o programa na primeira vez
            printf("Pasta de Usuários criada com sucesso!\n");
    }

    lista_usuariosb = fopen("Usuarios\\Lista_Usuarios.dat", "rb"); //abre o arquivo binário onde estão armazenados os dados dos usuários

    if(lista_usuariosb == 0){//verificar se o arquivo já existe; se não existir, ele cria um arquivo do zero e informa o usuário

        printf("Criando o arquivo...\n");
        FILE *temp  = fopen("Usuarios\\Lista_Usuarios.dat", "wb");

        //verifica se houve erro na criação do arquivo; se houver, retorna para a tela inicial
        if(temp == 0){
            printf("Falha na criação do arquivo.\n");
            exit(1);
        }

        fclose(temp);
        lista_usuariosb = fopen("Usuarios\\Lista_Usuarios.dat", "rb"); //fechar o arquivo temporário e agora acessar esse mesmo arquivo, mas pelo seu "nome oficial"
        //criar o arquivo temporário garante que os dados dos usuários já salvos não serão perdidos
        // abre o arquivo para ler os dados dos usuários
    }

    int i = 0;
    while(fread(&usuario[i], sizeof(Usuario), 1, lista_usuariosb) == 1){
    //fread aloca em cada endereço da struct usuario os dados dentro do arquivo
    //guarde no endereço de usuario[i], lendo do arquivo lista_usuariosb, cada unidade de tamanho/quantidade de bytes igual ao de struct Usuario, numa quantidade de 1
    //fread retorna a quantidade de espaços lidos -> se retornar 1, ele recebeu a totalidade dos dados de um usuário, preenchendo cada campo
    // incrementa o contador i para ler os dados do próximo usuário
    // quando não houverem mais dados dentro do arquivo, o retorno do fread será diferente de 1, então o vetor de struct já foi completamente preenchido
        i++;
    }

    fclose(lista_usuariosb);

    return i; //retorna a quantidade de usuários lidos

};

//objetivo: criar os arquivos de texto referentes aos dados dos usuários, tornando os dados antes guardados apenas em binário algo
//compreensível para o usuário
void relatoriotxt(int *total_usuarios, Usuario *usuario){ //recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários.
    //É necessário que sejam ponteiros, já que, à medida que o programa é executado, novos usuários podem ser cadastrados ou deletados. Usar os ponteiros permite acessar diretamente
    //os valores guardado nesses endereços -> se usar apenas um int e Usuario, estaríamos considerando uma situação estática, o que não é o caso

    temp = fopen("temporario.txt", "w"); //cria um arquivo temporário e verifica se houve falha; se houver, retorna para a tela inicial

    if(temp == NULL){
        printf("Falha na criação do arquivo.\n");
        exit(1);
    }

    fprintf(temp, "------------------ USUÁRIOS ------------------\n\n"); //fprintf escreve no arquivo temporário os dados dos usuários, que já foram previamente lidos do arquivo em binário
    for(int i = 0; i < *total_usuarios; i++){// *total_usuarios (valor inteiro guardado nesse endereço) != total_usuarios (endereço propriamnete dito)
        fprintf(temp, "Matrícula: %d\n", usuario[i].matricula);
        fprintf(temp, "Nome: %s\n", usuario[i].nome);
        fprintf(temp, "Curso: %s\n\n", usuario[i].curso);
    }

    fclose(temp); //fechar o arquivo temporário, remove o antigo arquivo de dados dos dados dos usuários e renomeia o arquivo temporário para o nome antigo
    //usa o arquivo temporário, mais uma vez, para não acessar diretamente o arquivo original de primeira. Como queremos preservar esses dados a qualquer custo, se ocorresse uma falha
    //na abertura do arquivo lista_usuariost, perderíamos tudo o que estava salvo
    remove("Usuarios\\Lista_Usuarios.txt");
    rename("temporario.txt", "Usuarios\\Lista_Usuarios.txt");

};


//objetivo: permitir que os arquivos referentes aos dados dos usuários sejam alterados duarante a executação do programa
void alterar_arquivo(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

//está conectado com a função relatorio_txt -> a diferença é que a função atual altera os dados dentro do arquivo binário, para então alterar os arquivos de texto
//por que separar essas funções?
//Os arquivos em binário são mais fáceis e mais rápidos de serem lidos durante o programa, mas possuem a desvantagem de não serem compreensíveis para o usuário.
//Para resolver isso, usamos o arquivo bin para as tarefas gerais do programa e, somente para gerar os reçatórios de texto, usamos funções como fscanf e fprintf, otimizando a execução do programa

    temp = fopen("temporario.dat", "wb"); //criação do arquivo bin temporário, onde as alterações serão salvos e então repassadas para o arquivo "oficial" lista_usuariosb

    if(temp == 0){
        printf("Falha na alteração do arquivo.\n");
        exit(1);
    }

    //bubble sort -> reordena a posição dos usuários em ordem alfabética
    for(int i = 0; i < *total_usuarios-1; i++){
        for(int j = 0; j < *total_usuarios-i-1; j++){
            if(strcmp(usuario[j].nome, usuario[j+1].nome) > 0){ //verifica se o termo [j] começa com uma inicial, assim como as demais letras,mais à frente do que o termo [j+1]
                Usuario temp = usuario[j]; //se sim, realoca os dados dos usuários dentro da struct
                usuario[j] = usuario[j+1];
                usuario[j+1] = temp;
            }
        }
    }

        fwrite(usuario, sizeof(Usuario), *total_usuarios, temp); //escreve no arquivo temporário os dados dentro de cada elemento de struct usuario, considerando o total de usuários
        //usuario -> dados que serão escritos no arquivo: nome, matrícula, curso e empréstimos qtd_emprestimos_ativos
        // sizeof(Usuario) -> tamanho/quantidade de bytes de cada unidade que será escrita
        //*total_usuarios -> quantidade de unidades que serão escritas
        //temp -> arquivos onde ficarão escritos os dados em binário
        fclose(temp);

        remove("Usuarios\\Lista_Usuarios.dat");
        rename("temporario.dat", "Usuarios\\Lista_Usuarios.dat"); //fechar o arquivo temporário, remover o arquivo "oficial" e renomear o temporário como "oficial"

        relatoriotxt(total_usuarios, usuario); //terminada a atualização dos dados em binário, eles serão também salvos no arquivo txt

    };


Usuario * cadastrar_usuarios(int *total_usuarios, Usuario *usuario){
    int limite = LIMITE; //definimos como uma variável de pré-processamente LIMITE = 1000 -> isso significa, que antes da execução do programa, esse valor já está definido;
    //faz uma previsão de quantos usuários o sistema da biblioteca suporta
    if(*total_usuarios >= limite){ //se a quantidade de usuários for superior a 1000, dobramos a capacidade para 2000
        limite *= 2;
        Usuario *temp = realloc(usuario, limite*sizeof(Usuario)); //fazemos uma realocação, expandindo o tamanho original da struct usuario
        //declara um ponteiro de struct que recebe a realocação de usuario, que terá um total de bytes igual ao novo limite definido e cada unidade tem o tamanho da struct Usuario

        if(temp == NULL){ //verifica se houve falha na alocação de temp -> se houver, retorna para a tela inicial sem perder os dados guardados em struct usuario
            printf("Falha na operação.\n");
            exit(1);
        }

        usuario = temp; //não havendo falha, a struct original recebe a temp -> ela mantém os dados antigos e adiciona os novos espaços para esse vetor de struct,
        //sendo que cada novo campo está inicializado com 0, pois usamos realloc -> evita lidar com o possível lixo de memória que a função malloc pode causar
    }

    int qtd;
    printf("Quantidade de usuários a cadastrar:\n");
    scanf("%d", &qtd);
    getchar(); //sempre que usamos scanf seguido de fgets usamos getchar para limpar o buffer

    for(int i = 0; i < qtd; i++){ //a cada iteração do laço, cria uma struct para cada novo usuario a ser cadastrado
    Usuario novo_usuario;
    printf("Nome do novo usuário:\n");
    fgets(novo_usuario.nome, sizeof(novo_usuario.nome), stdin);
    tratar_string(novo_usuario.nome);

    printf("Curso do novo usuário:\n");
    fgets(novo_usuario.curso, sizeof(novo_usuario.curso), stdin);
    tratar_string(novo_usuario.curso);

    //todas as entradas de strings passam pela função tratar_string

    int repetido = 0; //funciona como um dado boolean, um verificador para encontrar as repetições

    //enquanto o numero sorteado for igual a um ja sorteado antes, ele sorteia um novo ate
    // ele ser diferente

    //definir a matrícula do usuário, sorteando um valor aleatório num intervalo entre 1 e 10000 + verificar se esse valor já existe
    //dentre as matrículas já cadastradas

    do{
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
    alterar_arquivo(total_usuarios, usuario); //altera os dados dentro dos arquivos lista_usuariost, lista_usuariosb e salva do arquivo de texto

    return usuario; //retorna o ponteiro de struct usuario atualizada com os novod usuários

};

Usuario * buscar_usuarios(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

    if(*total_usuarios == 0){ //considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
        printf("Nenhum usuário cadastrado.\n");
        return NULL;
    }

  int escolha, encontrado = 0;

  printf("Buscar matrícula (1) ou nome (2)?\n");
  scanf("%d", &escolha);
  getchar();

  switch(escolha){

    case 1:{

        while(!encontrado){//enquanto encontrado == 0 (falso), repete a solicitação da matrícula
            int matricula;
            printf("Inserir matrícula do usuario:\n");
            scanf("%d", &matricula);
            getchar();

            for(int i = 0; i < *total_usuarios; i++){

                if(usuario[i].matricula == matricula){//comparar a matrícula digitada pelo usuário com as matrículas salvas na struct usuario
                    encontrado = 1;
                    printf("Matrícula: %d\n", usuario[i].matricula);
                    printf("Nome: %s\n", usuario[i].nome);
                    printf("Curso: %s\n", usuario[i].curso);
                    break;} //interrompe o laço assim que encontra o usuário
            }

            if(!encontrado){//informa mensagem de erro antes de solicitar novamente a matrícula, caso não tenha sido encontrada
                printf("Usuário não encontrado. Tente novamente.\n");
            }
        }

        break;
    }

    case 2:{

        char nome[100];
        printf("Inserir nome do usuário:\n");
        fgets(nome, sizeof(nome), stdin);
        tratar_string(nome); //serve para padronizar a entrada do usuário com o padrão de escrita nos arquivos, facilitando a buscar_usuarios


        while(!encontrado){//enquanto encontrado == 0 (falso), repete a solicitação do nome
            for(int i = 0; i < *total_usuarios; i++){

                if(strcmp(nome, usuario[i].nome) == 0){//comparar o nome digitado pelo usuario com os nomes salvos na struct usuario
                    encontrado = 1;
                    printf("Matrícula: %d\n", usuario[i].matricula);
                    printf("Nome: %s\n", usuario[i].nome);
                    printf("Curso: %s\n", usuario[i].curso);
                    break;} //interrompe o laço assim que encontra o usuário
            }


            if(!encontrado){//informa mensagem de erro antes de solicitar novamente o nome, caso não tenha sido encontrado
                printf("Usuário não encontrado. Tente novamente.\n");
            }
        }

        break;
    }

    default: printf("Comando inválido. Tente novamente.\n"); break; //volta para a tela inicial caso o comando seja inválido, ou seja, diferente de 1(matrícula) ou 2(nome)

  }

  return usuario;

};

//objetivo: garantindo que os dados de lista_usuariosb já foram lidos, mostra os dados de todos os usuários cadastrados
Usuario * listar_usuarios(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

    if(*total_usuarios == 0){//considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
        printf("Nenhum usuário cadastrado.\n");
        return NULL;
    }

    printf("------------------ USUÁRIOS ------------------\n\n");
    for(int i = 0; i < *total_usuarios; i++){
        printf("Matrícula: %d\nNome: %s\nCurso: %s\n\n", usuario[i].matricula, usuario[i].nome, usuario[i].curso);
    }

    return usuario;
};

//objetivo: alterar os dados de uma certa quantidade de usuários, preservando os dados dos demais usuários. Ao final, salvar as alterações nos arquivos, atulizar o ponteiro de struct usuario e o valor em *total_usuarios
Usuario * atualizar_usuarios(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

    if(*total_usuarios == 0){//considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
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
                int encontrado = 0;

                for(int j = 0; j < qtd; j++){//laço relacionado a cada usuário a ser atualizado -> a cada incremento, uma nova atualização
                    printf("Matrícula do usuário:\n");
                    scanf("%d", &matricula);
                    getchar();

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
                        printf("Usuário não encontrado. Tente novamente.\n");
                        j--; //volta para a posição anterior antes do laço j incrementar, mantendo a posição atual -> permite corrigir a matrícula não encontrada
                    }
                }

             alterar_arquivo(total_usuarios, usuario); //só altera o arquivo ao final do programa -> mais eficiente salvar as alterações uma única vez depois que todos os usuários já foram atualizados
             printf("Atualização bem-sucedida!\n");
             break;

        }

        case 2:{

            for(int j = 0; j < qtd; j++){//laço relacionado a cada usuário a ser atualizado -> a cada incremento, uma nova atualização
                int encontrado = 0;
                char nome[100];
                printf("Nome do usuário:\n");
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
                        printf("Usuário não encontrado.Tente novamente.\n");
                        j--;//volta para a posição anterior antes do laço externo j incrementar para testar a busca mais uma vez
                    }

            }

            alterar_arquivo(total_usuarios, usuario); //só altera o arquivo ao final do programa -> mais eficiente salvar as alterações uma única vez depois que todos os usuários já foram atualizados
            printf("Atualização bem-sucedida!\n");
            break;

        }

        default: printf("Comando inválido. Tente novamente.\n"); break; //volta para a tela inicial caso o comando seja inválido, ou seja, diferente de 1(matrícula) ou 2(nome)

    }

    return usuario;
};

//objetivo: remover uma certa quantidade de usuários, preservando os dados dos demais usuários. Ao final, salvar as alterações nos arquivos, atulizar o ponteiro de struct usuario e o valor em *total_usuarios
Usuario * remover_usuarios(int *total_usuarios, Usuario *usuario){//recebe o endereço do inteiro onde ficará guardado o total de usuários e recebe o endereço da struct alocada de usuários

    if(*total_usuarios == 0){//considera as duas possibilidades: 1 - sistema já em funcionamento e com usuários já cadastrados; 2 - primeira execução, quando não existem usuários cadastrados
        printf("Nenhum usuário cadastrado.\n");
        return NULL;
    }

    int escolha, qtd;

    printf("Quantidade de usuários a remover:\n");
    scanf("%d", &qtd);

    printf("Buscar matrícula (1) ou nome (2)?\n");
    scanf("%d", &escolha);
    getchar();

    switch(escolha){

        case 1:{

            for(int j = 0; j < qtd; j++){//laço relacionado a cada usuário a ser removido -> a cada incremento, uma nova remoção
                int encontrado = 0;
                int matricula;
                printf("Inserir matrícula do usuário:\n");
                scanf("%d", &matricula);
                getchar();

                for(int i = 0; i < *total_usuarios; i++){//laço relacionado com a busca dentro da struct usuarios

                    if(matricula == usuario[i].matricula){
                        encontrado = 1;

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
                     printf("Usuário não encontrado. Tente novamente\n");
                     j--;} //volta para a posição anterior antes do laço externo j incrementar para testar a busca mais uma vez caso não tenha encontrado


            }

            Usuario *temp = realloc(usuario, (*total_usuarios)*sizeof(Usuario)); //cria um ponteiro temp que recebe o ponteiro de saída da realocação de struct usuario, considerando os usuários que foram removidos
            if(temp == NULL && *total_usuarios > 0){//verifica se houve falha na realocação; se houver, a struct original não será perdida
                printf("Falha na operação.\n"); //temp não pode ser NULL se o *total_usuarios é não nulo e positivo -> caso seja, há um erro grave
                exit(1);}

            usuario = temp; //não havendo falha na operação, atribuímos à struct "oficial" os dados da struct temporária
            alterar_arquivo(total_usuarios, usuario);//só altera o arquivo ao final do programa -> mais eficiente salvar as alterações uma única vez depois que todos os usuários já foram atualizados
            printf("Remoção bem-sucedida!\n");
            break;

        }

        case 2: {

            for(int j = 0; j < qtd; j++){//laço relacionado a cada usuário a ser removido
                int encontrado = 0;
                char nome[100];
                printf("Inserir nome do usuário:\n");
                fgets(nome, sizeof(nome), stdin);
                tratar_string(nome);

                for(int i = 0; i < *total_usuarios; i++){//laço relacionado com a busca dentro da struct usuarios

                    if(strcmp(nome, usuario[i].nome) == 0){
                        encontrado = 1;

                        for(int k = i; k < (*total_usuarios)-1; k++){ //reorganiza os usuarios sem deixar "buracos" no vetor
                            usuario[k] = usuario[k+1];
                        }

                        (*total_usuarios)--;
                        break;
                    }
                }

                if(!encontrado){//se encontrado == 0 (falso)
                    printf("Usuário não encontrado. Tente novamente.\n");
                    j--;} //volta para a posição anterior antes do laço externo j incrementar para testar a busca mais uma vez caso não tenha encontrado
            }

        Usuario *temp = realloc(usuario, (*total_usuarios)*sizeof(Usuario)); //cria um ponteiro temp que recebe o ponteiro de saída da realocação de struct usuario, considerando os usuários que foram removidos

        if(temp ==  NULL && *total_usuarios > 0){
            printf("Falha na operação.\n");
            exit(1);}

        usuario = temp;

        alterar_arquivo(total_usuarios, usuario); //só altera o arquivo ao final do programa -> mais eficiente salvar as alterações uma única vez depois que todos os usuários já foram atualizados
        printf("Remoção bem-sucedida!\n");
        break;
        }

        default: printf("Comando inválido. Tente novamente.\n"); break;

    }

    return usuario;

};

#endif

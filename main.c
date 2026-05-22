#include <stdio.h>
#include <string.h>

// Estrutura para armazenar informações do funcionário
struct Funcionario {
    int id;
    char nome[100];
    float salario;
};

// Declaração do array para armazenar funcionários
struct Funcionario funcionarios[100];
int total_funcionarios = 0;

// Protótipos das funções
void adicionar_funcionario();
void listar_funcionarios();
void atualizar_funcionario();
void deletar_funcionario();

int main() {
    int opcao;

    while(1) {
        printf("\nMenu Banco de Dados de Funcionarios:\n");
        printf("1. Adicionar Funcionario\n");
        printf("2. Listar Funcionarios\n");
        printf("3. Atualizar Funcionario\n");
        printf("4. Deletar Funcionario\n");
        printf("5. Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionar_funcionario();
                break;
            case 2:
                listar_funcionarios();
                break;
            case 3:
                atualizar_funcionario();
                break;
            case 4:
                deletar_funcionario();
                break;
            case 5:
                printf("Encerrando programa...\n");
                return 0;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
    return 0;
}

// Adiciona um novo funcionário
void adicionar_funcionario() {
    struct Funcionario novo_funcionario;

    printf("Digite o ID do Funcionario: ");
    scanf("%d", &novo_funcionario.id);
    getchar(); // Limpa o buffer
    printf("Digite o Nome do Funcionario: ");
    fgets(novo_funcionario.nome, sizeof(novo_funcionario.nome), stdin);
    novo_funcionario.nome[strcspn(novo_funcionario.nome, "\n")] = '\0';
    printf("Digite o Salario do Funcionario: ");
    scanf("%f", &novo_funcionario.salario);

    funcionarios[total_funcionarios++] = novo_funcionario;
    printf("Funcionario adicionado com sucesso!\n");
}

// Lista todos os funcionários
void listar_funcionarios() {
    if (total_funcionarios == 0) {
        printf("Nenhum registro de funcionario encontrado.\n");
        return;
    }

    printf("\nRegistros de Funcionarios:\n");
    for (int i = 0; i < total_funcionarios; i++) {
        printf("ID: %d, Nome: %s, Salario: %.2f\n", funcionarios[i].id, funcionarios[i].nome, funcionarios[i].salario);
    }
}

// Atualiza dados de um funcionário existente
void atualizar_funcionario() {
    int id, encontrado = 0;

    printf("Digite o ID do funcionario a ser atualizado: ");
    scanf("%d", &id);

    for (int i = 0; i < total_funcionarios; i++) {
        if (funcionarios[i].id == id) {
            encontrado = 1;
            printf("Digite o novo nome: ");
            getchar();
            fgets(funcionarios[i].nome, sizeof(funcionarios[i].nome), stdin);
            funcionarios[i].nome[strcspn(funcionarios[i].nome, "\n")] = '\0';
            printf("Digite o novo salario: ");
            scanf("%f", &funcionarios[i].salario);
            printf("Funcionario atualizado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionario com ID %d nao encontrado.\n", id);
    }
}

// Remove um funcionário do array
void deletar_funcionario() {
    int id, encontrado = 0;

    printf("Digite o ID do funcionario a ser deletado: ");
    scanf("%d", &id);

    for (int i = 0; i < total_funcionarios; i++) {
        if (funcionarios[i].id == id) {
            encontrado = 1;
            for (int j = i; j < total_funcionarios - 1; j++) {
                funcionarios[j] = funcionarios[j + 1];
            }
            total_funcionarios--;
            printf("Funcionario deletado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionario com ID %d nao encontrado.\n", id);
    }
}
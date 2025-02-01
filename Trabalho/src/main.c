#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *pBuffer;

void adicionarPessoa();
void removerPessoa();
void buscarPessoa();
void listarTodos();

int main() {
    pBuffer = malloc(sizeof(int) + sizeof(char) + 50);  // Inicializa com espaço para contador, switch e busca
    if (!pBuffer) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    *(int *)pBuffer = 0; //Inicializa contador no 0
    
    do {
        printf("\nMenu:\n1 - Adicionar Pessoa\n2 - Remover Pessoa\n3 - Buscar Pessoa\n4 - Listar Todos\n5 - Sair\n\nEscolha uma opcao: ");
        
        char *op = (char *)pBuffer + sizeof(int); // Opção armazenada no pBuffer
        *op = getchar(); // Captura a opção
        while (getchar() != '\n'); // Limpa buffer de entrada

        switch (*op) {
            case '1': adicionarPessoa(); break;
            case '2': removerPessoa(); break;
            case '3': buscarPessoa(); break;
            case '4': listarTodos(); break;
            case '5': free(pBuffer); return 0;
            default: printf("\nOpcao invalida!\n");
        }
    } while (1);
}

void adicionarPessoa() {
    void *tempBuffer;
    pBuffer = realloc(pBuffer, sizeof(int) + sizeof(char) + 50 + (*(int *)pBuffer + 1) * (100 + sizeof(int))); 
    // Contador / Switch op / Busca / Dados / 50 bytes (Nome) + 4 bytes (Idade) + 50 bytes (Email)
    
    if (!pBuffer) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    tempBuffer = (char *)pBuffer + sizeof(int) + sizeof(char) + 50 + *(int *)pBuffer * (100 + sizeof(int)); //Coloca buffer na posição correta
    printf("\nDigite o Nome: ");
    fgets((char *)tempBuffer, 50, stdin);
    
    tempBuffer = (char *)tempBuffer + 50; //Coloca buffer na posição correta
    printf("\nDigite a Idade: ");
    scanf("%d", (int *)tempBuffer);

    getchar();

    tempBuffer = (char *)tempBuffer + sizeof(int); //Coloca buffer na posição correta
    printf("\nDigite seu Email: ");
    fgets((char *)tempBuffer, 50, stdin);

    (*(int *)pBuffer)++; //Incrementa o contador de usuários

    printf("\nUsuario cadastrado com sucesso\n");
}

void removerPessoa() {
    void *tempBuffer = (char *)pBuffer + sizeof(int) + sizeof(char) + 50;
    if (*(int *)pBuffer == 0) {
        printf("\nNenhuma pessoa cadastrada.\n");
        return;
    }
    char *busca = (char *)pBuffer + sizeof(int) + sizeof(char); // Usa o espaço do buffer de busca
    
    printf("\nNome da pessoa a remover: ");
    fgets(busca, 50, stdin);
    for (int i = 0; i < *(int *)pBuffer; i++) {
        if (strcmp(tempBuffer, busca) == 0) {
            memmove(tempBuffer, (char *)tempBuffer + 100 + sizeof(int), (*(int *)pBuffer - i - 1) * (100 + sizeof(int)));
            (*(int *)pBuffer)--;
            pBuffer = realloc(pBuffer, sizeof(int) + sizeof(char) + 50 + (*(int *)pBuffer) * (100 + sizeof(int)));
            printf("\nPessoa removida!\n");
            return;
        }
        tempBuffer = (char *)tempBuffer + 100 + sizeof(int);
    }
    printf("\nPessoa nao encontrada!\n");
}

void buscarPessoa() {
    void *tempBuffer = (char *)pBuffer + sizeof(int) + sizeof(char) + 50;
    if (*(int *)pBuffer == 0) {
        printf("\nNenhuma pessoa cadastrada.\n");
        return;
    }
    char *busca = (char *)pBuffer + sizeof(int) + sizeof(char); // Usa o espaço do buffer de busca

    printf("\nNome da pessoa a buscar: ");
    fgets(busca, 50, stdin);
    for (int i = 0; i < *(int *)pBuffer; i++) {
        if (strcmp(tempBuffer, busca) == 0) {
            tempBuffer = (char *)tempBuffer + 50;
            printf("\nNome: %sIdade: %d\nEmail: %s\n", busca, *(int *)tempBuffer, (char *)tempBuffer + sizeof(int));
            return;
        }
        tempBuffer = (char *)tempBuffer + 100 + sizeof(int);
    }
    printf("\nPessoa nao encontrada!\n");
}

void listarTodos() {
    void *tempBuffer = (char *)pBuffer + sizeof(int) + sizeof(char) + 50;
    if (*(int *)pBuffer == 0) {
        printf("\nNenhuma pessoa cadastrada.\n");
        return;
    }
    for (int i = 0; i < *(int *)pBuffer; i++) {
        printf("Nome: %s", (char *)tempBuffer);
        tempBuffer = (char *)tempBuffer + 50;
        printf("Idade: %d\n", *(int *)tempBuffer);
        tempBuffer = (char *)tempBuffer + sizeof(int);
        printf("Email: %s", (char *)tempBuffer);
        tempBuffer = (char *)tempBuffer + 50;
    }
}

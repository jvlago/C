#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *pBuffer;

void AdicionarPessoa();
void RemoverPessoa();
void BuscarPessoa();
void ListarTodos();

int main() {
    pBuffer = malloc( sizeof(int) + sizeof(char) + 50 );  // Inicializa com espaço para contador, switch e busca
    if ( !pBuffer ) {
        printf( "Erro ao alocar memoria!\n" );
        return 1;
    }

    *(int *)pBuffer = 0;  // Inicializa contador no 0

    do {
        printf( "\nMenu:\n"
               "1 - Adicionar Pessoa\n"
               "2 - Remover Pessoa\n"
               "3 - Buscar Pessoa\n"
               "4 - Listar Todos\n"
               "5 - Sair\n\n"
               "Escolha uma opcao: " );

        char *op = (char *)pBuffer + sizeof(int);  // Opção armazenada no pBuffer
        *op = getchar();  // Captura a opção
        while ( getchar() != '\n' );  // Limpa buffer de entrada

        switch ( *op ) {
            case '1':
                AdicionarPessoa();
                break;

            case '2':
                RemoverPessoa();
                break;

            case '3':
                BuscarPessoa();
                break;

            case '4':
                ListarTodos();
                break;

            case '5':
                free( pBuffer );
                return 0;

            default:
                printf( "\nOpcao invalida!\n" );
                break;
        }
    } while ( 1 );

    return 0;
}

/*
====================
AdicionarPessoa
 Responsável por cadastrar uma nova pessoa.
 Essa função aumenta dinamicamente o tamanho do buffer para incluir os dados da nova pessoa,
 que incluem o nome (50 bytes), a idade (tamanho de um int) e o email (50 bytes).
 Ela solicita esses dados ao usuário, armazena-os no buffer e incrementa o contador de usuários.
====================
*/

void AdicionarPessoa() {
    void *tempBuffer;

    pBuffer = realloc( pBuffer, sizeof(int) + sizeof(char) + 50 + (*(int *)pBuffer + 1) * (100 + sizeof(int)) );
    // Aloca espaço para: contador / switch op / busca / (dados: 50 bytes (Nome) + sizeof(int) (Idade) + 50 bytes (Email))
    if ( !pBuffer ) {
        printf( "Erro ao alocar memoria!\n" );
        exit( 1 );
    }

    tempBuffer = (char *)pBuffer + sizeof(int) + sizeof(char) + 50 + *(int *)pBuffer * (100 + sizeof(int));
    // Coloca buffer na posição correta

    printf( "\nDigite o Nome: " );
    fgets( (char *)tempBuffer, 50, stdin );

    tempBuffer = (char *)tempBuffer + 50;  // Avança 50 bytes (Nome)
    printf(" \nDigite a Idade: " );
    scanf( "%d", (int *)tempBuffer );

    getchar();  // Limpa o '\n' deixado pelo scanf

    tempBuffer = (char *)tempBuffer + sizeof(int);  // Avança o espaço da idade
    printf( "\nDigite seu Email: " );
    fgets( (char *)tempBuffer, 50, stdin );

    (*(int *)pBuffer)++;  // Incrementa o contador de usuários

    printf( "\nUsuario cadastrado com sucesso\n" );
}

/*
====================
RemoverPessoa
 Realiza a remoção de uma pessoa cadastrada.
 A função solicita ao usuário o nome da pessoa a ser removida e,
 em seguida, percorre o buffer procurando uma correspondência.
 Se encontrar a pessoa, remove os dados correspondentes utilizando a função memmove para realocar os dados subsequentes,
 decrementa o contador e ajusta o tamanho do buffer por meio de realloc.
 Caso a pessoa não seja encontrada, exibe uma mensagem informando o usuário.
====================
*/

void RemoverPessoa() {
    if ( *(int *)pBuffer == 0 ) {
        printf( "\nNenhuma pessoa cadastrada.\n" );
        return;
    }

    void *tempBuffer = (char *)pBuffer + sizeof(int) + sizeof(char) + 50;
    char *busca = (char *)pBuffer + sizeof(int) + sizeof(char);  // Usa o espaço do buffer de busca

    printf( "\nNome da pessoa a remover: " );
    fgets( busca, 50, stdin );

    for ( int i = 0; i < *(int *)pBuffer; i++ ) {
        if ( strcmp((char *)tempBuffer, busca) == 0 ) {
            memmove( tempBuffer, (char *)tempBuffer + 100 + sizeof(int),(*(int *)pBuffer - i - 1) * (100 + sizeof(int)) );
            (*(int *)pBuffer)--;

            pBuffer = realloc( pBuffer, sizeof(int) + sizeof(char) + 50 + (*(int *)pBuffer) * (100 + sizeof(int)) );
            printf( "\nPessoa removida!\n" );
            return;
        }
        tempBuffer = (char *)tempBuffer + 100 + sizeof(int);
    }

    printf( "\nPessoa nao encontrada!\n" );
}

/*
====================
BuscarPessoa
 Procura e exibe os dados de uma pessoa cadastrada com base no nome fornecido pelo usuário.
 A função percorre o buffer comparando os nomes armazenados com o nome buscado.
 Se encontrar a pessoa, exibe seu nome, idade e email.
 Caso contrário, informa que a pessoa não foi encontrada.
====================
*/

void BuscarPessoa() {
    if ( *(int *)pBuffer == 0 ) {
        printf( "\nNenhuma pessoa cadastrada.\n" );
        return;
    }
    
    void *tempBuffer = (char *)pBuffer + sizeof(int) + sizeof(char) + 50;
    char *busca = (char *)pBuffer + sizeof(int) + sizeof(char);  // Usa o espaço do buffer de busca

    printf( "\nNome da pessoa a buscar: " );
    fgets( busca, 50, stdin );

    for ( int i = 0; i < *(int *)pBuffer; i++ ) {
        if ( strcmp((char *)tempBuffer, busca) == 0 ) {
            tempBuffer = (char *)tempBuffer + 50;
            printf( "\nNome: %sIdade: %d\nEmail: %s\n", busca, *(int *)tempBuffer, (char *)tempBuffer + sizeof(int) );
            return;
        }
        tempBuffer = (char *)tempBuffer + 100 + sizeof(int);
    }

    printf( "\nPessoa nao encontrada!\n" );
}

/*
====================
ListarTodos
 Lista os dados de todas as pessoas cadastradas no sistema.
 A função percorre o buffer, exibindo sequencialmente o nome, a idade e o email de cada pessoa cadastrada.
 Se não houver nenhuma pessoa cadastrada, informa ao usuário que não há registros disponíveis.
====================
*/

void ListarTodos() {
    if ( *(int *)pBuffer == 0 ) {
        printf( "\nNenhuma pessoa cadastrada.\n" );
        return;
    }
    
    void *tempBuffer = (char *)pBuffer + sizeof(int) + sizeof(char) + 50;

    for ( int i = 0; i < *(int *)pBuffer; i++ ) {
        printf( "\nNome: %s", (char *)tempBuffer );
        tempBuffer = (char *)tempBuffer + 50;

        printf( "Idade: %d\n", *(int *)tempBuffer );
        tempBuffer = (char *)tempBuffer + sizeof(int);

        printf( "Email: %s", (char *)tempBuffer );
        tempBuffer = (char *)tempBuffer + 50;
    }
}

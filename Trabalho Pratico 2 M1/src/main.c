#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo_t {
    int pass, total;
    double ratio, dif;
    struct Nodo_t *prox;
} Nodo_t;

typedef struct {
    Nodo_t *head;
} Class_t;

Class_t* CreateClass();
void Push( Class_t* class, int pass, int total );
Nodo_t* Pop( Class_t* class );
void AddOneStudent( Nodo_t* nodo );
double GetClassRatio( Class_t* class, int classesSize );
void FreeClass( Class_t* class );

/*
====================
maxAverageRatio
 Função principal que recebe as turmas e distribui os alunos extras da forma que maximize a média das razões de aprovação.
====================
*/

double maxAverageRatio( int** classes, int classesSize, int* classesColSize, int extraStudents ) {
    Class_t* class = CreateClass();
    for (int i = 0; i < classesSize; i++) {
        Push( class, classes[i][0], classes[i][1] );
    }
    for (int i = 0; i < extraStudents; i++) {
        Nodo_t* nodo = Pop( class );
        if ( nodo ) {
            AddOneStudent( nodo );
            Push( class, nodo->pass, nodo->total );
            free( nodo );
        }
    }
    double result = GetClassRatio( class, classesSize );
    FreeClass( class );
    return result;
}

int main() {
    int* classes[] = {
        (int[]){2, 4},
        (int[]){3, 9},
        (int[]){4, 5},
        (int[]){2, 10}
    };
    int classesSize = sizeof( classes ) / sizeof( classes[0] ), extraStudents = 4;
    int *classesColSize = NULL; // Didn't use.
    double result = maxAverageRatio( classes, classesSize, classesColSize, extraStudents );
    printf( "%.5f\n", result );
    return 0;
}

/*
====================
CreateClass
 Cria e inicializa uma estrutura Class, que representa uma lista encadeada de Nodo.
====================
*/

Class_t* CreateClass() {
    Class_t *class = ( Class_t* ) malloc( sizeof( Class_t ) ); 
    if ( class ) {
        class->head = NULL;
    }
    return class;
}

/*
====================
Push
 Insere um novo nó (Nodo) na lista encadeada de forma ordenada com base no impacto que adicionar um aluno teria na razão de aprovação.
====================
*/

void Push( Class_t* class, int pass, int total ) {
    Nodo_t *novoNodo = ( Nodo_t* ) malloc( sizeof( Nodo_t ) );
    if ( !novoNodo ) return;
    
    novoNodo->pass = pass;
    novoNodo->total = total;
    novoNodo->ratio = ( double )pass / total;
    novoNodo->dif = ( ( double )( pass + 1 ) / ( total + 1 ) ) - novoNodo->ratio;
    novoNodo->prox = NULL;

    if ( class->head == NULL || class->head->dif <= novoNodo->dif ) {
        novoNodo->prox = class->head;
        class->head = novoNodo;
    } else {
        Nodo_t* current = class->head;
        while ( current->prox && current->prox->dif >= novoNodo->dif ) {
            current = current->prox;
        }
        novoNodo->prox = current->prox;
        current->prox = novoNodo;
    }
}

/*
====================
Pop
 Remove e retorna o nó do início da lista (o que tem o maior impacto ao adicionar um aluno).
====================
*/

Nodo_t* Pop( Class_t* class ) {
    if ( !class->head ) return NULL;
    Nodo_t* wr = class->head;
    class->head = wr->prox;
    return wr;
}

/*
====================
AddOneStudent
 Adiciona um aluno aprovado à turma (Nodo), atualizando os valores de pass, total, ratio e dif.
====================
*/

void AddOneStudent( Nodo_t* nodo ) {
    nodo->pass += 1;
    nodo->total += 1;
    nodo->ratio = ( double )nodo->pass / nodo->total;
    nodo->dif = ( ( double )( nodo->pass + 1 ) / ( nodo->total + 1 ) ) - nodo->ratio;
}

/*
====================
GetClassRatio
 Calcula a média das razões de aprovação de todas as turmas na lista.
====================
*/

double GetClassRatio( Class_t* class, int classesSize ) {
    Nodo_t *nodo = class->head;
    double sum = 0;
    while ( nodo ) {
        sum += nodo->ratio;
        nodo = nodo->prox;
    }
    return sum / classesSize;
}

/*
====================
FreeClass
 Libera toda a memória alocada para a estrutura Class e seus nós (Nodo).
====================
*/

void FreeClass( Class_t* class ) {
    Nodo_t *nodo = class->head;
    while ( nodo ) {
        Nodo_t *temp = nodo;
        nodo = nodo->prox;
        free( temp );
    }
    free( class );
}
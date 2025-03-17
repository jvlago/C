#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int difficulty;
    int profit;
} Work_t;

/*
====================
Compare
 Função de comparação usada pelo qsort para ordenar um array de inteiros em ordem crescente.
====================
*/

int Compare( const void* a, const void* b ) {
   return ( *( int* )a - *( int* )b );
}

/*
====================
CompareW
 Função de comparação usada pelo qsort para ordenar um array de estruturas Work_t
 com base no campo difficulty (dificuldade) em ordem crescente.
====================
*/

int CompareW( const void* a, const void* b ) {
    return ( ( Work_t* )a )->difficulty - ( ( Work_t* )b )->difficulty;
}

/*
====================
maxProfitAssignment
 Calcula o lucro máximo que os trabalhadores podem obter com base em suas habilidades (worker)
 e nas dificuldades e lucros dos trabalhos disponíveis.
====================
*/

int maxProfitAssignment( int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize ) {
    Work_t* work = ( Work_t* )malloc( sizeof( Work_t ) * profitSize );
    for( int i = 0; i < profitSize; i++ ){ // Constraint: profitSize = difficultySize
        work[i].difficulty = difficulty[i];
        work[i].profit = profit[i];
    }
    qsort( worker, workerSize, sizeof( int ), Compare );
    qsort( work, profitSize, sizeof( Work_t ), CompareW );
    int sum = 0, j = 0, best_profit = 0;
    for ( int i = 0; i < workerSize; i++ ) {
        while ( j < profitSize && work[j].difficulty <= worker[i] ) {
            if ( work[j].profit > best_profit ) {
                best_profit = work[j].profit;
            }
            j++;
        }
        sum += best_profit;
    }
    free( work );
    return sum;
}

int main() {
    int difficulty[] = {2, 4, 6, 8, 10};
    int profit[] = {10, 20, 30, 40, 50};
    int worker[] = {4, 5, 6, 7};
    int difficultySize = sizeof( difficulty ) / sizeof( difficulty[0] );
    int profitSize = sizeof( profit ) / sizeof( profit[0] );
    int workerSize = sizeof( worker ) / sizeof( worker[0] );
    int result = maxProfitAssignment( difficulty, difficultySize, profit, profitSize, worker, workerSize );
    printf( "maxProfitAssignment: %d\n", result );
    return 0;
}
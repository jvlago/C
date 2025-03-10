#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
====================
CountNodes
 Retorna a quantidade total de nós na árvore de forma recursiva.
====================
*/

int CountNodes( struct TreeNode* root ){
    if( !root ) return 0;
    return 1 + CountNodes( root->left ) + CountNodes( root->right );
}

/*
====================
Sums
 Calcula a soma dos valores de cada subárvore e armazena no array sum. 
====================
*/

int Sums( struct TreeNode* root, int* sum, int* i ){
    if ( !root ) return 0;
    int leftSum = Sums( root->left, sum, i );
    int rightSum = Sums( root->right, sum, i );
    sum[*i] = root->val + leftSum + rightSum;
    return sum[( *i )++];
}

/*
====================
Frequency
 Encontra as somas de subárvores mais frequentes e remove duplicatas.
====================
*/

void Frequency( int* sum, int* returnSize ) {
    int maxFreq = 0;
    int count = 0;
    int freq[*returnSize];
    for ( int i = 0; i < *returnSize; i++ ) {
        freq[i] = 0;
        for ( int j = 0; j < *returnSize; j++ ) {
            if ( sum[i] == sum[j] ) {
                freq[i]++;
            }
        }
        if ( freq[i] > maxFreq ) {
            maxFreq = freq[i];
            count = 1;
        } else if ( freq[i] == maxFreq ) {
            count++;
        }
    }
    int* result = ( int* )malloc( sizeof( int ) * count );
    int idx = 0;
    for ( int i = 0; i < *returnSize; i++ ) {
        if ( freq[i] == maxFreq ) {
            int isDuplicate = 0;
            for ( int k = 0; k < idx; k++ ) {
                if ( result[k] == sum[i] ) {
                    isDuplicate = 1;
                    break;
                }
            }
            if ( !isDuplicate ) {
                result[idx++] = sum[i];
            }
        }
    }
    *returnSize = idx;
    for ( int i = 0; i < idx; i++ ) {
        sum[i] = result[i];
    }
    free( result );
}

/*
====================
findFrequentTreeSum
 Calcula todas as somas de subárvores e retorna as mais frequentes. 
====================
*/

int* findFrequentTreeSum( struct TreeNode* root, int* returnSize ) {
    *returnSize = CountNodes( root );
    if ( *returnSize == 0 ) return NULL;
    int* sum = ( int* )malloc( sizeof( int ) * *returnSize );
    int i = 0;
    Sums( root, sum, &i );
    Frequency( sum, returnSize );
    return sum;
}

/*
====================
NewNode
 Cria um novo nó da árvore com o valor fornecido e retorna um ponteiro para ele.
====================
*/

struct TreeNode* NewNode( int val ) {
    struct TreeNode* node = ( struct TreeNode* )malloc( sizeof( struct TreeNode ) );
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*
====================
FreeTree
 Libera a memória alocada para todos os nós da árvore recursivamente.
====================
*/

void FreeTree( struct TreeNode* root ) {
    if ( !root ) return;
    FreeTree( root->left );
    FreeTree( root->right );
    free( root );
}

int main() {
    struct TreeNode* root = NewNode( 5 );
    root->left = NewNode( 14 );
    root->left->left = NewNode( 1 );
    int returnSize;
    int* result = findFrequentTreeSum( root, &returnSize );
    for ( int i = 0; i < returnSize; i++ ) {
        printf( "%d ", result[i] );
    }
    free( result );
    FreeTree( root );
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int** generate(int numRows, int* returnSize, int** returnColumnSizes);

int main() {
    int numRows;
    int returnSize;
    int* returnColumnSizes;
    do{
    printf("Digite a quantidade de linhas\n");
    scanf("%d",&numRows);
    }while(numRows < 1 || numRows > 30); // Para garantir que numRows estara entre 1 e 30
    int** tr = generate(numRows, &returnSize, &returnColumnSizes); // Gera a matriz
    for (int i = 0; i < returnSize; i++){
        for (int j = 0; j < returnColumnSizes[i]; j++){
            printf("%d ", tr[i][j]); // Printa cada valor do triângulo
        }
        printf("\n"); // Quebra de linha para quando pular a linha
    }
    for (int i = 0; i < returnSize; i++){ // Desaloca a memória
        free(tr[i]);
    }
    free(tr);
    free(returnColumnSizes);
    return 0;
}

int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int** r = (int**)malloc(numRows*sizeof(int*)); // Aloca memoria para as linhas
    *returnSize = numRows; // Envia a quantidade de linhas
    *returnColumnSizes = (int*)malloc(numRows*sizeof(int)); // Aloca o vetor de colunas
    for(int i = 0; i < numRows; i++){
        r[i] = (int*)malloc((i+1)*sizeof(int)); //Aloca memoria para as colunas
        (*returnColumnSizes)[i] = i + 1; // Envia a quantidade de elementos da coluna atual
            r[i][0] = 1; // Se for o primeiro elemento da coluna
            r[i][i] = 1; // Se for o último elemento da coluna
        for(int j = 1; j < i; j++){ // Laço sem o primeiro e último elemento
            r[i][j] = r[i-1][j]+r[i-1][j-1]; // Soma da regra do triângulo de pascal
        }
    }
    return r;
}
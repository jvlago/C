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
    }while(numRows < 1 || numRows > 30);
    int** tr = generate(numRows, &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; i++){
        for (int j = 0; j < returnColumnSizes[i]; j++){
            printf("%d ", tr[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < returnSize; i++){
        free(tr[i]);
    }
    free(tr);
    free(returnColumnSizes);
    return 0;
}

int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int** r = (int**)malloc(numRows*sizeof(int*));
    *returnSize = numRows;
    *returnColumnSizes = (int*)malloc(numRows*sizeof(int));
    for(int i = 0; i < numRows; i++){
        r[i] = (int*)malloc((i+1)*sizeof(int));
        (*returnColumnSizes)[i] = i + 1;
            r[i][0] = 1;
            r[i][i] = 1;
        for(int j = 1; j < i; j++){
            r[i][j] = r[i-1][j]+r[i-1][j-1];
        }
    }
    return r;
}
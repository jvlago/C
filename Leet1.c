/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* saida = (int*)malloc(2*sizeof(int));
    *returnSize = 2;
    if (saida == NULL){
    printf("Erro\n");
    return NULL;
    }
    for(int i = 0; i < numsSize; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if(nums[i] + nums[j] == target){
                saida[0] = i;
                saida[1] = j;
                return saida;
            }
        }
    }
    return NULL;
}
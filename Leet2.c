/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdio.h>
#include <stdlib.h>
struct ListNode {
      int val;
      struct ListNode *next;
};
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* aux = (struct ListNode*) malloc(sizeof(struct ListNode));
    struct ListNode* soma = aux;
    aux->next=NULL;
    int lista1=0, lista2=0, v1=0;
    do{
        if (l1 != NULL) {
            lista1 = l1->val;
            l1 = l1->next;
        }
        else lista1 = 0;
        if (l2 != NULL) {
            lista2 = l2->val;
            l2 = l2->next;
        }
        else lista2 = 0;
        aux->val = lista1 + lista2 + v1;
        v1=0;
        if(aux->val >= 10){
            aux->val = aux->val-10;
            v1++;
        }
        if(l1 != NULL || l2 != NULL || v1 !=0)
        {
            aux->next=malloc(sizeof(struct ListNode)); 
            aux->next->next=NULL;
            aux = aux->next;
        }
    }while(l1 != NULL || l2 != NULL || v1 !=0);
    return soma;
}
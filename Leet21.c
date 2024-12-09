#include <stdio.h>
#include <stdlib.h>
struct ListNode {
    int val;
    struct ListNode *next;
    };
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode* aux = malloc(sizeof(struct ListNode));
    struct ListNode* head = aux;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            aux->next = list1;
            list1 = list1->next;
        } else {
            aux->next = list2;
            list2 = list2->next;
        }
        aux = aux->next;
    }

    if(list1==NULL) aux->next=list2;
    else if(list2==NULL) aux->next=list1;

    return head->next;
}
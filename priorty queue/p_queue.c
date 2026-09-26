#include"p_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "../myAlloc/myAlloc.h"

static inline int findTop(unsigned short block) {
for (int i = 0 ; i < 16 ; i++) {
        if ((block >> i) & 1) 
            return i;
    }

    return -1;
}

void initialQ(pQueue_t *q) {
    for (int i = 0 ; i < pqMAX ; i++) {
        
        q -> priority[i].head = NULL;
        q -> priority[i].tail = NULL;
        q -> priority[i].size = 0;
    }
    for (int i = 0; i < pqBlock; i++) 
        q -> number[i] = 0;
    q -> block = 0;
}

void insertQ(pQueue_t *q, int grade, void *data) {
    qNode_t *newNode = (qNode_t*)myAlloc(sizeof(qNode_t));
    if (newNode == NULL) return;
    newNode -> data = data;
    newNode -> next = NULL;
    qList_t *List = &(q -> priority[grade]);
    
    unsigned short b = grade / 16;
    unsigned short n = grade % 16;
    if (!List -> head) { //本身是新的priority queue
        q -> number[b] = q -> number[b] | (1 << n);
        q -> block = q -> block | (1 << b);
        List -> head = newNode;
        List -> tail = newNode;
    }
    else {
        List -> tail -> next = newNode;
        List -> tail = newNode;
    }

    List -> size++;
}

void *deleteQ(pQueue_t *q) {
    int b = findTop(q -> block);
    if (b == -1) return NULL;
    int n = findTop(q -> number[b]);

    int grade = b * pqNumber + n;
    qList_t *List = &(q -> priority[grade]);
    qNode_t *deleteNode = List -> head;;
    void *retV = deleteNode -> data;

    List -> head = deleteNode -> next;
    List -> size--;
    myFree(deleteNode); 

    if (!List -> head)  {
        List -> tail = NULL;
        q -> number[b] = q -> number[b] & ~( 1 << n);
        if (q -> number[b] == 0) {
            q -> block = q -> block & ~(1 << b);
        }
    }
    return retV;

}
#include <stdio.h>
#include "myAlloc/myAlloc.h"       // 包含 myAlloc 的 "菜單"
#include "priorty queue/p_queue.h"  // 包含 p_queue 的 "菜單"

// 假設 p_queue.h 裡有 pQueue_t, initialQ, insertQ, deleteQ

int main() {
    printf("Starting Priority Queue Test...\n");
    
    // 1. 宣告一個佇列
    pQueue_t myQueue;
    
    // 2. 初始化 (它會去呼叫 p_queue.c 裡的 initialQ)
    initialQ(&myQueue);

    // 3. 測試插入 (它會去呼叫 p_queue.c 裡的 insertQ, 
    //    而 insertQ "內部" 會去呼叫 myAlloc.c 裡的 myAlloc)
    int dataA = 100;
    insertQ(&myQueue, 5, &dataA);
    printf("Inserted data (grade 5)\n");    int dataB = 200;
    insertQ(&myQueue, 1, &dataB);
    printf("Inserted data (grade 1)\n");

    // 4. 測試刪除
    int* result = (int*)deleteQ(&myQueue);
    
    if (result != NULL && *result == 200) {
        printf("Deleted highest priority (grade 1), value: %d\n", *result);
    } else {
        printf("Deletion failed!\n");
    }

    // (myFree 會在 deleteQ 內部被呼叫)

    return 0;
}
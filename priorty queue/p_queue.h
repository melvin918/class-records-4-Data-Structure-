#ifndef pQueue_H
#define pQueue_H
#define pqMAX 256
#define pqBlock 16
#define pqNumber 16

// priority queue MAX = 256
// grade = 0 是最高級(MSB)，grade = 255 是最低級(LSB)

typedef struct qNode {
    void *data;
    struct qNode *next;
};
typedef struct qNode qNode_t;

typedef struct qList {
    int size;
    qNode_t *head;
    qNode_t *tail;
};
typedef struct qList qList_t;

// 將每 256 級分成 16 個 block，每個 block 有 16 級
// 每個 block / number 都是 16 Bits 的信號，由 1 跟 0 兩個數字組成，0 代表沒東西，1 則代表有
typedef struct pQueue {
    qList_t priority[pqMAX];
    unsigned short block;
    unsigned short number[pqBlock];
};
typedef struct pQueue pQueue_t;

void initialQ(pQueue_t *q);
void insertQ(pQueue_t *q, int grade, void *data); 
void *deleteQ(pQueue_t *q);

#endif // priority queue_H
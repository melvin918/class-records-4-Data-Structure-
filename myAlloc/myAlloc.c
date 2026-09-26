#include "myAlloc.h"
#include <stdio.h>
#define total_space_size 65536 

// 要一塊連續的 64KB 的記憶體 (因為 char 是 1 byte)
static char g_memory_arena[total_space_size];


// 用來記我總共大小 (64KB) 目前哪一塊被分配出去
// size 總共大小
// is_free 這塊記憶體目前有沒有人使用，1 表示空的，0 表示有東西
// nexT 將記憶體串一起
typedef struct block{
    size_t size; 
    int is_free;
    struct block *next;
};
typedef struct block block_t;


// 永遠指向第一塊位置 (0號位置)
static block_t *first_block_head = NULL;


// 把所有的記憶體空間(64KB)轉型成 block_t
static void init_Memory() {

    first_block_head = (block_t*)g_memory_arena;

    first_block_head -> size = total_space_size;
    first_block_head -> is_free = 1;
    first_block_head -> next = NULL;
}

void *myAlloc (size_t space_request) {
    if (!first_block_head ) 
        init_Memory();

    size_t total_need = space_request + sizeof(block_t);

    block_t *nowSpace = first_block_head;
    while (nowSpace) {
        if (nowSpace -> size >= total_need && nowSpace -> is_free) {

            size_t remain_size = nowSpace -> size - total_need;
            
            if (remain_size > sizeof(block_t)) {
                block_t *new_free_block = (block_t*)((char*)nowSpace + total_need);
                
                new_free_block -> size = remain_size;
                new_free_block -> is_free = 1;
                new_free_block -> next = nowSpace -> next;
                
                nowSpace -> size = total_need;
                nowSpace -> next = new_free_block;
            }

            nowSpace -> is_free = 0;
            return (void*)(nowSpace + 1);
        }
        nowSpace = nowSpace -> next;
    }
    return NULL;

}

void myFree (void *ptr) {
    if (!ptr) return;
    
    block_t *free_ptr = (block_t*)ptr - 1;

    free_ptr -> is_free = 1;
    block_t *next_block = free_ptr-> next;

    if (next_block && next_block -> is_free) {
        free_ptr -> size = free_ptr -> size + next_block -> size;
        free_ptr -> next = next_block -> next;
    }
        
}
#include "os_malloc.h"
#include "os_def.h"
#include "os_type.h"

struct block
{
    struct block *next;
    uint32_t size;
};

typedef struct block block_t;

#define min_block_size (sizeof(block_t) + 8)

struct memory_area
{
    void *start;
    void *end;
    uint32_t total;
    uint32_t free;
    block_t firstblock;
    block_t end_block;
};
typedef struct memory_area HEAP_T;

volatile HEAP_T g_heap;

static uint32_t Align(uint32_t size, uint32_t len)
{
    uint32_t align_len;
    if ((len % size) != 0)
    {
        align_len = (len / size + 1) * size;
        return align_len;
    }
    else
    {
        return len;
    }
}
/***************************移除一个block，从单链表上面***************/
static block_t *remove_block(block_t *prev_block, block_t *free_block)
{
    if (prev_block == OS_NULL || free_block == OS_NULL)
    {
        osPrintf("remove_block parar error\n");
        return (block_t *)-1;
    }
    prev_block->next = free_block->next;
    free_block->next = (block_t *)0;
    return free_block;
}

/****************************拆分一个block，从一个已经不再链表上的block**/
/****************************总是返回低地址，剩下高地址再次插入链表******/
static block_t *split_block(block_t *block, uint32_t size)
{

    block_t *next_block;
    if (block == OS_NULL || size == 0)
    {
        osPrintf("split_block parar error\n");
        return (block_t *)-1;
    }

    next_block = (block_t *)((uint8_t *)block + size);
    next_block->size = block->size - size;
    block->size = size;
    return next_block;
}

/*********************插入一个block到链表上，prev为要插入的前一个block指针**/
static int32_t insert_block(block_t *prev_block, block_t *free_block)
{
    block_t *next_block;
    if (prev_block == OS_NULL || free_block == OS_NULL)
    {
        osPrintf("insert_block parar error\n");
        return -1;
    }

    if (((uint8_t *)prev_block + prev_block->size) == (uint8_t *)free_block)
    {
        prev_block->size = prev_block->size + free_block->size;
        free_block->next = (block_t *)0;
        free_block->size = 0;
    }
    else
    {
        next_block = prev_block->next;
        prev_block->next = free_block;
        free_block->next = next_block;
    }
    return 0;
}
/********************合并两个block****************************************/
static block_t *merge_block(block_t *prev_block, block_t *curr_block)
{
    prev_block->size = prev_block->size + curr_block->size;
    return prev_block;
}

void osHeapInit(uint32_t *start, uint32_t *end)
{

    if (start == OS_NULL || end == OS_NULL || ((uint32_t)start > (uint32_t)end))
        return -1;

    g_heap.start = start;
    g_heap.end = end;
    g_heap.total = g_heap.free = (uint32_t)end - (uint32_t)start;

    g_heap.firstblock.size = 0;
    g_heap.firstblock.next = (block_t *)start;
    g_heap.end_block.size = 0;
    g_heap.end_block.next = (block_t *)0;

    g_heap.firstblock.next->next = &(g_heap.end_block);
    g_heap.firstblock.next->size = g_heap.total;
}

void *osMalloc(uint32_t size)
{
    HEAP_T *heap = &g_heap;
    block_t *last_block = &heap->end_block;
    block_t *prev_block = &heap->firstblock;
    block_t *free_block = prev_block->next;
    block_t *return_block = OS_NULL;
    uint32_t real_size = Align(8, size) + sizeof(block_t);
    uint8_t *ptr = OS_NULL;

    if (size == 0)
    {   
        osPrintf("malloc parar error\n");
        return (int *)-1;
    }
   
    while (free_block->size < real_size)
    {
        prev_block = free_block;
        free_block = prev_block->next;

        if (free_block == last_block)
            return (void *)-1;
    }

    if ((free_block->size - real_size) > min_block_size)
    {
        remove_block(prev_block, free_block);
        return_block = split_block(free_block, real_size);
        insert_block(prev_block, return_block);
    }
    else
    {
        remove_block(prev_block, free_block);
    }
    heap->free -= real_size;
    ptr = (uint8_t *)free_block;
    ptr = ptr + sizeof(block_t);
    return (void *)ptr;
}

void osFree(void *ptr)
{
    HEAP_T *heap = &g_heap;
    block_t *last_block = &heap->end_block;
    block_t *prev_block = &heap->firstblock;
    block_t *free_block = prev_block->next;
    block_t *curr_block = (block_t *)((uint8_t *)ptr - sizeof(block_t));
    heap->free += curr_block->size;
    if (ptr == OS_NULL)
    {
        return;
    }

    while (((uint32_t)free_block < (uint32_t)curr_block) && (free_block != last_block))
    {
        prev_block = free_block;
        free_block = prev_block->next;
    }

    if (((uint8_t *)curr_block + curr_block->size) == (uint8_t *)free_block)
    {
        remove_block(prev_block, free_block);
        merge_block(curr_block, free_block);
    }

    insert_block(prev_block, curr_block);
    return;
}

void osHeapInfo(void)
{
    HEAP_T *heap = &g_heap;
    block_t *free_block = heap->firstblock.next;
    block_t *end_block = &heap->end_block;
    int i = 1;
    osPrintf("-----------------------------memory info------------------------------\n");
    osPrintf("total size-----------------free size--------------------use size------\n");
    osPrintf("%d-------------------------%d---------------------------%d------------\n",heap->total, heap->free, heap->total - heap->free);
    while(free_block != end_block)
    {
      osPrintf("the %d block start address:0x%x:size:0x%x\n",i++, (uint32_t)free_block, free_block->size);
      free_block = free_block->next;
    }
}

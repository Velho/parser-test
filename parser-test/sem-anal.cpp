#include "sem-anal.h"
#include "token.h"

#include <string.h>
#include <stdlib.h>

#define SEM_HEAP_SIZE   8192

//
// Dynamic array for the 
//

//
// TODO : Fix the pointer to pointer Heap.
//
typedef struct {
    SemClas* sem_heap;
    size_t sem_count;
    size_t sem_capacity;
} SemDynamicTable;

SemDynamicTable g_DynamicTable = { };


static void SemInsertTable(SemDynamicTable* table, SemClas* clas)
{
    // Handle the capacity.
    if (table->sem_capacity <= table->sem_count)
    {
        // Double the capacity.
        table->sem_capacity = table->sem_capacity * 2;
        // TODO : Decipher the msvc C6308
        table->sem_heap = (SemClas*)realloc(table->sem_heap, table->sem_capacity * sizeof(SemClas));
    }

    // Insert the given clas.
    memcpy(&table->sem_heap[table->sem_count++], clas, sizeof(SemClas));
}

static SemClas* SemAlloc(Token* /* tok_clas */, void* /* data */)
{
    SemClas* semobject = (SemClas*)malloc(sizeof(SemClas));

    // Manage the allocations in the dynamic table.
    SemInsertTable(&g_DynamicTable, semobject);

    return semobject;
}

void SemInit()
{
    g_DynamicTable.sem_capacity = 1;
    g_DynamicTable.sem_heap = (SemClas*)realloc(g_DynamicTable.sem_heap, g_DynamicTable.sem_capacity * sizeof(SemClas));

    if (g_DynamicTable.sem_heap == NULL)
    {
        // Error handling.
    }
}

void SemRelease()
{
    size_t idx;

    for (idx = 0; idx < g_DynamicTable.sem_count; idx++)
    {
        free(&g_DynamicTable.sem_heap[idx]);
    }

    // Free the realloc struct?
    free(g_DynamicTable.sem_heap);
}

SemClas* SemAssignToken(Token* tok_clas, void* data)
{
    SemClas* semobject = SemAlloc(tok_clas, data);

    return semobject;
}


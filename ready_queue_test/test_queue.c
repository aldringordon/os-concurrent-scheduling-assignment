/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: test_queue.c
 * Purpose: test the behaviour of ready_queue.c
 * to make sure it works and functions properly before
 * proceeding with any of the other code
 */
#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"
#include "task.h"
#include "ready_queue.h"

ReadyQueue* readFile(FILE* file)
{
    ReadyQueue* queue;
    int size = 10;
    createReadyQueue(&queue, size);

    printf("created queue, capacity = %d, size = %d\n", queue->max_size, queue->size);

    Task* task;
    task = (Task*)malloc(sizeof(Task));

    int numRead = 0;
    int done = FALSE;

    while(done != TRUE)
    {
        if(numRead == 11)
        {
            done = TRUE;
        }
        else
        {
            fscanf(file, "%d %d\n", &task->n, &task->burst);
            numRead++;
            printf("%d read: %d %d\n", numRead, task->n, task->burst);
            addTask(&queue, task);
        }
    }

    return queue;
}

int main(int argc, char*argv[])
{
    FILE* file;
    ReadyQueue* queue;
    file = fopen("task_file", "r");
    queue = readFile(file);
    fclose(file);

    Task* task;

    printf("size of queue before getTask() calls: %d\n\n", queue->size);
    for(int i = 0; i < 10; i++)
    {
        task = getTask(&queue);
        printf("\t%d = task #%d burst:%d\n", i, task->n, task->burst);
    }
    printf("\nsize after: %d\n", queue->size);
}

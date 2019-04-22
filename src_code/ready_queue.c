/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: ready_queue.c
 * Purpose: Contains methods related to Ready-Queue
 * which contains a list of tasks to be serviced by the CPUs
 *
 * Has a capacity of 'm' tasks and initially set to empty
 *
 * based off linkedList.c from COMP1000 Unix & C Programming
 * included in ~/reference_code
 *
 * modified to be a doubly linked list
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "task.h"
#include "boolean.h"

/**
 * Create empty ready_queue with defined capacity
 * @param size = capacity of ready_queue tasks
 */
void createReadyQueue(ReadyQueue** queue, int size)
{
    *queue = (ReadyQueue*)malloc(sizeof(ReadyQueue));
    (*queue)->head = NULL;
    (*queue)->tail = NULL;
    (*queue)->max_size = size;
    (*queue)->size = 0;
}

/**
 * Add a task to Ready-Queue
 *
 * @param queue = the ReadyQueue
 * @param task = task to be added
 *
 * @return int = boolean:
 * - TRUE : task was added
 * - FALSE : ReadyQueue is full and task not added
 *
 */
int addTask(ReadyQueue** queue, Task* task)
{
    /* if number of tasks < capacity */
    if((*queue)->size < (*queue)->max_size)
    {
        ReadyQueueTask* newNode;
        Task* newTask;

        newNode = (ReadyQueueTask*)malloc(sizeof(ReadyQueueTask));
        newTask = (Task*)malloc(sizeof(Task));
        *newTask = *task;
        newNode->task = newTask;

    /* if the queue is empty */
        if((*queue)->head == NULL && (*queue)->tail == NULL)
        {
            (*queue)->head = newNode; /* point head to first new node, only updates when a node is removed from the queue */
            newNode->prev = NULL;
        }
        else /* otherwise */
        {
            newNode->prev =  (*queue)->tail;
        }
        newNode->next = NULL; /* default when adding to end */

        (*queue)->tail->next = newNode; /* point old tail to new node */
        (*queue)->tail = newNode; /* point tail to new node */
        (*queue)->size++;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

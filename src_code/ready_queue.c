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
 * modified to be a double ended, doubly linked list
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"
#include "task.h"
#include "ready_queue.h"

/**
 * free node memory
 * @param node node to be deleted
 */
void freeNode(ReadyQueueNode* node)
{
    free(node);
}

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
    (*queue)->jobs_left = 1;
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
        ReadyQueueNode* newNode;
        Task* newTask;

        newNode = (ReadyQueueNode*)malloc(sizeof(ReadyQueueNode));
        newTask = (Task*)malloc(sizeof(Task));

        *newTask = *task;
        newNode->task = newTask;;

    /* if the queue is empty */
        if((*queue)->size == 0)
        {
            (*queue)->head = newNode; /* point head to first new node, only updates when a node is removed from the queue */
            (*queue)->tail = newNode;
            newNode->prev = NULL;
        }
        else /* otherwise */
        {
            newNode->prev = (*queue)->tail; /* point newNode.prev to tail */
            (*queue)->tail->next = newNode; /* point tail.next to newNode */
            (*queue)->tail = newNode; /* point tail to newNode */
        }
        newNode->next = NULL; /* default when adding to end */

        (*queue)->size++;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void signalEmptyJobPool(ReadyQueue** queue)
{
    (*queue)->jobs_left = 0;
}

/**
 * returns and remove first task in queue (FIFO)
 * @param  task empty task struct to return fields to
 */
Task* getTask(ReadyQueue** queue)
{
    Task* task;
    if((*queue)->size > 0)
    {
        task = (*queue)->head->task; /* return first task */

        printf("getTask() called: #: %d BURST: %d\n", task->n, task->burst);

        if((*queue)->size == 1)
        {
            freeNode((*queue)->head);
            (*queue)->head = NULL;
            (*queue)->tail = NULL;
        }
        else
        {
            (*queue)->head = (*queue)->head->next; /* point head to head.next */
            freeNode((*queue)->head->prev); /* free original head node (head.prev) */
            (*queue)->head->prev = NULL; /* set new head.prev = null */
        }

        (*queue)->size--;
    }
    else
    {
        task = NULL;
    }
    return task;
}

/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: ready_queue.h
 * Purpose: header file for ready_queue.c
 * contains queue related structs
 *
 * based off list.h from COMP1000 Unix & C Programming
 * included in ~/reference_code
 *
 */
#ifndef READY_QUEUE_H
#define READY_QUEUE_H

typedef struct ReadyNode
{
    void* task;
    struct ReadyNode* next;
    struct ReadyNode* prev;
} ReadyQueueNode;

typedef struct
{
    int max_size;
    int size;
    int jobs_left; /* 0 if no more jobs in Job-Queue, 1 otherwise */
    ReadyQueueNode* head;
    ReadyQueueNode* tail;
} ReadyQueue;

#endif

void createReadyQueue(ReadyQueue** queue, int size, int jobs);
int addTask(ReadyQueue** queue, Task* task);
Task* getTask(ReadyQueue** queue);
void signalEmptyJobPool(ReadyQueue** queue);

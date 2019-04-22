/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: queue.h
 * Purpose: header file for ready_queue.c
 * contains queue related structs
 *
 * based off list.h from COMP1000 Unix & C Programming
 * included in ~/reference_code
 *
 */
#ifndef READY_QUEUE_H
#define READY_QUEUE_H

typedef struct Node
{
    void* task;
    struct Node* next;
    struct Node* prev;
} ReadyQueueNode;

typedef struct
{
    int max_size;
    int size;
    ReadyQueueNode* head;
    ReadyQueueNode* tail;
} ReadyQueue;

#endif

void createReadyQueue(ReadyQueue** queue, int size);
int addTask(ReadyQueue** queue, Task* task);
Task* getTask(ReadyQueue** queue);

/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: job_queue.h
 * Purpose: header file for job_queue.c
 * contains related structs and accessible methods
 */
#ifndef JOB_QUEUE_H
#define JOB_QUEUE_H

typedef struct Node
{
    void* task;
    struct Node* next;
} JobQueueNode;

typedef struct
{
    int size;
    JobQueueNode* head;
    JobQueueNode* tail;
} JobQueue;

#endif

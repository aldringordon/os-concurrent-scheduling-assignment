/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: job_queue.c
 * Purpose: Implementation of Job-Queue which
 * stores all the tasks from task_file.
 * The Job-Queue is accessed by the function task() in scheduler.c when
 * it requests 2 tasks to be put into the Ready-Queue.
 *
 * Only needs to be a double ended, singly linked list
 * as the jobs are accessed from the front sequentially
 * and new jobs are added to the end of the list each time
 */

/**
 * create empty job queue
 * @param queue
 */
#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "job_queue.h"
#include "boolean.h"

#define TASK_FILE "task_file" /* constant, name of task file to read from */

void createJobQueue(JobQueue** queue)
{
    *queue = (JobQueue*)malloc(sizeof(JobQueue));
    (*queue)->head = NULL;
    (*queue)->tail = NULL;
    (*queue)->size = 0;
}

/**
 * add a job to the queue
 * @param queue
 * @param job = task from task_file
 */
void addJob(JobQueue** queue, Task* job)
{
    JobQueueNode* newNode;
    Task* newJob;

    newNode = (JobQueueNode*)malloc(sizeof(JobQueueNode));
    newJob = (Task*)malloc(sizeof(Task));
    *newJob = *job;
    newNode->task = newJob;
    newNode->next = NULL;

    if((*queue)->size == 0)
    {
        (*queue)->head = newNode;
        (*queue)->tail = newNode;
    }
    else
    {
        (*queue)->tail->next = newNode; /* point tail.next to new node */
        (*queue)->tail = newNode; /* point tail to new node */
    }

    (*queue)->size++;
}

/**
 * frees the node memory
 * @param node
 */
void freeNode(JobQueueNode* node)
{
    free(node);
}

/**
 * remove and return a job from the queue
 * @param  queue
 * @return
 */
Task* getJob(JobQueue** queue)
{
    Task* job;
    JobQueueNode* curr;
    if((*queue)->size == 0)
    {
        job = NULL;
    }
    else
    {
        job = (*queue)->head->task;

        if((*queue)->size == 1)
        {
            freeNode((*queue)->head);
            (*queue)->head = NULL;
            (*queue)->tail = NULL;
        }
        else
        {
            curr = (*queue)->head; /* point curr to head */
            (*queue)->head = (*queue)->head->next; /* point head to head.next */
            freeNode(curr); /* free curr */
        }
        (*queue)->size--;
    }
    return job;
}

void readJobs(JobQueue** queue)
{
    FILE* file = fopen(TASK_FILE, "r");
    int done = FALSE;
    Task* task = (Task*)malloc(sizeof(Task));

    if(file == NULL)
    {
        printf("Error Opening \"task_file\"\n");
    }
    else
    {
        while(done != TRUE)
        {
            if(fscanf(file, "%d %d\n", &task->n, &task->burst) == EOF)
            {
                done = TRUE;
            }
            else
            {
                addJob(queue, task);
            }
        }
    }
    free(task);
    fclose(file);
}

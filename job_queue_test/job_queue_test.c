/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: job_queue_test.c
 * Purpose: test job_queue.c
 * to make sure it works as intended
 */

#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"
#include "task.h"
#include "job_queue.h"

int main(int argc, char* argv[])
{
    JobQueue* queue;
    createJobQueue(&queue);
    readJobs(&queue);

    Task* task;
    printf("size of job_queue before getJob() calls: %d\n", queue->size);

    int total_jobs = queue->size;
    for(int i = 0; i < total_jobs; i++)
    {
        task = getJob(&queue);
        printf("JOBS_LEFT: %d -- ", queue->size);
        printf("%d read: %d %d\n", i+1, task->n, task->burst);

    }
    printf("\t size after: %d\n", queue->size);
}

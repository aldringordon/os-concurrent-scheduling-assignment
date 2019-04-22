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

JobQueue* readFile(FILE* file)
{
    JobQueue* queue;
    createJobQueue(&queue);

    printf("created job queue size: %d\n", queue->size);

    Task* task = (Task*)malloc(sizeof(Task));

    int numRead = 0;
    int done = FALSE;

    while(done != TRUE)
    {
        if(numRead == 100)
        {
            done = TRUE;
        }
        else
        {
            fscanf(file, "%d %d\n", &task->n, &task->burst);
            numRead++;
            if(numRead%10 == 0)
            {
                printf("%d read: %d %d\n", numRead, task->n, task->burst);
            }
            addJob(&queue, task);
        }
    }

    return queue;
}

int main(int argc, char* argv[])
{
    FILE* file;
    JobQueue* queue;
    file = fopen("task_file", "r");
    queue = readFile(file);
    fclose(file);

    Task* task;

    printf("size of job_queue before getJob() calls: %d\n", queue->size);
    for(int i = 1; i < 101; i++)
    {
        task = getJob(&queue);
        if(i%10==0)
        {
            printf("%d read: %d %d\n", i, task->n, task->burst);
        }
    }
    printf("\t size after: %d\n", queue->size);
}

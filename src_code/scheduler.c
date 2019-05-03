/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: scheduler.c
 * Purpose: Main Program that contains the tasks
 * in the assignment specification.
 *
 * Should be called as:
 *  $ ./scheduler task_file m
 *
 * Specified required functions:
 *  - task() : gets two tasks at a time and puts
 *  it into the Ready_Queue
 *  - cpu() : simulates the operations of the CPUs
 *
 * References have been annotated at each line with an
 * index to the specification at the end of the program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* Reference #2 */
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h> /* Reference #3 */

#include "task.h"
#include "job_queue.h"
#include "ready_queue.h"
#include "data.h"
#include "boolean.h"

#define NUM_THREADS 4 /* task, CPU-1, CPU-2, CPU-3 */

/* shared data between threads */
int num_tasks;
int total_waiting_time;
int total_turnaround_time;

pthread_mutex_t queue_lock;
pthread_mutex_t cpu_lock;

pthread_cond_t no_tasks;
pthread_cond_t tasks;

/* job pool */
JobQueue* job_queue;

/**
 * takes a task from ready_queue and executes for
 * its "entire cpu burst" sleep(burst/10)
 * @param ready_queue [description]
 */
void* cpu(void* shared_data)
{
    Task *task = NULL;
    Data* data = (Data*)shared_data;
    ReadyQueue** ready_queue = data->queue;
    printf("call to CPU(%d)\n", data->thread_id);

    do
    {
        while(pthread_cond_wait(&tasks, &queue_lock)) {/*no-op*/}

        pthread_mutex_lock(&queue_lock); /* arrival of tasks */

        task = getTask(ready_queue);

        if(task == NULL)
        {
            pthread_cond_signal(&no_tasks);
        }
        pthread_mutex_unlock(&queue_lock);


    }while(TRUE);

    pthread_exit(NULL);
}

/**
 * places files from the Job-Queue into the Ready-Queue
 * @param job_queue list of jobs to be added to ready_queue
 */
void* task(void* shared_data)
{
    Task *task1, *task2;
    Data* data = (Data*)shared_data;
    ReadyQueue** ready_queue = data->queue;
    printf("call to task(%d)\n", data->thread_id);

    printf("TASK() ready_queue jobs_left: %d\n", (*ready_queue)->jobs_left);
    do
    {
        task1 = getJob(&job_queue);
        if(task1 != NULL)
        {
            /* sim_log */
        }

        task2 = getJob(&job_queue);
        if(task2 != NULL)
        {
            /* sim_log */
        }

        if(task1 == NULL && task2 == NULL)
        {
            break;
        }

        pthread_mutex_lock(&queue_lock);
        if(addTask(ready_queue, task1) == TRUE)
        {
            /* sim_log */
        }

        if(addTask(ready_queue, task2) == TRUE)
        {
            /* sim_log */
        }
        pthread_mutex_unlock(&queue_lock);

        pthread_cond_signal(&tasks);

        while(pthread_cond_wait(&no_tasks)) {/*no-op*/}

    }while(TRUE);

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    /* ./scheduler filename m */
    char* filename; /* argv[1] */
    int m; /* argv[2] */

    int i, rc;

    ReadyQueue* ready_queue;

    pthread_t threads[NUM_THREADS];
    Data thread_data[NUM_THREADS];

    /* initialize shared data */
    num_tasks = 0;
    total_waiting_time = 0;
    total_turnaround_time = 0;

    /* initialize mutex lock */
    pthread_mutex_init(&queue_lock, NULL); /* Reference #5 */
    pthread_mutex_init(&cpu_lock, NULL);

    /* initialize condition variables */
    pthread_cond_init(&tasks, NULL);
    pthread_cond_init(&no_tasks, NULL);

    if(argc < 3)
    {
        printf("Error - Usage: ./scheduler task_file m\n");
        return EXIT_FAILURE; /* Reference #1 */
    }
    else
    {
        m = atoi(argv[2]);
        filename = argv[1];

        printf("Ready-Queue Size: %d\n", m);
        printf("task_file filename: %s\n", filename);

        /* create a simulation_log */
        system("rm -rf simulation_log");
        system("echo SIMULATION LOG >> simulation_log");

        /* create Job-Queue*/
        printf("Initializing Job-Queue\n");
        createJobQueue(&job_queue);
        readJobs(&job_queue, filename);

        /* create Ready-Queue */
        printf("Initializing Ready-Queue\n");
        createReadyQueue(&ready_queue, m, job_queue->size);

        /* create 4 threads: 1 for task, 3 for cpus */
        printf("Generating threads\n");
        for(i = 0; i < NUM_THREADS; i++) /* Reference #5 */
        {
            thread_data[i].thread_id = i;
            thread_data[i].queue = &ready_queue;
            if(i == 0) /* task thread */
            {
                if((rc = pthread_create(&threads[i], NULL, task, &thread_data[i])))
                {
                    fprintf(stderr, "Error: pthread_create, rc: %d\n", rc);
                    return EXIT_FAILURE;
                }
            }
            else /* cpu threads */
            {
                if((rc = pthread_create(&threads[i], NULL, cpu, &thread_data[i])))
                {
                    fprintf(stderr, "Error: pthread_create, rc: %d\n", rc);
                    return EXIT_FAILURE;
                }
            }
        }

        /* block until all thread complete
        Reference #4
        */
        for(i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(threads[i], NULL);
        }
        printf("Joined threads\n");

        /* cleanup */
        pthread_mutex_destroy(&queue_lock);
        pthread_mutex_destroy(&cpu_lock);
        pthread_cond_destroy(&tasks);
        pthread_cond_destroy(&no_tasks);
        free(job_queue);
        free(ready_queue);
    }

    return EXIT_SUCCESS; /* See Reference #1 */
}

/**
 * References:
 *
 * #1: https://stackoverflow.com/questions/9549342/should-i-return-0-or-1-for-successful-function
 *      "For greater portability, you can use the macros EXIT_SUCCESS and
 *      EXIT_FAILURE for the conventional status value for success and failure,
 *      respectively. They are declared in the file stdlib.h.""
 *
 * #2: https://www.tutorialspoint.com/c_standard_library/time_h.htm
 *      For time and date related methods.
 *
 * #3: https://www.geeksforgeeks.org/use-posix-semaphores-c/
 *      Using posix semaphores
 *
 * #4: https://randu.org/tutorials/threads/
 *      Example program using pthread functions
 *
 * #5: https://randu.org/tutorials/threads/
 *      Multithreaded Programming - pthread Mutexes
 */

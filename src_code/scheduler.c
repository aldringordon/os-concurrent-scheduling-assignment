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
#include <std.io>
#include <stdlib.h>
#include <time.h> /* Reference #2 */
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h> /* Reference #3 */

int num_tasks, total_waiting_time, total_turnaround_time;
ReadyQueue* ready_queue;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

/**
 * places files from the Job-Queue into the Ready-Queue
 * @param job_queue list of jobs to be added to ready_queue
 */
void* task(JobQueue** job_queue)
{
    Task* task;
    do
    {
        if((*job_queue)->size > 1)
        {
            task = getJob(job_queue);
            addTask(&ready_queue, task);
        }
        // OUTPUT TO SIMLOG

        pthread_cond_wait(&empty, &mutex);
        pthread_mutex_lock(&mutex);

        if((*job_queue)->size > 1)
        {
            task = getJob(job_queue);
            addTask(&ready_queue, task);
            // OUTPUT TO SIMLOG
        }

        task = getJob(job_queue);
        addTask(&ready_queue, task);
        // OUTPUT TO SIMLOG

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&full, &mutex);


    }while((*job_queue)->size != 0);

    signalEmptyJobPool(&ready_queue);
}

/**
 * takes a task from ready_queue and executes for
 * its "entire cpu burst" sleep(burst/10)
 * @param ready_queue [description]
 */
void* cpu()
{
    Task *task;
    do
    {
        pthread_cond_wait(&full, &mutex);
        pthread_mutex_lock(&mutex);

        task1 = getTask(&ready_queue);
        // OUTPUT SERVICE_TIME TO SIMLOG

        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&empty, &mutex);

        sleep((task->)/25);
        // OUTPUT COMPLETITION_TIME TO SIMLOG
        free(task);

    }while(*ready_queue->jobs_left != 0);
}

int main(int argc, char* argv[])
{
    JobQueue* job_queue;

    num_tasks = 0;
    total_waiting_time = 0;
    total_turnaround_time = 0;

    if(argc < 3)
    {
        printf("Error - Usage: ./scheduler task_file m\n");
        return EXIT_FAILURE; /* See Reference #1 */
    }
    else
    {
        /* create Job-Queue*/
        createJobQueue(&job_queue);

        /* create Ready-Queue */
        createReadyQueue(&ready_queue, argv[2]); /* argv[2] = m (capacity) */

        /* create 4 threads: 1 for task, 3 for cpus */
        pthread_create(&task, NULL , task, &job_queue);
        pthread_create(&cpu1, NULL , cpu, NULL);
        pthread_create(&cpu2, NULL , cpu, NULL);
        pthread_create(&cpu3, NULL , cpu, NULL);

        /* block until all thread complete Reference #4 */
        pthread_join(task, NULL);
        pthread_join(cpu1, NULL);
        pthread_join(cpu2, NULL);
        pthread_join(cpu3, NULL);

        /* cleanup */
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
 */

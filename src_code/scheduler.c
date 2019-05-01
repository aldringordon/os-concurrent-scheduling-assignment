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
#include <time.h> /* See Reference #2 */
#include <unistd.h>
#include <pthread.h>

int num_tasks, total_waiting_time, total_turnaround_time;

/**
 * places files from the Job-Queue into the Ready-Queue
 * @param job_queue list of jobs to be added to ready_queue
 */
void* task(JobQueue** job_queue)
{
    do
    {

    }while(*job_queue->size != 0);
}

/**
 * takes a task from ready_queue and executes for
 * its "entire cpu burst" sleep(burst/10)
 * @param ready_queue [description]
 */
void* cpu(ReadyQueue** ready_queue)
{
    do
    {

    }while(*ready_queue->size != 0);
}

int main(int argc, char* argv[])
{
    JobQueue* job_queue;
    ReadyQueue* ready_queue;

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
        pthread_create(&task, ~ , ~ , ~ );
        pthread_create(&cpu1, ~ , ~ , ~ );
        pthread_create(&cpu2, ~ , ~ , ~ );
        pthread_create(&cpu3, ~ , ~ , ~ );



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
 */

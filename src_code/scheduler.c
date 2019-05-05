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
 *
 *
 * NOTE: valgrind --tool=helgrind ./scheduler task_file 10
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* Reference #2 */
#include <unistd.h>
#include <pthread.h>

#include "task.h"
#include "job_queue.h"
#include "ready_queue.h"
#include "data.h"
#include "boolean.h"
#include "io.h"

#define NUM_THREADS 4 /* task, CPU-1, CPU-2, CPU-3 */

/* shared data between threads */
int num_tasks;
int total_waiting_time;
int total_turnaround_time;

/* mutexes */
pthread_mutex_t queue_lock;
pthread_mutex_t cpu_lock;

/* conditions */
pthread_cond_t tasks;
pthread_cond_t empty;

/* job pool, contains the list of jobs read in from task_file
implemented as a double ended, singly linked list,
same implementation as the ready_queue (FIFO)
found in job_queue.c/.h */
JobQueue* job_queue;

/**
 * takes a task from ready_queue and executes for
 * its "entire cpu burst" sleep(burst/10)
 * @param ready_queue [description]
 */
void* cpu(void* shared_data)
{
    Task* task = NULL; /* task to be processed */
    Data* data = (Data*)shared_data; /* convert shared data into accessible adt */
    int cpu_id = data->thread_id; /* identifies thread with cpu name {1, 2, 3} */
    ReadyQueue** ready_queue = data->queue; /* buffer */
    time_t rawtime; /* for getting time */
    struct tm* time_info; /* converting rawtime into accessible time struc */
    int num_processed = 0; /* number of tasks this thread has processed */

    /* output to screen thread creation so user can see progress */
    printf("\nTHREAD CREATION: cpu(%d)\n\n", cpu_id);

    do
    {
        /* CPU waits for tasks */
        pthread_mutex_lock(&queue_lock);

        if((*ready_queue)->size == 0 && (*ready_queue)->jobs_left != 0)
        {
            pthread_cond_wait(&tasks, &queue_lock);
        }

        do
        {
            task = getTask(ready_queue);
            pthread_mutex_unlock(&queue_lock);

            if(task != NULL)
            {

                /* assignment specification 7)
                output to simulation_log when CPU takes tasl from queue */
                time(&rawtime);
                time_info = localtime(&rawtime);
                task->service_time = *time_info;
                task_serviced(cpu_id, task->n, &task->arrival_time, &task->service_time);

                /* output to screen process execution so user can see progress */
                printf("\tcpu(%d): processing: task#:%d burst_time:%d\n", cpu_id, task->n, task->burst);

                /* assignment specification 5)
                simulate the execution of a task for its entire cpu_burst
                via a sleep call proportional to the burst time
                used a sleep call with the burst time integer divided by 10
                so a 43 burst task will take 4 seconds, 89 burst: 8 seconds etc*/
                sleep(task->burst/10);
                num_processed++;

                /* output to screen process execution so user can see progress */
                printf("\t\tcpu(%d): processed: task#:%d burst_time:%d execution_time: %d\n", cpu_id, task->n, task->burst, task->burst/10);

                /* assignment specification 8)
                output to simulation_log when CPU finishes servicing a task
                according to the assignment specification its:
                completion time = service time + cpu burst*/
                task->completion_time = task->arrival_time;
                task->completion_time.tm_sec += task->burst;
                mktime(&task->completion_time); /* normalizes the time structure i.e if seconds was 70 = add 1 min take 60 seconds*/
                task_completed(cpu_id, task->n, &task->arrival_time, &task->completion_time);

                pthread_mutex_lock(&cpu_lock);
                num_tasks++;
                /* difftime returns a double value of the difference between time1 and time 2 both of type "time_t"
                mktime converts a "struct *tm" into "time_t"
                next 2 lines converts the "struct *tm" times to be used in calculation and passes
                them to difftime to calculate the time difference, this is then converted from a
                double to an int */

                /* waiting time = service time - arrival time */
                total_waiting_time += (int)(difftime(mktime(&task->service_time), mktime(&task->arrival_time)));

                /* turnaround time = completion time - arrival time */
                total_turnaround_time += (int)(difftime(mktime(&task->completion_time), mktime(&task->arrival_time)));;
                pthread_mutex_unlock(&cpu_lock);

                free(task);
            }
            pthread_mutex_lock(&queue_lock);
        }while((*ready_queue)->size != 0);

        /* CPU signals TASK that queue is empty */

        pthread_mutex_unlock(&queue_lock);
        pthread_cond_signal(&empty);

    }while((*ready_queue)->jobs_left != 0);

    /* output to screen thread termination so user can see progress */
    printf("THREAD TERMINATION: cpu(%d) num_tasks processed: = %d\n", cpu_id, num_processed);
    cpu_terminated(cpu_id, num_processed);
    pthread_exit(NULL);
}

/**
 * places files from the Job-Queue into the Ready-Queue
 * @param job_queue list of jobs to be added to ready_queue
 */
void* task(void* shared_data)
{
    Task *task1, *task2; /* 2 tasks to be added to Ready-Queue */
    Data* data = (Data*)shared_data; /* convert shared data into accessible adt */
    ReadyQueue** ready_queue = data->queue; /* buffer */
    int jobs_added = 0; /* number of jobs added to buffer */
    time_t rawtime; /* for getting time */
    struct tm* time_info; /* converting rawtime into accessible time struc */
    /* output to screen thread creation so user can see progress */
    printf("\nTHREAD CREATION: task()\n\n");
    do
    {
        /* TASK blocks when ready_queue has been
        filled with the amount of tasks available to be
        put into the buffer */
        pthread_mutex_lock(&queue_lock);
        if((*ready_queue)->size != 0 && (*ready_queue)->jobs_left != 0)
        {
            pthread_cond_wait(&empty, &queue_lock);
        }

        /* add jobs while there are still jobs left, and buffer isn't full
        and stop adding jobs if task1 = null or task 2 = null (no more jobs)*/
        do
        {
            task1 = getJob(&job_queue);
            /* t1_arr_time */
            if(task1 != NULL)
            {
                /* SIM LOG */
                time(&rawtime);
                time_info = localtime(&rawtime);
                task1->arrival_time = *time_info;
                task_placed(task1->n, task1->burst, &task1->arrival_time);
                addTask(ready_queue, task1);
                jobs_added++;
            }

            /* check that 2nd task can fit in queue
            before if it didnt fit it would just drop the
            task and total job_size would never reach 0
            because the task was never processed */
            if(((*ready_queue)->size) < ((*ready_queue)->max_size))
            {
                task2 = getJob(&job_queue);
                /* t2_arr_time */
                if(task2 != NULL)
                {
                    /* SIM LOG */
                    time(&rawtime);
                    time_info = localtime(&rawtime);
                    task2->arrival_time = *time_info;
                    task_placed(task2->n, task2->burst, &task2->arrival_time);
                    addTask(ready_queue, task2);
                    jobs_added++;
                }
            }
        /* WHILE LOOP IN ENGLISH:
        while [ (there are still jobs)  AND (the amount of jobs is less then maximum buffer size) ] AND [ both tasks are not NULL ] */
        }while((((*ready_queue)->jobs_left > 0) && ((*ready_queue)->size) < ((*ready_queue)->max_size)) && ((task1 != NULL) && (task2 != NULL)));

        /* TASK signals CPU that jobs to be
        processed have been added to the queue
        thus no longer empty */
        pthread_mutex_unlock(&queue_lock);
        pthread_cond_signal(&tasks);
    }while((*ready_queue)->jobs_left != 0);

    /* signal any cpu still waiting to finish
    put this here as without it one of the threads would never
    unblock and the program would never finish */
    pthread_cond_signal(&tasks);
    /* assignment specification 9) termination of task() function */
    task_terminated(jobs_added); /* io.c */
    /* output to screen thread termination so user can see progress */
    printf("\nTHREAD TERMINATION: task()\n\n");
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    /* ./scheduler filename m */
    char* filename; /* argv[1] */
    int m; /* argv[2] */
    int i; /* for loop counter */
    int rc; /* check return value of pthread_create */

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
    pthread_cond_init(&empty, NULL);

    if(argc < 3) /* make sure program is called correctly */
    {
        printf("Error - Usage: ./scheduler task_file m\n");
        return EXIT_FAILURE; /* Reference #1 */
    }
    else if((atoi(argv[2]) < 1) || (atoi(argv[2]) > 10)) /* make sure buffer size is within range */
    {
        printf("Error - m must be a value between 1 and 10\n");
        return EXIT_FAILURE;
    }
    else
    {
        m = atoi(argv[2]);
        filename = argv[1];

        /* create a simulation_log */
        system("rm -rf simulation_log");

        /* create Job-Queue*/
        createJobQueue(&job_queue);
        readJobs(&job_queue, filename);

        /* create Ready-Queue */
        createReadyQueue(&ready_queue, m, job_queue->size);

        /* create 4 threads: 1 for task, 3 for cpus */
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

        /* SIM LOG */
        /* output progress to screen */
        printf("total tasks: %d\n", num_tasks);
        printf("total wait time: %d\n", total_waiting_time);
        printf("total turnaround time: %d\n", total_turnaround_time);
        printf("\naverage wait time: %d\n", total_waiting_time/num_tasks);
        printf("average turnaround time: %d\n", total_turnaround_time/num_tasks);

        /* assignment specification 11)
        write shared information to simulation_log
        after all CPUs and task threads have terminated */
        simulation_finished(num_tasks, total_waiting_time/num_tasks, total_turnaround_time/num_tasks); /* io.c */

        /* cleanup */
        pthread_mutex_destroy(&queue_lock);
        pthread_mutex_destroy(&cpu_lock);
        pthread_cond_destroy(&tasks);
        pthread_cond_destroy(&empty);

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
 *
 * #4: https://randu.org/tutorials/threads/
 *      Example program using pthread functions
 *
 * #5: https://randu.org/tutorials/threads/
 *      Multithreaded Programming - pthread Mutexes
 */

/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: data.c
 * Purpose: contains methods relating to data struct in data.h
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "data.h"

void init_data(Data** data, ReadyQueue** queue, pthread_mutex_t mutex, pthread_cond_t empty, pthread_cond_t not_empty)
{
    (*Data)->num_tasks = 0;
    (*Data)->total_waiting_time = 0;
    (*Data)->total_turnaround_time = 0;
    (*Data)->ready_queue = *queue;
    (*Data)->mutex = mutex;
    (*Data)->empty = empty;
    (*Data)->not_empty = not_empty;
}

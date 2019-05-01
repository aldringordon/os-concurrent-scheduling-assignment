/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: data.h
 * Purpose: contains the struct which is
 * used to share data between threads
 */
#ifndef DATA_H
#define DATA_H

typedef struct
{
    int num_tasks;
    int total_waiting_time;
    int total_turnaround_time;
    ReadyQueue* ready_queue;
    pthread_mutex_t mutex;
    pthread_cond_t empty;
    pthread_cond_t not_empty;
} Data;

#endif

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
    int thread_id;
    ReadyQueue* queue;
} Data;

#endif

/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: task.h
 * Purpose: contains structure of a CPU task
 * read in from task_file
 */
#include <time.h>

#ifndef TASK_H
#define TASK_H

typedef struct
{
    int n; /* task# */
    int burst; /* cpu_burst */
    struct tm arrival_time;
    struct tm service_time;
    struct tm completion_time;
} Task;

#endif

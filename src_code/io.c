/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: io.c
 * Purpose: contains functions to output
 * information to simulation_log
 */

#include "io.h"

void task_placed(int task_num, int cpu_burst, Time* arrival_time)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'\n%d: %d\nArrival time: %d:%d:%d\' >> simulation_log", task_num, cpu_burst, arrival_time->hour, arrival_time->min, arrival_time->sec);
    system(command);
}

void task_serviced(int cpu, int task_num, Time* arrival_time, Time* service_time)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'\nStatistics for CPU-%d:\n%d\nArrival time: %d:%d:%d\nService time: %d:%d:%d\' >> simulation_log", cpu, task_num, arrival_time->hour, arrival_time->min, arrival_time->sec, service_time->hour, service_time->min, service_time->sec);
    system(command);
}

/**
 * Reference: https://stackoverflow.com/questions/1859201/add-seconds-to-a-date#comment1756625_1859226
 * "add seconds to a date"
 */
void task_completed(int cpu, int task_num, Time* arrival_time, Time* completion_time)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'\nStatistics for CPU-%d:\n%d\nArrival time: %d:%d:%d\nCompletion time: %d:%d:%d\' >> simulation_log", cpu, task_num, arrival_time->hour, arrival_time->min, arrival_time->sec, completion_time->hour, completion_time->min, completion_time->sec);
    system(command);
}

void task_terminated(int num_tasks)
{
    char command[192];
    time_t rawtime;
    struct tm* termination_time;

    time(&rawtime);
    termination_time = localtime(&rawtime);

    snprintf(command, sizeof(command), "echo \'\nNumber of tasks put into Ready-Queue: %d\nTerminate at time: %d:%d:%d\' >> simulation_log", num_tasks, termination_time->tm_hour, termination_time->tm_min, termination_time->tm_sec);
    system(command);
}

void cpu_terminated(int cpu, int num_tasks)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'\nCPU-%d terminates after servicing %d tasks\' >> simulation_log", cpu, num_tasks);
    system(command);
}

void simulation_finished(int num_tasks, int avg_wait, int avg_turnaround)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'\nNumber of tasks: %d\nAverage waiting time: %d seconds\nAverage turn around time: %d seconds\' >> simulation_log", num_tasks, avg_wait, avg_turnaround);
    system(command);
}

/* convert time struct from time.h into something storable
had to allocate arrival time memory otherwise when passed to cpu
thread it loses its arrival time and must be recalculated which
doesnt maintain its original arrival time */

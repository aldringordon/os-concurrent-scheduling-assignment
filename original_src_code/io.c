/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: io.c
 * Purpose: contains functions to output
 * information to simulation_log
 */

#include "io.h"

void task_placed(int task_num, int cpu_burst, struct tm* arrival_time)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'%d: %d\nArrival time: %d:%d:%d\' >> simulation_log", task_num, cpu_burst, arrival_time->tm_hour, arrival_time->tm_min, arrival_time->tm_sec);
    system(command);
}

void task_serviced(int cpu, int task_num, struct tm* arrival_time, struct tm* service_time)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'Statistics for CPU-%d:\n%d\nArrival time: %d:%d:%d\nService time: %d:%d:%d\' >> simulation_log", cpu, task_num, arrival_time->tm_hour, arrival_time->tm_min, arrival_time->tm_sec, service_time->tm_hour, service_time->tm_min, service_time->tm_sec);
    system(command);

}

/**
 * Reference: https://stackoverflow.com/questions/1859201/add-seconds-to-a-date#comment1756625_1859226
 * "add seconds to a date"
 */
void task_completed(int cpu, int task_num, struct tm* arrival_time, struct tm* completion_time)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'Statistics for CPU-%d:\n%d\nArrival time: %d:%d:%d\nCompletion time: %d:%d:%d\' >> simulation_log", cpu, task_num, arrival_time->tm_hour, arrival_time->tm_min, arrival_time->tm_sec, completion_time->tm_hour, completion_time->tm_min, completion_time->tm_sec);
    system(command);
}

void task_terminated(int num_tasks)
{
    char command[192];
    time_t rawtime;
    struct tm* termination_time;

    time(&rawtime);
    termination_time = localtime(&rawtime);

    snprintf(command, sizeof(command), "echo \'Number of tasks put into Ready-Queue: %d\nTerminate at time: %d:%d:%d\' >> simulation_log", num_tasks, termination_time->tm_hour, termination_time->tm_min, termination_time->tm_sec);

    system(command);
}

void cpu_terminated(int cpu, int num_tasks)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'CPU-%d terminates after servicing %d tasks\' >> simulation_log", cpu, num_tasks);
    system(command);
}

void simulation_finished(int num_tasks, int avg_wait, int avg_turnaround)
{
    char command[192];
    snprintf(command, sizeof(command), "echo \'Number of tasks: %d\nAverage waiting time: %d seconds\nAverage turn around time: %d seconds\' >> simulation_log", num_tasks, avg_wait, avg_turnaround);
    system(command);
}

/* convert time struct from time.h into something storable
had to allocate arrival time memory otherwise when passed to cpu
thread it loses its arrival time and must be recalculated which
doesnt maintain its original arrival time */

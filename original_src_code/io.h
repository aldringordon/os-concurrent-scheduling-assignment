/**
 * Aldrin Gordon
 * Student No: 18340587
 * File: io.h
 * Purpose: header file for io.c to be called
 * by scheduler.c to output information to simulation_log
 */
#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "task.h"

#endif

void task_placed(int task_num, int cpu_burst, struct tm* arrival_time);
void task_serviced(int cpu, int task_num, struct tm* arrival_time, struct tm* service_time);
void task_completed(int cpu, int task_num, struct tm* arrival_time, struct tm* completion_time);
void task_terminated(int num_tasks);
void cpu_terminated(int cpu, int num_tasks);
void simulation_finished(int num_tasks, int avg_wait, int avg_turnaround);

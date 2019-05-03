# makefile for simulation source code
# Author: Aldrin Gordon
EXEC = scheduler
OBJ = scheduler.o ready_queue.o job_queue.o
CFLAGS = -Wall -pedantic -ansi
CC = gcc
CLEAN = rm -rf
SIM_LOG = simulation_log
SCHEDULER = scheduler.c ready_queue.h job_queue.h task.h boolean.h
READY_QUEUE = ready_queue.c ready_queue.h task.h boolean.h
JOB_QUEUE = job_queue.c job_queue.h task.h boolean.h

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -pthread -o $(EXEC)

scheduler.o : $(SCHEDULER)
	$(CC) -c scheduler.c $(CFLAGS)

ready_queue.o : $(READY_QUEUE)
	$(CC) -c ready_queue.c $(CFLAGS)

job_queue.o : $(JOB_QUEUE)
	$(CC) -c job_queue.c $(CFLAGS)

clean :
	$(CLEAN) $(OBJ) $(EXEC) $(SIM_LOG)

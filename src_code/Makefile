# makefile for simulation source code
# Author: Aldrin Gordon
EXEC = scheduler
OBJ = scheduler.o ready_queue.o job_queue.o io.o
CFLAGS = -Wall -pedantic -ansi
CC = gcc
CLEAN = rm -rf
SIM_LOG = simulation_log
SCHEDULER = scheduler.c ready_queue.h job_queue.h task.h boolean.h
READY_QUEUE = ready_queue.c ready_queue.h task.h boolean.h
JOB_QUEUE = job_queue.c job_queue.h task.h boolean.h
IO = io.c task.h io.h

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -pthread -o $(EXEC)

scheduler.o : $(SCHEDULER)
	$(CC) -c scheduler.c $(CFLAGS)

ready_queue.o : $(READY_QUEUE)
	$(CC) -c ready_queue.c $(CFLAGS)

job_queue.o : $(JOB_QUEUE)
	$(CC) -c job_queue.c $(CFLAGS)

io.o : $(IO)
	$(CC) -c io.c $(CFLAGS)

clean :
	$(CLEAN) $(OBJ) $(EXEC) $(SIM_LOG)

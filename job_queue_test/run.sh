#!/bin/bash
python task_file_generator.py
gcc -g -c job_queue_test.c job_queue.c
gcc job_queue_test.o job_queue.o -o test_job_queue
./test_job_queue
rm -rf job_queue_test.o job_queue.o test_job_queue

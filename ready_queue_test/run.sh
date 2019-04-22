#!/bin/bash
python task_file_generator.py
gcc -g -c test_queue.c ready_queue.c
gcc test_queue.o ready_queue.o -o test_queue
./test_queue
rm -rf test_queue.o ready_queue.o test_queue task_file

#!/bin/bash
gcc -g -c test_queue.c ready_queue.c
gcc test_queue.o ready_queue.o -o test_queue
./test_queue

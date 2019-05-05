# Aldrin Gordon
# 18340587
# File: task_file_generator.py
# Purpose: generate a task_file file which is used
# as the list of tasks to be read into the main
# program scheduler.c
# Note: this program has nothing to do with the
# implementation of the simulation itself, i just
# dont want to create a task_file of 100 tasks manually
import sys
import random

tasks = int(input("Enter number of tasks: "))
file = open("task_file","w")

for i in range(1, tasks+1):
    file.write(str(i) + ' ' + str(random.randint(1,50)) + '\n')

file.close()

CURTIN UNIVERSITY
Discipline of Computing
School of Electrical Engineering, Computing, and Mathematical Sciences

Operating Systems (COMP2006)
Semester 1, 2019

Assignment
Multiple-Processor Scheduling Simulation

Author: Aldrin Gordon

Synopsis:

The source code relating to the actual simulation is located
in /src_code/ .

There are two methods for running the simulation:

Method #1:
    1. execute "run_simulation.sh"

        $ ./run_simulation.sh

Method #2:
    1. navigate to /src_code/

        $ cd sr_code/

    2. execute the makefile

        $ make

    3. generate a "task_file" file

        $ python task_file_generator.py

    4. execute the program

        $ ./scheduler_simulation

And yes, run_simulation.sh from Method #1 is literally just a script that has the commands to run Method #2.
No, I do not understand how to write a proper script.

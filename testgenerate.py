#!/usr/bin/python3

import os
import sys
import random

def generate_test(out_filename): 
    out_file = open(out_filename, "w")
    num_jobs = random.randint(0, 100)
    out_file.write(str(num_jobs) + "\n")

    for i in range(num_jobs):
        t_arrival   = random.randint(0, 100)
        t_execution = random.randint(0, 100)
        out_file.write("\n\n")
        out_file.write(str(t_arrival) + "\n")
        out_file.write(str(t_execution) + "\n") 
        out_file.write("\n\n")

if len(sys.argv) > 1:
    num_test = int(sys.argv[1])
else:
    num_test = 1

for i in range(num_test):
    out_file = "Tests/testfile" + str(i) + ".txt"
    generate_test(out_file)

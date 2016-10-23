#!/usr/bin/python3

import sys
import os
import hashlib

def replace_slashes(s):
    if '/' in s:
        while '/' in s:
            s = s.replace('/', '.')
    return s

def test_program(program_name, inputfile):
    from_program = replace_slashes(program_name)
    outputfile = "Output/" + replace_slashes(inputfile) + from_program
    command = program_name + " " + inputfile + " > " +  outputfile
    print(command)
    os.system(command)

    return outputfile

def check_hashes(my_file, control_file):
    my_hash      = hashlib.sha512(open(my_file, 'rb').read()).hexdigest()
    control_hash = hashlib.sha512(open(control_file, 'rb').read()).hexdigest()
    if control_hash != my_hash:
        print("FAILED! at " + my_file)
        print("Expecting:")
        os.system("cat " + control_file)
        print("Got:")
        os.system("cat " + my_file)
    else:
        print("PASSED at " + my_file)
    
    print()


def run_test(my_programs, control_programs): 
    for i in range(len(my_programs)):
        my_prog = my_programs[i]
        cont_prog = control_programs[i]
        for testfile in os.listdir("Tests"):
            testfile = "Tests/" + testfile

            my_output = test_program(my_prog, testfile)
            control_output = test_program(cont_prog, testfile)

            check_hashes(my_output, control_output)


my_programs = ["Bin/sjf", "Bin/fcfs", "Bin/stcf"]
control_programs = ["./SJF", "./FCFS", "./STCF"]

run_test(my_programs, control_programs)

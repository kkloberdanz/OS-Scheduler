#!/usr/bin/python3

import sys
import os

def replace_slashes(s):
    if '/' in s:
        while '/' in s:
            s = s.replace('/', '')
    return s

def test_program(program_name, inputfile):
    outputfile = replace_slashes(inputfile)
    from_program = replace_slashes(program_name)
    command = program_name + " " + inputfile + " > " + "Output/" + outputfile + ".out." + from_program
    print(command)
    os.system(command)


    '''
if not os.isdir("Tests"):
    os.mkdir("Tests")

if not os.isdir("Output"):
    os.mkdir("Output")
    '''

# my_programs = ["Bin/sjf", "Bin/fcfs", "Bin/stfc"]
# control_programs = ["./SJF", "./FCFS", "./STCF"]
my_programs = ["Bin/sjf", "Bin/fcfs"]
control_programs = ["./SJF", "./FCFS"]

for i in range(len(my_programs)):
    my_prog = my_programs[i]
    cont_prog = control_programs[i]
    for testfile in os.listdir("Tests"):
        testfile = "Tests/" + testfile
        test_program(my_prog, testfile)
        test_program(cont_prog, testfile)


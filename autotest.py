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
    command = "timeout 1 " + program_name + " " + inputfile + " > " +  outputfile
    print(command)
    try:
        rc = os.system(command)
        if rc != 0:
            return "NONE"
    except KeyboardInterrupt:
        cleanup()
        quit()


    return outputfile

def check_hashes(my_file, control_file):
    my_hash      = hashlib.sha256(open(my_file, 'rb').read()).hexdigest()
    control_hash = hashlib.sha256(open(control_file, 'rb').read()).hexdigest()
    if control_hash != my_hash:
        print("FAILED! at " + my_file)
        print("Expecting:")
        os.system("cat " + control_file)
        print("Got:")
        os.system("cat " + my_file)
        print()
        return False
    else:
        print("PASSED at " + my_file)
        print()
        return True
    


def run_test(my_programs, control_programs): 
    analysis = open("testanalysis.txt", "w")
    for i in range(len(my_programs)):
        my_prog = my_programs[i]
        cont_prog = control_programs[i]
        num_success = 0
        num_fails = 0
        for testfile in os.listdir("Tests"):
            testfile = "Tests/" + testfile

            my_output = test_program(my_prog, testfile)
            control_output = test_program(cont_prog, testfile)

            if my_output == "NONE":
                print("--- TIMEOUT --- : " + my_prog)

            elif control_output == "NONE":
                print("--- TIMEOUT --- : " + cont_prog)

            else:
                if check_hashes(my_output, control_output):
                    num_success += 1
                else:
                    num_fails += 1

        analysis.write("Program: " + my_prog + "\n")    
        analysis.write("    Total Tests: " + str(num_success + num_fails) + "\n")
        analysis.write("    Successes  : " + str(num_success) + "\n")
        analysis.write("    Failures   : " + str(num_fails) + "\n\n")    

def cleanup():
    os.system("rm -rf Output/*")

try:
    my_programs = ["Bin/sjf", "Bin/fcfs", "Bin/stcf"]
    control_programs = ["./SJF", "./FCFS", "./STCF"]

    run_test(my_programs, control_programs)

except KeyboardInterrupt:
    cleanup()
    quit()

cleanup()

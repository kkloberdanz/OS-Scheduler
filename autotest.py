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
    num_timeouts = 0
    for i in range(len(my_programs)):
        my_prog = my_programs[i]
        cont_prog = control_programs[i]
        num_success = 0
        num_fails = 0
        total_tests  = 0
        for testfile in os.listdir("Tests"):
            testfile = "Tests/" + testfile

            my_output = test_program(my_prog, testfile)
            control_output = test_program(cont_prog, testfile)

            if my_output == "NONE":
                print("--- TIMEOUT --- : " + my_prog)
                num_timeouts += 1

            elif control_output == "NONE":
                print("--- TIMEOUT --- : " + cont_prog)
                num_timeouts += 1

            else:
                total_tests += 1
                if check_hashes(my_output, control_output):
                    num_success += 1
                else:
                    num_fails += 1


        # num_timeouts = total_tests - (num_success + num_fails)
        analysis.write("Program: " + my_prog + "\n")
        analysis.write("    Total Tests     : " + str(total_tests) + "\n")
        analysis.write("    Successes       : " + str(num_success) + "\n")
        analysis.write("    Failures        : " + str(num_fails) + "\n")
        analysis.write("    Timeouts        : " + str(num_timeouts) + "\n\n")
        analysis.write("    Percent Success : %.2f" % (100*(num_success / total_tests)))
        analysis.write("%")
        analysis.write("    Percent Timeouts: %.2f" % (100*(num_timeouts / (num_success + num_fails + num_timeouts))))
        analysis.write("%\n\n")

def cleanup():
    os.system("rm -rf Output/*")

try:
    my_programs = ["Bin/sjf", "Bin/fcfs", "Bin/stcf"]
    control_programs = ["./SJF", "./FCFS", "./STCF"]
    # my_programs = ["Bin/stcf"]
    # control_programs = ["./STCF"]

    run_test(my_programs, control_programs)

except KeyboardInterrupt:
    cleanup()
    quit()

cleanup()

CFLAGS = -std=gnu++11
#fcfs: Job.o
	##g++ -o fcfs fcfs.cpp Job.cpp -DDEBUG -std=gnu++11
	#g++ -o fcfs Build/fcfs.o  Build/Job.o $(CFLAGS)

#Job.o: Job.hpp
	#g++ -o Build/Job.o Job.cpp $(CFLAGS) 

#fcfs.o: Job.hpp
	#g++ -o Build/fcfs.o -c fcfs.cpp $(CFLAGS) 

all:
	g++ -o Bin/fcfs fcfs.cpp Job.cpp helpers.cpp
	g++ -o Bin/sjf  sjf.cpp  Job.cpp helpers.cpp

clean:
	rm -rf Bin/*
	rm -rf Build/*

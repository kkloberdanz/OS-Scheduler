# Debug
#CFLAGS = -std=gnu++11 -Wall -Wextra -Wpedantic -DDEBUG -O0

# Production
CFLAGS = -std=gnu++11 -Wall -Wextra -Wpedantic -O2

all:
	g++ -o Bin/fcfs fcfs.cpp Job.cpp helpers.cpp $(CFLAGS)
	g++ -o Bin/sjf  sjf.cpp  Job.cpp helpers.cpp $(CFLAGS)

clean:
	rm -rf Bin/*
	rm -rf Build/*

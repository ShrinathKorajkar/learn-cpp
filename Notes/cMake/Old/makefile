# Makefile

## variables
CC = g++
CFLAGS = -Wall -std=c++11

## target : dependencies
all: my_program


## target : dependencies (commandline to execute)
my_program: main.cpp functions.cpp
	$(CC) $(CFLAGS) -o my_program main.cpp functions.cpp

clean:
	rm -f my_program



#  to Run : 
# make     # Builds the executable 'my_program'
# ./my_program  # Runs the executable
# make clean  # Cleans up the generated files


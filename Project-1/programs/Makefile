# A SIMPY MAKEFILE FOR C++ PROGRAMS

# paths
INCLUDE = ../include
MODULES = ../modules

#compiler
CC = g++

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CPPFLAGS = -Wall  -g -I$(INCLUDE) -std=c++11

# Αρχεία .o
OBJS =  school.o $(MODULES)/school_structure.o

# Το εκτελέσιμο πρόγραμμα
EXEC = prog 

# Command line arguments
ARGS = 1 3 3 2
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind:
	valgrind --leak-check=full ./$(EXEC) $(ARGS)
# A SIMPY MAKEFILE FOR C++ PROGRAMS

# paths
INCLUDE = ../include
MODULES = ../modules

#compiler
CC = g++

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CPPFLAGS = -Wall -Werror  -g -I$(INCLUDE) -std=c++11

# Αρχεία .o
OBJS =  main.o $(MODULES)/school.o

# Το εκτελέσιμο πρόγραμμα
EXEC = prog

# Command line arguments
ARGS = 2 3 5 8 2
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind:
	valgrind --leak-check=full ./$(EXEC) $(ARGS)
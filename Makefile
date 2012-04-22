CC=g++
CFLAGS=-O2 -c -Wall
LDFLAGS=-O2
MAIN_S=tchess_main.cpp
EXEC=tchess

EXEC_D=tchess_main.o 
OBJS=$(EXEC_D) 

$(EXEC): $(OBJS) 
	    $(CC) $(LDFLAGS) -o $(EXEC) $(OBJS)

tchess_main.o: tchess_main.cpp tchess_algorithms.hpp tchess_board.hpp tchess_piece.hpp
	    $(CC) $(CFLAGS) $(MAIN_S)

clean:
	    rm $(EXEC_D) $(EXEC)

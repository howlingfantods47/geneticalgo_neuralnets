CC = g++
CFLAGS = -c -O3
DEBUGFLAGS = -c -g -O0
LDFLAGS = 
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
LIB = creature.h
all : $(OBJ) $(LIB)
	$(CC) $(LDFLAGS) $(OBJ) 
.cpp.o : 
	$(CC) $(CFLAGS) $(LDFLAGS) $< 
clean :
	rm -f *.o a.out 



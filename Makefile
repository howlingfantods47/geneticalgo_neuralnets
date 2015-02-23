CC = g++
CFLAGS = -c -O3
DEBUGFLAGS = -c -g -O0
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SRC = main.cpp environment.cpp
OBJ = $(SRC:.cpp=.o)
LIB = creature.h environment.h
all : $(OBJ) $(LIB)
	$(CC) $(LDFLAGS) $(OBJ) 
.cpp.o : 
	$(CC) $(CFLAGS) $(LDFLAGS) $< 
clean :
	rm -f *.o a.out 



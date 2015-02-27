CC = g++
CFLAGS = -c -O3
DEBUGFLAGS = -c -g -O0
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SRC = main.cpp environment.cpp creature.cpp
OBJ = $(SRC:.cpp=.o)
LIB = creature.h environment.h helper.h
all : $(OBJ) $(LIB)
	$(CC) $(LDFLAGS) $(OBJ) 
.cpp.o : 
	$(CC) $(DEBUGFLAGS) $(LDFLAGS) $< 
clean :
	rm -f *.o a.out 



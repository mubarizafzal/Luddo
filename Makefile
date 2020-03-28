
CC=g++
CFLAGS= -Wall -w -g

INCLUDE:= -Iincludes/ -I/usr/local/include

#requires all these libraries
LINK:= -L/usr/local/lib -lfltk -lXext -lX11 -lm -lXrender -lXcursor -lXfixes -lXft -lfontconfig -lXinerama -lpthread -ldl 

SOURCES:= $(wildcard src/*.cpp)

EXE=Board

all: $(EXE)

$(EXE):
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(EXE) $(LINK)

clean:
	rm $(EXE)

run:
	./$(EXE) &


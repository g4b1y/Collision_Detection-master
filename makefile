CC=g++
CFLAGS=-c -Wall -std=c++11 
SFML-LIB = "G:\SFML-2.5.1\lib"
SFML-INCLUDE = "G:\SFML-2.5.1\include"
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = ./main.cpp ./Run/Run.cpp ./Collision/Collision.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE = main


all: $(SOURCES) $(EXECUTABLE) 
        
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) -L $(SFML-LIB) $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I $(SFML-INCLUDE) $(LIBFLAGS)
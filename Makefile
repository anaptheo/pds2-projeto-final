CC = g++ 
CFLAGS = -Wall -g -std=c++11
SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.hpp)
OBJECTS = $(SOURCES:.cpp=.o)
INCLUDE_DIR = ./include
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -I ${INCLUDE_DIR} $(OBJECTS) -o $@

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I ${INCLUDE_DIR} -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean

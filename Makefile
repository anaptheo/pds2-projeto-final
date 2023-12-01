CC = g++
CFLAGS = -Wall -g -std=c++11
SOURCES = src/main.cpp src/locacao.cpp src/formatacao.cpp src/Cliente/cliente.cpp src/Filme/blueray.cpp src/Filme/dvd.cpp src/Filme/fita.cpp src/Filme/filme.cpp
HEADERS = include/bluray.hpp include/cliente.hpp include/dvd.hpp include/filme.hpp include/fita.hpp include/locacao.hpp include/formatacao.hpp
OBJECTS = $(SOURCES:.cpp=.o)
BUILD_DIR = ./build
INCLUDE_DIR = ./include
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean

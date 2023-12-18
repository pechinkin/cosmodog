HEADERS := character.hpp
SOURCES := main.cpp 
EXEC := dog

CFLAGS := -std=c++11 -Wall

XXX := 	-I//opt/homebrew/Cellar/sfml/2.5.1_2/include/\
		-L/opt/homebrew/Cellar/sfml/2.5.1_2/lib\
		-lsfml-graphics -lsfml-window -lsfml-system

INC_DIR = .

all: $(SOURCES) $(HEADERS)
	g++ $(SOURCES) -o $(EXEC) -I$(INC_DIR) $(CFLAGS) $(XXX)

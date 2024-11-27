EXTERNAL := -lGLU -lGL -lglut -lglfw
GCC_FLAGS := -Wall -Wswitch -Werror -pedantic -std=c++17 -O3
BIN_OUT := bin/debug

all:
	g++ $(GCC_FLAGS) $(EXTERNAL) -o $(BIN_OUT) src/*.cpp

debug:
	g++ $(GCC_FLAGS) -DDEBUG -g $(EXTERNAL) -o $(BIN_OUT) src/*.cpp

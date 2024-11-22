GCC_FLAGS := -lGLU -lGL -lglut -lglfw
BIN_OUT := bin/debug

all:
	g++ $(GCC_FLAGS) -o $(BIN_OUT) src/*.cpp
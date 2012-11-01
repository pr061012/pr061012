all: main.cpp
	g++ -g -Wall main.cpp -L"$(CURDIR)" -lGL -lGLU -lglfw -lSOIL

CFLAGS = -g -Wall
COBJS = gui_main.h gui_main.cpp main.cpp ../../view/ViewObject.h ../../view/ViewObject.cpp


all: main.cpp
	g++ $(CFLAGS) $(COBJS) -L"$(CURDIR)" -lGL -lGLU -lglfw -lSOIL

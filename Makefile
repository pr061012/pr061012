# Main compilation parameters.
CPP         = c++
CFLAGS      = -g -c -Wall -std=c++11 -march=native -O2
CFLAGS     += -Wextra -pedantic -Wold-style-cast -Woverloaded-virtual -Winit-self -Wparentheses
LFLAGS      =
LIBS        = -larmadillo -lGL -lSOIL -lglfw -lGLC -ljsoncpp

# Paths.
INPUT_DIR   = ./
MODEL_DIR   = $(INPUT_DIR)model/
CONTROL_DIR = $(INPUT_DIR)control/
VIEW_DIR    = $(INPUT_DIR)view/
CLI_DIR     = $(INPUT_DIR)cli/
COMMON_DIR  = $(INPUT_DIR)common/

# Files with sources.
SOURCES     = $(wildcard $(MODEL_DIR)*/*.cpp $(MODEL_DIR)*/*/*.cpp $(MODEL_DIR)*/*/*/*.cpp $(MODEL_DIR)*/*/*/*/*.cpp)
SOURCES    += $(wildcard $(CONTROL_DIR)*.cpp $(CONTROL_DIR)*/*.cpp $(CONTROL_DIR)*/*/*.cpp)
SOURCES    += $(wildcard $(VIEW_DIR)*.cpp $(VIEW_DIR)*/*.cpp $(VIEW_DIR)*/*/*.cpp)
SOURCES    += $(wildcard $(CLI_DIR)*.cpp)
SOURCES    += $(wildcard $(COMMON_DIR)*/*.cpp)
SOURCES    += main.cpp

# Object files.
OBJECTS     = $(SOURCES:.cpp=.o)

# Executable file.
EXECUTABLE  = pr061012

# Graphic libraries
# FIXME: Ugly.
GLFW3_PATH = /usr/include/GL/glfw3.h
TEST_GLFW3 = $(wildcard $(GLFW3_PATH))

ifeq ($(TEST_GLFW3), $(GLFW3_PATH))
	CFLAGS += -DUSE_GLFW3
else
	CFLAGS += -DUSE_GLFW
endif

# View debug.
ifeq ($(view), pretty)
else
#	CFLAGS += -DVIEW_DEBUG
endif

# Rules.

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CPP) $(LFLAGS) $(OBJECTS) -o $@ $(LIBS) 

.cpp.o:
	$(CPP) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

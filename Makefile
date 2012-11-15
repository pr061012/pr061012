# Main compilation parameters.
CC          = g++
CFLAGS      = -g -c -Wall -O2 -std=c++11 -D VIEW_DEBUG
LFLAGS      =
LIBS        = -larmadillo -lGL -lSOIL -lglfw

# Paths.
INPUT_DIR   = ./
MODEL_DIR   = $(INPUT_DIR)model/
CONTROL_DIR = $(INPUT_DIR)control/
VIEW_DIR    = $(INPUT_DIR)view/
COMMON_DIR  = $(INPUT_DIR)common/

# Files with sources.
SOURCES     = $(wildcard $(MODEL_DIR)*/*.cpp $(MODEL_DIR)*/*/*.cpp $(MODEL_DIR)*/*/*/*.cpp $(MODEL_DIR)*/*/*/*/*.cpp)
SOURCES    += $(wildcard $(CONTROL_DIR)*.cpp $(CONTROL_DIR)*/*.cpp $(CONTROL_DIR)*/*/*.cpp)
SOURCES    += $(wildcard $(VIEW_DIR)*.cpp $(VIEW_DIR)*/*.cpp)
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
CFLAGS += -DVIEW_DEBUG

# Rules.

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@ $(LIBS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

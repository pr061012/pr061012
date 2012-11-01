# Main compilation parameters.
CC         = g++
CFLAGS     = -g -c -Wall -O2 -std=c++11
LFLAGS     =

# Paths.
INPUT_DIR  = ./
MODEL_DIR  = $(INPUT_DIR)model/

# Files with sources.
SOURCES    = $(wildcard $(MODEL_DIR)*/*.cpp $(MODEL_DIR)*/*/*.cpp $(MODEL_DIR)/*/*/*/*.cpp $(MODEL_DIR)/*/*/*/*/*.cpp)
SOURCES   += main.cpp

# Object files.
OBJECTS    = $(SOURCES:.cpp=.o)

# Executable file.
EXECUTABLE = pr061012

# Rules.

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

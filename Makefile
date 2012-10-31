CC         = g++
CFLAGS     = -g -c -Wall -O2 -std=c++11
LFLAGS     =

INPUT_DIR  = ./
EXECUTABLE = pr061012

MODEL_DIR  = $(INPUT_DIR)model/

SOURCES    = $(wildcard $(MODEL_DIR)*/*.cpp $(MODEL_DIR)*/*/*.cpp $(MODEL_DIR)/*/*/*/*.cpp $(MODEL_DIR)/*/*/*/*/*.cpp)
SOURCES   += main.cpp

OBJECTS    = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

# Main compilation parameters.
CC         = g++
CFLAGS     = -g -c -Wall -O2 -std=c++11
LFLAGS     =
LIBS       =

# Paths.
MODEL_DIR  = ../../model/

# Files with sources.
SOURCES    = $(MODEL_DIR)World/Object/Object.cpp
SOURCES	  += $(MODEL_DIR)World/Action/Action.cpp
SOURCES	  += $(MODEL_DIR)Utilities/Shape/Shape.cpp
SOURCES	  += $(MODEL_DIR)Utilities/Point/Point.cpp
SOURCES   += main.cpp

# Object files.
OBJECTS    = $(SOURCES:.cpp=.o)

# Executable file.
EXECUTABLE = test

# Rules.

all: $(SOURCES) $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

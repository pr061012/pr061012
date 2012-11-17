# Main compilation parameters.
CC         = g++
CFLAGS     = -g -c -Wall -O2 -std=c++11
LFLAGS     =
LIBS       =

# Paths.
COMMON_DIR = ../../common/

# Files with sources.
SOURCES   += $(COMMON_DIR)ParamArray/EParamArrayInvalidKey.cpp
SOURCES   += $(COMMON_DIR)Log/Log.cpp
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

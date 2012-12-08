# Main compilation parameters.
CC         = c++
CFLAGS     = -g -c -Wall -std=c++11
LFLAGS     =
LIBS       =

# Paths.
MODEL_DIR  = ../../model/
VIEW_DIR   = ../../view/
COMMON_DIR = ../../common/

# Files with sources.
SOURCES    = $(MODEL_DIR)Utilities/Vector/Vector.cpp $(MODEL_DIR)Utilities/Shape/Shape.cpp
SOURCES   += $(MODEL_DIR)World/Action/Action.cpp
SOURCES   += $(MODEL_DIR)World/Object/Object.cpp
SOURCES   += $(MODEL_DIR)World/ObjectHeap/ObjectHeap.cpp
SOURCES   += $(MODEL_DIR)World/Object/Creatures/Humanoid/HumanoidValueMap.cpp
SOURCES   += $(COMMON_DIR)Math/DoubleComparison.cpp
SOURCES   += $(VIEW_DIR)ViewObject/ViewObject.cpp
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

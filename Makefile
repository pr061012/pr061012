CC         = g++
CFLAGS     = -g -c -Wall -O2
LFLAGS     =

MODEL_PATH = ./model
VIEW_PATH  =

SOURCES    = main.cpp $(MODEL_PATH)/God/God.cpp $(MODEL_PATH)/Utilities/Point/Point.cpp $(MODEL_PATH)/Utilities/Shape/Shape.cpp $(MODEL_PATH)/World/World.cpp $(MODEL_PATH)/World/DecisionMaker/DecisionMaker.cpp $(MODEL_PATH)/World/Indexator/Indexator.cpp $(MODEL_PATH)/World/Indexator/Window/Window.cpp $(MODEL_PATH)/World/Object/Object.cpp $(MODEL_PATH)/World/Object/Building/Building.cpp $(MODEL_PATH)/World/Object/Creatures/Creature.cpp $(MODEL_PATH)/World/Object/Creatures/Humanoid/Humanoid.cpp $(MODEL_PATH)/World/Object/Creatures/NonHumanoid/NonHumanoid.cpp $(MODEL_PATH)/World/Object/Resource/Resource.cpp $(MODEL_PATH)/World/Object/Tool/Tool.cpp $(MODEL_PATH)/World/Object/Weather/Weather.cpp $(MODEL_PATH)/World/ObjectFactory/ObjectFactory.cpp $(MODEL_PATH)/World/ObjectHeap/ObjectHeap.cpp
SOURCES   += 

OBJECTS    = $(SOURCES:.cpp=.o)
EXECUTABLE = pr061012

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


.PHONY: all clean FORCE

CXX = g++
SRC = src/main.cpp
TARGET = main

all: $(TARGET)

$(TARGET): FORCE $(SRC)
	$(CXX) $(SRC) -o $(TARGET) -lraylib

FORCE:

clean:
	rm -f $(TARGET)
.PHONY: all build configure clean

TARGET = main
SOURCE_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
SOURCES = $(shell find $(SOURCE_DIR) -name '*.cpp')
OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
CXXFLAGS = -Wall -std=c++23 # Compiler flags

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ 

$(OBJ_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@  

run: $(TARGET)
	./main

clean:
	rm -rf $(BUILD_DIR)
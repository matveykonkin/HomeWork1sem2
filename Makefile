CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -pthread
GTEST_LIBS = -lgtest -lgtest_main -pthread

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
DOC_DIR = doc

SRC = $(SRC_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/tests.cpp
OBJ = $(BUILD_DIR)/main.o
TEST_OBJ = $(BUILD_DIR)/tests.o
TARGET = $(BUILD_DIR)/main
TEST_TARGET = $(BUILD_DIR)/tests

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

docs:
	@mkdir -p $(DOC_DIR)
	doxygen Doxyfile

clean:
	rm -rf $(BUILD_DIR) $(DOC_DIR)

.PHONY: all test clean docs
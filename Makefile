CXX = g++
TARGET = testCI

all: $(TARGET)

$(TARGET): main.cpp testCI.cpp
	$(CXX) $^ -o $@

clean:
	rm -f $(TARGET)
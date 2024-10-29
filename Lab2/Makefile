CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2 -g

TARGET = test
SOURCES = main-test.cpp Person.cpp

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

rebuild: clean build
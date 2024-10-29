CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2

GENERATOR_TARGET = generator
GENERATOR_SOURCE = main-generator.cpp

FILE_SOURCE = f.cpp

TEST_TARGET = test
TEST_SOURCE = main-test.cpp

build:
	$(CXX) $(CXXFLAGS) -o $(GENERATOR_TARGET) $(GENERATOR_SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SOURCE) $(FILE_SOURCE)

clean:
	rm -f $(GENERATOR_TARGET) $(TEST_TARGET)

rebuild:
	clean build
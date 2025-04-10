CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -g

TARGET = matrix_ops

SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS) matrix.h
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o core.* *~

.PHONY: all clean
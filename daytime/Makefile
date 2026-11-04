CXX      = g++
CXXFLAGS = -Wall -O2 -std=c++17
SRC      = daytime.cpp
TARGET   = daytime_client

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean

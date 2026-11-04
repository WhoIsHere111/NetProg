CXX      = g++
CXXFLAGS = -Wall -O2 -std=c++17
SRC      = echo.cpp
TARGET   = echo_client

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean

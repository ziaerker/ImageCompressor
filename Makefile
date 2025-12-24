
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude 

TARGET = Compressor
SRCS = src/main.cpp src/Image.cpp src/Compressor.cpp src/Menu.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
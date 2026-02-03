CXX := C:/msys64/ucrt64/bin/g++.exe
TARGET := main.exe
SRC := main.cpp

CXXFLAGS := -Wall -Wextra
LDFLAGS := -lraylib -lopengl32 -lgdi32 -lwinmm

.PHONY: build run clean

build:$(TARGET)

$(TARGET):$(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run:build
	.\$(TARGET)

clean:
	-del /Q $(TARGET) 2>NUL
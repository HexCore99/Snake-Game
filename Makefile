MSYS2_UCRT64 := C:/msys64/ucrt64
CXX := $(MSYS2_UCRT64)/bin/g++.exe
TARGET := main.exe
SRC := main.cpp

CPPFLAGS := -I$(MSYS2_UCRT64)/include
CXXFLAGS := -Wall -Wextra -std=c++17
LDFLAGS := -L$(MSYS2_UCRT64)/lib
LDLIBS := -lraylib -lopengl32 -lgdi32 -lwinmm

.PHONY: all build run clean rebuild

all: build

build: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	.\$(TARGET)

clean:
	if exist $(TARGET) del /Q $(TARGET)

rebuild: clean build

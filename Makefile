SRC := main.cpp
PKG_CONFIG ?= pkg-config
RAYLIB_INCLUDE_DIR ?=
RAYLIB_LIB_DIR ?=

CXXFLAGS += -Wall -Wextra

ifeq ($(OS),Windows_NT)
PLATFORM := windows
else
UNAME_S ?= $(shell uname -s 2>/dev/null)
ifeq ($(UNAME_S),Linux)
PLATFORM := linux
endif
endif

ifeq ($(PLATFORM),windows)
CXX ?= g++.exe
TARGET ?= Snake.exe
RUN_CMD := .\\$(TARGET)
CLEAN_CMD := -del /Q $(TARGET) 2>NUL

LDFLAGS += -mwindows
LDLIBS += -lraylib -lopengl32 -lgdi32 -lwinmm
else ifeq ($(PLATFORM),linux)
CXX ?= g++
TARGET ?= Snake
RUN_CMD := ./$(TARGET)
CLEAN_CMD := rm -f $(TARGET)

ifneq ($(strip $(RAYLIB_INCLUDE_DIR)),)
CPPFLAGS += -I$(RAYLIB_INCLUDE_DIR)
endif

ifneq ($(strip $(RAYLIB_LIB_DIR)),)
LDFLAGS += -L$(RAYLIB_LIB_DIR)
endif

RAYLIB_CFLAGS := $(shell $(PKG_CONFIG) --cflags raylib 2>/dev/null)
RAYLIB_LIBS := $(shell $(PKG_CONFIG) --libs raylib 2>/dev/null)

ifneq ($(strip $(RAYLIB_CFLAGS)),)
CPPFLAGS += $(RAYLIB_CFLAGS)
endif

ifneq ($(strip $(RAYLIB_LIBS)),)
LDLIBS += $(RAYLIB_LIBS)
else
LDLIBS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif
else
$(error Unsupported platform. Use Windows/MSYS2 or Linux with raylib installed.)
endif

.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS) $(LDLIBS)

run: build
	$(RUN_CMD)

clean:
	$(CLEAN_CMD)

SRC_DIR = src
BUILD_DIR = build/debug
CC = gcc
SRC_FILE = $(wildcard $(SRC_DIR)/*.c)
OBJ_NAME = play
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -L /opt/homebrew/Cellar/sdl2/2.26.5/lib -L /opt/homebrew/Cellar/sdl2_image/2.6.3_1/lib
COMPILER_FLAGS = -std=c99 -Wall -O0 -g
LINKER_FLAGS = -lSDL2 -lSDL2_image 

all:
	$(CC) $(SRC_FILE) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME) -v
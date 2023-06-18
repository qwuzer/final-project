# CC = gcc
# CFLAGS = -Wall -Werror

# # Specify the target executable
# TARGET = main

# # List the object files
# OBJ = main.o init.o prt_board.o

# # Specify the source files
# SRC = main.c init.c prt_board.c

# # Define the default target
# all: $(TARGET)

# # Build the target executable
# $(TARGET): $(OBJ)
# 	$(CC) $(CFLAGS) $^ -o $@

# # Build the object files
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Clean the generated files
# clean:
# 	rm -f $(OBJ) $(TARGET)

all:
	gcc main.c init.c prt_board2.c prtInfo.c ai.c -o main -lncurses -lm

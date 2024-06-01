# Variables
CC = clang
CFLAGS = -Iinclude -Wall -Wextra -Werror -g
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
TARGET = $(BIN_DIR)/program

# Find all .c files in src/ directory
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Create corresponding .o files in bin/ directory
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Default target
all: $(BIN_DIR) $(TARGET)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Link object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile source files to object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)

.PHONY: all clean

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I$(SRC_DIR)
TARGET = mycat

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/arguments.c $(SRC_DIR)/file_io.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files into executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile .c files to .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/mycat.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the program with default arguments
run: $(TARGET)
	./$(TARGET)

# Format code
format:
	clang-format -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h

.PHONY: all clean run format

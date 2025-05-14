
# Directories and target
# -----------------------------------------
# Directories
SRC_DIR		:= source
INC_DIR		:= $(SRC_DIR)/include
BUILD_DIR	:= build
BIN_DIR		:= bin
# Executable name
TARGET		:= $(BIN_DIR)/executable
# -----------------------------------------

# Compilers and flags
# -----------------------------------------
CC				:= gcc
XC				:= g++
CFLAGS		:= -Wall -Wextra -g -I$(INC_DIR) $(SDLFLAGS)
XCFLAGS		:= $(CFLAGS)
# -----------------------------------------

# File variables
# -----------------------------------------
# Source code files
C_SRCS		:= $(wildcard $(SRC_DIR)/*.c)
CPP_SRCS	:= $(wildcard $(SRC_DIR)/*.cpp)
# Object files
C_OBJS		:= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SRCS))
CPP_OBJS	:= $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SRCS))
OBJS			:= $(C_OBJS) $(CPP_OBJS)
# -----------------------------------------

# Rules
.PHONY: all run clean

# Default target
# -----------------------------------------
all: $(TARGET)

# Create executable
$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(XC) $(XCFLAGS) -o $@ $^
# -----------------------------------------

# Run the executable
# -----------------------------------------
run: $(TARGET)
	./$(TARGET)
# -----------------------------------------

# Create object files
# -----------------------------------------
# Create build/ directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile C source code
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ source code
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(XC) $(XCFLAGS) -c $< -o $@
# -----------------------------------------

# -----------------------------------------
# Delete temporary files and directories created during compilation
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
# -----------------------------------------

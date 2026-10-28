# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

# ------Below code is not working------
# Detect OS
ifeq ($(OS),Windows_NT)
    IS_WINDOWS := 1
else
    IS_WINDOWS := 0
endif

ifeq ($(IS_WINDOWS),0)
    RM := rm -f
    RMDIR := rm -rf
    MKDIR := mkdir -p
    DIR_SEP := /
else
    RM := del /f /q
    RMDIR := rd /s /q
    MKDIR := mkdir
    DIR_SEP := /
endif
# -------------------------------------

# ----Change this part manually for Windows and Linux env----
#RM := del /f /q
#RMDIR := rd /s /q
#MKDIR := mkdir
#DIR_SEP := /
# -------------------------------------------------------------

# Project Name (current directory of Makefile)
TARGET := $(lastword $(subst $(DIR_SEP), ,$(CURDIR)))
TARGET := $(subst _repo,,$(TARGET))

# Directory Structure
SRC_DIR := src
LIB_DIR := lib
LIBC_DIR := lib_c
LIBH_DIR := lib_h
CONF_DIR := config
INC_DIR := include
BUILD_DIR ?= build
BIN_DIR ?= bin
LOG_DIR ?= log
TEST_DIR := tests

# Compiler and Flags
CC = gcc
BASE_CFLAGS = -Wall -Wextra -std=c99 -I$(INC_DIR) -I$(LIB_DIR)$(DIR_SEP)$(LIBH_DIR) -I$(CONF_DIR)
DEPFLAGS = -MMD -MP

# Build Configuration: Run make BUILD=release or make BUILD=debug (default: debug)
BUILD ?= debug
ifeq ($(BUILD),release)
    CFLAGS = $(BASE_CFLAGS) -O3 -DNDEBUG
    BUILD_MSG = [RELEASE BUILD]
else
    CFLAGS = $(BASE_CFLAGS) -g3 -O0 -DDEBUG
    BUILD_MSG = [DEBUG BUILD]
endif

# Automatically discover source files
SRCS = $(wildcard $(SRC_DIR)$(DIR_SEP)*.c)
LIBS = $(wildcard $(LIB_DIR)$(DIR_SEP)$(LIBC_DIR)$(DIR_SEP)*.c)
OBJS = $(patsubst %.c, $(BUILD_DIR)$(DIR_SEP)%.o, $(notdir $(SRCS) $(LIBS)))
#Substitued below line with above line
#OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

# ------------------------------------------------------------------------------
# Rules
# ------------------------------------------------------------------------------

# Default target
all: $(LOG_DIR)
	@echo "$(BUILD_MSG)"
	@$(MAKE) -j$(nproc) $(BIN_DIR)$(DIR_SEP)$(TARGET)

# Link executable (Order-only prerequisite ensures bin directory exists)
$(BIN_DIR)$(DIR_SEP)$(TARGET): $(OBJS) | $(BIN_DIR)
	@echo "----------------------------------------"
	@echo "Linking final binary: $@"
	$(CC) $(OBJS) -o $@
	@echo "Build complete successfully!"

# Compile C source files to object files
$(BUILD_DIR)$(DIR_SEP)%.o: $(SRC_DIR)$(DIR_SEP)%.c | $(BUILD_DIR)
	@echo "Compiling: $< -> $@"
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(BUILD_DIR)$(DIR_SEP)%.o: $(LIB_DIR)$(DIR_SEP)$(LIBC_DIR)$(DIR_SEP)%.c | $(BUILD_DIR)
	@echo "Compiling: $< -> $@"
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
	
# Create required directories automatically using order-only prerequisites
$(BUILD_DIR) $(BIN_DIR) $(LOG_DIR):
	@$(MKDIR) $@
#Note- removed -p option from above line
# Include auto-generated dependency files for header tracking
-include $(DEPS)

# Clean up build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@$(RMDIR) $(BUILD_DIR) $(BIN_DIR) $(LOG_DIR)

# Phony targets prevent conflicts with files named 'all' or 'clean'
.PHONY: all clean

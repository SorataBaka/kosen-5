# ──────────────────────────────────────────────
# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

# ──────────────────────────────────────────────
# Directories and targets
BIN_DIR := bin
TARGET  := $(BIN_DIR)/simulate

# Source and object files
SRCS    := simulate.c dice.c helper.c help.c area.c janken.c
OBJS    := $(patsubst %.c,$(BIN_DIR)/%.o,$(SRCS))

# ──────────────────────────────────────────────
# Default goal
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Pattern rule: compile each .c into bin/%.o
$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure bin directory exists before anything else
$(BIN_DIR):
	mkdir -p $@

# ──────────────────────────────────────────────
# House-keeping
clean:
	rm -f $(TARGET) $(OBJS)

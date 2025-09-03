# Compiler
CC = gcc

# Compilation flags
CFLAGS = -Wall -O2 -Iheaders

# Target executable
TARGET = out/readnode

# Source files
SRCS = main.c read_file.c stack.c log.c dfs.c spanning_tree.c queue.c bfs.c

# Object files
OBJS = $(SRCS:%.c=out/%.o)

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Compile .c files to .o files in out/
out/%.o: %.c | out
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure out directory exists
out:
	mkdir -p out

# Clean build files
clean:
	rm -rf out/*

# Run target (optional convenience)
run: $(TARGET)
	gdb $(TARGET)

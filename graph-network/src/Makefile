# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2 -Iheaders

# Target executable
TARGET = readnode

# Source files
SRCS = main.c read_file.c stack.c log.c

# Object files (placed in out/)
OBJS = $(SRCS:%.c=out/%.o)

# Default target
all: out $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o out/$(TARGET) $(OBJS)

# Compile .c files to .o in out/
out/%.o: %.c | out
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure out directory exists
out:
	mkdir -p out

# Clean build files
clean:
	rm -f out/*.o out/$(TARGET)

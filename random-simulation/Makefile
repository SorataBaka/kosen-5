# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -std=c11

# Executable name
TARGET = simulate

# Source files
SRCS = simulate.c dice.c helper.c help.c

# Object files (auto-generated from SRCS)
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile each .c file to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) *.o

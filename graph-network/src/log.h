#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>

extern FILE *file_pointer;
extern bool verbose;
extern bool output;

void init_file(char *filename);
void enable_verbose();
void disable_verbose();
void close_file();
void log_console(const char *level, const char *format, ...);
void log_file(const char *format, ...);

#endif
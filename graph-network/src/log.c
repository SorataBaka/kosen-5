#include "log.h"
FILE *file_pointer = NULL;
bool verbose = false;
bool output = false;

void init_file(char *filename)
{
  if (file_pointer != NULL || file_pointer)
  {
    fprintf(stderr, "Fatal error: Log file is already opened.");
    abort();
  }

  file_pointer = fopen(filename, "w");

  if (file_pointer == NULL || !file_pointer)
  {
    fprintf(stderr, "Fatal error: Unable to open file.");
    abort();
  }
  output = true;
  return;
}
void enable_verbose()
{
  verbose = true;
  return;
}
void disable_verbose()
{
  verbose = false;
  return;
}
void close_file()
{
  fclose(file_pointer);
  return;
}
void log_console(const char *level, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  if (verbose == true)
  {
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
  }
  va_end(args);
}
void log_file(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  if (output == true && file_pointer != NULL)
  {
    vfprintf(file_pointer, format, args);
    fprintf(file_pointer, "\n");
  }
  va_end(args);
}

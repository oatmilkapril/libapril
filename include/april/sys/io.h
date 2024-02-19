#ifndef LIBAPRIL_IO_H
#define LIBAPRIL_IO_H

#include <stdio.h>

FILE *april_fopen(const char *filename, const char *mode);

FILE *april_fdopen(int fd, const char *type);

void april_fclose(FILE *file);

int april_fgetc(FILE *stream);

void april_ungetc(int c, FILE *stream);

char *april_fgets(char *buffer, int buffer_size, FILE *stream);

size_t april_fread(void *buffer, size_t element_size, size_t num_elements, FILE *stream);

void april_fwrite(const void *buffer, size_t element_size, size_t num_elements, FILE *stream);

#endif // LIBAPRIL_IO_H

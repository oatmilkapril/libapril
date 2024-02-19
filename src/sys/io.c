#include <april/sys/io.h>
#include <april/error.h>

int april_fgetc(FILE *stream) {
    int data = getc(stream); 

    if (data == EOF && ferror(stream)) {
        april_handle_error("fgetc error");
    }

    return data;
}

void april_ungetc(int c, FILE *stream) {
    if (ungetc(c, stream) == EOF) {
        april_handle_error("ungetc error");
    }
}

char *april_fgets(char *buffer, int buffer_size, FILE *stream) {
    char *data = fgets(buffer, buffer_size, stream);

    if (data == NULL && ferror(stream)) {
        april_handle_error("fgets error");
    }
    
    return data;
}


size_t april_fread(void *buffer, size_t element_size, size_t num_elements, FILE *stream) {
    size_t num_elements_read = fread(buffer, element_size, num_elements, stream);

    if (num_elements_read < num_elements && ferror(stream)) {
        april_handle_unix_error("fread error");
    }
}

void april_fwrite(const void *buffer, size_t element_size, size_t num_elements, 
        FILE *stream) {
    if (fwrite(buffer, element_size, num_elements, stream)) {
        april_handle_unix_error("fwrite error");
    }
}

#include <april/error.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void april_handle_error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

void april_handle_unix_error(char *message) {
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(EXIT_FAILURE);
}

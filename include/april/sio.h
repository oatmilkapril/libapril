#ifndef LIBAPRIL_SIO_H
#define LIBAPRIL_SIO_H

#include <sys/types.h>

ssize_t april_sio_puts(const char *s);

ssize_t april_sio_putl(long v);

void april_sio_handle_error(char *s);

#endif // LIBAPRIL_SIO_H

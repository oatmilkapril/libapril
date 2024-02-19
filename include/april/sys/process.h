#ifndef LIBAPRIL_SYS_H
#define LIBAPRIL_SYS_H

#include <sys/types.h>

pid_t april_fork(void);
void april_execve(const char *filename, char *const argv[], char *const envp[]);

pid_t april_waitpid(pid_t pid, int *status_code, int options);
pid_t april_wait(int *status);

unsigned int april_sleep(unsigned int duration_seconds);
void april_pause();

void april_setpgid(pid_t pid, pid_t pgid);
pid_t april_getpgrp();

char *april_getenv(const char *name);
void april_setenv(const char *name, const char *value, int overwrite);
void april_unsetenv(const char *name);

#endif // LIBAPRIL_SYS_H

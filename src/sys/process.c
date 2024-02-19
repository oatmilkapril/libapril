#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "april/sys/process.h"
#include "april/error.h"

pid_t april_fork() {
    pid_t pid = fork();

    if (pid < 0) {
        april_handle_unix_error("fork error");
    }

    return pid;
}

void april_execve(const char *filename, char *const argv[], char *const envp[]) {
    if (execve(filename, argv, envp) < 0) {
        april_handle_unix_error("execve error");
    }
}

pid_t april_waitpid(pid_t pid, int *status_code, int options) {
    pid_t retpid = waitpid(pid, status_code, options);

    if (retpid < 0) {
        april_handle_unix_error("waitpid error");
    }

    return retpid;
}

pid_t april_wait(int *status) {
    pid_t pid = wait(status);

    if (pid < 0) {
        april_handle_unix_error("wait error");
    }

    return pid;
}

unsigned int april_sleep(unsigned int duration_secs) {
    unsigned int return_code = sleep(duration_secs);

    if (return_code < 0) {
        april_handle_unix_error("sleep error");
    }

    return return_code;
}

void april_pause() {
    pause();
}

void april_setpgid(pid_t pid, pid_t group_id) {
    int return_code = setpgid(pid, group_id);

    if (return_code < 0) {
        april_handle_unix_error("setpgid error");
    } 

    return;
}

pid_t april_getpgrp() {
    return getpgrp();
}

char *april_getenv(const char *name) {
    return getenv(name);
}

void april_setenv(const char *name, const char *value, int overwrite) {
    if (setenv(name, value, overwrite) != 0) {
        april_handle_unix_error("setenv error");
    }
}

void april_unsetenv(const char *name) {
    if (unsetenv(name) != 0) {
        april_handle_unix_error("unsetenv error");
    }
}

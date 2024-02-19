#ifndef LIBAPRIL_SIGNAL_H
#define LIBAPRIL_SIGNAL_H

#include <signal.h>
#include <stdbool.h>

typedef void (*april_sig_handler)(int signum);

typedef enum {
    APRIL_SIGHOW_BLOCK = SIG_BLOCK,
    APRIL_SIGHOW_UNBLOCK = SIG_UNBLOCK,
    APRIL_SIGHOW_SETMASK = SIG_SETMASK
} april_sighow;

void april_kill(pid_t pid, int signum);

unsigned int april_alarm(unsigned int delay_secs);

april_sig_handler april_signal(int signum, april_sig_handler handler);

void april_sigprocmask(april_sighow how, const sigset_t *set, sigset_t *oldset);

void april_sigemptyset(sigset_t *set);

void april_sigfillset(sigset_t *set);

void april_sigaddset(sigset_t *set, int signum);

void april_sigdelset(sigset_t *set, int signum);

bool april_sigismember(const sigset_t *set, int signum);

int april_sigsuspend(const sigset_t *set);

#endif // LIBAPRIL_SIGNAL_H

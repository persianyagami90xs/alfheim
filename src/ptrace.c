#include "ptrace.h"
#include "common.h"

#include <sys/ptrace.h>
#include <sys/wait.h>

void ptrace_attach(pid_t pid){
    int status;

    if(ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1){
        bad("failed to attach pid %d | %s\n", pid, strerror(errno));
        exit(1);
    }

    waitpid(pid, &status, 0);
}

long ptrace_getreg(pid_t pid, int reg){
    return ptrace(PTRACE_PEEKUSER, pid, sizeof(long)*reg, 0L);
}

long ptrace_setreg(pid_t pid, int reg, long ip){
    return ptrace(PTRACE_POKEUSER, pid, sizeof(long)*reg, ip);
}

long ptrace_getregs(pid_t pid, void *regs){
    return ptrace(PTRACE_GETREGS, pid, NULL, regs);
}

long ptrace_setregs(pid_t pid, const void *regs){
    return ptrace(PTRACE_SETREGS, pid, NULL, regs);
}

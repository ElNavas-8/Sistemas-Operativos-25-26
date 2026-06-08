#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = syscall(SYS_getpid);
    printf("Llamada a getpid() usando syscall: %ld\n", pid);
    printf("Llamada a getpid() usando getpid(): %d\n", getpid());
    printf("Llamada a getppid() usando syscall: %ld\n", (int) syscall(30));

    return 0;
}
#include "kernel/types.h"
#include "user/user.h"

void burn_cpu(int pid, const char *prio_name) {
    int count = 200000000;

    printf("Process %d (%s) Started\n", pid, prio_name);
    int i;
    
    for (i = 0; i < count; i++) {
        // Waste CPU cycles
    }

    printf("Process %d (%s) FINISHED\n", pid, prio_name);
    exit(0);
}

int main(int argc, char *argv[]) {
    int pid;
    int i;


    for (i = 0; i < 4; i++) {
        pid = fork();
        
        if (pid == 0) {

            int my_pid = getpid();

            if (my_pid % 2 != 0) {
                burn_cpu(my_pid, "HIGH");
            } else {
                burn_cpu(my_pid, "LOW");
            }
        }
    }


    for (i = 0; i < 4; i++) {
        wait(0);
    }

    exit(0);
}

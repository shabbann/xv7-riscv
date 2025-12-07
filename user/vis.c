#include "kernel/types.h"
#include "user/user.h"

void burn_cpu(int count) {
    volatile int i;
    for(i=0; i < count * 1000000; i++) {}
}

void child_task(int p_in, int p_out, int burst, char *name) {
    char b = 'R';
    int pid = getpid();

    // 1. TRAINING: Run to establish history
    burn_cpu(burst);

    // 2. SIGNAL: Tell parent "I am done training"
    write(p_out, &b, 1);

    // 3. WAIT: Sleep until Parent says "GO"
    // (This forces sched() -> calculates avg_burst)
    read(p_in, &b, 1);

    // 4. RACE: We woke up!
    printf("%s (PID %d) Woke up! Executing...\n", name, pid);
    burn_cpu(10); 
    printf("%s (PID %d) FINISHED\n", name, pid);
    exit(0);
}

int main() {
    int to_child[2];   // Parent writes, Child reads
    int to_parent[2];  // Child writes, Parent reads
    char buf;

    pipe(to_child);
    pipe(to_parent);

    printf("--- SJF HANDSHAKE TEST ---\n");

    // Create LONG Job 
    if(fork() == 0) {
        child_task(to_child[0], to_parent[1], 500, "LONG");
    }

    // Create SHORT Job
    if(fork() == 0) {
        child_task(to_child[0], to_parent[1], 50, "SHORT");
    }

    // PARENT: Sleep until we receive 2 "Ready" signals
    // This forces the Parent to stop hogging the CPU!
    printf("PARENT: Waiting for children to train...\n");
    read(to_parent[0], &buf, 1); // Wait for Child 1
    read(to_parent[0], &buf, 1); // Wait for Child 2

    printf("PARENT: Children are ready (and sleeping). Waking them up!\n");
    
    // WAKE THEM UP
    write(to_child[1], "GO", 2);

    wait(0);
    wait(0);
    exit(0);
}

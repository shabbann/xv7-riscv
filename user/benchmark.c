#include "kernel/types.h"
#include "user.h"
void delay(int count) {
  volatile int i;
  for (i = 0; i < count * 1000000; i++) {
     // waste time
  }
}
int main() {
    int i, pid;
    int k;
    int num_procs = 10;
    
    printf("--- STARTING BENCHMARK (%d processes) ---\n", num_procs);

    for (i = 0; i < num_procs; i++) {
        pid = fork();
        if (pid == 0) {
            // Child: Do heavy useless work
            // Using volatile to prevent compiler optimization
            volatile int x = 0; 
            for (k = 0; k < 100000000; k++) {
                x = x + 1;
                if (k % 100000 == 0) {
                   // Every now and then, yield to simulate I/O or just pause
                   // allowing the scheduler to make a decision
                   delay(1); 
                }
            }
            exit(0);
        }
    }

    // Parent waits for everyone
    for (i = 0; i < num_procs; i++) {
        wait(0);
    }
    
    printf("--- BENCHMARK FINISHED ---\n");
    exit(0);
}


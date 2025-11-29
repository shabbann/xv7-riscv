#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid;
  volatile int i; // <--- "volatile" prevents optimization
  
  pid = fork();
  
  if(pid == 0){
    // Child
    for(i = 0; i < 100000000; i++){} // This will now actually run
    printf("Child Finished\n");
  } else {
    // Parent
    for(i = 0; i < 100000000; i++){} // This will now actually run
    printf("Parent Finished\n");
    wait(0);
  }
  exit(0);
}

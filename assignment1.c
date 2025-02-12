#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    pid_t child_pid, grandchild_pid;

    printf("Original process with PID %d and PPID %d\n", getpid(),getppid());

    child_pid = fork();
    if(child_pid < 0){
        perror("fork failed");
        exit(1);
    }
    if(child_pid == 0){
        printf("Child process with PID %d and PPID %d\n", getpid(),getppid());
        grandchild_pid = fork();
        if(grandchild_pid < 0){
            perror("fork failed");
            exit(1);
        }
        if(grandchild_pid == 0){
            sleep(1);
            printf("Grandchild process with PID %d and PPID %d\n", getpid(),getppid());
            printf("Grandchild is about to exit\n");
            exit(0);
        }else{
            wait(NULL);
            printf("Child process with PID %d and PPID %d\n", getpid(), getppid());
            printf("Child is about to exit\n");
            exit(0);
        }
    }else{
        sleep(1);
        printf("Parent process with PID %d and PPID %d\n", getpid(), getppid());
        wait(NULL);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

// AIM: make child process print before parent process without using wait

int main(int argc, char* argv []){
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0){
        printf("(pid:%d): hello\n", getpid());
    } else {
        usleep(1000); // sleep for 1ms
        printf("(pid:%d): goodbye\n", getpid());
    }
    return 0;
}
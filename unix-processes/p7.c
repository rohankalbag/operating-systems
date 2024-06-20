#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv []){
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0){
        close(STDOUT_FILENO);
        printf("(pid:%d): I'm the child\n", getpid()); // this will not be printed
    } else {
        int rc_wait = wait(NULL);
        printf("(pid:%d): I'm the parent\n", getpid());
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv []){
    close(STDOUT_FILENO);
    open("./p2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    printf("(pid:%d): I'm the parent\n", getpid());
    fflush(0);
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0){
        printf("(pid:%d): Hello World\n", getpid());
    } else {
        int rc_wait = wait(NULL);
        printf("(pid:%d): Hello World\n", getpid());
    }
    return 0;
}
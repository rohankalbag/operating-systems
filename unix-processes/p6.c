#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv []){
    printf("(pid:%d): hello there, running ls now\n", getpid());
    fflush(0);
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0){
        char * path = "/bin/ls";
        char * flags = "-al";
        execl(path, flags, NULL);
        printf("this should not be seen\n");
    } else {
        printf("(pid:%d): waiting for child (pid:%d) to complete execution\n", getpid(), rc);
        int status;
        int rc_wait = waitpid(rc, &status, 0);
        printf("(pid:%d): (child pid:%d exited with status %d) goodbye, done running ls\n", getpid(), rc_wait, status);
    }
    return 0;
}
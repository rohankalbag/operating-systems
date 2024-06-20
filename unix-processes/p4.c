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
        int rc_wait = wait(NULL);
        printf("(pid:%d): (rc_wait: %d) goodbye, done running ls\n", getpid(), rc_wait);
    }
    return 0;
}
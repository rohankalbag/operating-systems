#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv []){
    int rc = fork();
    int x = 10;
    printf("(pid:%d) x is %d\n", getpid(), x);
    x += 5;
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0){
        printf("(pid:%d) x is %d\n", getpid(), x);
        x += 5;
    } else {
        int rc_wait = wait(NULL);
        printf("(pid:%d) x is %d\n", getpid(),  x);
    }
    return 0;
}
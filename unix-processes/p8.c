#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    int pipe_file_descriptors[2];
    pipe(pipe_file_descriptors);
    
    int c1 = fork();
    
    if (c1 < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    if(c1 == 0){
        close(pipe_file_descriptors[0]); // read end
        printf("sending: hello\n");
        dup2(pipe_file_descriptors[1], STDOUT_FILENO); // write end to stdout
        printf("hello\n");
        close(pipe_file_descriptors[1]); // write end
        exit(0);
    }

    int c2 = fork();

    if (c2 < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    if(c2 == 0){
        close(pipe_file_descriptors[1]); // write end
        dup2(pipe_file_descriptors[0], STDIN_FILENO); // read end to stdin
        char buffer[6];
        read(STDIN_FILENO, buffer, 5);
        buffer[5] = '\0';
        printf("received: %s\n", buffer);
        close(pipe_file_descriptors[0]); // read end
        exit(0);
    }

    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
    return 0;

}
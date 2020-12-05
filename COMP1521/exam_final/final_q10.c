#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MAX_LINE 65536

int main (int argc, char **argv) {

    char file[MAX_LINE] = {0};
    char *commands[MAX_LINE];
    //Attach commands from argv
    commands[0] = argv[1];
    int i = 1;
    while (i < argc) {
        commands[i] = argv[i];
        i +=1;
    }
    commands[i] = NULL;

    while (scanf("%s", file) != EOF) {
        commands[i] = file;

        pid_t pid;
        extern char **environ;
        posix_spawnp(&pid, argv[1], NULL, NULL, commands, environ);

        int status;
        waitpid(pid, &status, 0);

    }
    return 0;
}

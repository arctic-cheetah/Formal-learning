#include <stdio.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

#define BUFSIZE 0xFFFF

int main(void) {

    // create a pipe for the child
    int pipe_file_descriptors[2];
    if (pipe(pipe_file_descriptors) == -1) {
        perror("pipe");
        return 1;
    }

    // create a list of file actions to be carried out on spawned process
    posix_spawn_file_actions_t actions;
    if (posix_spawn_file_actions_init(&actions) != 0) {
        perror("posix_spawn_file_actions_init");
        return 1;
    }

    // tell spawned process to close unused write end of pipe
    // without this - spawned process will not receive EOF
    // when write end of the pipe is closed below,
    // because spawned process also has the write-end open
    // deadlock will result
    
    if (posix_spawn_file_actions_addclose(&actions, pipe_file_descriptors[1]) != 0) {
        perror("posix_spawn_file_actions_init");
        return 1;
    }
    

    // tell spawned process to replace file descriptor 0 (stdin)
    // with read end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, pipe_file_descriptors[0], 0) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        return 1;
    }


    // create a process running /usr/bin/xz
    char *xz[] = {"xz", "-dc", NULL};
    pid_t pid;
    extern char **environ;
    if (posix_spawn(&pid, "/usr/bin/xz", &actions, NULL, xz, environ) != 0) {
        perror("spawn");
        return 1;
    }



    // close unused read end of pipe
    close(pipe_file_descriptors[0]);

    //FILE *f0 = fdopen(pipe_file_descriptors[0], "r");
    // create a stdio stream from write-end of pipe
    FILE *f1 = fdopen(pipe_file_descriptors[1], "w");
    if (!f1) {
        perror("fdopen");
        return 1;
    }

    //Need to read from parent pid

    // send some input to the /usr/bin/sort process
    fprintf(f1, " text_file.xz");
    fclose(f1);

    //Need to read output
    
    /*
    char line[256];
    if (fgets(line, sizeof(line), f0) == NULL) {
        perror("Line: ");
        return 1;
    }
    printf("Decompression: %s", line);
    */

    // close write-end of the pipe
    // without this sort will hang waiting for more input

    //fclose(f0);
    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    printf("/usr/bin/xz exit status was %d\n", exit_status);

    // free the list of file actions
    posix_spawn_file_actions_destroy(&actions);

    return 0;
}